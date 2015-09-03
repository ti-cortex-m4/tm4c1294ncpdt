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



void    ResetExtended3(void);
void    ResetExtended3_Full(void);

void    MakeExtended3(void);

ulong   DateToEventIndex(time  ti);
time    EventIndexToDate(ulong  dw);


#endif
