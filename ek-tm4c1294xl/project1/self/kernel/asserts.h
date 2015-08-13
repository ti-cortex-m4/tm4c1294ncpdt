/*------------------------------------------------------------------------------
ASSERTS,H


------------------------------------------------------------------------------*/

#ifndef __ASSERTS
#define __ASSERTS


#include "../main.h"


#define ASSERTS_SIZE    16
#define FILE_NAME_SIZE  128


typedef struct
{
  uint          iwEvent;
  time          tiEvent;
  ulong         dwLine;
  char          szFileName[FILE_NAME_SIZE];
} assert;


#endif


extern  assert                  mpAsserts[ASSERTS_SIZE];



void    InitAsserts(void);
void    ResetAsserts(void);

void    AddAssert(char  *pcFileName, ulong  dwLine);
void    OutAsserts(void);
