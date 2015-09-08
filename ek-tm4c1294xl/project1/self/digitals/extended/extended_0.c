/*------------------------------------------------------------------------------
EXTENDED_0.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_extended_0.h"
#include "../../serial/ports.h"
#include "../../digitals/digitals.h"
#include "../../devices/devices.h"
#include "../../time/timedate.h"
#include "automatic_0.h"
#include "extended_0.h"




//                                         0123456789ABCDEF
static char const       szExtended0[]   = "Проверка связи  ",
                        szGoodLink[]    = " хорошая связь  ",
                        szBadLink[]     = " плохая связь ! ",
                        szLinkError[]   = "    ошибка !    ";



void    InitExtended0(void) 
{ 
  if ((bExt0Limit   <= 0) || (bExt0Limit   > 50) || 
      (bExt0Counter <= 0) || (bExt0Counter > 50) ||
      (bExt0Limit > bExt0Counter))
  {
    bExt0Limit = 20;
    bExt0Counter = 20;
  }
}



void    ResetExtended0(bool  fFull)
{ 
  boExt0Flag = false;

  bExt0Limit = 20;
  bExt0Counter = 20;

  if (fFull == 1)
  {
    memset(&mpdwExt0RepeatsPH, 0, sizeof(mpdwExt0RepeatsPH));
    memset(&mpdwExt0ErrorsPH, 0, sizeof(mpdwExt0ErrorsPH));
  }
}



bool    MakeExtended0(void)
{
uchar i;

  if (boExt0Flag == false)
    return 1;
  else
  {
    ShowHi(szExtended0); Clear();

    i = 0;
    for (x=1; x<=bExt0Counter; x++)
    {
      Clear(); sprintf(szLo+4,"%2bu из %-2bu", x, bExt0Counter); 
      Delay(((x % 5) + 1)*100);

      if (ReadTimeDate_Short(ibDig) == 1)
      {
        mpdwExt0RepeatsPH[ibPort][GetHouIndex()]++;
      }
      else
      {
        ShowLo(szLinkError); DelayInf();

        if (++i > (bExt0Counter - bExt0Limit))
        {
          mpdwExt0ErrorsPH[ibPort][GetHouIndex()]++;
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

    PushChar(boExt0Flag);
    PushChar(bExt0Limit);
    PushChar(bExt0Counter);

    Push(&mpdwExt0RepeatsPH, sizeof(mpdwExt0RepeatsPH));
    Push(&mpdwExt0ErrorsPH, sizeof(mpdwExt0ErrorsPH));

    OutptrOutBuff(3+4*4*48+4*4*48);
  }
}
