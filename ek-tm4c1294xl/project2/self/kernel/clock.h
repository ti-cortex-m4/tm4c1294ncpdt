/*------------------------------------------------------------------------------
clock.h


------------------------------------------------------------------------------*/

#ifndef __CLOCK_H__
#define __CLOCK_H__


typedef struct
{
  uint          wDays;
  uchar         bHours;
  uchar         bMinutes;
  uchar         bSeconds;
} days_t;


void Clock_1Hz(void);
ulong GetClockSeconds(void);

days_t SecondsToDays(ulong dwSeconds);


#endif
