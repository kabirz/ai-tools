    .syntax unified
    .cpu cortex-m4
    .fpu fpv4-sp-d16
    .thumb

    .extern SystemInit
    .extern __libc_init_array
    .extern main

    .section .isr_vector,"a",%progbits
    .type g_pfnVectors, %object
    .size g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
    .word   _estack
    .word   Reset_Handler
    .word   NMI_Handler
    .word   HardFault_Handler
    .word   MemManage_Handler
    .word   BusFault_Handler
    .word   UsageFault_Handler
    .word   0
    .word   0
    .word   0
    .word   0
    .word   SVC_Handler
    .word   DebugMon_Handler
    .word   0
    .word   PendSV_Handler
    .word   SysTick_Handler

    /* External Interrupts */
    .word   WWDG_IRQHandler
    .word   PVD_IRQHandler
    .word   TAMP_STAMP_IRQHandler
    .word   RTC_WKUP_IRQHandler
    .word   FLASH_IRQHandler
    .word   RCC_IRQHandler
    .word   EXTI0_IRQHandler
    .word   EXTI1_IRQHandler
    .word   EXTI2_IRQHandler
    .word   EXTI3_IRQHandler
    .word   EXTI4_IRQHandler
    .word   DMA1_Stream0_IRQHandler
    .word   DMA1_Stream1_IRQHandler
    .word   DMA1_Stream2_IRQHandler
    .word   DMA1_Stream3_IRQHandler
    .word   DMA1_Stream4_IRQHandler
    .word   DMA1_Stream5_IRQHandler
    .word   DMA1_Stream6_IRQHandler
    .word   ADC_IRQHandler
    .word   CAN1_TX_IRQHandler
    .word   CAN1_RX0_IRQHandler
    .word   CAN1_RX1_IRQHandler
    .word   CAN1_SCE_IRQHandler
    .word   EXTI9_5_IRQHandler
    .word   TIM1_BRK_TIM9_IRQHandler
    .word   TIM1_UP_TIM10_IRQHandler
    .word   TIM1_TRG_COM_TIM11_IRQHandler
    .word   TIM1_CC_IRQHandler
    .word   TIM2_IRQHandler
    .word   TIM3_IRQHandler
    .word   TIM4_IRQHandler
    .word   I2C1_EV_IRQHandler
    .word   I2C1_ER_IRQHandler
    .word   I2C2_EV_IRQHandler
    .word   I2C2_ER_IRQHandler
    .word   SPI1_IRQHandler
    .word   SPI2_IRQHandler
    .word   USART1_IRQHandler
    .word   USART2_IRQHandler
    .word   USART3_IRQHandler
    .word   EXTI15_10_IRQHandler
    .word   RTC_Alarm_IRQHandler
    .word   OTG_FS_WKUP_IRQHandler
    .word   TIM8_BRK_TIM12_IRQHandler
    .word   TIM8_UP_TIM13_IRQHandler
    .word   TIM8_TRG_COM_TIM14_IRQHandler
    .word   TIM8_CC_IRQHandler
    .word   DMA1_Stream7_IRQHandler
    .word   FMC_IRQHandler
    .word   SDIO_IRQHandler
    .word   TIM5_IRQHandler
    .word   SPI3_IRQHandler
    .word   UART4_IRQHandler
    .word   UART5_IRQHandler
    .word   TIM6_DAC_IRQHandler
    .word   TIM7_IRQHandler
    .word   DMA2_Stream0_IRQHandler
    .word   DMA2_Stream1_IRQHandler
    .word   DMA2_Stream2_IRQHandler
    .word   DMA2_Stream3_IRQHandler
    .word   DMA2_Stream4_IRQHandler
    .word   ETH_IRQHandler
    .word   ETH_WKUP_IRQHandler
    .word   CAN2_TX_IRQHandler
    .word   CAN2_RX0_IRQHandler
    .word   CAN2_RX1_IRQHandler
    .word   CAN2_SCE_IRQHandler
    .word   OTG_FS_IRQHandler
    .word   DMA2_Stream5_IRQHandler
    .word   DMA2_Stream6_IRQHandler
    .word   DMA2_Stream7_IRQHandler
    .word   USART6_IRQHandler
    .word   I2C3_EV_IRQHandler
    .word   I2C3_ER_IRQHandler
    .word   OTG_HS_EP1_OUT_IRQHandler
    .word   OTG_HS_EP1_IN_IRQHandler
    .word   OTG_HS_WKUP_IRQHandler
    .word   OTG_HS_IRQHandler
    .word   DCMI_IRQHandler
    .word   CRYP_IRQHandler
    .word   HASH_RNG_IRQHandler
    .word   FPU_IRQHandler
    .word   0
    .word   0
    .word   SPI4_IRQHandler
    .word   SPI5_IRQHandler
    .word   0
    .word   0

    .thumb_set Default_Handler, Default_Handler

    .text
Reset_Handler:
    ldr   r0, =_estack
    mov   sp, r0

    bl    SystemInit
    bl    __libc_init_array
    bl    main
    b     .

    .weak  NMI_Handler
    .weak  HardFault_Handler
    .weak  MemManage_Handler
    .weak  BusFault_Handler
    .weak  UsageFault_Handler
    .weak  SVC_Handler
    .weak  DebugMon_Handler
    .weak  PendSV_Handler
    .weak  SysTick_Handler

    .weak  WWDG_IRQHandler
    .weak  PVD_IRQHandler
    .weak  TAMP_STAMP_IRQHandler
    .weak  RTC_WKUP_IRQHandler
    .weak  FLASH_IRQHandler
    .weak  RCC_IRQHandler
    .weak  EXTI0_IRQHandler
    .weak  EXTI1_IRQHandler
    .weak  EXTI2_IRQHandler
    .weak  EXTI3_IRQHandler
    .weak  EXTI4_IRQHandler
    .weak  DMA1_Stream0_IRQHandler
    .weak  DMA1_Stream1_IRQHandler
    .weak  DMA1_Stream2_IRQHandler
    .weak  DMA1_Stream3_IRQHandler
    .weak  DMA1_Stream4_IRQHandler
    .weak  DMA1_Stream5_IRQHandler
    .weak  DMA1_Stream6_IRQHandler
    .weak  ADC_IRQHandler
    .weak  CAN1_TX_IRQHandler
    .weak  CAN1_RX0_IRQHandler
    .weak  CAN1_RX1_IRQHandler
    .weak  CAN1_SCE_IRQHandler
    .weak  EXTI9_5_IRQHandler
    .weak  TIM1_BRK_TIM9_IRQHandler
    .weak  TIM1_UP_TIM10_IRQHandler
    .weak  TIM1_TRG_COM_TIM11_IRQHandler
    .weak  TIM1_CC_IRQHandler
    .weak  TIM2_IRQHandler
    .weak  TIM3_IRQHandler
    .weak  TIM4_IRQHandler
    .weak  I2C1_EV_IRQHandler
    .weak  I2C1_ER_IRQHandler
    .weak  I2C2_EV_IRQHandler
    .weak  I2C2_ER_IRQHandler
    .weak  SPI1_IRQHandler
    .weak  SPI2_IRQHandler
    .weak  USART1_IRQHandler
    .weak  USART2_IRQHandler
    .weak  USART3_IRQHandler
    .weak  EXTI15_10_IRQHandler
    .weak  RTC_Alarm_IRQHandler
    .weak  OTG_FS_WKUP_IRQHandler
    .weak  TIM8_BRK_TIM12_IRQHandler
    .weak  TIM8_UP_TIM13_IRQHandler
    .weak  TIM8_TRG_COM_TIM14_IRQHandler
    .weak  TIM8_CC_IRQHandler
    .weak  DMA1_Stream7_IRQHandler
    .weak  FMC_IRQHandler
    .weak  SDIO_IRQHandler
    .weak  TIM5_IRQHandler
    .weak  SPI3_IRQHandler
    .weak  UART4_IRQHandler
    .weak  UART5_IRQHandler
    .weak  TIM6_DAC_IRQHandler
    .weak  TIM7_IRQHandler
    .weak  DMA2_Stream0_IRQHandler
    .weak  DMA2_Stream1_IRQHandler
    .weak  DMA2_Stream2_IRQHandler
    .weak  DMA2_Stream3_IRQHandler
    .weak  DMA2_Stream4_IRQHandler
    .weak  ETH_IRQHandler
    .weak  ETH_WKUP_IRQHandler
    .weak  CAN2_TX_IRQHandler
    .weak  CAN2_RX0_IRQHandler
    .weak  CAN2_RX1_IRQHandler
    .weak  CAN2_SCE_IRQHandler
    .weak  OTG_FS_IRQHandler
    .weak  DMA2_Stream5_IRQHandler
    .weak  DMA2_Stream6_IRQHandler
    .weak  DMA2_Stream7_IRQHandler
    .weak  USART6_IRQHandler
    .weak  I2C3_EV_IRQHandler
    .weak  I2C3_ER_IRQHandler
    .weak  OTG_HS_EP1_OUT_IRQHandler
    .weak  OTG_HS_EP1_IN_IRQHandler
    .weak  OTG_HS_WKUP_IRQHandler
    .weak  OTG_HS_IRQHandler
    .weak  DCMI_IRQHandler
    .weak  CRYP_IRQHandler
    .weak  HASH_RNG_IRQHandler
    .weak  FPU_IRQHandler
    .weak  SPI4_IRQHandler
    .weak  SPI5_IRQHandler

NMI_Handler:
HardFault_Handler:
MemManage_Handler:
BusFault_Handler:
UsageFault_Handler:
SVC_Handler:
DebugMon_Handler:
PendSV_Handler:
SysTick_Handler:
WWDG_IRQHandler:
PVD_IRQHandler:
TAMP_STAMP_IRQHandler:
RTC_WKUP_IRQHandler:
FLASH_IRQHandler:
RCC_IRQHandler:
EXTI0_IRQHandler:
EXTI1_IRQHandler:
EXTI2_IRQHandler:
EXTI3_IRQHandler:
EXTI4_IRQHandler:
DMA1_Stream0_IRQHandler:
DMA1_Stream1_IRQHandler:
DMA1_Stream2_IRQHandler:
DMA1_Stream3_IRQHandler:
DMA1_Stream4_IRQHandler:
DMA1_Stream5_IRQHandler:
DMA1_Stream6_IRQHandler:
ADC_IRQHandler:
CAN1_TX_IRQHandler:
CAN1_RX0_IRQHandler:
CAN1_RX1_IRQHandler:
CAN1_SCE_IRQHandler:
EXTI9_5_IRQHandler:
TIM1_BRK_TIM9_IRQHandler:
TIM1_UP_TIM10_IRQHandler:
TIM1_TRG_COM_TIM11_IRQHandler:
TIM1_CC_IRQHandler:
TIM2_IRQHandler:
TIM3_IRQHandler:
TIM4_IRQHandler:
I2C1_EV_IRQHandler:
I2C1_ER_IRQHandler:
I2C2_EV_IRQHandler:
I2C2_ER_IRQHandler:
SPI1_IRQHandler:
SPI2_IRQHandler:
USART1_IRQHandler:
USART2_IRQHandler:
USART3_IRQHandler:
EXTI15_10_IRQHandler:
RTC_Alarm_IRQHandler:
OTG_FS_WKUP_IRQHandler:
TIM8_BRK_TIM12_IRQHandler:
TIM8_UP_TIM13_IRQHandler:
TIM8_TRG_COM_TIM14_IRQHandler:
TIM8_CC_IRQHandler:
DMA1_Stream7_IRQHandler:
FMC_IRQHandler:
SDIO_IRQHandler:
TIM5_IRQHandler:
SPI3_IRQHandler:
UART4_IRQHandler:
UART5_IRQHandler:
TIM6_DAC_IRQHandler:
TIM7_IRQHandler:
DMA2_Stream0_IRQHandler:
DMA2_Stream1_IRQHandler:
DMA2_Stream2_IRQHandler:
DMA2_Stream3_IRQHandler:
DMA2_Stream4_IRQHandler:
ETH_IRQHandler:
ETH_WKUP_IRQHandler:
CAN2_TX_IRQHandler:
CAN2_RX0_IRQHandler:
CAN2_RX1_IRQHandler:
CAN2_SCE_IRQHandler:
OTG_FS_IRQHandler:
DMA2_Stream5_IRQHandler:
DMA2_Stream6_IRQHandler:
DMA2_Stream7_IRQHandler:
USART6_IRQHandler:
I2C3_EV_IRQHandler:
I2C3_ER_IRQHandler:
OTG_HS_EP1_OUT_IRQHandler:
OTG_HS_EP1_IN_IRQHandler:
OTG_HS_WKUP_IRQHandler:
OTG_HS_IRQHandler:
DCMI_IRQHandler:
CRYP_IRQHandler:
HASH_RNG_IRQHandler:
FPU_IRQHandler:
SPI4_IRQHandler:
SPI5_IRQHandler:
Default_Handler:
    b .

    .size Reset_Handler, .-Reset_Handler
