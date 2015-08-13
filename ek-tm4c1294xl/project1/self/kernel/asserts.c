/*------------------------------------------------------------------------------
ASSERTS.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "asserts.h"



assert                  mpAsserts[16];



void    InitAsserts(void)
{
}



void    ResetAsserts(void)
{
}



void    AddAssert(char  *pcFileName, ulong  dwLine)
{
}



void    OutAsserts(void)
{
  InitPushCRC();

  Push(mpAsserts, sizeof(mpAsserts));

  Output(sizeof(mpAsserts));
}
