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
  ulong         dwLine;
  char          szFileName[128];
} assert;


#endif


extern  assert                  mpAsserts[16];



void    InitAsserts(void);
void    ResetAsserts(void);

void    AddAssert(char  *pcFileName, ulong  dwLine);
void    OutAsserts(void);
