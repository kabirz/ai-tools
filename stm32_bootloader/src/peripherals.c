#include "peripherals.h"

#include "stm32f4xx.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_utils.h"

static volatile uint32_t systick_ms = 0;

void Peripherals_Init(void)
{
    SystemCoreClockUpdate();

    LL_Init1msTick(SystemCoreClock);
    LL_SYSTICK_EnableIT();
    LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
}

void Peripherals_DeInit(void)
{
    SysTick->CTRL = 0;
    LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART3);
    LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_CAN1);
    LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
    LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
}

uint32_t Peripherals_GetTick(void)
{
    return systick_ms;
}

void Peripherals_Delay(uint32_t ms)
{
    uint32_t start = Peripherals_GetTick();
    while ((Peripherals_GetTick() - start) < ms)
    {
    }
}

void SysTick_Handler(void)
{
    systick_ms++;
}
