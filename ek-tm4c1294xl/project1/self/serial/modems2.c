/*------------------------------------------------------------------------------
MODEMS2.C


------------------------------------------------------------------------------*/
/*
#include    "main.h"
#include    "xdata.h"
#include    "timer0.h"
#include    "display.h"
#include    "delay.h"
#include    "ports.h"
#include    "modems.h"


bit     ModQualityOK(uchar  bSecond) {
  return( (ModInput(bSecond,0) == SER_POSTANSWER_MODEM) );
}


void    QueryModemQuality(void) {
  InitPush();

  PushChar('A');
  PushChar('T');

  PushChar('+');
  PushChar('C');
  PushChar('S');
  PushChar('Q');

  PushChar('\r');
  PushChar('\n');

  Query(SERIAL_MODEM, 6+2, 1);
}


bit     ReadModemQuality(void) {
uchar i;

  for (i=0; i<bMINORREPEATS; i++) {
    DelayOff();
    QueryModemBaud(0);

    if (ModInputOK(1) == 1) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) ;

  for (i=0; i<bMINORREPEATS; i++) {
    DelayOff();
    QueryModemCommon(0);

    if (ModInputOK(1) == 1) break;
    if (fKey == 1) return(0);
    sprintf(szLo+15, "%1bu", i+1);
  }

  if (i == bMINORREPEATS)
    return(0);

  for (i=0; i<bMINORREPEATS; i++) {
    DelayOff();
    QueryModemQuality();

    if (ModQualityOK(1) == 1) break;
    if (fKey == 1) return(0);
    sprintf(szLo+15, "%1bu", i+1);
  }

  return(1);
}


bit   SafeReadModemQuality(uchar  ibPrt) {
stream  s;
bit     f;
 
  s = mppoPorts[ibPrt].enStream;
  mppoPorts[ibPrt].enStream = STR_MASTERDIRECT;
  f = ReadModemQuality();
  mppoPorts[ibPrt].enStream = s;

  return f;
}


void    ShowModemQuality(uchar  ibPrt) {
uchar   i;

  Clear();

  ibPort = ibPrt;
  diCurr.ibPort = ibPrt;

  if (SafeReadModemQuality(ibPrt) != 1) 
    Error();
  else {
    for (i=0; i<IndexInBuff()-1; i++) {
      szLo[i] = InBuff(i);
    }
  }
}

*/