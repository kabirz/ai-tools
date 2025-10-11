#include "crc32.h"

uint32_t CRC32_Compute(const uint8_t *data, size_t length)
{
    uint32_t crc = 0xFFFFFFFFUL;

    if (data == NULL)
    {
        return crc ^ 0xFFFFFFFFUL;
    }

    for (size_t i = 0; i < length; ++i)
    {
        crc ^= data[i];
        for (uint32_t bit = 0; bit < 8U; ++bit)
        {
            if (crc & 1U)
            {
                crc = (crc >> 1U) ^ 0xEDB88320UL;
            }
            else
            {
                crc >>= 1U;
            }
        }
    }

    return crc ^ 0xFFFFFFFFUL;
}
