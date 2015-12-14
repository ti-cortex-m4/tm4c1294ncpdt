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
  time          tiRTC;
  uint          cwSeconds;
} period30;


void    InitPeriod30(void);
void    ResetPeriod30(void);

void    NextSecPeriod30(void);
void    NextHhrPeriod30(void);

void    OutPeriod30(void);


#endif
