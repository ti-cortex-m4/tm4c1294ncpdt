/*------------------------------------------------------------------------------
CORRECT2.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "correct2.h"


/*
void    ResetCorrect2(void)
{
  boCorrect2 = boFalse;

  memset(&mpcwCorrect2, 0, sizeof(mpcwCorrect2));
  memset(&mpbCorrect2, 0, sizeof(mpbCorrect2));

  cdwCorrect20 = 0;
  cdwCorrect21 = 0;
  cdwCorrect22 = 0;
  cdwCorrect23 = 0;
  cdwCorrect24 = 0;
}
*/

bool    Correct2Disabled(void)
{
  return false; //(boCorrect2 == boTrue);
}

/*
#ifndef MODBUS

bit     SuperUser2(void)
{
  return( (mpbCorrect2[0] == 2) &&
          (mpbCorrect2[1] == 6) &&
          (mpbCorrect2[2] == 1) &&
          (mpbCorrect2[3] == 1) &&
          (mpbCorrect2[4] == 3) &&
          (mpbCorrect2[5] == 7) &&
          (mpbCorrect2[6] == 9) &&
          (mpbCorrect2[7] == 1) );
}


bit     Correct2Allow(void)
{
  cdwCorrect20++;

  PopFar(mpbCorrect2, sizeof(mpbCorrect2));
  mpbCorrect2[0] ^= 0x45;
  mpbCorrect2[1] ^= 0xF6;
  mpbCorrect2[2] ^= 0x57;
  mpbCorrect2[3] ^= 0x27;
  mpbCorrect2[4] ^= 0xE6;
  mpbCorrect2[5] ^= 0x16;
  mpbCorrect2[6] ^= 0xD6;
  mpbCorrect2[7] ^= 0x56;
  mpbCorrect2[8] ^= 0xE6;
  mpbCorrect2[9] ^= 0x47;

  if (boCorrect2 == boFalse) { cdwCorrect21++; return 1; }
  if (SuperUser2()) { cdwCorrect22++; return 1; }

  if (memcmp(mpbPassOne, mpbCorrect2, 10) == 0)
    { cdwCorrect23++; return 1; }
  else
    { cdwCorrect24++; return 0; }
}

#endif
*/

void    Correct2(event  ev)
{
//  uchar i;
//  if ((i = GetCorrectIndex(ev)) == 0) return;
//
//  mpcwCorrect2[0]++;
//  mpcwCorrect2[i]++;
}

/*
#ifndef MODBUS

void    OutCorrect21(void)
{
uchar i;

  InitPushCRC();
  for (i=0; i<100; i++) PushChar(0);

  InitPushCRC();

  PushChar(boCorrect2);
  Push(&mpbCorrect2, sizeof(mpbCorrect2));
  Push(&mpcwCorrect2, sizeof(mpcwCorrect2));

  PushLong(&cdwCorrect20);
  PushLong(&cdwCorrect21);
  PushLong(&cdwCorrect22);
  PushLong(&cdwCorrect23);
  PushLong(&cdwCorrect24);

  Output(100);
}

#endif
*/
