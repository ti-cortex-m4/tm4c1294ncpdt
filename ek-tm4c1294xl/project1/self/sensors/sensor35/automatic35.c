/*------------------------------------------------------------------------------
AUTOMATIC_35!C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../memory/mem_profile.h"
//#include "../memory/mem_factors.h"
//#include "../display/display.h"
//#include "../keyboard/keyboard.h"
//#include "../time/delay.h"
//#include "../time/timedate.h"
//#include "../hardware/watchdog.h"
//#include "../kernel/crc_s.h"
//#include "../serial/ports.h"
//#include "../serial/ports2.h"
//#include "../serial/ports_devices.h"
//#include "../serial/input_wrapper.h"
//#include "../devices/devices.h"
//#include "../sensors/unpack_35.h"
//#include "../digitals/digitals.h"
//#include "../digitals/wait_answer.h"
//#include "automatic1.h"
#include "device35.h"
#include "automatic35.h"



#ifndef SKIP_35
/*
void    Query35(uchar  cbIn, uchar  cbOut)
{
  uchar bCrc = MakeCrcSOutBuff(1, cbOut-3);

  InitPush(0);
  PushChar(0xC0);

  uchar i;
  for (i=0; i<cbOut-3; i++) SkipChar();

  PushChar(bCrc);
  PushChar(0xC0);


  for (i=0; i<=cbOut-1; i++)
    mpbOutBuffSave[i] = OutBuff(i);

  uchar j = 0;
  SetOutBuff(j++, 0xC0);
  for (i=1; i<=cbOut-2; i++)
  {
    if (mpbOutBuffSave[i] == 0xC0)
    {
      SetOutBuff(j++, 0xDB);
      SetOutBuff(j++, 0xDC);
    }
    else if (mpbOutBuffSave[i] == 0xDB)
    {
      SetOutBuff(j++, 0xDB);
      SetOutBuff(j++, 0xDD);
    }
    else
    {
      SetOutBuff(j++, mpbOutBuffSave[i]);
    }
  }
  SetOutBuff(j++, 0xC0);


  Query(cbIn,j,true);
}


serial  Input35(void)
{
  InputStart();
  InitWaitAnswer();

  while (1)
  {
    if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWatchdog();
    ShowWaitAnswer(1);
    if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

    if (mpSerial[ibPort] == SER_INPUT_MASTER)
      Decompress35();

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      if (Checksum35() == 0)
      {
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;

      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  return mpSerial[ibPort];
}



bool    QueryConfigS_Full(uchar  bPercent)
{
  uchar i;
  for (i=0; i<MaxRepeat35(); i++)
  {
    DelayOff();
    QueryConfig35();

    if (Input35() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeat35()) return(0);
  ShowPercent(bPercent);

  ReadConfig35();
  return(1);
}


time2   QueryTimeS_Full(uchar  bPercent)
{
  uchar i;
  for (i=0; i<MaxRepeat35(); i++)
  {
    DelayOff();
    QueryTime35();

    if (Input35() == SER_GOODCHECK) break;
    if (fKey == true) return GetTime2Error();
  }

  if (i == MaxRepeat35()) return GetTime2Error();
  ShowPercent(bPercent);

  return GetTime2(ReadTime35(), true);
}


bool    QueryEngDayS_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<MaxRepeat35(); i++)
  {
    DelayOff();
    QueryEngDay35(bTime);

    if (Input35() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeat35()) return(0);
  ShowPercent(bPercent);

  ReadEnergy35();
  return(1);
}


bool    QueryEngMonS_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<MaxRepeat35(); i++)
  {
    DelayOff();
    QueryEngMon35(bTime);

    if (Input35() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeat35()) return(0);
  ShowPercent(bPercent);

  ReadEnergy35();
  return(1);
}



time2   ReadTimeCan35(void)
{
  Clear();

  time2 ti2 = QueryTimeS_Full(50);
  if (ti2.fValid == false) return GetTime2Error();

  tiChannelC = ti2.tiValue;
  mpboChannelsA[0] = true;

  return GetTime2(ti2.tiValue, true);
}


double2 ReadCntCurr35(void)
{
  Clear();

  if (QueryConfigS_Full(50) == 0) return GetDouble2Error();

  if (QueryEngMonS_Full(0, 75) == 0) return GetDouble2Error();

  mpdbChannelsC[0] = (double)mpdwChannelsA[0] / wDividerS;
  mpboChannelsA[0] = true;

  return GetDouble2(mpdbChannelsC[0], true);
}


double2 ReadCntMonCan35(uchar  ibMon)
{
  Clear();

  if (QueryConfigS_Full(25) == 0) return GetDouble2Error();

  time2 ti2 = QueryTimeS_Full(50);
  if (ti2.fValid == false) return GetDouble2Error();
  time ti = ti2.tiValue;

  if (ti.bMonth != ibMon+1)
  {
    if (QueryEngMonS_Full((bMONTHS+ti.bMonth-1-ibMon) % bMONTHS, 75) == 0) return GetDouble2Error();
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
