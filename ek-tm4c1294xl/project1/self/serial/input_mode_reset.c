/*------------------------------------------------------------------------------
INPUT_MODE_RESET.C


------------------------------------------------------------------------------*/

#include    "../main.h"
#include    "../nvram/cache.h"
#include    "input_mode_reset.h"



cache const             chInputModeReset = {INPUT_MODE_RESET, &bInputModeReset, sizeof(uchar)};



void    InitInputModeReset(void)
{
  LoadCacheChar(&chInputModeReset, 0);
}


void    ResetInputModeReset(void)
{
  bInputModeReset = 0;
  SaveCache(&chInputModeReset);
}



void    NextHhrInputModeReset(void)
{
  if ((fActive == 0) || (bInputModeReset == 0)) return;
  if (GetHouIndex() % bInputModeReset != 0) return;

  tiInputModeReset = tiCurr;
  dwInputModeReset++;

  if (IsSlave(2)) InputMode2();
  if (IsSlave(3)) InputMode3();
}
