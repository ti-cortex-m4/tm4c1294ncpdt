/*------------------------------------------------------------------------------
DIAGRAM.C

 График значений счетчиков по получасам за сутки
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_diagram.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_ports.h"
#include "../../realtime/realtime.h"
#include "../../flash/files.h"
#include "../../time/rtc.h"
#include "../../serial/ports.h"
#include "diagram.h"



/*static*/ diagram          dgBuff;



bool    SaveDgrHou(uchar  ibHouTo)
{
  return SaveBuff(DIAGRAM_HHR_VALUES + ibHouTo*DIAGRAM_CAN_PAGES, mpDiagram, sizeof(mpDiagram));
}


bool    LoadDgrHou(uchar  ibHouFrom)
{
  return LoadBuff(DIAGRAM_HHR_VALUES + ibHouFrom*DIAGRAM_CAN_PAGES, mpDiagram, sizeof(mpDiagram));
}


/*
void    NextHouDiagram(void)
{
  LoadDgrHou(iwHardHou);

  memset(&mpDiagram, 0xFF, sizeof(mpDiagram));

  for (ibCan=0; ibCan<16; ibCan++)
  {
    if (GetDigitalDevice(ibCan) == 0)
    {
      reBuffA  = *PGetCanImpAll(mpimAbsCan,ibCan);
      reBuffA *= *PGetCanReal(mpreValueCntHou,ibCan);
      reBuffA += *PGetCanReal(mpreCount,ibCan);

      dgBuff.dbValue = reBuffA;

      tiAlt = *PGetCurrTimeDate();
      dgBuff.stValuef.bSecond = tiAlt.bSecond;
      dgBuff.stValuef.bMinute = tiAlt.bMinute;
      dgBuff.stValuef.bHour   = tiAlt.bHour;

      mpDiagram[ibCan] = dgBuff;
    }
  }

  SaveDgrHou(iwHardHou);
}
*/

void    MakeDiagram(uchar  ibCan, double  db)
{
  LoadDgrHou(iwHardHou);

  diagram vl;
  vl.dbValue = db;

  time ti = *GetCurrTimeDate();
  vl.stValue.bSecond = ti.bSecond;
  vl.stValue.bMinute = ti.bMinute;
  vl.stValue.bHour   = ti.bHour;

  mpDiagram[ibCan] = vl;

  SaveDgrHou(iwHardHou);
}



void    OutDiagram(bool  fDouble)
{
  uint iwHou = GetDayHouIndex(bInBuff6);

  InitPushPtr();
  uint wSize = 0;

  uchar h;
  for (h=0; h<48; h++)
  {
    if (LoadDgrHou(iwHou) == false) { Result(bRES_BADFLASH); return; }

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
      {
        if ((bInBuff6 == 0) && (h > GetCurrHouIndex()))
        {
          if (fDouble)
          {
            PushChar(0xFF);
            PushChar(0xFF);
            PushChar(0xFF);
            PushChar(0xFF);
            PushChar(0xFF);
            PushChar(0xFF);
            PushChar(0xFF);
            PushChar(0xFF);
          }
          else
          {
            PushChar(0xFF);
            PushChar(0xFF);
            PushChar(0xFF);
            PushChar(0xFF);
          }

          wSize += PushChar(0xFF);
          wSize += PushChar(0xFF);
          wSize += PushChar(0xFF);
        }
        else
        {
          diagram vl = mpDiagram[c];

          wSize += PushFloatOrDouble(vl.dbValue, fDouble);

          wSize += PushChar(vl.stValue.bHour);
          wSize += PushChar(vl.stValue.bMinute);
          wSize += PushChar(vl.stValue.bSecond);
        }

        if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
      } 
    }
          
    if (++iwHou >= wHOURS) iwHou = 0;
  }      

  OutptrOutBuff(wSize);
}

