#include "transport.h"

#include "stm32f4xx.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"

#include <stddef.h>
#include <string.h>

#define BOOT_CAN                 CAN1
#define BOOT_CAN_GPIO_PORT       GPIOB
#define BOOT_CAN_TX_PIN          LL_GPIO_PIN_9
#define BOOT_CAN_RX_PIN          LL_GPIO_PIN_8
#define BOOT_CAN_AF              LL_GPIO_AF_9
#define BOOT_CAN_RX_ID           0x321U
#define BOOT_CAN_TX_ID           0x322U

typedef enum
{
    CAN_STATE_PREAMBLE,
    CAN_STATE_CMD,
    CAN_STATE_LEN_L,
    CAN_STATE_LEN_H,
    CAN_STATE_ADDR_0,
    CAN_STATE_ADDR_1,
    CAN_STATE_ADDR_2,
    CAN_STATE_ADDR_3,
    CAN_STATE_PAYLOAD,
    CAN_STATE_CRC_0,
    CAN_STATE_CRC_1,
    CAN_STATE_CRC_2,
    CAN_STATE_CRC_3
} can_parser_state_t;

static transport_frame_cb_t can_callback = NULL;
static protocol_frame_t can_frame;
static can_parser_state_t can_state = CAN_STATE_PREAMBLE;
static uint16_t can_payload_received = 0;
static uint32_t can_crc_value = 0;

static void TransportCAN_ParseByte(uint8_t byte);
static void TransportCAN_Configure(void);

void TransportCAN_Init(transport_frame_cb_t callback)
{
    can_callback = callback;
    TransportCAN_Configure();
}

void TransportCAN_Poll(void)
{
    while ((BOOT_CAN->RF0R & CAN_RF0R_FMP0) != 0U)
    {
        uint32_t rir = BOOT_CAN->sFIFOMailBox[0].RIR;
        uint32_t std_id = (rir >> 21U) & 0x7FFU;

        if (std_id == BOOT_CAN_RX_ID)
        {
            uint8_t rdlc = (uint8_t)(BOOT_CAN->sFIFOMailBox[0].RDTR & CAN_RDT0R_DLC);
            uint32_t rdlr = BOOT_CAN->sFIFOMailBox[0].RDLR;
            uint32_t rdhr = BOOT_CAN->sFIFOMailBox[0].RDHR;

            uint8_t data[8];
            for (uint8_t i = 0; i < 4U; ++i)
            {
                data[i] = (uint8_t)((rdlr >> (8U * i)) & 0xFFU);
            }
            for (uint8_t i = 0; i < 4U; ++i)
            {
                data[i + 4U] = (uint8_t)((rdhr >> (8U * i)) & 0xFFU);
            }

            if (rdlc > 8U)
            {
                rdlc = 8U;
            }

            for (uint8_t i = 0; i < rdlc; ++i)
            {
                TransportCAN_ParseByte(data[i]);
            }
        }

        BOOT_CAN->RF0R |= CAN_RF0R_RFOM0;
    }
}

void TransportCAN_Send(const uint8_t *data, size_t length)
{
    if ((data == NULL) || (length == 0U))
    {
        return;
    }

    size_t offset = 0U;
    while (offset < length)
    {
        size_t chunk = (length - offset) > 8U ? 8U : (length - offset);

        while ((BOOT_CAN->TSR & CAN_TSR_TME0) == 0U)
        {
        }

        CAN_TxMailBox_TypeDef *mailbox = &BOOT_CAN->sTxMailBox[0];
        mailbox->TIR = 0;
        mailbox->TIR |= (BOOT_CAN_TX_ID << 21U);
        mailbox->TIR &= ~CAN_TI0R_RTR;
        mailbox->TIR &= ~CAN_TI0R_IDE;

        mailbox->TDTR = (uint32_t)chunk & 0xFU;

        uint32_t data_low = 0U;
        uint32_t data_high = 0U;

        for (size_t i = 0; i < chunk && i < 4U; ++i)
        {
            data_low |= ((uint32_t)data[offset + i] << (8U * i));
        }

        for (size_t i = 4U; i < chunk; ++i)
        {
            data_high |= ((uint32_t)data[offset + i] << (8U * (i - 4U)));
        }

        mailbox->TDLR = data_low;
        mailbox->TDHR = data_high;

        mailbox->TIR |= CAN_TI0R_TXRQ;

        offset += chunk;
    }
}

static void TransportCAN_ParseByte(uint8_t byte)
{
    switch (can_state)
    {
        case CAN_STATE_PREAMBLE:
            if (byte == PROTOCOL_PREAMBLE)
            {
                memset(&can_frame, 0, sizeof(can_frame));
                can_frame.preamble = byte;
                can_crc_value = 0U;
                can_state = CAN_STATE_CMD;
            }
            break;

        case CAN_STATE_CMD:
            can_frame.cmd = byte;
            can_state = CAN_STATE_LEN_L;
            break;

        case CAN_STATE_LEN_L:
            can_frame.length = (uint16_t)byte;
            can_state = CAN_STATE_LEN_H;
            break;

        case CAN_STATE_LEN_H:
            can_frame.length |= ((uint16_t)byte << 8U);
            if (can_frame.length > PROTOCOL_MAX_PAYLOAD)
            {
                can_state = CAN_STATE_PREAMBLE;
            }
            else
            {
                can_state = CAN_STATE_ADDR_0;
            }
            break;

        case CAN_STATE_ADDR_0:
        case CAN_STATE_ADDR_1:
        case CAN_STATE_ADDR_2:
        case CAN_STATE_ADDR_3:
        {
            uint8_t shift = (uint8_t)((can_state - CAN_STATE_ADDR_0) * 8U);
            can_frame.address |= ((uint32_t)byte << shift);
            if (can_state == CAN_STATE_ADDR_3)
            {
                can_payload_received = 0U;
                if (can_frame.length == 0U)
                {
                    can_crc_value = 0U;
                    can_state = CAN_STATE_CRC_0;
                }
                else
                {
                    can_state = CAN_STATE_PAYLOAD;
                }
            }
            else
            {
                can_state++;
            }
            break;
        }

        case CAN_STATE_PAYLOAD:
            can_frame.payload[can_payload_received++] = byte;
            if (can_payload_received >= can_frame.length)
            {
                can_crc_value = 0U;
                can_state = CAN_STATE_CRC_0;
            }
            break;

        case CAN_STATE_CRC_0:
        case CAN_STATE_CRC_1:
        case CAN_STATE_CRC_2:
        case CAN_STATE_CRC_3:
        {
            uint8_t shift = (uint8_t)((can_state - CAN_STATE_CRC_0) * 8U);
            can_crc_value |= ((uint32_t)byte << shift);
            if (can_state == CAN_STATE_CRC_3)
            {
                can_frame.crc = can_crc_value;
                can_crc_value = 0U;
                can_state = CAN_STATE_PREAMBLE;
                if (can_callback != NULL)
                {
                    can_callback(TRANSPORT_CAN, &can_frame);
                }
            }
            else
            {
                can_state++;
            }
            break;
        }

        default:
            can_state = CAN_STATE_PREAMBLE;
            can_crc_value = 0U;
            break;
    }
}

static void TransportCAN_Configure(void)
{
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_CAN1);

    LL_GPIO_SetPinMode(BOOT_CAN_GPIO_PORT, BOOT_CAN_TX_PIN, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinSpeed(BOOT_CAN_GPIO_PORT, BOOT_CAN_TX_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
    LL_GPIO_SetAFPin_8_15(BOOT_CAN_GPIO_PORT, BOOT_CAN_TX_PIN, BOOT_CAN_AF);
    LL_GPIO_SetPinOutputType(BOOT_CAN_GPIO_PORT, BOOT_CAN_TX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(BOOT_CAN_GPIO_PORT, BOOT_CAN_TX_PIN, LL_GPIO_PULL_UP);

    LL_GPIO_SetPinMode(BOOT_CAN_GPIO_PORT, BOOT_CAN_RX_PIN, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinSpeed(BOOT_CAN_GPIO_PORT, BOOT_CAN_RX_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
    LL_GPIO_SetAFPin_8_15(BOOT_CAN_GPIO_PORT, BOOT_CAN_RX_PIN, BOOT_CAN_AF);
    LL_GPIO_SetPinPull(BOOT_CAN_GPIO_PORT, BOOT_CAN_RX_PIN, LL_GPIO_PULL_UP);

    BOOT_CAN->MCR |= CAN_MCR_INRQ;
    while ((BOOT_CAN->MSR & CAN_MSR_INAK) == 0U)
    {
    }

    /* Bit rate 500 kbps assuming 42 MHz CAN clock: prescaler 6, BS1=13, BS2=2 */
    uint32_t sjw = 0U;  /* SJW = 1 - 1 */
    uint32_t bs1 = 12U; /* 13 - 1 */
    uint32_t bs2 = 1U;  /* 2 - 1 */
    uint32_t prescaler = 5U; /* 6 - 1 */

    BOOT_CAN->BTR = (sjw << 24U) | (bs2 << 20U) | (bs1 << 16U) | prescaler;

    /* Filter configuration: accept only BOOT_CAN_RX_ID */
    CAN1->FMR |= CAN_FMR_FINIT;
    CAN1->FM1R &= ~(1U << 0);
    CAN1->FS1R |= (1U << 0);
    CAN1->FFA1R &= ~(1U << 0);
    CAN1->sFilterRegister[0].FR1 = (BOOT_CAN_RX_ID << 21U);
    CAN1->sFilterRegister[0].FR2 = (0x7FFU << 21U);
    CAN1->FA1R |= (1U << 0);
    CAN1->FMR &= ~CAN_FMR_FINIT;

    BOOT_CAN->MCR &= ~CAN_MCR_INRQ;
    while ((BOOT_CAN->MSR & CAN_MSR_INAK) != 0U)
    {
    }
}
