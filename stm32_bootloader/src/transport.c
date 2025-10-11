#include "transport.h"

#include <stddef.h>

typedef void (*transport_driver_init_t)(transport_frame_cb_t);
typedef void (*transport_driver_poll_t)(void);
typedef void (*transport_driver_send_t)(const uint8_t *, size_t);

static transport_frame_cb_t upper_layer_callback = NULL;

static void Transport_Dispatch(transport_id_t source, const protocol_frame_t *frame);

void TransportUART_Init(transport_frame_cb_t callback);
void TransportUART_Poll(void);
void TransportUART_Send(const uint8_t *data, size_t length);

void TransportCAN_Init(transport_frame_cb_t callback);
void TransportCAN_Poll(void);
void TransportCAN_Send(const uint8_t *data, size_t length);

void Transport_Init(transport_frame_cb_t callback)
{
    upper_layer_callback = callback;
    TransportUART_Init(Transport_Dispatch);
    TransportCAN_Init(Transport_Dispatch);
}

void Transport_Poll(void)
{
    TransportUART_Poll();
    TransportCAN_Poll();
}

void Transport_Send(transport_id_t target, const uint8_t *data, size_t length)
{
    switch (target)
    {
        case TRANSPORT_UART:
            TransportUART_Send(data, length);
            break;
        case TRANSPORT_CAN:
            TransportCAN_Send(data, length);
            break;
        default:
            break;
    }
}

void Transport_Broadcast(const uint8_t *data, size_t length)
{
    TransportUART_Send(data, length);
    TransportCAN_Send(data, length);
}

static void Transport_Dispatch(transport_id_t source, const protocol_frame_t *frame)
{
    if (upper_layer_callback != NULL)
    {
        upper_layer_callback(source, frame);
    }
}
