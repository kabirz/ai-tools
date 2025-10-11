#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stddef.h>
#include <stdint.h>

#define PROTOCOL_MAX_PAYLOAD 256U
#define PROTOCOL_PREAMBLE    0x55U

typedef enum
{
    TRANSPORT_UART = 0,
    TRANSPORT_CAN  = 1
} transport_id_t;

typedef enum
{
    PROTOCOL_CMD_PING    = 0x01,
    PROTOCOL_CMD_INFO    = 0x02,
    PROTOCOL_CMD_ERASE   = 0x03,
    PROTOCOL_CMD_WRITE   = 0x04,
    PROTOCOL_CMD_VERIFY  = 0x05,
    PROTOCOL_CMD_EXECUTE = 0x06,
    PROTOCOL_CMD_RESET   = 0x07
} protocol_cmd_t;

typedef struct
{
    uint8_t preamble;
    uint8_t cmd;
    uint16_t length;
    uint32_t address;
    uint32_t crc;
    uint8_t payload[PROTOCOL_MAX_PAYLOAD];
} protocol_frame_t;

void Protocol_Init(void);
void Protocol_ResetTimeout(void);
void Protocol_OnFrame(transport_id_t source, const protocol_frame_t *frame);

#endif /* PROTOCOL_H */
