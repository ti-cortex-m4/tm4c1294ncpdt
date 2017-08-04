/*------------------------------------------------------------------------------
UNI_EVENTS2,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_records.h"
#include "../../memory/mem_flash.h"
#include "../../include/flash.h"
#include "../../include/queries_uni.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../time/calendar.h"
#include "response_uni.h"
#include "uni_events0.h"
#include "uni_events2.h"



static time PushEventParams(void)
{
  switch (reCurr.ev)
  {
    case EVE_PREVNEXTTIME2:

    case EVE_PROGRAM_2:
    case EVE_EXT_CORRECT2:
    case EVE_ESC_K:
    case EVE_ESC_k:
    case EVE_INQ_CORRECT1:
    case EVE_INQ_CORRECT2:
    case EVE_INQ_CORRECT4:
      {
        time  ti;
        ti.bSecond = reCurr.mpbBuff[0];
        ti.bMinute = reCurr.mpbBuff[1];
        ti.bHour   = reCurr.mpbBuff[2];
        ti.bDay    = reCurr.mpbBuff[3];
        ti.bMonth  = reCurr.mpbBuff[4];
        ti.bYear   = reCurr.mpbBuff[5];

        combo32 co;
        co.dwBuff = DateToSecIndex(ti);

        PushChar(co.mpbBuff[0]);
        PushChar(co.mpbBuff[1]);
        PushChar(co.mpbBuff[2]);
        PushChar(co.mpbBuff[3]);
      }
      break;

    case 64:
    case 65:
      PushChar(reCurr.mpbBuff[0]+1);
      PushChar(0);
      PushChar(0);
      PushChar(0);
      break;

    case 93:
      PushChar(reCurr.mpbBuff[1]);
      PushChar(reCurr.mpbBuff[2]);
      PushChar(reCurr.mpbBuff[3]);
      PushChar(0);
      break;

    case 94:
      PushChar(reCurr.mpbBuff[1]);
      PushChar(reCurr.mpbBuff[2]);
      PushChar(0);
      PushChar(0);
      break;

    case 98:
      PushChar(reCurr.mpbBuff[0]);
      PushChar(reCurr.mpbBuff[1]);
      PushChar(0);
      PushChar(0);

    case 97:
      PushChar(reCurr.mpbBuff[2]);
      PushChar(reCurr.mpbBuff[3]);
      PushChar(reCurr.mpbBuff[4]);
      PushChar(reCurr.mpbBuff[5]);
      break;

    case 99:
      PushChar(reCurr.mpbBuff[0]);
      PushChar(reCurr.mpbBuff[1]);
      PushChar(reCurr.mpbBuff[2]);
      PushChar(reCurr.mpbBuff[3]);
      break;

    default:
      PushChar(0);
      PushChar(0);
      PushChar(0);
      PushChar(0);
      break;
  }

  return reCurr.ti;
}


static void PushEvents2(uint  iwPage, uchar  ibBlock, uint  wTotal, uint  wIndex, uint  wCount)
{
  MonitorString("\n\n push events \n");
  MonitorString("\n page "); MonitorIntDec(iwPage); MonitorString(" block "); MonitorCharDec(ibBlock-1); MonitorString(" total "); MonitorIntDec(wTotal);
  MonitorString(" index "); MonitorIntDec(wIndex); MonitorString(" count "); MonitorIntDec(wCount);

  InitPushUni();

  uint c = 0;
  LoadEventsPage(bInBuff6, iwPage);

  uint i;
  for (i=0; i<wTotal; i++)
  {
    time ti = ReadEventBlock(ibBlock);

    MonitorString(" index "); MonitorIntDec(i);
    if (i+1 >= wIndex)
    {
      if ((ti.bDay == bInBuff7) && (ti.bMonth == bInBuff8) && (ti.bYear == bInBuff9))
      {
        MonitorString(" push ");
        PushChar(reCurr.ev);
        ti = PushEventParams();

        PushChar(ti.bMinute);
        PushChar(ti.bHour);
        PushChar(ti.bDay);
        PushChar(ti.bMonth);
        PushChar(ti.bYear);

        if (++c >= wCount)
        {
          MonitorString("\n success");
          Output2(wCount*10);
          return;
        }
      }
    }

    if (++ibBlock > bRECORD_BLOCK)
    {
      ibBlock = 1;
      if (iwPage > 0)
      {
        iwPage--;
        LoadEventsPage(bInBuff6, iwPage);
      }
      else
      {
        MonitorString("\n underflow");
        Result2_Info(bUNI_BADDATA,7);
        return;
      }
    }
  }

  MonitorString("\n failure");
  Result2_Info(bUNI_BADDATA,8);
}


static void PushEvents1(uint  wIndex, uint  wCount)
{
uint    iwPage,p;
uchar   ibBlock,b;
uint    wTotal;

  MonitorString("\n\n events ");
  MonitorCharDec(bInBuff7); MonitorString("."); MonitorCharDec(bInBuff8); MonitorString("."); MonitorCharDec(bInBuff9);
  MonitorString(" index "); MonitorIntDec(wIndex); MonitorString(" count "); MonitorIntDec(wCount);

  bool f = 0;
  p = 0;
  b = 0;
  wTotal = 0;

  for (iwPage=0; iwPage<GetPagesCount(bInBuff6); iwPage++)
  {
    LoadEventsPage(bInBuff6, iwPage);

    for (ibBlock=bRECORD_BLOCK; ibBlock>0; ibBlock--)
    {
      time ti = ReadEventBlock(ibBlock);
      if ((ti.bDay == bInBuff7) && (ti.bMonth == bInBuff8) && (ti.bYear == bInBuff9))
      {
        MonitorString(" calc ");

        f = 1;
        p = iwPage;
        b = ibBlock;
        wTotal++;
      }
      else
      {
        if (f == 1)
        {
          MonitorString("\n success");
          PushEvents2(p, b, wTotal, wIndex, wCount);
          return;
        }
      }
    }
  }

  MonitorString("\n failure");
  Result2_Info(bUNI_BADDATA,6);
}


void    GetEventsUni(void)
{
  if ((bInBuff6 < 1) || (bInBuff6 > 3))
    Result2_Info(bUNI_BADDATA,1);
  else if ((bInBuff7 < 1) || (bInBuff7 > 31))
    Result2_Info(bUNI_BADDATA,2);
  else if ((bInBuff8 < 1) || (bInBuff8 > 12))
    Result2_Info(bUNI_BADDATA,3);
  else if (bInBuff9 > 99)
    Result2_Info(bUNI_BADDATA,4);
  else if (bInBuffB == 0)
    Result2_Info(bUNI_BADDATA,5);
  else
  {
    SetDelayUni();
    PushEvents1(bInBuffA, bInBuffB);
  }
}


void    GetEventsUni_Fix(void)
{
  if ((bInBuff6 < 1) || (bInBuff6 > 3))
    Result2_Info(bUNI_BADDATA,1);
  else if ((bInBuff7 < 1) || (bInBuff7 > 31))
    Result2_Info(bUNI_BADDATA,2);
  else if ((bInBuff8 < 1) || (bInBuff8 > 12))
    Result2_Info(bUNI_BADDATA,3);
  else if (bInBuff9 > 99)
    Result2_Info(bUNI_BADDATA,4);
  else if (0x100*bInBuffC+bInBuffD == 0)
    Result2_Info(bUNI_BADDATA,5);
  else
  {
    SetDelayUni();
    PushEvents1(0x100*bInBuffA+bInBuffB, 0x100*bInBuffC+bInBuffD);
  }
}
