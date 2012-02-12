#ifndef D_LedDriver_H
#define D_LedDriver_H

#include <stdint.h>

typedef int BOOL;

#ifndef TRUE
#  define TRUE 1
#endif

#ifndef FALSE
#  define FALSE 0
#endif

void LedDriver_Create(uint16_t * address);

void LedDriver_Destory(void);

void LedDriver_TurnOn(int ledNumber);

void LedDriver_TurnOff(int ledNumber);

void LedDriver_TurnAllOn();

void LedDriver_TurnAllOff();

BOOL LedDriver_IsOn(int ledNumber);

BOOL LedDriver_IsOff(int ledNumber);

#endif

