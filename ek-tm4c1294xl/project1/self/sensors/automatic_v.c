/*------------------------------------------------------------------------------
AUTOMATIC_V!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
#include "../memory/mem_profile.h"
//#include "../memory/mem_factors.h"
//#include "../time/delay.h"
//#include "../time/timedate.h"
//#include "../hardware/watchdog.h"
//#include "../kernel/crc_s.h"
#include "../serial/ports.h"
#include "../serial/ports2.h"
#include "../serial/ports_devices.h"
//#include "../devices/devices.h"
//#include "../devices/decompress_s.h"
//#include "../digitals/digitals.h"
//#include "../digitals/wait_answer.h"
//#include "automatic1.h"
#include "device_v.h"
#include "automatic_v.h"



#ifndef SKIP_V

void    QueryV(uchar  cbIn, uchar  cbOut)
{
  uchar bCrc = MakeCrcVOutBuff(2, cbOut-4);

  InitPush(0);
  PushChar(0x73);
  PushChar(0x55);

  uchar i;
  for (i=0; i<cbOut-4; i++) SkipChar();

  PushChar(bCrc);
  PushChar(0x55);


  for (i=0; i<=cbOut-1; i++)
    mpbOutBuffZ[i] = GetOutBuff(i);

  uchar j = 0;
  SetOutBuff(j++, 0x73);
  SetOutBuff(j++, 0x55);
  for (i=2; i<=cbOut-2; i++)
  {
    if (mpbOutBuffZ[i] == 0x55)
    {
      SetOutBuff(j++, 0x73);
      SetOutBuff(j++, 0x11);
    }
    else if (mpbOutBuffZ[i] == 0x73)
    {
      SetOutBuff(j++, 0x73);
      SetOutBuff(j++, 0x22);
    }
    else
    {
      SetOutBuff(j++, mpbOutBuffZ[i]);
    }
  }
  SetOutBuff(j++, 0x55);


  Query(cbIn,j,true);
}


serial  InputV(void)
{/*
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
*/
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

/*
bool    QueryEngDayS_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEngDayS(bTime);

    if (InputS() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadEnergyS();
  return(1);
}


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

/*
double2 ReadCntCurrS(void)
{
  Clear();

  if (QueryConfigS_Full(50) == 0) return GetDouble2Error();

  if (QueryEngMonS_Full(0, 75) == 0) return GetDouble2Error();

  mpdbChannelsC[0] = (float)mpdwChannelsA[0] / wDividerS;
  mpboChannelsA[0] = true;

  return GetDouble2(mpdbChannelsC[0], true);
}


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

  mpdbChannelsC[0] = (float)mpdwChannelsA[0] / wDividerS;
  mpboChannelsA[0] = true;

  return GetDouble2(mpdbChannelsC[0], true);
}
*/
#endif

