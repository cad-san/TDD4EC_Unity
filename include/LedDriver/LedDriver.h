#ifndef D_LedDriver_H
#define D_LedDriver_H

#include <stdint.h>

void LedDriver_Create(uint16_t * address);

void LedDriver_Destory(void);

void LedDriver_TurnOn(int ledNumber);

void LedDriver_TurnOff(int ledNumber);

void LedDriver_TurnAllOn();

#endif

