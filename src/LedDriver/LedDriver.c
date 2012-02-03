/*- ------------------------------------------------------------------ -*/
/*-    Copyright (c) James W. Grenning -- All Rights Reserved          -*/
/*-    For use by owners of Test-Driven Development for Embedded C,    -*/
/*-    and attendees of Renaissance Software Consulting, Co. training  -*/
/*-    classes.                                                        -*/
/*-                                                                    -*/
/*-    Available at http://pragprog.com/titles/jgade/                  -*/
/*-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3                -*/
/*-                                                                    -*/
/*-    Authorized users may use this source code in your own           -*/
/*-    projects, however the source code may not be used to            -*/
/*-    create training material, courses, books, articles, and         -*/
/*-    the like. We make no guarantees that this source code is        -*/
/*-    fit for any purpose.                                            -*/
/*-                                                                    -*/
/*-    www.renaissancesoftware.net james@renaissancesoftware.net       -*/
/*- ------------------------------------------------------------------ -*/


#include "LedDriver.h"
#include "RuntimeError.h"


/* START: final */
enum {ALL_LEDS_OFF = 0, ALL_LEDS_ON = ~0};

static uint16_t * ledsAddress;
static uint16_t ledsImage;

void LedDriver_Create(uint16_t * address)
{
    ledsAddress = address;
    ledsImage = ALL_LEDS_OFF;
    *ledsAddress = ledsImage;
}

void LedDriver_Destroy(void)
{
}

enum {FIRST_LED = 1, LAST_LED = 16};

static BOOL IsLedOutOfBounds(int ledNumber)
{
    if ((ledNumber < FIRST_LED) || (ledNumber > LAST_LED))
        {
            RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
            return TRUE;
        }
    return FALSE;
}

static uint16_t convertLedNumberToBit(int ledNumber)
{
    return 1 << (ledNumber - 1);
}

/* START: updateHardware */
static void updateHardware(void)
{
    *ledsAddress = ledsImage;
}
/* END: updateHardware */

/* START: ConsistentLevelOfAbstraction */
static void setLedImageBit(int ledNumber)
{
    ledsImage |= convertLedNumberToBit(ledNumber);
}

void LedDriver_TurnOn(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber))
        return;

    setLedImageBit(ledNumber);
    updateHardware();
}

static void clearLedImageBit(int ledNumber)
{
    ledsImage &= ~convertLedNumberToBit(ledNumber);
}

void LedDriver_TurnOff(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber))
        return;

    clearLedImageBit(ledNumber);
    updateHardware();
}
/* END: ConsistentLevelOfAbstraction */
/* START: updateHardware */

void LedDriver_TurnAllOn(void)
{
    ledsImage = ALL_LEDS_ON;
    updateHardware();
}
/* END: updateHardware */

void LedDriver_TurnAllOff(void)
{
    ledsImage = ALL_LEDS_OFF;
    updateHardware();
}

BOOL LedDriver_IsOn(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber))
        return FALSE;

    return 0 != (ledsImage & convertLedNumberToBit(ledNumber));
}

BOOL LedDriver_IsOff(int ledNumber)
{
     return !LedDriver_IsOn(ledNumber);
}
/* END: final */


/*
 * Intermediate examples below this comment
 */

#if 0 /* START: LedDriver_IsOff.forceFail */
BOOL LedDriver_IsOff(int ledNumber)
{
     return FALSE; /* !LedDriver_IsOn(ledNumber); */
}
#endif /* END: LedDriver_IsOff.forceFail */


#if 0 /* START: IsOn2 */
BOOL LedDriver_IsOn(int ledNumber)
{
    return 0 != (ledsImage & convertLedNumberToBit(ledNumber));
}
#endif /* END: IsOn2 */

#if 0 /* START: IsOnFakeOutOfBounds */
BOOL LedDriver_IsOn(int ledNumber)
{
    return TRUE;
    /* return 0 != (ledsImage & convertLedNumberToBit(ledNumber)); */
}
#endif /* END: IsOnFakeOutOfBounds */


#if 0
/* START: AddLedsImageVariable.init */
/* START: AddLedsImageVariable */
/* START: TurnAllOnTurnAllOff */
enum {ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON};

/* END: TurnAllOnTurnAllOff */
/* START: ledsAddress */
static uint16_t * ledsAddress;
/* END: ledsAddress */
static uint16_t ledsImage;

void LedDriver_Create(uint16_t * address)
{
    ledsAddress = address;
    ledsImage = ALL_LEDS_OFF;
    *ledsAddress = ledsImage;
}
/* END: AddLedsImageVariable.init */
/* END: AddLedsImageVariable */

void LedDriver_Destroy(void)
{
}

#if 0 /* START: IsOutOfBounds */
enum {FIRST_LED = 1, LAST_LED = 16};

static BOOL IsLedOutOfBounds(int ledNumber)
{
    return (ledNumber < FIRST_LED) || (ledNumber > LAST_LED);
}
#endif /* END: IsOutOfBounds */

/* START: IsOutOfBounds2 */
enum {FIRST_LED = 1, LAST_LED = 16};

static BOOL IsLedOutOfBounds(int ledNumber)
{
    if ((ledNumber < FIRST_LED) || (ledNumber > LAST_LED))
        {
            RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
            return TRUE;
        }
    return FALSE;
}
/* END: IsOutOfBounds2 */

/* START: GuardForOutOfBoundsRefactored2 */
static uint16_t convertLedNumberToBit(int ledNumber)
{
    return 1 << (ledNumber - 1);
}
/* END: GuardForOutOfBoundsRefactored2 */

/* START: GuardForOutOfBoundsRefactored3 */
static void updateHardware(void)
{
    *ledsAddress = ledsImage;
}

static void setLedImageBit(int ledNumber)
{
    ledsImage |= convertLedNumberToBit(ledNumber);
    updateHardware();
}


void LedDriver_TurnOn(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber))
        return;

    setLedImageBit(ledNumber);
}

static void clearLedImageBit(int ledNumber)
{
    ledsImage &= ~convertLedNumberToBit(ledNumber);
    updateHardware();
}

void LedDriver_TurnOff(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber))
        return;

    clearLedImageBit(ledNumber);
}
/* END: GuardForOutOfBoundsRefactored3 */


/* START: TurnAllOnTurnAllOff */
void LedDriver_TurnAllOn(void)
{
    ledsImage = ALL_LEDS_ON;
    updateHardware();
}

void LedDriver_TurnAllOff(void)
{
    ledsImage = ALL_LEDS_OFF;
    updateHardware();
}
/* END: TurnAllOnTurnAllOff */

/* START: IsOnRefactored */
BOOL LedDriver_IsOn(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber))
        return FALSE;

    return 0 != (ledsImage & convertLedNumberToBit(ledNumber));
}
/* END: IsOnRefactored */

/* START: IsOff */
BOOL LedDriver_IsOff(int ledNumber)
{
     return !LedDriver_IsOn(ledNumber);
}
/* END: IsOff */
/* END: final */
#endif

#if 0 /* START: IsOn */
BOOL LedDriver_IsOn(int ledNumber)
{
    return ledsImage & (convertLedNumberToBit(ledNumber));
}
/* END: IsOn */
#endif

#if 0 /* START: IsOnWithGuard */
BOOL LedDriver_IsOn(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber))
        return FALSE;

    return ledsImage & (convertLedNumberToBit(ledNumber));
}
/* END: IsOnWithGuard */
#endif


#if 0 /* START: GuardForOutOfBoundsRefactored */
void LedDriver_TurnOn(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber))
        return;

    ledsImage |= convertLedNumberToBit(ledNumber);
    updateHardware();
}

void LedDriver_TurnOff(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber))
        return;

    ledsImage &= ~(convertLedNumberToBit(ledNumber));
    updateHardware();
}
#endif /* END: GuardForOutOfBoundsRefactored */

#if 0 /* START: StartingPoint */
#include "LedDriver.h"

void LedDriver_Create(uint16_t * address)
{
}

void LedDriver_Destroy(void)
{
}
#endif /* END: StartingPoint */

#if 0 /* START: Constructor1 */
void LedDriver_Create(uint16_t * address)
{
    *address = 0;
}
#endif /* END: Constructor1 */

#if 0 /* START: ledsAddress */
void LedDriver_Create(uint16_t * address)
{
    ledsAddress = address;
    *ledsAddress = 0;
}
#endif /* END: ledsAddress */


#if 0 /* START: TurnOnSkeleton */
void LedDriver_TurnOn(int ledNumber)
{
}
#endif /* END: TurnOnSkeleton */

#if 0 /* START: TurnOnFakeIt */
void LedDriver_TurnOn(int ledNumber)
{
    *ledsAddress = 1;
}
#endif /* END: TurnOnFakeIt */


#if 0 /* START: FirstThreeTests */
#include "LedDriver.h"

static uint16_t * ledsAddress;

void LedDriver_Create(uint16_t * address)
{
    ledsAddress = address;
    *ledsAddress = 0;
}

void LedDriver_Destroy(void)
{
}

void LedDriver_TurnOn(int ledNumber)
{
    *ledsAddress = 1;
}

void LedDriver_TurnOff(int ledNumber)
{
    *ledsAddress = 0;
}
/* END: FirstThreeTests */
#endif

#if 0 /* START: TurnOnShiftItFirstTry */
void LedDriver_TurnOn(int ledNumber)
{
    *ledsAddress |= (1 << ledNumber);
}
/* END: TurnOnShiftItFirstTry */
#endif

#if 0 /* START: TurnOnShiftIt2ndTry */
void LedDriver_TurnOn(int ledNumber)
{
    *ledsAddress |= 1 << (ledNumber - 1);
}
/* END: TurnOnShiftIt2ndTry */
#endif

#if 0 /* START: TurnOnShiftIt3rdTry */
static uint16_t convertLedNumberToBit(int ledNumber)
{
    return  1 << (ledNumber - 1);
}

void LedDriver_TurnOn(int ledNumber)
{
    *ledsAddress |= convertLedNumberToBit(ledNumber);
}
/* END: TurnOnShiftIt3rdTry */
#endif

#if 0 /* START: AddLedsImageVariable.use */
/* START: AddLedsImageVariable */
void LedDriver_TurnOn(int ledNumber)
{
    ledsImage |= convertLedNumberToBit(ledNumber);
    *ledsAddress = ledsImage;
}
/* END: AddLedsImageVariable */
/* END: AddLedsImageVariable.use */
#endif

#if 0 /* START: GuardForOutOfBounds */
void LedDriver_TurnOn(int ledNumber)
{
    if (ledNumber <= 0 || ledNumber > 16)
        return;

    ledsImage |= convertLedNumberToBit(ledNumber);
    updateHardware();
}
/* END: GuardForOutOfBounds */
#endif

#if 0 /* START: TheCodeIWishIHad */
void LedDriver_TurnOn(int ledNumber)
{
    /* if (IsLedOutOfBounds(ledNumber)) */
    /*  return; */

    if (ledNumber <= 0 || ledNumber > 16)
        return;

    ledsImage |= convertLedNumberToBit(ledNumber);
    updateHardware();
}
/* END: TheCodeIWishIHad */
#endif

#if 0 /* START: TurnOffFakeIt */
void LedDriver_TurnOff(int ledNumber)
{
    *ledsAddress = 0;
}
/* END: TurnOffFakeIt */
#endif

#if 0 /* START: TurnOffFirstTry */
void LedDriver_TurnOff(int ledNumber)
{
    *ledsAddress &= ~(convertLedNumberToBit(ledNumber));
}
/* END: TurnOffFirstTry */
#endif

#if 0 /* START: AddLedsImageVariable */
/* START: AddLedsImageVariable.use */
void LedDriver_TurnOff(int ledNumber)
{
    ledsImage &= ~(convertLedNumberToBit(ledNumber));
    *ledsAddress = ledsImage;
}
/* END: AddLedsImageVariable.use */
/* END: AddLedsImageVariable */
#endif
#if 0 /* START: GuardForOutOfBounds */

void LedDriver_TurnOff(int ledNumber)
{
    if (ledNumber <= 0 || ledNumber > 16)
        return;

    ledsImage &= ~(convertLedNumberToBit(ledNumber));
    updateHardware();
}
/* END: GuardForOutOfBounds */
#endif

#if 0 /* START: TurnAllOnFirstTry */
void LedDriver_TurnAllOn(void)
{
    *ledsAddress = 0xffff;
}
/* END: TurnAllOnFirstTry */
#endif

#if 0 /* START: TurnAllOnFirstTryRefactored */
enum {ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON};

void LedDriver_TurnAllOn(void)
{
    *ledsAddress = ALL_LEDS_ON;
}
/* END: TurnAllOnFirstTryRefactored */
#endif

#if 0 /* START: TurnAllOnSecondTry */
/* START: AddLedsImageVariable.use */
/* START: AddLedsImageVariable */
void LedDriver_TurnAllOn(void)
{
    ledsImage = ALL_LEDS_ON;
    *ledsAddress = ledsImage;
}
/* END: AddLedsImageVariable.use */
/* END: AddLedsImageVariable */
/* END: TurnAllOnSecondTry */
#endif

#if 0 /* START: TurnAllOnEmptyImpl */
void LedDriver_TurnAllOn(void)
{
}
/* END: TurnAllOnEmptyImpl */
#endif

#if 0 /* START: TurnAllOffFirstTry */
void LedDriver_TurnAllOff(void)
{
    ledsImage = ALL_LEDS_OFF;
    updateHardware();
}
/* END: TurnAllOffFirstTry */
#endif

#if 0 /* START: IsOnFakeFalse */
BOOL LedDriver_IsOn(int ledNumber)
{
    return FALSE;
}
/* END: IsOnFakeFalse */
#endif

#if 0 /* START: IsOnFakeTrue */
BOOL LedDriver_IsOn(int ledNumber)
{
    return TRUE;
}
#endif /* END: IsOnFakeTrue */

#if 0 /* START: IsOnFakeFalseWithGuard */
BOOL LedDriver_IsOn(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber))
        return FALSE;

    return FALSE;
}
#endif /* END: IsOnFakeFalseWithGuard */

#if 0 /* START: GuardForOutOfBoundsRefactored2 */
void LedDriver_TurnOn(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber))
        return;

    ledsImage |= convertLedNumberToBit(ledNumber);
    updateHardware();
}

void LedDriver_TurnOff(int ledNumber)
{
    if (IsLedOutOfBounds(ledNumber))
        return;

    ledsImage &= ~convertLedNumberToBit(ledNumber);
    updateHardware();
}
/* END: GuardForOutOfBoundsRefactored2 */
#endif

#if 0
/* START: TurnAllOnTurnAllOff */
void LedDriver_TurnAllOn(void)
{
    ledsImage = ALL_LEDS_ON;
    *ledsAddress = ledsImage;
}

void LedDriver_TurnAllOff(void)
{
    ledsImage = ALL_LEDS_OFF;
    *ledsAddress = ledsImage;
}
/* END: TurnAllOnTurnAllOff */
#endif

