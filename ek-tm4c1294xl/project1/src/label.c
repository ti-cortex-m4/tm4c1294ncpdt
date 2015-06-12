/*------------------------------------------------------------------------------
LABEL.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "nvram/cache.h"
#include        "label.h"



static uchar            mpbLabel[0x20];


cache const             chLabel = {LABEL, &mpbLabel, sizeof(mpbLabel)};



void    SetLabel(void)
{
  uchar i;
  for (i=0; i<sizeof(mpbLabel); i++)
  {
    mpbLabel[i] = i;
  }

  SaveCache(&chLabel);
}



bool    GetLabel(void)
{
  uchar i;
  for (i=0; i<sizeof(mpbLabel); i++)
  {
    if (mpbLabel[i] != i)
      return false;
  }

  return true;
}



void    BreakLabel(void)
{
  mpbLabel[0] = 0xFF;

  SaveCache(&chLabel);
}
