#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <stdbool.h>
#include <stdint.h>

#define BOOT_FLASH_ORIGIN    0x08000000UL
#define BOOTLOADER_MAX_SIZE  (32UL * 1024UL)
#define APP_FLASH_ORIGIN     (BOOT_FLASH_ORIGIN + BOOTLOADER_MAX_SIZE)

#define APP_FIRST_WORD       (*(const uint32_t *)(APP_FLASH_ORIGIN))
#define APP_RESET_VECTOR     (*(const uint32_t *)(APP_FLASH_ORIGIN + 4U))

void Bootloader_Init(void);
void Bootloader_Run(void);
void Bootloader_JumpToApplication(void);
bool Bootloader_ShouldStayInBootloader(void);
void Bootloader_RequestJump(void);

#endif /* BOOTLOADER_H */
