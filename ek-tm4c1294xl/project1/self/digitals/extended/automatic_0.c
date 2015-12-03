/*------------------------------------------------------------------------------
AUTOMATIC_0!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../digitals/digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../sensors/device_a.h"
#include "../../sensors/device_b.h"
#include "../../sensors/device_c.h"
#include "../../sensors/device_k.h"
#include "../../sensors/device_p.h"
#include "../../sensors/device_s.h"
#include "../../sensors/automatic_s.h"
#include "../../sensors/device_u.h"
#include "../../console.h"
#include "../../time/timedate.h"
#include "extended_0.h"



#ifndef SKIP_A

time2   ReadTimeDateA_Short(void)
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

time2   ReadTimeDateB_Short(void)
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

time2   ReadTimeDateC_Short(void)
{
  DelayOff();
  QueryTimeC();

  if (RevInput() != SER_GOODCHECK) return GetTime2Error();


  return GetTime2(ReadTimeC(), true);
}

#endif



#ifndef SKIP_D

bool    ReadTimeDateD_Short(void)
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

bool    ReadTimeDateE_Short(void)
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

bool    ReadTimeDateF_Short(void)
{
  QueryBreakF();
  QueryTimeF();

  if (Input() != SER_GOODCHECK) return(0);


  ReadTimeAltF();

  return(1);
}

#endif



#ifndef SKIP_G

bool    ReadTimeDateG_Short(void)
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

bool    ReadTimeDateH_Short(void)
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

bool    ReadTimeDateI_Short(void)
{
  DelayOff();
  QueryTimeI();

  if (TxtInput() != SER_GOODCHECK) return(0);


  ReadTimeAltI();

  return(1);
}

#endif



#ifndef SKIP_K

time2   ReadTimeDateK_Short(void)
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

bool    ReadTimeDateO_Short(void)
{
  DelayOff();
  QueryTimeO();

  if (TxtInput() != SER_GOODCHECK) return(0);


  ReadTimeAltO();

  return(1);
}

#endif



#ifndef SKIP_P

time2   ReadTimeDateP_Short(void)
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

time2   ReadTimeDateQ_Short(void)
{
  return ReadTimeDateK_Short();
}

#endif



#ifndef SKIP_S

time2   ReadTimeDateS_Short(void)
{
  DelayOff();
  QueryTimeS();

  if (InputS() != SER_GOODCHECK) return GetTime2Error();


  return GetTime2(ReadTimeS(), true);
}

#endif



#ifndef SKIP_T

bool    ReadTimeDateT_Short(void)
{
  DelayOff();
  QueryTimeT();

  if (TxtInput() != SER_GOODCHECK) return(0);


  ReadTimeAltT();

  return(1);
}

#endif



#ifndef SKIP_U

time2   ReadTimeDateU_Short(void)
{
  return ReadTimeDateK_Short();
}

#endif



#ifndef SKIP_Z

bool    ReadTimeDateZ_Short(void)
{
  DelayOff();
  QueryTimeZ();

  if (ZetInput() != SER_GOODCHECK) return(0);


  ReadTimeAltZ();

  return(1);
}

#endif



time2   ReadTimeDate_Short(uchar  ibCan)
{
  LoadCurrDigital(ibCan);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_A
    case 15:
    case 1:  return ReadTimeDateA_Short();
#endif

#ifndef SKIP_B
    case 8:
    case 2:  return ReadTimeDateB_Short();

    case 12: return GetTime2(tiCurr, true);
#endif

#ifndef SKIP_C
    case 3:  return ReadTimeDateC_Short();
#endif

#ifndef SKIP_D
    case 4:  return( ReadTimeDateD_Short() );  break;
#endif

#ifndef SKIP_E
    case 7:
    case 5:  return( ReadTimeDateE_Short() );  break;
#endif

#ifndef SKIP_F
    case 6:  return( ReadTimeDateF_Short() );  break;
#endif

#ifndef SKIP_G
    case 9:  return( ReadTimeDateG_Short() );  break;
#endif

#ifndef SKIP_H
    case 10: return( ReadTimeDateH_Short() );  break;
#endif

#ifndef SKIP_I
    case 11: return( ReadTimeDateI_Short() );  break;
#endif

#ifndef SKIP_K
    case 14:
    case 13: return ReadTimeDateK_Short();
#endif

#ifndef SKIP_L
    case 17:
    case 16: tiAlt = tiCurr; return(1);  break;
#endif

#ifndef SKIP_M
    case 18: tiAlt = tiCurr; return(1);  break;
#endif

#ifndef SKIP_N
    case 19: tiAlt = tiCurr; return(1);  break;
#endif

#ifndef SKIP_O
    case 20: return( ReadTimeDateO_Short() );  break;
#endif

#ifndef SKIP_P
    case 21: return ReadTimeDateP_Short();
#endif

#ifndef SKIP_Q
    case 22: return ReadTimeDateQ_Short();
#endif

#ifndef SKIP_R
    case 23: tiAlt = tiCurr; return(1);  break;
#endif

#ifndef SKIP_S
    case 24: return ReadTimeDateS_Short();
#endif

#ifndef SKIP_T
    case 25: return( ReadTimeDateT_Short() );  break;
#endif

#ifndef SKIP_U
    case 26:
    case 28: return ReadTimeDateU_Short();
#endif

    default: return GetTime2Error();
  }
}
