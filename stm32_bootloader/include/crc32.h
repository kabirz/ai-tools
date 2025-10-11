#ifndef CRC32_H
#define CRC32_H

#include <stddef.h>
#include <stdint.h>

uint32_t CRC32_Compute(const uint8_t *data, size_t length);

#endif /* CRC32_H */
