#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include <stdint.h>

void Peripherals_Init(void);
void Peripherals_DeInit(void);
uint32_t Peripherals_GetTick(void);
void Peripherals_Delay(uint32_t ms);

#endif /* PERIPHERALS_H */
