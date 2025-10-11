#include "bootloader.h"

#include "flash_driver.h"
#include "peripherals.h"
#include "protocol.h"
#include "transport.h"

#include "stm32f4xx.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_utils.h"

#define BOOT_HOLD_GPIO       GPIOA
#define BOOT_HOLD_PIN        LL_GPIO_PIN_0
#define BOOT_IDLE_TIMEOUT_MS 5000U

static volatile uint32_t last_activity_tick = 0;
static volatile bool jump_requested = false;

static void Bootloader_OnFrame(transport_id_t source, const protocol_frame_t *frame);
static bool ApplicationIsValid(void);

void Bootloader_Init(void)
{
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

    LL_GPIO_SetPinMode(BOOT_HOLD_GPIO, BOOT_HOLD_PIN, LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinPull(BOOT_HOLD_GPIO, BOOT_HOLD_PIN, LL_GPIO_PULL_UP);

    FlashDriver_Init();
    Protocol_Init();
    Transport_Init(Bootloader_OnFrame);
    last_activity_tick = Peripherals_GetTick();
}

void Bootloader_Run(void)
{
    if (!Bootloader_ShouldStayInBootloader() && ApplicationIsValid())
    {
        Bootloader_JumpToApplication();
    }

    while (1)
    {
        Transport_Poll();

        if (jump_requested && ApplicationIsValid())
        {
            Bootloader_JumpToApplication();
        }

        uint32_t now = Peripherals_GetTick();
        if ((now - last_activity_tick) > BOOT_IDLE_TIMEOUT_MS)
        {
            if (ApplicationIsValid())
            {
                Bootloader_JumpToApplication();
            }
            else
            {
                last_activity_tick = now;
            }
        }
    }
}

bool Bootloader_ShouldStayInBootloader(void)
{
    if (!ApplicationIsValid())
    {
        return true;
    }

    return (LL_GPIO_IsInputPinSet(BOOT_HOLD_GPIO, BOOT_HOLD_PIN) == 0);
}

void Bootloader_JumpToApplication(void)
{
    typedef void (*app_entry_t)(void);

    __disable_irq();

    Peripherals_DeInit();

    uint32_t app_sp = APP_FIRST_WORD;
    uint32_t app_reset = APP_RESET_VECTOR;

    SCB->VTOR = APP_FLASH_ORIGIN;
    __set_MSP(app_sp);

    app_entry_t app = (app_entry_t)app_reset;
    app();

    while (1)
    {
    }
}

static void Bootloader_OnFrame(transport_id_t source, const protocol_frame_t *frame)
{
    (void)source;
    last_activity_tick = Peripherals_GetTick();
    Protocol_OnFrame(source, frame);
}

static bool ApplicationIsValid(void)
{
    uint32_t app_sp = APP_FIRST_WORD;
    uint32_t app_reset = APP_RESET_VECTOR;

    if ((app_sp < 0x20000000UL) || (app_sp > (0x20000000UL + (128U * 1024U))))
    {
        return false;
    }

    if ((app_reset < APP_FLASH_ORIGIN) || (app_reset > (0x08000000UL + (1024U * 1024U))))
    {
        return false;
    }

    return true;
}

void Bootloader_RequestJump(void)
{
    jump_requested = true;
}
