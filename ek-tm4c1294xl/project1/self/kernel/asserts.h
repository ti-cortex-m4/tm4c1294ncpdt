/*------------------------------------------------------------------------------
ASSERTS.H


------------------------------------------------------------------------------*/

#ifndef __ASSERTS
#define __ASSERTS


#include "../main.h"



typedef struct
{
  uint          iwEvent;
  time          tiEvent;
  char          szFileName[128];
  ulong         wLine;
} assert;


#endif


void    InitAsserts(void);
void    ResetAsserts(void);

void    AddAssert(char  *pcFileName, ulong  dwLine);
void    OutAsserts(void);
