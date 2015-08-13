/*------------------------------------------------------------------------------
ASSERTS.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "../nvram/cache.h"
#include "../time/rtc.h"
#include "asserts.h"



assert                  mpAsserts[16];

cache const             chAsserts = {ASSERTS, &mpAsserts, sizeof(mpAsserts)};



void    InitAsserts(void)
{
  LoadCache(&chAsserts);
}


void    ResetAsserts(void)
{
  memset(&mpAsserts, 0, sizeof(mpAsserts));
  SaveCache(&chAsserts);
}



void    AddAssert(char  *pcFileName, ulong  dwLine)
{
  uchar i = 0;

  mpAsserts[i].iwEvent = ++i;
  mpAsserts[i].tiEvent = *GetCurrTimeDate();
  mpAsserts[i].dwLine = dwLine;

  memset(&mpAsserts[i].szFileName, 0, 128);
  strncpy(mpAsserts[i].szFileName, pcFileName, 128);

  SaveCache(&chAsserts);
}



void    OutAsserts(void)
{
  InitPushCRC();
  Push(mpAsserts, sizeof(mpAsserts));
  Output(sizeof(mpAsserts));
}
