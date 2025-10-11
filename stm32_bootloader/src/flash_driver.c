#include "flash_driver.h"

#include "stm32f4xx.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_flash.h"
#include "stm32f4xx_ll_pwr.h"

#include <stddef.h>
#include <string.h>

static int FlashDriver_WaitForLastOperation(void);
static int FlashDriver_GetSectorFromAddress(uint32_t address);

void FlashDriver_Init(void)
{
    LL_FLASH_Unlock();
    LL_FLASH_DisableDataCache();
    LL_FLASH_DisableInstructionCache();
    LL_FLASH_DisablePrefetch();
}

int FlashDriver_MassErase(uint32_t start_address, uint32_t length)
{
    if (length == 0U)
    {
        return 0;
    }

    uint32_t end_address = start_address + length;

    if (end_address <= start_address)
    {
        return -1;
    }

    for (uint32_t addr = start_address; addr < end_address; )
    {
        int sector = FlashDriver_GetSectorFromAddress(addr);
        if (sector < 0)
        {
            return -2;
        }

        if (FlashDriver_WaitForLastOperation() != 0)
        {
            return -3;
        }

        LL_FLASH_Erase_Sector((uint32_t)sector, LL_FLASH_VOLTAGE_RANGE_3);

        if (FlashDriver_WaitForLastOperation() != 0)
        {
            return -4;
        }

        switch (sector)
        {
            case LL_FLASH_SECTOR_0:
            case LL_FLASH_SECTOR_1:
            case LL_FLASH_SECTOR_2:
            case LL_FLASH_SECTOR_3:
                addr = (addr & ~0x3FFFU) + 0x4000U;
                break;
            case LL_FLASH_SECTOR_4:
                addr = (addr & ~0x0FFFFU) + 0x10000U;
                break;
            default:
                addr = (addr & ~0x1FFFFU) + 0x20000U;
                break;
        }
    }

    return 0;
}

int FlashDriver_Write(uint32_t address, const uint8_t *data, size_t length)
{
    if ((data == NULL) || (length == 0U))
    {
        return 0;
    }

    if ((address % 4U) != 0U)
    {
        return -1;
    }

    size_t offset = 0;
    while (offset < length)
    {
        uint32_t word = 0xFFFFFFFFUL;
        size_t remaining = length - offset;
        if (remaining >= 4U)
        {
            memcpy(&word, &data[offset], 4U);
        }
        else
        {
            memcpy(&word, &data[offset], remaining);
        }

        if (FlashDriver_WaitForLastOperation() != 0)
        {
            return -2;
        }

        LL_FLASH_Program(LL_FLASH_PROGRAM_WORD, address + offset, word);

        if (FlashDriver_WaitForLastOperation() != 0)
        {
            return -3;
        }

        if (*((volatile uint32_t *)(address + offset)) != word)
        {
            return -4;
        }

        offset += 4U;
    }

    return 0;
}

static int FlashDriver_GetSectorFromAddress(uint32_t address)
{
    if (address < 0x08004000U)
    {
        return LL_FLASH_SECTOR_0;
    }
    else if (address < 0x08008000U)
    {
        return LL_FLASH_SECTOR_1;
    }
    else if (address < 0x0800C000U)
    {
        return LL_FLASH_SECTOR_2;
    }
    else if (address < 0x08010000U)
    {
        return LL_FLASH_SECTOR_3;
    }
    else if (address < 0x08020000U)
    {
        return LL_FLASH_SECTOR_4;
    }
    else if (address < 0x08040000U)
    {
        return LL_FLASH_SECTOR_5;
    }
    else if (address < 0x08060000U)
    {
        return LL_FLASH_SECTOR_6;
    }
    else if (address < 0x08080000U)
    {
        return LL_FLASH_SECTOR_7;
    }

#ifdef LL_FLASH_SECTOR_8
    else if (address < 0x080A0000U)
    {
        return LL_FLASH_SECTOR_8;
    }
    else if (address < 0x080C0000U)
    {
        return LL_FLASH_SECTOR_9;
    }
    else if (address < 0x080E0000U)
    {
        return LL_FLASH_SECTOR_10;
    }
    else if (address < 0x08100000U)
    {
        return LL_FLASH_SECTOR_11;
    }
#endif

    return -1;
}

static int FlashDriver_WaitForLastOperation(void)
{
    while (LL_FLASH_IsActiveFlag_BSY())
    {
    }

    if (LL_FLASH_IsActiveFlag_OPERR() ||
        LL_FLASH_IsActiveFlag_WRPERR() ||
        LL_FLASH_IsActiveFlag_PGAERR() ||
        LL_FLASH_IsActiveFlag_PGPERR() ||
        LL_FLASH_IsActiveFlag_PGSERR())
    {
        LL_FLASH_ClearFlag_OPERR();
        LL_FLASH_ClearFlag_WRPERR();
        LL_FLASH_ClearFlag_PGAERR();
        LL_FLASH_ClearFlag_PGPERR();
        LL_FLASH_ClearFlag_PGSERR();
        return -1;
    }

    return 0;
}
