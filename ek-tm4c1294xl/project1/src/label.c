/*------------------------------------------------------------------------------
LABEL,C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "nvram/cache.h"
#include        "label.h"



uchar                   mpbLabelGlobal[0x20];

cache const             chLabelGlobal = {LABEL_GLOBAL, &mpbLabelGlobal, sizeof(mpbLabelGlobal)};



void    SetLabelGlobal(void)
{
  uchar i;
  for (i=0; i<sizeof(mpbLabelGlobal); i++)
  {
    mpbLabelGlobal[i] = i;
  }

  SaveCache(&chLabelGlobal);
}



bool    GetLabelGlobal(void)
{
  LoadCache(&chLabelGlobal);

  uchar i;
  for (i=0; i<sizeof(mpbLabelGlobal); i++)
  {
    if (mpbLabelGlobal[i] != i)
      return false;
  }

  return true;
}



void    BreakLabelGlobal(void)
{
  mpbLabelGlobal[0] = 0xFF;

  SaveCache(&chLabelGlobal);
}
