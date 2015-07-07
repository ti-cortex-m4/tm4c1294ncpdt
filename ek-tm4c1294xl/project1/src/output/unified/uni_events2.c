/*------------------------------------------------------------------------------
UNI_EVENTS2.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_records.h"
#include "../../memory/mem_flash.h"
#include "../../include/flash.h"
#include "../../include/queries_uni.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/print2.h"
#include "../../flash/records.h"
#include "../../flash/records2.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../time/rtc.h"
#include "../../hardware/watchdog.h"
#include "response_uni.h"
#include "uni_events0.h"
#include "uni_events2.h"



time    PushEventParams(void);


static time             tiT;



void    PushEvents2(uint  iwPage, uchar  ibBlock, uint  wTotal, uint  wIndex, uint  wCount)
{
  x_str("\n\n push events \n");
  x_str("\n page "); x_intdec(iwPage); x_str(" block "); x_bytedec(ibBlock-1); x_str(" total "); x_intdec(wTotal);
  x_str(" index "); x_intdec(wIndex); x_str(" count "); x_intdec(wCount);

  InitPushUni();

  uint c = 0;
  LoadEventsPage(bInBuff6, iwPage);

  uint i;
  for (i=0; i<wTotal; i++)
  {
    tiT = ReadEventBlock(ibBlock);

    x_str(" index "); x_intdec(i);
    if (i+1 >= wIndex)
    { 
      if ((tiT.bDay == bInBuff7) && (tiT.bMonth == bInBuff8) && (tiT.bYear == bInBuff9))
      {
        x_str(" push ");
        PushChar(reCurr.ev);
        tiT = PushEventParams();

        PushChar(tiT.bMinute);
        PushChar(tiT.bHour);
        PushChar(tiT.bDay);
        PushChar(tiT.bMonth);
        PushChar(tiT.bYear);

        if (++c >= wCount)
        {
          x_str("\n success");
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
        x_str("\n underflow");
        Result2_Info(bUNI_BADDATA,7);
        return;
      }
    }
  }

  x_str("\n failure");
  Result2_Info(bUNI_BADDATA,8);
}


void    PushEvents1(uint  wIndex, uint  wCount)
{
uint    iwPage,p;
uchar   ibBlock,b;
uint    wTotal;

  x_str("\n\n get events \n");
  x_bytedec(bInBuff7); x_str("."); x_bytedec(bInBuff8); x_str("."); x_bytedec(bInBuff9);
  x_str(" index "); x_intdec(wIndex); x_str(" count "); x_intdec(wCount);

  bool f = 0;
  p = 0;
  b = 0;
  wTotal = 0;

  for (iwPage=0; iwPage<GetPagesCount(bInBuff6); iwPage++)
  {
    LoadEventsPage(bInBuff6, iwPage);

    for (ibBlock=bRECORD_BLOCK; ibBlock>0; ibBlock--) 
    { 
      tiT = ReadEventBlock(ibBlock);

      if ((tiT.bDay == bInBuff7) && (tiT.bMonth == bInBuff8) && (tiT.bYear == bInBuff9))
      { 
        x_str(" calc ");

        f = 1;
        p = iwPage;
        b = ibBlock;
        wTotal++;
      }
      else
      {
        if (f == 1)
        { 
          x_str("\n success");
          PushEvents2(p, b, wTotal, wIndex, wCount);
          return;
        }
      }
    }
  }

  x_str("\n failure");
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
    x_init();
    SetDelayUni();
    PushEvents1(bInBuffA, bInBuffB);
    x_done();
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
    x_init();
    SetDelayUni();
    PushEvents1(0x100*bInBuffA+bInBuffB, 0x100*bInBuffC+bInBuffD);
    x_done();
  }
}
