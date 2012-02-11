#include "LedDriver.h"

static uint16_t * ledsAddress;
static uint16_t ledsImage;

enum { ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON };

void LedDriver_Create(uint16_t * address)
{
	ledsAddress = address;
	ledsImage = ALL_LEDS_OFF;
	*ledsAddress = ledsImage;
}

void LedDriver_Destory(void)
{
}

static void updateHardware(void)
{
	*ledsAddress = ledsImage;
}

static uint16_t convetLedNumberToBit(int ledNumber)
{
	return 1 << (ledNumber-1);
}

void LedDriver_TurnOn(int ledNumber)
{
	
	ledsImage |= convetLedNumberToBit(ledNumber);
	updateHardware();
}

void LedDriver_TurnOff(int ledNumber)
{
	ledsImage &= ~(convetLedNumberToBit(ledNumber));
	updateHardware();
}

void LedDriver_TurnAllOn()
{
	ledsImage = ALL_LEDS_ON;
	updateHardware();
}
