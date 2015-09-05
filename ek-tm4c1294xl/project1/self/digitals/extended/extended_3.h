/*------------------------------------------------------------------------------
EXTENDED_3.H


------------------------------------------------------------------------------*/

#ifndef __EXTENDED_3
#define __EXTENDED_3


// тип внешнего события
typedef enum
{
  INC_ERROR             = 0,
  INC_DEVICE            = 1,
  INC_PHASE1            = 2,
  INC_PHASE2            = 3,
  INC_PHASE3            = 4
} incident;



extern  cache const             chExt3Flag;
extern  cache const             chEventFlagA;
extern  cache const             chEventFlagB;



void    InitExtended3(void);
void    ResetExtended3(void);
void    ResetExtended3_Manual(void);

void    MakeExtended3(void);

ulong   DateToEventIndex(time  ti);
time    EventIndexToDate(ulong  dw);


#endif
