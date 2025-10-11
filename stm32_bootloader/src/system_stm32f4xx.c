#include "stm32f4xx.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_flash.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_rcc.h"

uint32_t SystemCoreClock = 168000000UL;

static void SystemClock_Config(void);

void SystemInit(void)
{
    SCB->VTOR = FLASH_BASE;
    SCB->CPACR |= ((3UL << 20U) | (3UL << 22U));

    /* Reset clock configuration */
    LL_RCC_DeInit();

    SystemClock_Config();

    /* Update CMSIS clock variable */
    SystemCoreClockUpdate();
}

static void SystemClock_Config(void)
{
    /* Enable power control clock and configure voltage scaling */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
    LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);

    /* Configure Flash latency */
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);

    /* Enable HSE and wait */
    LL_RCC_HSE_Enable();
    while (LL_RCC_HSE_IsReady() != 1)
    {
    }

    /* Configure PLL: HSE 8MHz -> PLLN 336, PLLM 8, PLLP 2 => 168 MHz */
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_8, 336, LL_RCC_PLLP_DIV_2);
    LL_RCC_PLL_Enable();
    while (LL_RCC_PLL_IsReady() != 1)
    {
    }

    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
    {
    }

    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);

    SystemCoreClock = 168000000UL;
}

void SystemCoreClockUpdate(void)
{
    SystemCoreClock = 168000000UL;
}
