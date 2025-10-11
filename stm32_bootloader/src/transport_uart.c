#include "transport.h"

#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_usart.h"

#include <stddef.h>
#include <string.h>

#define BOOT_USART                 USART3
#define BOOT_USART_GPIO_PORT       GPIOD
#define BOOT_USART_TX_PIN          LL_GPIO_PIN_8
#define BOOT_USART_RX_PIN          LL_GPIO_PIN_9
#define BOOT_USART_AF              LL_GPIO_AF_7
#define BOOT_USART_APB_HZ          42000000U
#define BOOT_USART_BAUDRATE        115200U

typedef enum
{
    UART_STATE_PREAMBLE,
    UART_STATE_CMD,
    UART_STATE_LEN_L,
    UART_STATE_LEN_H,
    UART_STATE_ADDR_0,
    UART_STATE_ADDR_1,
    UART_STATE_ADDR_2,
    UART_STATE_ADDR_3,
    UART_STATE_PAYLOAD,
    UART_STATE_CRC_0,
    UART_STATE_CRC_1,
    UART_STATE_CRC_2,
    UART_STATE_CRC_3
} uart_state_t;

static transport_frame_cb_t rx_callback = NULL;
static protocol_frame_t rx_frame;
static uart_state_t rx_state = UART_STATE_PREAMBLE;
static uint16_t rx_payload_received = 0;
static uint32_t rx_crc = 0;

static void TransportUART_ParseByte(uint8_t byte);

void TransportUART_Init(transport_frame_cb_t callback)
{
    rx_callback = callback;

    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);

    LL_GPIO_SetPinMode(BOOT_USART_GPIO_PORT, BOOT_USART_TX_PIN, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinSpeed(BOOT_USART_GPIO_PORT, BOOT_USART_TX_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
    LL_GPIO_SetAFPin_8_15(BOOT_USART_GPIO_PORT, BOOT_USART_TX_PIN, BOOT_USART_AF);
    LL_GPIO_SetPinPull(BOOT_USART_GPIO_PORT, BOOT_USART_TX_PIN, LL_GPIO_PULL_UP);
    LL_GPIO_SetPinOutputType(BOOT_USART_GPIO_PORT, BOOT_USART_TX_PIN, LL_GPIO_OUTPUT_PUSHPULL);

    LL_GPIO_SetPinMode(BOOT_USART_GPIO_PORT, BOOT_USART_RX_PIN, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinSpeed(BOOT_USART_GPIO_PORT, BOOT_USART_RX_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
    LL_GPIO_SetAFPin_8_15(BOOT_USART_GPIO_PORT, BOOT_USART_RX_PIN, BOOT_USART_AF);
    LL_GPIO_SetPinPull(BOOT_USART_GPIO_PORT, BOOT_USART_RX_PIN, LL_GPIO_PULL_UP);
    LL_GPIO_SetPinOutputType(BOOT_USART_GPIO_PORT, BOOT_USART_RX_PIN, LL_GPIO_OUTPUT_PUSHPULL);

    LL_USART_Disable(BOOT_USART);
    LL_USART_SetTransferDirection(BOOT_USART, LL_USART_DIRECTION_TX_RX);
    LL_USART_ConfigAsyncMode(BOOT_USART);
    LL_USART_SetDataWidth(BOOT_USART, LL_USART_DATAWIDTH_8B);
    LL_USART_SetParity(BOOT_USART, LL_USART_PARITY_NONE);
    LL_USART_SetStopBitsLength(BOOT_USART, LL_USART_STOPBITS_1);
    LL_USART_SetHWFlowCtrl(BOOT_USART, LL_USART_HWCONTROL_NONE);
    LL_USART_SetBaudRate(BOOT_USART, BOOT_USART_APB_HZ, LL_USART_OVERSAMPLING_16, BOOT_USART_BAUDRATE);
    LL_USART_Enable(BOOT_USART);
}

void TransportUART_Poll(void)
{
    while (LL_USART_IsActiveFlag_RXNE(BOOT_USART))
    {
        uint8_t byte = LL_USART_ReceiveData8(BOOT_USART);
        TransportUART_ParseByte(byte);
    }
}

void TransportUART_Send(const uint8_t *data, size_t length)
{
    if ((data == NULL) || (length == 0U))
    {
        return;
    }

    for (size_t i = 0; i < length; ++i)
    {
        while (!LL_USART_IsActiveFlag_TXE(BOOT_USART))
        {
        }
        LL_USART_TransmitData8(BOOT_USART, data[i]);
    }

    while (!LL_USART_IsActiveFlag_TC(BOOT_USART))
    {
    }
}

static void TransportUART_ParseByte(uint8_t byte)
{
    switch (rx_state)
    {
        case UART_STATE_PREAMBLE:
            if (byte == PROTOCOL_PREAMBLE)
            {
                memset(&rx_frame, 0, sizeof(rx_frame));
                rx_frame.preamble = byte;
                rx_state = UART_STATE_CMD;
            }
            break;

        case UART_STATE_CMD:
            rx_frame.cmd = byte;
            rx_state = UART_STATE_LEN_L;
            break;

        case UART_STATE_LEN_L:
            rx_frame.length = (uint16_t)byte;
            rx_state = UART_STATE_LEN_H;
            break;

        case UART_STATE_LEN_H:
            rx_frame.length |= ((uint16_t)byte << 8U);
            if (rx_frame.length > PROTOCOL_MAX_PAYLOAD)
            {
                rx_state = UART_STATE_PREAMBLE;
            }
            else
            {
                rx_state = UART_STATE_ADDR_0;
            }
            break;

        case UART_STATE_ADDR_0:
        case UART_STATE_ADDR_1:
        case UART_STATE_ADDR_2:
        case UART_STATE_ADDR_3:
        {
            uint8_t shift = (uint8_t)((rx_state - UART_STATE_ADDR_0) * 8U);
            rx_frame.address |= ((uint32_t)byte << shift);
            if (rx_state == UART_STATE_ADDR_3)
            {
                rx_payload_received = 0U;
                if (rx_frame.length == 0U)
                {
                    rx_state = UART_STATE_CRC_0;
                    rx_crc = 0U;
                }
                else
                {
                    rx_state = UART_STATE_PAYLOAD;
                }
            }
            else
            {
                rx_state++;
            }
            break;
        }

        case UART_STATE_PAYLOAD:
            rx_frame.payload[rx_payload_received++] = byte;
            if (rx_payload_received >= rx_frame.length)
            {
                rx_state = UART_STATE_CRC_0;
                rx_crc = 0U;
            }
            break;

        case UART_STATE_CRC_0:
        case UART_STATE_CRC_1:
        case UART_STATE_CRC_2:
        case UART_STATE_CRC_3:
        {
            uint8_t shift = (uint8_t)((rx_state - UART_STATE_CRC_0) * 8U);
            rx_crc |= ((uint32_t)byte << shift);
            if (rx_state == UART_STATE_CRC_3)
            {
                rx_frame.crc = rx_crc;
                rx_crc = 0U;
                uart_state_t prev_state = rx_state;
                rx_state = UART_STATE_PREAMBLE;
                if (rx_callback != NULL && prev_state == UART_STATE_CRC_3)
                {
                    rx_callback(TRANSPORT_UART, &rx_frame);
                }
            }
            else
            {
                rx_state++;
            }
            break;
        }

        default:
            rx_state = UART_STATE_PREAMBLE;
            rx_crc = 0U;
            break;
    }
}
