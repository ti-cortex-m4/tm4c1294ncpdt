/*------------------------------------------------------------------------------
DEVICE_U_PLC!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy_spec.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_limits.h"
#include "../../display/display.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../time/delay.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports_common.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
#include "../../digitals/current/current_run.h"
#include "../../digitals/limits.h"
#include "../../special/special.h"
#include "../../hardware/watchdog.h"
#include "../device_k.h"
#include "../device_q.h"
#include "device_u.h"
#include "device_u_plc.h"



void    InitHeaderU_Plc(void)
{
  if (!UseBounds())
    wBaseCurr = 0; // счетчик получасов
  else
  {
    wBaseCurr = (mpcwStartRelCan[ibDig] / bPlcUSize) * bPlcUSize;
    Clear(); sprintf(szLo+1,"начало %04u:%02u",wBaseCurr,(uchar)(wBaseCurr/48 + 1));
    DelayMsg();
  }

  tiDigPrev = tiCurr;

  uchar i = tiDigPrev.bHour*2 + tiDigPrev.bMinute/30;
  i = (i / bPlcUSize) * bPlcUSize;

  tiDigPrev.bHour = i / 2;
  tiDigPrev.bMinute = (i % 2)*30;
}


static void QueryHeaderU_Plc_Inner(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('G');
  PushChar1Bcc('R');
  PushChar1Bcc('A');

  PushLineBcc(ibLineU);

  PushChar1Bcc('(');
  PushChar2Bcc(tiDig.bDay);
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bMonth);
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bYear);
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bHour*2 + tiDig.bMinute/30 + 1);
  PushChar1Bcc('.');
  PushChar2Bcc(bPlcUSize);
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  BccQueryIO(2000, 4+22+1, bPlcUSize);
}


void    QueryHeaderU_Plc(void)
{
  HideCurrTime(1);

  ulong dw = DateToHouIndex(tiDigPrev);
  dw -= wBaseCurr;
  tiDig = HouIndexToDate(dw);


  szHi[10] = 'A' + ibLineU;

  bMaxLineU = GetMaxLineU(ibDig);
  QueryHeaderU_Plc_Inner();
}


void    ReadHeaderU_Plc(void)
{
  InitPop(1);

  uchar i;
  for (i=0; i<bPlcUSize; i++)
  {
    mpdbBuffCanHou[ibLineU][i] = PopDoubleQ()/2;
  }
}


static bool ReadDataU_Plc_Inner(uchar  i)
{
  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if (SearchDefHouIndex(tiDig) == 0) return(1);


  ShowProgressDigHou();

  MakeDataU(i);

  MakeSpecial(tiDig);
  return(MakeStopHou(0));
}


bool    ReadDataU_Plc(void)
{
  uchar i;
  for (i=0; i<bPlcUSize; i++)
  {
    ulong dw = DateToHouIndex(tiDigPrev);

    dw += (bPlcUSize-1);
    dw -= (wBaseCurr + i);

    tiDig = HouIndexToDate(dw);

    if (ReadDataU_Plc_Inner(bPlcUSize-1-i) == 0) return(0);
  }

  wBaseCurr += bPlcUSize;
  if (wBaseCurr > wHOURS) return(0);

  return(1);
}
