#ifndef ALARM_H
#define ALARM_H

#include <stdbool.h>
#include "Clock.h"

typedef struct {
  Clock_Val_t duration;
  Clock_Val_t started_at;
} Alarm_t;

/**
 * Initialize an alarm and sets it's configured duration.
 */
void Alarm_Init(Alarm_t * alarm, Clock_Val_t duration);

/**
 * Starts the alarm. Alarm will expire `duration` ticks from the time this
 * function is called.
 */
void Alarm_Start(Alarm_t * alarm);

/**
 * Resets the alarm. Alarm will expire `duration` ticks from the time the alarm
 * first expired. If the alarm was never started, it will expire `duration`
 * ticks from now.
 */
void Alarm_Reset(Alarm_t * alarm);

/**
 * True when the alarm has expired.
 */
bool Alarm_IsExpired(Alarm_t * alarm);

#endif /* ALARM_H */
