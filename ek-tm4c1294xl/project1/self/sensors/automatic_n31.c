/*------------------------------------------------------------------------------
AUTOMATIC_N31.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
//#include "../memory/mem_factors.h"
#include "../hardware/watchdog.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../serial/monitor.h"
#include "../devices/devices.h"
#include "../sensors/unpack_n31.h"
#include "../digitals/wait_answer.h"
#include "device_n31.h"
#include "automatic1.h"
#include "automatic_n31.h"



#ifndef SKIP_N31

uchar                   mpbCoder[4], ibCoder;



void    InitPushCod(void)
{
  InitPush(0);
  ibCoder = 0;
}


void    PushCharCod(uchar  bT)
{
  PushChar(bT ^ mpbCoder[ibCoder]);
  ibCoder = (ibCoder + 1)%4;
}



void    InitPopCod(void)
{
  InitPop(3);
  ibCoder = 0;
}


uchar   PopCharCod(void)
{
  uchar i = PopChar() ^ mpbCoder[ibCoder];
  ibCoder = (ibCoder + 1)%4;

  return i;
}


void    QueryN31(uint  cwIn, uchar  cbOut)
{
  uchar bCrc = MakeCrcN31OutBuff(1, cbOut-2);

  InitPush(0);
  Skip(cbOut-1);

  PushChar(bCrc);

  Query(cwIn,cbOut,1);
}

/*
bool    ChecksumW(void)
{
  InitPop(1);

  uchar bT = 0;

  uint i;
  for (i=0; i<CountInBuff()-2; i++)
  {
    bT ^= PopChar0Bcc();
  }

//  MonitorString("\n checksum "); MonitorCharHex(bT & 0x7F); MonitorString(" ? "); MonitorCharHex(PopChar0Bcc());

  return ((bT & 0x7F) == PopChar0Bcc());
}
*/

serial  InputN31(void)
{
  InitWaitAnswer();

  while (1)
  {
    if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWatchdog();
    ShowWaitAnswer(1);
    if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

    if (mpSerial[ibPort] == SER_INPUT_MASTER)
    {
      if ((InBuff(0) == 0x7E) && (IndexInBuff() > 3) && (IndexInBuff() == InBuff(1)+4))
        mpSerial[ibPort] = SER_BADLINK;
    }

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      uchar bCrc = MakeCrcN31InBuff(1, CountInBuff()-1);
      if (bCrc == 0)
      {
        UnpackN31();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;

      break;
    }
    else if (mpSerial[ibPort] == SER_BADLINK)
    {
      uchar bCrc = MakeCrcN31InBuff(1, IndexInBuff()-1);
      if (bCrc == 0)
      {
        UnpackN31();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;

      break;
    }
    else if (mpSerial[ibPort] == SER_OVERFLOW) break;
  }

  MonitorIn();
  return mpSerial[ibPort];
}

/*
bit     OpenDeviceG(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryOpenG();

    if (CodInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);


  if (ReadOpenG() == 0) return(0);

  return(1);
}
*/

bool    QueryOpenN31_Full(uchar  bPercent)
{
  Clear();

  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    QueryOpenN31();

    if (InputN31() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (r == bMINORREPEATS) return false;
  ShowPercent(bPercent);

  if (ReadOpenN31() == false) return false;

  return true;
}


time2   QueryTimeN31_Full(uchar  bPercent)
{
  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    QueryTimeN31();

    if (InputN31() == SER_GOODCHECK) break;
    if (fKey == true) return GetTime2Error();
  }

  if (r == bMINORREPEATS) return GetTime2Error();
  ShowPercent(bPercent);

  return GetTime2(ReadTimeN31(), true);
}

/*
double2 QueryKtransW_Full(uchar  bPercent)
{
  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    QueryCloseW();
    QueryKtransW(0);

    if (InputW() == SER_GOODCHECK) break;
    if (fKey == true) return GetDouble2Error();
  }

  if (r == bMINORREPEATS) return GetDouble2Error();
  ShowPercent(bPercent+0);

  InitPop(1);
  double dbKtrans0 = PopDoubleW();


  for (r=0; r<bMINORREPEATS; r++)
  {
    QueryCloseW();
    QueryKtransW(1);

    if (InputW() == SER_GOODCHECK) break;
    if (fKey == true) return GetDouble2Error();
  }

  if (r == bMINORREPEATS) return GetDouble2Error();
  ShowPercent(bPercent+1);

  InitPop(1);
  double dbKtrans1 = PopDoubleW();


  QueryCloseW();

  return GetDouble2(dbKtrans0*dbKtrans1, true);
}
*/

double2 ReadTransN31_Full(void)
{
  if (QueryOpenN31_Full(25) == false) return GetDouble2Error();


  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    DelayOff();
    QueryTransN31();

    if (InputN31() == SER_GOODCHECK) break;
    if (fKey == true) return GetDouble2Error();
  }

  if (r == bMINORREPEATS) return GetDouble2Error();
  ShowPercent(50);


  InitPop(3+4+4+1);

  double dbTransU = PopDoubleN31();
  double dbTransI = PopDoubleN31();

  return GetDouble2(dbTransU*dbTransI, true);
}


bool    AutomaticN31(void)
{
  double2 db2 = ReadTransN31_Full();
  if (db2.fValid == false) return false;

  ShowPercent(100);

  SetupFactors(GetFactors(db2.dbValue, 10000));

  return true;
}



bool    QueryEngAbsN31_Full(uchar  bPercent)
{
  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    QueryEngAbsN31();

    if (InputN31() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (r == bMINORREPEATS) return false;
  ShowPercent(bPercent);

  ReadEngN31();

  return true;
}

/*
bool    QueryEngMonW_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      QueryCloseW();
      QueryEngMonW(i,bTime);

      if (InputW() == SER_GOODCHECK) break;
      if (IndexInBuff() == 10)
      {
        Clear();
        sprintf(szLo+3, "мес€ц -%u ?",bTime);
        Delay(1000);
        return false;
      }
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return false;
    ShowPercent(bPercent+i);

    ReadEngW(i);
  }

  QueryCloseW();

  return true;
}


bool    QueryEngDayW_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      QueryCloseW();
      QueryEngDayW(i,bTime);

      if (InputW() == SER_GOODCHECK) break;
      if (IndexInBuff() == 10)
      {
        Clear();
        sprintf(szLo+3, "сутки -%u ?",bTime);
        Delay(1000);
        return false;
      }
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return false;
    ShowPercent(bPercent+i);

    ReadEngW(i);
  }

  QueryCloseW();

  return true;
}


status  QueryEngMonTrfW_Full(uchar  bTime, uchar  bPercent, uchar  ibTrf)
{
  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      QueryCloseW();
      QueryEngMonTrfW(i,bTime);

      if (InputW() == SER_GOODCHECK) break;
      if (IndexInBuff() == 10)
      {
        Clear();
        sprintf(szLo+3, "мес€ц -%u ?",bTime);
        Delay(1000);
        return ST_NOTPRESENTED;
      }
      if (fKey == true) return ST_OK;
    }

    if (r == bMINORREPEATS) return ST_OK;
    ShowPercent(bPercent+i);

    ReadEngTrfW(i,ibTrf);
  }

  QueryCloseW();

  return ST_OK;
}
*/
/*
bit     ReadTimeDateG(void)
{
uchar   i;

  Clear();
  if (OpenDeviceG() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeG();

    if (CodInput() != SER_GOODCHECK)
      continue;
    else
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);

  ReadTimeAltG();


  tiChannelC = tiAlt;
  for (i=0; i<6; i++) mpboChannelsA[i] = boTrue;

  return(1);
}
*/
time2   ReadTimeCanN31(void)
{
  if (QueryOpenN31_Full(25) == 0) GetTime2Error();

  time2 ti2 = QueryTimeN31_Full(50);
  if (ti2.fValid == false) return GetTime2Error();


  tiChannelC = ti2.tiValue;

  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    mpboChannelsA[i] = true;
  }

  return GetTime2(ti2.tiValue, true);
}



double2 ReadCntCurrN31(void)
{
  if (QueryOpenN31_Full(25) == 0) GetDouble2Error();

  if (QueryEngAbsN31_Full(50) == 0) return GetDouble2Error();


//  uchar i;
//  for (i=0; i<MAX_LINE_N31; i++)
//  {
//    mpdbChannelsC[i] *= dbTrans;
//    mpboChannelsA[i] = true;
//  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}

/*
double2 ReadCntMonCanW(uchar  ibMon)
{
  Clear();

  double2 db2 = QueryKtransW_Full(25);
  if (db2.fValid == false) return GetDouble2Error();
  double dbTrans = db2.dbValue;


  time2 ti2 = QueryTimeW_Full(50);
  if (ti2.fValid == false) return GetDouble2Error();
  time ti = ti2.tiValue;

  if (ti.bMonth != ibMon+1)
  {
    uchar m = (12 + ti.bMonth - (ibMon+1) - 1) % 12;
    if (QueryEngMonW_Full(m, 75) == 0) return GetDouble2Error();
  }
  else
  {
    if (QueryEngDayW_Full(0, 75) == 0) return GetDouble2Error();
  }


  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}


status  ReadCntMonCanTariffW(uchar  ibMon, uchar  ibTrf) // на начало мес€ца
{
  Clear();

  double2 db2 = QueryKtransW_Full(25);
  if (db2.fValid == false) return ST_BADDIGITAL;
  double dbTrans = db2.dbValue;


  time2 ti2 = QueryTimeW_Full(50);
  if (ti2.fValid == false) return ST_BADDIGITAL;
  time ti = ti2.tiValue;


  uchar m = (12 + ti.bMonth - (ibMon+1)) % 12;
  status st = QueryEngMonTrfW_Full(m, 75+ibTrf, ibTrf);
  if (st != ST_OK) return st;


  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return ST_OK;
}
*/
#endif
