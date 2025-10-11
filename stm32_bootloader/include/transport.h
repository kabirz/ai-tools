#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <stddef.h>
#include <stdint.h>

#include "protocol.h"

typedef void (*transport_frame_cb_t)(transport_id_t source, const protocol_frame_t *frame);

void Transport_Init(transport_frame_cb_t callback);
void Transport_Poll(void);
void Transport_Send(transport_id_t target, const uint8_t *data, size_t length);
void Transport_Broadcast(const uint8_t *data, size_t length);

#endif /* TRANSPORT_H */
