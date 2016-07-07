/*------------------------------------------------------------------------------
clock.h


------------------------------------------------------------------------------*/

#ifndef __CLOCK_H__
#define __CLOCK_H__


void Clock_10Hz(void);
ulong GetClockSeconds(void);

date_t SecondsToDate(ulong dwSeconds);


#endif
