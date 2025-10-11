#include "bootloader.h"
#include "peripherals.h"

int main(void)
{
    Peripherals_Init();
    Bootloader_Init();
    Bootloader_Run();

    while (1)
    {
    }
}
