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

#include "LightScheduler.h"
#include "LightController.h"
#include "common.h"

/* START: MultipleEventData */
enum
{
    UNUSED = -1,
    TURN_OFF, TURN_ON,
    MAX_EVENTS = 128
};

typedef struct
{
    int id;
    Day day;
    int minuteOfDay;
    int event;

} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvents[MAX_EVENTS];
/* END: MultipleEventData */


/* START: MultipleEventCreate2 */

void LightScheduler_Create(void)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
        scheduledEvents[i].id = UNUSED;

    TimeService_SetPeriodicAlarmInSeconds(60,
            LightScheduler_Wakeup);
}
/* END: MultipleEventCreate1 */

/* START: SingleEventDestroy2 */
void LightScheduler_Destroy(void)
{
    TimeService_CancelPeriodicAlarmInSeconds(60,
            LightScheduler_Wakeup);
}
/* END: SingleEventDestroy2 */

/* START: ErrorReturns */
static int scheduleEvent(int id, Day day, int minute, int event)
{
    int i;

    if (id < 0 || id >= MAX_LIGHTS)
        return LS_ID_OUT_OF_BOUNDS;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id == UNUSED)
        {
            scheduledEvents[i].day = day;
            scheduledEvents[i].minuteOfDay = minute;
            scheduledEvents[i].event = event;
            scheduledEvents[i].id = id;
            return LS_OK;
        }
    }
    return LS_TOO_MANY_EVENTS;
}

int LightScheduler_ScheduleTurnOn(int id, Day day, int minute)
{
    return scheduleEvent(id, day, minute, TURN_ON);
}

int LightScheduler_ScheduleTurnOff(int id, Day day, int minute)
{
    return scheduleEvent(id, day, minute, TURN_OFF);
}
/* END: ErrorReturns */

/* START: DoesLightRespondToday2 */
static int DoesLightRespondToday(Time * time, int reactionDay)
{
    int today = time->dayOfWeek;

    if (reactionDay == EVERYDAY)
        return TRUE;
    if (reactionDay == today)
        return TRUE;
    if (reactionDay == WEEKEND && (today == SATURDAY || today == SUNDAY))
        return TRUE;
    if (reactionDay == WEEKDAY && today >= MONDAY && today <= FRIDAY)
        return TRUE;
    return FALSE;
}
/* END: DoesLightRespondToday2 */

/* START: operateLight */
static void operateLight(ScheduledLightEvent * lightEvent)
{
    if (lightEvent->event == TURN_ON)
         LightController_On(lightEvent->id);
    else if (lightEvent->event == TURN_OFF)
         LightController_Off(lightEvent->id);
}
/* END: operateLight */

/* START: processEvent2 */
static void processEventDueNow(Time * time, ScheduledLightEvent * lightEvent)
{
    if (lightEvent->id == UNUSED)
        return;
    if (!DoesLightRespondToday(time, lightEvent->day))
        return;
    if (lightEvent->minuteOfDay != time->minuteOfDay)
        return;

    operateLight(lightEvent);
}
/* END: processEvent2 */

/* START: MultipleEvent3 */
void LightScheduler_Wakeup(void)
{
    int i;

    Time time;
    TimeService_GetTime(&time);

    for (i = 0; i < MAX_EVENTS; i++)
    {
        processEventDueNow(&time, &scheduledEvents[i]);
    }
}
/* END: MultipleEvent3 */

/* START: MultipleEventRemove1 */
void LightScheduler_ScheduleRemove(int id, Day day, int minute)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id == id
         && scheduledEvents[i].day == day
         && scheduledEvents[i].minuteOfDay == minute)
         {
             scheduledEvents[i].id = UNUSED;
         }
    }
 }
/* END: MultipleEventRemove1 */

#if 0
/* START: SingleEventDataInit1 */
enum
{
    UNUSED = -1,
    TURN_OFF, TURN_ON,
};

typedef struct
{
    int id;
    int minuteOfDay;
    int event;

} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvent;

void LightScheduler_Create(void)
{
    scheduledEvent.id = UNUSED;

}
/* END: SingleEventDataInit1 */
#endif

#if 0 /* START: MultipleEventCreate1 */
static ScheduledLightEvent scheduledEvent;
static ScheduledLightEvent scheduledEvents[MAX_EVENTS];

void LightScheduler_Create(void)
{
    int i;

    scheduledEvent.id = UNUSED;

    for (i = 0; i < MAX_EVENTS; i++)
        scheduledEvents[i].id = UNUSED;

    TimeService_SetPeriodicAlarmInSeconds(60,
            LightScheduler_Wakeup);
}
#endif /* END: MultipleEventCreate1 */

#if 0 /* START: SingleEventCreate2 */
static ScheduledLightEvent scheduledEvent;

void LightScheduler_Create(void)
{
    int i;

    scheduledEvent.id = UNUSED;

    TimeService_SetPeriodicAlarmInSeconds(60,
            LightScheduler_Wakeup);
}
#endif /* END: SingleEventCreate2 */

#if 0 /* START: SingleEventDestroy */
void LightScheduler_Destroy(void)
{
}
#endif /* END: SingleEventDestroy */

#if 0 /* START: MultipleEventSchedule1 */
static void scheduleEvent(int id, Day day, int minuteOfDay, int event)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id == UNUSED)
        {
            scheduledEvents[i].day = day;
            scheduledEvents[i].minuteOfDay = minuteOfDay;
            scheduledEvents[i].event = event;
            scheduledEvents[i].id = id;
            break;
        }
    }

    scheduledEvent.day = day;
    scheduledEvent.minuteOfDay = minuteOfDay;
    scheduledEvent.event = event;
    scheduledEvent.id = id;
}
/* END: MultipleEventSchedule1 */
#endif

#if 0
/* START: SingleEventScheduleExtracted */
static void scheduleEvent(int id, Day day, int minuteOfDay, int event)
{
    scheduledEvent.minuteOfDay = minuteOfDay;
    scheduledEvent.event = event;
    scheduledEvent.id = id;
}
/* END: SingleEventScheduleExtracted */
#endif

#if 0 /* START: MultipleEvent */
static void scheduleEvent(int id, Day day, int minuteOfDay, int event)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id == UNUSED)
        {
            scheduledEvents[i].day = day;
            scheduledEvents[i].minuteOfDay = minuteOfDay;
            scheduledEvents[i].event = event;
            scheduledEvents[i].id = id;
            break;
        }
    }
}
/* END: MultipleEvent */

/* START: SingleEventSchedule1 */
void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
    scheduleEvent(id, day, minuteOfDay, TURN_ON);
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
    scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}
/* END: SingleEventSchedule1 */
#endif

#if 0 /* START: SingleEventWakeup2 */
void LightScheduler_Wakeup(void)
{
    Time time;
    TimeService_GetTime(&time);
    processEventDueNow(&time, &scheduledEvent);
}
/* END: SingleEventWakeup2 */
#endif

#if 0 /* START: MultipleEventWakeup1 */
void LightScheduler_Wakeup(void)
{
    int i;
    Time time;
    TimeService_GetTime(&time);

    for (i = 0; i < MAX_EVENTS; i++)
    {
        processEventDueNow(&time, &scheduledEvents[i]);
    }

    processEventDueNow(&time, &scheduledEvent);
}
/* END: MultipleEventWakeup1 */
#endif

#if 0 /* START: MultipleEvent2 */
void LightScheduler_Wakeup(void)
{
    int i;

    Time time;
    TimeService_GetTime(&time);

    for (i = 0; i < MAX_EVENTS; i++)
    {
        processEventDueNow(&time, &scheduledEvents[i]);
    }
}
#endif /* END: MultipleEvent2 */

#if 0 /* START: MultipleEvent1 */
void LightScheduler_Wakeup(void)
{
    int i;
    Time time;
    TimeService_GetTime(&time);

    for (i = 0; i < MAX_EVENTS; i++)
    {
        processEventDueNow(&time, &scheduledEvents[i]);
    }

    processEventDueNow(&time, &scheduledEvent);
}
#endif /* END: MultipleEvent1 */

#if 0 /* START: SingleEventRemove1 */
void LightScheduler_ScheduleRemove(int id, Day day, int minuteOfDay)
{
    if (scheduledEvent.id == id
    && scheduledEvent.day == day
    && scheduledEvent.minuteOfDay == minuteOfDay)
    {
        scheduledEvent.id = UNUSED;
    }
}
#endif /* END: SingleEventRemove1 */

#if 0
static ScheduledLightEvent scheduledEvent;

/* START: DoesLightRespondToday1 */
static int DoesLightRespondToday(Time * time, int reactionDay)
{
    int today = time->dayOfWeek;

    if (reactionDay == EVERYDAY)
        return TRUE;
    if (reactionDay == today)
        return TRUE;
    if (reactionDay == WEEKEND && (SATURDAY == today || SUNDAY == today))
        return TRUE;
    if (reactionDay == WEEKDAY && today >= MONDAY && today <= FRIDAY)
        return TRUE;
    return FALSE;
}
/* END: DoesLightRespondToday1 */
#endif

#if 0 /* START: SingleEventWakeupWithExactDayMatch */
static void processEventDueNow(Time * time, ScheduledLightEvent * lightEvent)
{
    int reactionDay = lightEvent->day;

    if (lightEvent->id == UNUSED)
        return;
    if (reactionDay != EVERYDAY && reactionDay != today)
        return;
    if (lightEvent->minuteOfDay != time->minuteOfDay)
        return;

    operateLight(lightEvent);
}
#endif /* END: SingleEventWakeupWithExactDayMatch */

#if 0 /* START: SingleEventWakeupWithEverydayMatch */
static void processEventDueNow(Time * time, ScheduledLightEvent * lightEvent)
{
    if (lightEvent->id == UNUSED)
        return;
    if (lightEvent->day != EVERYDAY)
        return;
    if (lightEvent->minuteOfDay != time->minuteOfDay)
        return;

    operateLight(lightEvent);
}
#endif /* END: SingleEventWakeupWithEverydayMatch */

#if 0 /* START: operateLight1 */
static void operateLight(ScheduledLightEvent * lightEvent)
{
    if (lightEvent->event == TURN_ON)
         LightController_On(lightEvent->id);
    else if (lightEvent->event == TURN_OFF)
         LightController_Off(lightEvent->id);
}
/* END: operateLight1 */

/* START: processEventDueNow1 */
static void processEventDueNow(Time * time, ScheduledLightEvent * lightEvent)
{
    if (lightEvent->id == UNUSED)
        return;

    if (lightEvent->minuteOfDay != time->minuteOfDay)
        return;

    operateLight(lightEvent);
}
/* END: processEventDueNow1 */

/* START: SingleEventWakeup1 */
void LightScheduler_Wakeup(void)
{
    Time time;
    TimeService_GetTime(&time);

    processEventDueNow(&time, &scheduledEvent);
}
/* END: SingleEventWakeup1 */

#endif

#if 0
static ScheduledLightEvent scheduledEvent;
/* START: SingleEventLongMethod */
void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
    scheduledEvent.minuteOfDay = minuteOfDay;
    scheduledEvent.event = TURN_ON;
    scheduledEvent.id = id;
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
    scheduledEvent.minuteOfDay = minuteOfDay;
    scheduledEvent.event = TURN_OFF;
    scheduledEvent.id = id;
}
/* END: SingleEventLongMethod */

/* START: WakeUpLongMethod */
void LightScheduler_Wakeup(void)
{
    Time time;
    TimeService_GetTime(&time);

    if (scheduledEvent.id == UNUSED)
        return;

    if (time.minuteOfDay != scheduledEvent.minuteOfDay)
        return;

    if (scheduledEvent.event == TURN_ON)
         LightController_On(scheduledEvent.id);
    else if (scheduledEvent.event == TURN_OFF)
         LightController_Off(scheduledEvent.id);

}
/* END: WakeUpLongMethod */
#endif

#if 0 /* START: SingleEventEverydayStruct */
typedef struct
{
    int id;
    int minuteOfDay;
} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvent;

void LightScheduler_Create(void)
{
    scheduledEvent.id = UNUSED;
}
#endif /* END: SingleEventEverydayStruct */

#if 0 /* START: SingleEventEveryday */
void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
    scheduledEvent.id = id;
    scheduledEvent.minuteOfDay = minuteOfDay;
}

void LightScheduler_Wakeup(void)
{
    Time time;
    TimeService_GetTime(&time);

    if (scheduledEvent.id == UNUSED)
        return;

    if (time.minuteOfDay != scheduledEvent.minuteOfDay)
        return;

    LightController_On(scheduledEvent.id);

}
#endif /* END: SingleEventEveryday */

#if 0 /* START: JustForWiring */
void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
}

void LightScheduler_Wakeup(void)
{
}
#endif /* END: JustForWiring */
