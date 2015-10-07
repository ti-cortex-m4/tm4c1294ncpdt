/*------------------------------------------------------------------------------
AUTOMATIC_V!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
#include "../memory/mem_profile.h"
//#include "../memory/mem_factors.h"
//#include "../time/delay.h"
//#include "../time/timedate.h"
#include "../hardware/watchdog.h"
#include "../kernel/crc_v.h"
#include "../serial/ports.h"
#include "../serial/ports2.h"
#include "../serial/ports_devices.h"
//#include "../devices/devices.h"
#include "../devices/decompress_v.h"
//#include "../digitals/digitals.h"
#include "../digitals/wait_answer.h"
//#include "automatic1.h"
#include "device_v.h"
#include "automatic_v.h"



#ifndef SKIP_V

void    QueryV(uchar  cbIn, uchar  cbOut)
{
  InitPush(cbOut-2);
  PushChar(MakeCrcVOutBuff(2, cbOut-4));


  uchar i;
  for (i=0; i<=cbOut-2; i++)
    mpbOutBuffSave[i] = OutBuff(i);

  uchar j = 0;
  SetOutBuff(j++, 0x73);
  SetOutBuff(j++, 0x55);

  for (i=2; i<=cbOut-2; i++)
  {
    if (mpbOutBuffSave[i] == 0x55)
    {
      SetOutBuff(j++, 0x73);
      SetOutBuff(j++, 0x11);
    }
    else if (mpbOutBuffSave[i] == 0x73)
    {
      SetOutBuff(j++, 0x73);
      SetOutBuff(j++, 0x22);
    }
    else
    {
      SetOutBuff(j++, mpbOutBuffSave[i]);
    }
  }
  SetOutBuff(j++, 0x55);

  Query(cbIn,j,true);
}


serial  InputV(void)
{
  InitWaitAnswer();

  while (1)
  {
    if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWatchdog();
    ShowWaitAnswer(1);
    if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

    if (mpSerial[ibPort] == SER_INPUT_MASTER)
      DecompressV();

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      if (ChecksumV() == 0)
        mpSerial[ibPort] = SER_GOODCHECK;
      else
        mpSerial[ibPort] = SER_BADCHECK;

      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  return mpSerial[ibPort];
}


/*
bool    QueryConfigS_Full(uchar  bPercent)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryConfigS();

    if (InputS() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadConfigS();
  return(1);
}
*/

time2   QueryTimeV_Full(uchar  bPercent)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeV();

    if (InputV() == SER_GOODCHECK) break;
    if (fKey == true) return GetTime2Error();
  }

  if (i == bMINORREPEATS) return GetTime2Error();
  ShowPercent(bPercent);

  return GetTime2(ReadTimeV(), true);
}


bool    QueryEngAbsV_Full(uchar  bPercent)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEngAbsV();

    if (InputV() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadEnergyV();
  return(1);
}

/*
bool    QueryEngMonS_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEngMonS(bTime);

    if (InputS() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadEnergyS();
  return(1);
}
*/


time2   ReadTimeCanV(void)
{
  Clear();

  time2 ti2 = QueryTimeV_Full(50);
  if (ti2.fValid == false) return GetTime2Error();

  tiChannelC = ti2.tiValue;
  mpboChannelsA[0] = true;

  return GetTime2(ti2.tiValue, true);
}


double2 ReadCntCurrV(void)
{
  Clear();

//  if (QueryConfigS_Full(50) == 0) return GetDouble2Error();

  if (QueryEngAbsV_Full(75) == 0) return GetDouble2Error();

  mpdbChannelsC[0] = (double)mpdwChannelsA[0]/* / wDividerS*/;
  mpboChannelsA[0] = true;

  return GetDouble2(mpdbChannelsC[0], true);
}

/*
double2 ReadCntMonCanS(uchar  ibMonth)
{
  Clear();

  if (QueryConfigS_Full(25) == 0) return GetDouble2Error();

  time2 ti2 = QueryTimeS_Full(50);
  if (ti2.fValid == false) return GetDouble2Error();
  time ti = ti2.tiValue;

  if (ti.bMonth != ibMonth+1)
  {
    if (QueryEngMonS_Full((bMONTHS+ti.bMonth-1-ibMonth) % bMONTHS, 75) == 0) return GetDouble2Error();
  }
  else
  {
    if (QueryEngDayS_Full(1, 75) == 0) return GetDouble2Error();
  }

  mpdbChannelsC[0] = (double)mpdwChannelsA[0] / wDividerS;
  mpboChannelsA[0] = true;

  return GetDouble2(mpdbChannelsC[0], true);
}
*/
#endif

