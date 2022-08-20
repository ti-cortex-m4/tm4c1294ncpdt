/*------------------------------------------------------------------------------
AUTOMATIC_0!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../digitals/digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../sensors/device_a.h"
#include "../../sensors/sensor2/device2.h"
#include "../../sensors/sensor3/device_c.h"
#include "../../sensors/device_k.h"
#include "../../sensors/sensor21/input_p.h"
#include "../../sensors/sensor21/device_p.h"
#include "../../sensors/sensor24/device_s.h"
#include "../../sensors/sensor24/automatic_s.h"
#include "../../sensors/sensor26/device_u.h"
#include "../../sensors/device_v.h"
#include "../../sensors/automatic_v.h"
#include "../../sensors/device_w.h"
#include "../../sensors/automatic_w.h"
#include "../../sensors/sensor31/device31.h"
#include "../../sensors/sensor31/automatic31.h"
#include "../../sensors/sensor32/device32.h"
#include "../../sensors/sensor32/automatic32.h"
#include "../../sensors/sensor33/device33.h"
#include "../../sensors/sensor33/automatic33.h"
#include "../../sensors/sensor34/time34.h"
#include "../../sensors/sensor35/automatic35.h"
#include "../../sensors/sensor36/automatic36.h"
#include "../../sensors/sensor39/automatic_get_time_39.h"
#include "../../console.h"
#include "../../time/timedate.h"
#include "automatic_0.h"



#ifndef SKIP_A

time2   ReadTimeCanA_Short(void)
{
  DelayOff();
  QueryOpenA();

  if (Input() != SER_GOODCHECK) return GetTime2Error();


  DelayOff();
  QueryTimeA();

  if (Input() != SER_GOODCHECK) return GetTime2Error();


  return GetTime2(ReadTimeA(), true);
}

#endif



#ifndef SKIP_B

time2   ReadTimeCanB_Short(void)
{
  DelayOff();
  QueryOpenB();

  if (Input() != SER_GOODCHECK) return GetTime2Error();


  DelayOff();
  QueryTimeB();

  if (Input() != SER_GOODCHECK) return GetTime2Error();


  return GetTime2(ReadTimeB(), true);
}

#endif



#ifndef SKIP_C

time2   ReadTimeCanC_Short(void)
{
  DelayOff();
  QueryTimeC();

  if (RevInput() != SER_GOODCHECK) return GetTime2Error();


  return GetTime2(ReadTimeC(), true);
}

#endif



#ifndef SKIP_D

bool    ReadTimeCanD_Short(void)
{
  DelayOff();
  QueryOpenD();

  if (ExtInput() != SER_GOODCHECK) return(0);


  DelayOff();
  QueryPasswordD();

  if (ExtInput() != SER_GOODCHECK) return(0);

  if (InBuff(2) != 0) return(0);


  DelayOff();
  QueryTimeD();

  if (ExtInput() != SER_GOODCHECK) return(0);


  ReadTimeD();

  QueryCloseD(0);

  return(1);
}

#endif



#ifndef SKIP_E

bool    ReadTimeCanE_Short(void)
{
  if (diCurr.bAddress <= 16)
  {
    QueryBreakE();

    InitPush();
    PushChar(0x1B);
    PushChar('0'+diCurr.bAddress);
    Query(1+1, 2, 1);

    if (EscInput() != SER_GOODCHECK) return(0);
  }
  else return(0);


  InitPush();
  PushChar(0x1B);
  PushChar('T');
  Query(6+1, 2, 1);

  if (EscInput() != SER_GOODCHECK) return(0);


  ReadTimeAltE();

  return(1);
}

#endif



#ifndef SKIP_F

bool    ReadTimeCanF_Short(void)
{
  QueryBreakF();
  QueryTimeF();

  if (Input() != SER_GOODCHECK) return(0);


  ReadTimeAltF();

  return(1);
}

#endif



#ifndef SKIP_G

bool    ReadTimeCanG_Short(void)
{
  QueryOpenG();

  if (CodInput() != SER_GOODCHECK) return(0);

  if (ReadOpenG() == 0) return(0);


  DelayOff();
  QueryTimeG();

  if (CodInput() != SER_GOODCHECK) return(0);


  ReadTimeAltG();

  return(1);
}

#endif



#ifndef SKIP_H

bool    ReadTimeCanH_Short(void)
{
  QueryOpenH();

  if (CodInput() != SER_GOODCHECK) return(0);

  if (ReadOpenH() == 0) return(0);


  DelayOff();
  QueryTimeH();

  if (CodInput() != SER_GOODCHECK) return(0);


  ReadTimeAltH();

  return(1);
}

#endif



#ifndef SKIP_I

bool    ReadTimeCanI_Short(void)
{
  DelayOff();
  QueryTimeI();

  if (TxtInput() != SER_GOODCHECK) return(0);


  ReadTimeAltI();

  return(1);
}

#endif



#ifndef SKIP_K

time2   ReadTimeCanK_Short(void)
{
  QueryCloseK();
  QueryTimeK();

  if (BccInput() != SER_GOODCHECK) return GetTime2Error();

  time ti = ReadTimeK();


  QueryCloseK();
  QueryDateK();

  if (BccInput() != SER_GOODCHECK) return GetTime2Error();

  ti = ReadDateK(ti);


  QueryCloseK();

  return GetTime2(ti, true);
}

#endif



#ifndef SKIP_O

bool    ReadTimeCanO_Short(void)
{
  DelayOff();
  QueryTimeO();

  if (TxtInput() != SER_GOODCHECK) return(0);


  ReadTimeAltO();

  return(1);
}

#endif



#ifndef SKIP_P

time2   ReadTimeCanP_Short(void)
{
  QueryOpenP();

  if (ElsInput(1) != SER_GOODCHECK) return GetTime2Error();


  DelayOff();
  QueryModeP();

  if (ElsInput(0) != SER_GOODCHECK) return GetTime2Error();


  DelayOff();
  QueryPasswordP();

  if (ElsInput(2) != SER_GOODCHECK) return GetTime2Error();


  DelayOff();
  QueryTimeP();

  if (ElsInput(0) != SER_GOODCHECK) return GetTime2Error();


  QueryCloseP();

  return GetTime2(ReadTimeP(), true);
}

#endif



#ifndef SKIP_Q

time2   ReadTimeCanQ_Short(void)
{
  return ReadTimeCanK_Short();
}

#endif



#ifndef SKIP_S

time2   ReadTimeCanS_Short(void)
{
  DelayOff();
  QueryTimeS();

  if (InputS() != SER_GOODCHECK) return GetTime2Error();


  return GetTime2(ReadTimeS(), true);
}

#endif



#ifndef SKIP_T

bool    ReadTimeCanT_Short(void)
{
  DelayOff();
  QueryTimeT();

  if (TxtInput() != SER_GOODCHECK) return(0);


  ReadTimeAltT();

  return(1);
}

#endif



#ifndef SKIP_U

time2   ReadTimeCanU_Short(void)
{
  return ReadTimeCanK_Short();
}

#endif



#ifndef SKIP_V

time2   ReadTimeCanV_Short(void)
{
  DelayOff();
  QueryTimeV();

  if (InputV() != SER_GOODCHECK) return GetTime2Error();


  return GetTime2(ReadTimeV(), true);
}

#endif


#ifndef SKIP_W

time2   ReadTimeCanW_Short(void)
{
  QueryCloseW();
  QueryTimeW();

  if (InputW() != SER_GOODCHECK) return GetTime2Error();

  QueryCloseW();

  return GetTime2(ReadTimeW(), true);
}

#endif


#ifndef SKIP_31

time2   ReadTimeCan31_Short(void)
{
  DelayOff();
  QueryOpen31();

  if (Input31() != SER_GOODCHECK) return GetTime2Error();

  if (ReadOpen31() == false) return GetTime2Error();

  DelayOff();
  QueryTime31();

  if (Input31() != SER_GOODCHECK) return GetTime2Error();

  return GetTime2(ReadTime31(), true);
}

#endif


#ifndef SKIP_32

time2   ReadTimeCan32_Short(void)
{
  DelayOff();
  QueryOpen32();

  if (Input32() != SER_GOODCHECK) return GetTime2Error();

  if (ReadOpen32() == false) return GetTime2Error();

  DelayOff();
  QueryTime32();

  if (Input32() != SER_GOODCHECK) return GetTime2Error();

  return GetTime2(ReadTime32(), true);
}

#endif


#ifndef SKIP_33

time2   ReadTimeCan33_Short(void)
{
  DelayOff();
  QueryOpen33();

  if (Input33() != SER_GOODCHECK) return GetTime2Error();

  if (ReadOpen33() == false) return GetTime2Error();

  DelayOff();
  QueryTime33();

  if (Input33() != SER_GOODCHECK) return GetTime2Error();

  return GetTime2(ReadTime33(), true);
}

#endif


#ifndef SKIP_34

time2   ReadTimeCan34_Short(void)
{
  DelayOff();
  QueryTime34();

  if (Input() != SER_GOODCHECK) return GetTime2Error();

  return GetTime2(ReadTime34(), true);
}

#endif



time2   ReadTimeCan_Short(uchar  ibCan)
{
  LoadCurrDigital(ibCan);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_A
    case 15:
    case 1:  return ReadTimeCanA_Short();
#endif

#ifndef SKIP_B
    case 8:
    case 2:  return ReadTimeCanB_Short();

    case 12: return GetTime2(tiCurr, true);
#endif

#ifndef SKIP_C
    case 3:  return ReadTimeCanC_Short();
#endif

#ifndef SKIP_D
    case 4:  return( ReadTimeCanD_Short() );  break;
#endif

#ifndef SKIP_E
    case 7:
    case 5:  return( ReadTimeCanE_Short() );  break;
#endif

#ifndef SKIP_F
    case 6:  return( ReadTimeCanF_Short() );  break;
#endif

#ifndef SKIP_G
    case 9:  return( ReadTimeCanG_Short() );  break;
#endif

#ifndef SKIP_H
    case 10: return( ReadTimeCanH_Short() );  break;
#endif

#ifndef SKIP_I
    case 11: return( ReadTimeCanI_Short() );  break;
#endif

#ifndef SKIP_K
    case 14:
    case 13: return ReadTimeCanK_Short();
#endif

#ifndef SKIP_L
    case 17:
    case 16: tiAlt = tiCurr; return(1);  break;
#endif

#ifndef SKIP_M
    case 18: tiAlt = tiCurr; return(1);  break;
#endif

#ifndef SKIP_N
    case 19: return GetTime2(tiCurr, true);
#endif

#ifndef SKIP_O
    case 20: return( ReadTimeCanO_Short() );  break;
#endif

#ifndef SKIP_P
    case 21: return ReadTimeCanP_Short();
#endif

#ifndef SKIP_Q
    case 22: return ReadTimeCanQ_Short();
#endif

#ifndef SKIP_R
    case 23: tiAlt = tiCurr; return(1);  break;
#endif

#ifndef SKIP_S
    case 24: return ReadTimeCanS_Short();
#endif

#ifndef SKIP_T
    case 25: return( ReadTimeCanT_Short() );  break;
#endif

#ifndef SKIP_U
    case 26:
    case 28: return ReadTimeCanU_Short();
#endif

#ifndef SKIP_V
    case 27: return ReadTimeCanV_Short();
#endif

#ifndef SKIP_W
    case 29:
    case 30: return ReadTimeCanW_Short();
#endif

#ifndef SKIP_31
    case 31: return ReadTimeCan31_Short();
#endif

#ifndef SKIP_32
    case 32: return ReadTimeCan32_Short();
#endif

#ifndef SKIP_33
    case 33: return ReadTimeCan33_Short();
#endif

#ifndef SKIP_34
    case 34: return ReadTimeCan34_Short();
#endif

#ifndef SKIP_35
    case 35: return ReadTimeCan35_Short();
#endif

#ifndef SKIP_36
    case 36:
    case 37: return ReadTimeCan36_Short();
#endif

#ifndef SKIP_39
    case 39: return ReadTimeCan39_Short();
#endif

    default: return GetTime2Error();
  }
}
