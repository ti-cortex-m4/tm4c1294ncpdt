/*------------------------------------------------------------------------------
DIAGRAM_OUT!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_ports.h"
#include "../../realtime/realtime.h"
#include "../../flash/flash.h"
#include "../../flash/files.h"
#include "../../serial/ports.h"
#include "diagram.h"
#include "diagram_out.h"



bool LoadDgrHou(uint  iwHouFrom);



// индекс на первый получас требуемых суток назад
static uint GetDayHouIndex_Diagram(uchar  ibDay)
{
  // индекс на первый получас текущих суток
  uint w = (wHOURS_DIAGRAM+iwHardDgr-GetCurrHouIndex()) % wHOURS_DIAGRAM;

  // индексы на первые получасы суток назад
  uchar i;
  for (i=0; i<ibDay; i++)
  {
    w = (wHOURS_DIAGRAM+w-48) % wHOURS_DIAGRAM;
  }

  // индекс на первый получас требуемых суток
  return w;
}


void    OutDiagram(bool  fDouble)
{
  if (bInBuff6 > wHOURS_DIAGRAM/48) { Result(bRES_BADADDRESS); return; }
  uint iwHhr = GetDayHouIndex_Diagram(bInBuff6);

  InitPushPtr();
  uint wSize = 0;

  uchar h;
  for (h=0; h<48; h++)
  {
    if (LoadDgrHou(iwHhr) == false) { Result(bRES_BADFLASH); return; }

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0)
      {
        if ((bInBuff6 == 0) && (h > GetCurrHouIndex()))
        {
          uchar i;
          for (i=0; i<GetFloatOrDoubleSize(fDouble); i++)
          {
            wSize += PushChar(0xFF);
          }

          wSize += PushChar(0xFF);
          wSize += PushChar(0xFF);
          wSize += PushChar(0xFF);
        }
        else
        {
          diagram vl = mpDiagram[c];

          wSize += PushFloatOrDouble(vl.dbValue, fDouble);

          wSize += PushChar(vl.stValue.bSecond);
          wSize += PushChar(vl.stValue.bMinute);
          wSize += PushChar(vl.stValue.bHour);
        }

        if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
      }
    }

    if (++iwHhr >= wHOURS_DIAGRAM) iwHhr = 0;
  }

  OutptrOutBuff(wSize);
}

