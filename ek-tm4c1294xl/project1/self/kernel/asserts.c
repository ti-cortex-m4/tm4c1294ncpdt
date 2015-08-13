/*------------------------------------------------------------------------------
ASSERTS.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "../nvram/cache.h"
#include "../time/rtc.h"
#include "asserts.h"



ulong                   dwAsserts;
assert                  mpAsserts[16];

cache const             chAssertsIdx = {ASSERTS_IDX, &dwAsserts, sizeof(ulong)};
cache const             chAsserts = {ASSERTS, &mpAsserts, sizeof(mpAsserts)};



void    InitAsserts(void)
{
  LoadCache(&chAssertsIdx);
  LoadCache(&chAsserts);
}


void    ResetAsserts(void)
{
	dwAsserts = 0;
  SaveCache(&chAssertsIdx);

  memset(&mpAsserts, 0, sizeof(mpAsserts));
  SaveCache(&chAsserts);
}



void    AddAssert(char  *pcFileName, ulong  dwLine)
{
  uchar i = dwAsserts % 16;

  dwAsserts++;
  SaveCache(&chAssertsIdx);

  mpAsserts[i].iwEvent = i;
  mpAsserts[i].tiEvent = *GetCurrTimeDate();
  mpAsserts[i].dwLine = dwLine;

  memset(&mpAsserts[i].szFileName, 0, 128);
  strncpy(mpAsserts[i].szFileName, pcFileName, 128);

  SaveCache(&chAsserts);
}



void    OutAsserts(void)
{
  InitPushCRC();

  PushLong(dwAsserts);

  uchar i;
  for (i=0; i<16; i++)
  {
    PushInt(mpAsserts[i].iwEvent);
    PushTime(mpAsserts[i].tiEvent);
    PushLong(mpAsserts[i].dwLine);
    Push(mpAsserts[i].szFileName, 128);
  }

  Output(4+sizeof(mpAsserts));
}
