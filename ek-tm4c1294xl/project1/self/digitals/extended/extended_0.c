/*------------------------------------------------------------------------------
EXTENDED_0!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_extended_0.h"
#include "../../realtime/realtime.h"
#include "../../serial/ports.h"
#include "../../digitals/digitals.h"
#include "../../devices/devices.h"
#include "../../time/timedate.h"
#include "../../flash/records.h"
#include "../../nvram/cache.h"
#include "automatic_0.h"
#include "extended_0.h"



//                                         0123456789ABCDEF
static char const       szExtended0[]   = "Проверка связи  ",
                        szGoodLink[]    = " хорошая связь  ",
                        szBadLink[]     = " плохая связь ! ",
                        szLinkError[]   = "    ошибка !    ";



cache const             chExt0Flag = {EXT_0_FLAG, &fExt0Flag, sizeof(bool)};
cache const             chExt0Limit = {EXT_0_LIMIT, &bExt0Limit, sizeof(uchar)};
cache const             chExt0Counter = {EXT_0_COUNTER, &bExt0Counter, sizeof(uchar)};



void    InitExtended0(void) 
{ 
  LoadCacheBool(&chExt0Flag, false);
  LoadCacheChar(&chExt0Limit, 0, 50, 20);
  LoadCacheChar(&chExt0Counter, 0, 50, 20);

  if (bExt0Limit > bExt0Counter)
  {
    bExt0Limit = 20;
    SaveCache(&chExt0Limit);

    bExt0Counter = 20;
    SaveCache(&chExt0Counter);
  }
}



void    ResetExtended0(bool  fFull)
{ 
  fExt0Flag = false;
  SaveCache(&chExt0Flag);

  bExt0Limit = 20;
  SaveCache(&chExt0Limit);

  bExt0Counter = 20;
  SaveCache(&chExt0Counter);

  if (fFull == 1)
  {
    memset(&mpdwExt0RepeatsPH, 0, sizeof(mpdwExt0RepeatsPH));
    memset(&mpdwExt0ErrorsPH, 0, sizeof(mpdwExt0ErrorsPH));
  }
}



bool    MakeExtended0(void)
{
  if (fExt0Flag == false)
    return 1;
  else
  {
    ShowHi(szExtended0); Clear();

    uchar c = 0;

    uchar i;
    for (i=1; i<=bExt0Counter; i++)
    {
      Clear(); sprintf(szLo+4,"%2u из %-2u", i, bExt0Counter);
      Delay(((i % 5) + 1)*100);

      time2 ti2 = ReadTimeDate_Short(ibDig);
      if (ti2.fValid == true)
      {
        mpdwExt0RepeatsPH[ibPort][GetCurrHouIndex()]++;
      }
      else
      {
        ShowLo(szLinkError); DelayInf();

        if (++c > (bExt0Counter - bExt0Limit))
        {
          mpdwExt0ErrorsPH[ibPort][GetCurrHouIndex()]++;

          bRecord = i;
          AddDigRecord(EVE_EXTENDED_0_ERROR);

          ShowLo(szBadLink); DelayMsg();
          return 0;
        }
      }
    }

    ShowLo(szGoodLink); DelayMsg();
    return 1;
  }
}



void    OutExtended0(void)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else
  {
    InitPushPtr();

    PushBool(fExt0Flag);
    PushChar(bExt0Limit);
    PushChar(bExt0Counter);

    uchar p;
    for (p=0; p<bPORTS; p++)
    {
      PushLongBigArray(mpdwExt0RepeatsPH[p], 48);
    }

    for (p=0; p<bPORTS; p++)
    {
      PushLongBigArray(mpdwExt0ErrorsPH[p], 48);
    }

    OutptrOutBuff(3+4*4*48+4*4*48);
  }
}
