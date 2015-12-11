/*------------------------------------------------------------------------------
PERIOD30.H


------------------------------------------------------------------------------*/

#ifndef __PERIOD30_H
#define __PERIOD30_H


#include "../main.h"


#define PERIOD30_SIZE   5


typedef struct
{
  uint          iwIdx;
  time          tiPrev;
  time          tiCurr;
  uint          cwSecond;
} period30;


extern period30                vPeriod30;


#endif
