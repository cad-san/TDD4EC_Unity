#include "LedDriver.h"
#include "RuntimeError.h"

enum { ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON };
enum { FIRST_LED = 1, LAST_LED = 16};

static uint16_t * ledsAddress;
static uint16_t ledsImage;

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

static void setLedImageBit(int ledNumber)
{	
	ledsImage |= convetLedNumberToBit(ledNumber);
}

static void clearLedImageBit(int ledNumber)
{
	ledsImage &= ~(convetLedNumberToBit(ledNumber));
}

static BOOL IsLedOutOfBounds(int ledNumber)
{
	if (ledNumber < FIRST_LED || ledNumber > LAST_LED)
	{
		RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
		return TRUE;
	}
	return FALSE;
}

void LedDriver_TurnOn(int ledNumber)
{
	if(IsLedOutOfBounds(ledNumber))
	{
		return;
	}

	setLedImageBit(ledNumber);
	updateHardware();
}

void LedDriver_TurnOff(int ledNumber)
{
	if(IsLedOutOfBounds(ledNumber))
	{
		return;
	}

	clearLedImageBit(ledNumber);
	updateHardware();
}

void LedDriver_TurnAllOn()
{
	ledsImage = ALL_LEDS_ON;
	updateHardware();
}

void LedDriver_TurnAllOff()
{
	ledsImage = ALL_LEDS_OFF;
	updateHardware();
}

BOOL LedDriver_IsOn(int ledNumber)
{
	if(IsLedOutOfBounds(ledNumber))
		return FALSE;

	return ledsImage & (convetLedNumberToBit(ledNumber));
}

BOOL LedDriver_IsOff(int ledNumber)
{
	return !LedDriver_IsOn(ledNumber);
}

