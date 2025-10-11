#ifndef FLASH_DRIVER_H
#define FLASH_DRIVER_H

#include <stddef.h>
#include <stdint.h>

#define FLASH_PAGE_SIZE_BYTES  16384U /* 16 KiB sectors on STM32F407 up to sector 3 */

void FlashDriver_Init(void);
int FlashDriver_MassErase(uint32_t start_address, uint32_t length);
int FlashDriver_Write(uint32_t address, const uint8_t *data, size_t length);

#endif /* FLASH_DRIVER_H */
