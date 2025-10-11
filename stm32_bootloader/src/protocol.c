#include "protocol.h"

#include "bootloader.h"
#include "crc32.h"
#include "flash_driver.h"
#include "transport.h"

#include <stddef.h>
#include <string.h>

#define STATUS_OK                 0U
#define STATUS_ERR_BAD_HEADER     1U
#define STATUS_ERR_LENGTH         2U
#define STATUS_ERR_RANGE          3U
#define STATUS_ERR_FLASH          4U
#define STATUS_ERR_CRC_MISMATCH   5U
#define STATUS_ERR_UNSUPPORTED    6U

typedef struct __attribute__((packed))
{
    uint32_t bootloader_version;
    uint32_t application_start;
    uint32_t max_image_size;
    uint32_t transport_mask;
} bootloader_info_t;

static uint32_t Protocol_CheckRange(uint32_t address, uint32_t length);
static void Protocol_SendStatus(transport_id_t target, protocol_cmd_t cmd, uint32_t status, const uint8_t *payload, uint16_t length);

void Protocol_Init(void)
{
}

void Protocol_ResetTimeout(void)
{
}

void Protocol_OnFrame(transport_id_t source, const protocol_frame_t *frame)
{
    if ((frame == NULL) || (frame->preamble != PROTOCOL_PREAMBLE))
    {
        Protocol_SendStatus(source, frame ? frame->cmd : PROTOCOL_CMD_PING, STATUS_ERR_BAD_HEADER, NULL, 0);
        return;
    }

    if (frame->length > PROTOCOL_MAX_PAYLOAD)
    {
        Protocol_SendStatus(source, frame->cmd, STATUS_ERR_LENGTH, NULL, 0);
        return;
    }

    uint32_t crc = CRC32_Compute(frame->payload, frame->length);
    if (crc != frame->crc)
    {
        Protocol_SendStatus(source, frame->cmd, STATUS_ERR_CRC_MISMATCH, NULL, 0);
        return;
    }

    switch (frame->cmd)
    {
        case PROTOCOL_CMD_PING:
        {
            static const uint8_t pong[] = { 'P', 'O', 'N', 'G' };
            Protocol_SendStatus(source, frame->cmd, STATUS_OK, pong, sizeof(pong));
            break;
        }
        case PROTOCOL_CMD_INFO:
        {
            bootloader_info_t info = {
                .bootloader_version = 0x00010000UL,
                .application_start = APP_FLASH_ORIGIN,
                .max_image_size = (0x08100000UL - APP_FLASH_ORIGIN),
                .transport_mask = (1UL << TRANSPORT_UART) | (1UL << TRANSPORT_CAN)
            };
            Protocol_SendStatus(source, frame->cmd, STATUS_OK, (const uint8_t *)&info, sizeof(info));
            break;
        }
        case PROTOCOL_CMD_ERASE:
        {
            if (frame->length < 4U)
            {
                Protocol_SendStatus(source, frame->cmd, STATUS_ERR_LENGTH, NULL, 0);
                break;
            }

            uint32_t length = ((const uint32_t *)frame->payload)[0];

            if (Protocol_CheckRange(frame->address, length) != STATUS_OK)
            {
                Protocol_SendStatus(source, frame->cmd, STATUS_ERR_RANGE, NULL, 0);
                break;
            }

            int status = FlashDriver_MassErase(frame->address, length);
            Protocol_SendStatus(source, frame->cmd, (status == 0) ? STATUS_OK : STATUS_ERR_FLASH, NULL, 0);
            break;
        }
        case PROTOCOL_CMD_WRITE:
        {
            if (Protocol_CheckRange(frame->address, frame->length) != STATUS_OK)
            {
                Protocol_SendStatus(source, frame->cmd, STATUS_ERR_RANGE, NULL, 0);
                break;
            }

            int status = FlashDriver_Write(frame->address, frame->payload, frame->length);
            Protocol_SendStatus(source, frame->cmd, (status == 0) ? STATUS_OK : STATUS_ERR_FLASH, NULL, 0);
            break;
        }
        case PROTOCOL_CMD_VERIFY:
        {
            if (frame->length < 8U)
            {
                Protocol_SendStatus(source, frame->cmd, STATUS_ERR_LENGTH, NULL, 0);
                break;
            }

            uint32_t length = ((const uint32_t *)frame->payload)[0];
            uint32_t expected_crc = ((const uint32_t *)frame->payload)[1];

            if (Protocol_CheckRange(frame->address, length) != STATUS_OK)
            {
                Protocol_SendStatus(source, frame->cmd, STATUS_ERR_RANGE, NULL, 0);
                break;
            }

            uint32_t computed = CRC32_Compute((const uint8_t *)frame->address, length);
            uint32_t status = (computed == expected_crc) ? STATUS_OK : STATUS_ERR_CRC_MISMATCH;
            Protocol_SendStatus(source, frame->cmd, status, (const uint8_t *)&computed, sizeof(computed));
            break;
        }
        case PROTOCOL_CMD_EXECUTE:
        {
            Protocol_SendStatus(source, frame->cmd, STATUS_OK, NULL, 0);
            Bootloader_RequestJump();
            break;
        }
        case PROTOCOL_CMD_RESET:
        {
            Protocol_SendStatus(source, frame->cmd, STATUS_OK, NULL, 0);
            NVIC_SystemReset();
            break;
        }
        default:
            Protocol_SendStatus(source, frame->cmd, STATUS_ERR_UNSUPPORTED, NULL, 0);
            break;
    }
}

static uint32_t Protocol_CheckRange(uint32_t address, uint32_t length)
{
    if (length == 0U)
    {
        return STATUS_ERR_LENGTH;
    }

    if (address < APP_FLASH_ORIGIN)
    {
        return STATUS_ERR_RANGE;
    }

    uint32_t end_address = address + length;

    if ((end_address < address) || (end_address > 0x08100000UL))
    {
        return STATUS_ERR_RANGE;
    }

    return STATUS_OK;
}

static void Protocol_SendStatus(transport_id_t target, protocol_cmd_t cmd, uint32_t status, const uint8_t *payload, uint16_t length)
{
    if ((payload == NULL) && (length != 0U))
    {
        length = 0U;
    }

    if (length > PROTOCOL_MAX_PAYLOAD)
    {
        length = PROTOCOL_MAX_PAYLOAD;
    }

    uint8_t frame_buffer[sizeof(protocol_frame_t)] = {0};
    size_t offset = 0U;

    frame_buffer[offset++] = PROTOCOL_PREAMBLE;
    frame_buffer[offset++] = (uint8_t)cmd;

    frame_buffer[offset++] = (uint8_t)(length & 0xFFU);
    frame_buffer[offset++] = (uint8_t)((length >> 8U) & 0xFFU);

    frame_buffer[offset++] = (uint8_t)(status & 0xFFU);
    frame_buffer[offset++] = (uint8_t)((status >> 8U) & 0xFFU);
    frame_buffer[offset++] = (uint8_t)((status >> 16U) & 0xFFU);
    frame_buffer[offset++] = (uint8_t)((status >> 24U) & 0xFFU);

    if ((payload != NULL) && (length > 0U))
    {
        memcpy(&frame_buffer[offset], payload, length);
    }
    offset += length;

    uint32_t crc = CRC32_Compute(payload, length);
    frame_buffer[offset++] = (uint8_t)(crc & 0xFFU);
    frame_buffer[offset++] = (uint8_t)((crc >> 8U) & 0xFFU);
    frame_buffer[offset++] = (uint8_t)((crc >> 16U) & 0xFFU);
    frame_buffer[offset++] = (uint8_t)((crc >> 24U) & 0xFFU);

    Transport_Send(target, frame_buffer, offset);
}
