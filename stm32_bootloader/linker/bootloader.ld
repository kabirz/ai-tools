MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 32K
    RAM   (xrw) : ORIGIN = 0x20000000, LENGTH = 128K
    CCM   (xrw) : ORIGIN = 0x10000000, LENGTH = 64K
}

ENTRY(Reset_Handler)

_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > FLASH

    .text :
    {
        *(.text)
        *(.text*)
        *(.glue_7)
        *(.glue_7t)
        *(.gnu.linkonce.t*)
    } > FLASH

    .rodata :
    {
        *(.rodata)
        *(.rodata*)
        *(.gnu.linkonce.r*)
    } > FLASH

    .ARM.extab :
    {
        *(.ARM.extab*)
    } > FLASH

    .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    } > FLASH

    .data : AT(__data_load_addr)
    {
        __data_start__ = .;
        *(.data)
        *(.data*)
        __data_end__ = .;
    } > RAM
    __data_load_addr = LOADADDR(.data);

    .bss (NOLOAD) :
    {
        __bss_start__ = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        __bss_end__ = .;
    } > RAM

    .ccmram (NOLOAD) :
    {
        __ccm_start__ = .;
        *(.ccmram)
        *(.ccmram*)
        __ccm_end__ = .;
    } > CCM

    ._user_heap_stack (NOLOAD) :
    {
        . = ALIGN(8);
        __end__ = .;
        PROVIDE(end = .);
        *(.heap*)
        *(.stack*)
        . = ALIGN(8);
    } > RAM

    __bootloader_image_end = .;
}

ASSERT(__bootloader_image_end <= ORIGIN(FLASH) + LENGTH(FLASH),
       "Bootloader image exceeds configured 32 KiB partition");
