/*------------------------------------------------------------------------------
AUTOMATIC36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../devices/devices.h"
//#include "../../sensors/automatic1.h"
#include "../../serial/monitor.h" //
#include "../../digitals/digitals.h"
#include "device36.h"
#include "device36_2.h"
#include "io36.h"
#include "monitor36.h"
#include "buffers36.h"
#include "automatic36_2.h"



bool    fOk;


double2 ReadCntMonCan36_1(void)
{
  Query36_DISC();
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  Query36_SNRM();
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 10; // TODO 0

  Query36_Open2(bNS, bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();
  DelayOff();

  bNR++;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();


/*
  bNS++;
  QueryTime36(bNS, bNR, bInvokeId++);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();
  time ti = ReadTime36();
  DelayOff();

  bNR++;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();
*/


  bNS++; MonitorString("\n\n step1");
  QueryEngCurrDay36(bNS, bNR, bInvokeId++);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
//  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();
//  PrintInBuff(22, IndexInBuff()-22-3); // input...
  DelayOff();

  bNR++; MonitorString("\n\n step2");
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
//  if (!ValidateSframe(bNR)) return GetDouble2Error();
//  PrintInBuff(8, IndexInBuff()-8-3); // input...
  DelayOff();

  bNR++; MonitorString("\n\n step3");
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
//  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();



  uchar bBlockNumber = 1;



  bNS++; MonitorString("\n\n step4");
  QueryNextBlock36(bNS, bNR, bInvokeId++, bBlockNumber);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
//  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();
//  PrintInBuff(22, IndexInBuff()-22-3); // input...
  DelayOff();

  bNR++; MonitorString("\n\n step5");
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
//  if (!ValidateSframe(bNR)) return GetDouble2Error();
//  PrintInBuff(8, IndexInBuff()-8-3); // input...
  DelayOff();

  bNR++; MonitorString("\n\n step6");
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
//  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();



  uint64_t ddw = ReadEngMon36();
  mpdwChannelsA[0] = ddw % 0x100000000;
  mpdbChannelsC[0] = (double)mpdwChannelsA[0] / 1000;
  mpboChannelsA[0] = true;

  DelayOff();

  bNR++;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();

  Query36_DISC(); // TODO always close
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
/*
  Clear();

  if (QueryConfig36_Full(25) == 0) return GetDouble2Error();

  time2 ti2 = QueryTime36_Full(50);
  if (ti2.fValid == false) return GetDouble2Error();
  time ti = ti2.tiValue;

  if (ti.bMonth != ibMon+1)
  {
    if (QueryEngMon36_Full((bMONTHS+ti.bMonth-1-ibMon) % bMONTHS, 75) == 0) return GetDouble2Error();
  }
  else
  {
    if (QueryEngDay36_Full(1, 75) == 0) return GetDouble2Error();
  }

  mpdbChannelsC[0] = (double)mpdwChannelsA[0] / GetDivider36();
  mpboChannelsA[0] = true;

  return GetDouble2(mpdbChannelsC[0], true);
*/
}

uchar   z(uchar i) {
  if ((i >= '0') && (i <= '9'))
    return i - '0';

  if ((i >= 'A') && (i <= 'F'))
    return i - 'A' + 0xA;

  return 0;
}

bool    x(const char  *psz)
{
  if (!fOk)
    return true;


  InitPush(0);
  uint wSize = 0;


  while (true)
  {
    if (!*psz) break;

    uchar a = *psz++;

    if (!*psz) {
      fOk = false; return true;
    }
    uchar b = *psz++;

    uchar d= z(a);
    uchar e= z(b);
    uchar f= z(a) << 4;
    uchar g= (z(a) << 4) | z(b);

    PushChar((z(a) << 4) | z(b));
    wSize++;

    if (!*psz) {
      break;
    }
    uchar c = *psz++;
    if (c != ' ') {
      fOk = false; return true;
    }

  }

  Query36(1000,wSize);

  fOk = true; return !fOk;
}


schar   y(void)
{

//  uchar bNR = 0;

  fOk = true;
  StartBuffer1();
/*
  if (x("7E A0 20 03 03 93 FE C9 81 80 14 05 02 00 80 06 02 00 80 07 04 00 00 00 01 08 04 00 00 00 01 CE 6A 7E")) return 1;
  if (Input36() != SER_GOODCHECK) return -1;
  DelayOff();
//  7E A0 1E 03 03 73 40 CC 81 80 12 05 01 80 06 01 80 07 04 00 00 00 01 08 04 00 00 00 01 53 3B 7E

  if (x("7E A0 44 03 03 10 65 94 E6 E6 00 60 36 A1 09 06 07 60 85 74 05 08 01 01 8A 02 07 80 8B 07 60 85 74 05 08 02 01 AC 0A 80 08 78 52 77 50 62 45 78 46 BE 10 04 0E 01 00 00 00 06 5F 1F 04 00 00 7E 1F 01 00 AF DF 7E")) return 2;
  if (Input36() != SER_GOODCHECK) return -2;
  DelayOff();
//  7E A0 37 03 03 30 EF CA E6 E7 00 61 29 A1 09 06 07 60 85 74 05 08 01 01 A2 03 02 01 00 A3 05 A1 03 02 01 00 BE 10 04 0E 08 00 06 5F 1F 04 00 00 18 1D 01 80 00 07 A1 DC 7E

  if (x("7E A0 07 03 03 31 94 97 7E")) return 3;
  if (Input36() != SER_GOODCHECK) return -3;
  DelayOff();
//  7E A0 07 03 03 31 94 97 7E

  if (x("7E A0 19 03 03 32 EC C8 E6 E6 00 C0 01 87 00 01 00 00 60 01 00 FF 02 00 FB 98 7E")) return 4;
  if (Input36() != SER_GOODCHECK) return -4;
  DelayOff();
//  7E A0 22 03 03 52 0D 27 E6 E7 00 C4 01 87 00 09 10 41 50 41 6E 6F 72 33 30 39 34 34 38 31 31 33 30 27 A3 7E

  if (x("7E A0 07 03 03 51 92 F4 7E")) return 5;
  if (Input36() != SER_GOODCHECK) return -5;
  DelayOff();
//  7E A0 07 03 03 51 92 F4 7E

  if (x("7E A0 19 03 03 54 DC CE E6 E6 00 C0 01 88 00 08 00 00 01 00 00 FF 02 00 5E 3E 7E")) return 6;
  if (Input36() != SER_GOODCHECK) return -6;
  DelayOff();
//  7E A0 1E 03 03 74 FF B8 E6 E7 00 C4 01 88 00 09 0C 07 E4 05 09 06 0E 1A 0F FF 00 B4 00 0A 05 7E

  if (x("7E A0 07 03 03 71 90 D5 7E")) return 7;
  if (Input36() != SER_GOODCHECK) return -7;
  DelayOff();
//  7E A0 07 03 03 71 90 D5 7E

  if (x("7E A0 19 03 03 76 CC CC E6 E6 00 C0 01 89 00 01 00 00 60 0E 00 FF 02 00 DA BB 7E")) return 8;
  if (Input36() != SER_GOODCHECK) return -8;
  DelayOff();
//  7E A0 12 03 03 96 D7 EB E6 E7 00 C4 01 89 00 11 01 FD AF 7E

  if (x("7E A0 07 03 03 91 9E 32 7E")) return 9;
  if (Input36() != SER_GOODCHECK) return -9;
  DelayOff();
//  7E A0 07 03 03 91 9E 32 7E

  if (x("7E A0 19 03 03 98 BC C2 E6 E6 00 C0 01 8A 00 07 01 00 63 01 00 FF 04 00 98 52 7E")) return 10;
  if (Input36() != SER_GOODCHECK) return -10;
  DelayOff();
//  7E A0 15 03 03 B8 8A 74 E6 E7 00 C4 01 8A 00 06 00 00 07 08 B9 68 7E

  if (x("7E A0 07 03 03 B1 9C 13 7E")) return 11;
  if (Input36() != SER_GOODCHECK) return -11;
  DelayOff();
//  7E A0 07 03 03 B1 9C 13 7E

  if (x("7E A0 19 03 03 BA AC C0 E6 E6 00 C0 01 8B 00 07 01 00 63 01 00 FF 07 00 61 2D 7E")) return 12;
  if (Input36() != SER_GOODCHECK) return -12;
  DelayOff();
//  7E A0 15 03 03 DA 9E 34 E6 E7 00 C4 01 8B 00 06 00 00 01 8E 82 42 7E

  if (x("7E A0 07 03 03 D1 9A 70 7E")) return 13;
  if (Input36() != SER_GOODCHECK) return -13;
  DelayOff();
//  7E A0 07 03 03 D1 9A 70 7E

  if (x("7E A0 19 03 03 DC 9C C6 E6 E6 00 C0 01 8C 00 07 01 00 63 01 00 FF 08 00 4F 0E 7E")) return 14;
  if (Input36() != SER_GOODCHECK) return -14;
  DelayOff();
//  7E A0 15 03 03 FC AA 70 E6 E7 00 C4 01 8C 00 06 00 00 33 95 DA AE 7E

  if (x("7E A0 07 03 03 F1 98 51 7E")) return 15;
  if (Input36() != SER_GOODCHECK) return -15;
  DelayOff();
//  7E A0 07 03 03 F1 98 51 7E

  if (x("7E A0 19 03 03 FE 8C C4 E6 E6 00 C0 01 8D 00 07 01 00 63 01 00 FF 03 00 76 BF 7E")) return 16;
  if (Input36() != SER_GOODCHECK) return -16;
  DelayOff();
//  7E A8 89 03 03 1E 6D 97 E6 E7 00 C4 01 8D 00 01 08 02 04 12 00 08 09 06 00 00 01 00 00 FF 0F 02 12 00 00 02 04 12 00 01 09 06 00 00 60 0A 01 FF 0F 02 12 00 00 02 04 12 00 03 09 06 01 00 0F 08 00 FF 0F 02 12 00 00 02 04 12 00 03 09 06 01 00 0F 08 01 FF 0F 02 12 00 00 02 04 12 00 03 09 06 01 00 0F 08 02 FF 0F 02 12 00 00 02 04 12 00 03 09 06 01 00 0F 08 03 FF 0F 02 12 00 00 02 04 12 00 03 09 06 01 00 0F 08 35 E3 7E

  if (x("7E A0 07 03 03 11 96 B6 7E")) return 17;
  if (Input36() != SER_GOODCHECK) return -17;
  DelayOff();
//  7E A0 22 03 03 10 1B 46 04 FF 0F 02 12 00 00 02 04 12 00 01 09 06 00 00 80 01 00 FF 0F 02 12 00 00 EB 7D 7E

  if (x("7E A0 07 03 03 31 94 97 7E")) return 18;
  if (Input36() != SER_GOODCHECK) return -18;
  DelayOff();
*/
  Query36_DISC();
  if (Input36() != SER_GOODCHECK) return -15;//GetDouble2Error();
  DelayOff();

  Query36_SNRM();
  if (Input36() != SER_GOODCHECK) return -16;//GetDouble2Error();
  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;

  Query36_Open2(bNS, bNR);
  if (Input36() != SER_GOODCHECK) return -17;//GetDouble2Error();
//  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();
  DelayOff();

  bNR++;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return -18;//GetDouble2Error();
//  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();



  bNS++;
  //bNR = 1;
  bInvokeId++;
  QueryEngCurrDay36(bNS, bNR, bInvokeId/*++*/);
  if (Input36() != SER_GOODCHECK) return -19;
  AddBuffer1(22, IndexInBuff()-22-3);
  DelayOff();

  bNR++;// = 2;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return -20;
  AddBuffer1(8, IndexInBuff()-8-3);
  DelayOff();

  bNR++;// = 3;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return -21;
  DelayOff();



  bNS++;// = 1;
//  bNR = 3;
//  bInvokeId = 0xE;
  uchar bBlockNumber = 1;
  QueryNextBlock36(bNS, bNR, bInvokeId/*++*/, bBlockNumber);
  if (Input36() != SER_GOODCHECK) return -22;
  AddBuffer1(22, IndexInBuff()-22-3);
  DelayOff();

  bNR++;// = 4;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return -23;
  AddBuffer1(8, IndexInBuff()-8-3);
  DelayOff();

  bNR++;// = 5;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return -24;
  DelayOff();



  bNS++;// = 2;
//  bNR = 5;
//  bInvokeId = 0xE;
  bBlockNumber = 2;
  QueryNextBlock36(bNS, bNR, bInvokeId/*++*/, bBlockNumber);
  if (Input36() != SER_GOODCHECK) return -25;
  AddBuffer1(22, IndexInBuff()-22-3);
  DelayOff();

  bNR++; // 6
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return -26;
  AddBuffer1(8, IndexInBuff()-8-3);
  DelayOff();

  bNR++; // 7
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return -27;
  DelayOff();





  FinishBuffer1();
  return 0;
}


double2 ReadCntMonCan36_2(void)
{
  return GetDouble2(y(), true);
}
