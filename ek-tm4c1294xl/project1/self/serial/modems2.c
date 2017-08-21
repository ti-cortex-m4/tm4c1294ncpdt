/*------------------------------------------------------------------------------
MODEMS2!C

 ('Отчет №24 от 01.06.2008')
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
#include "ports.h"
#include "ports_devices.h"
#include "ports_modems.h"
#include "modems.h"
#include "modems2.h"



bool    ModQualityOK(uchar  bSecond)
{
  return (ModInput(bSecond,0) == SER_POSTANSWER_MODEM);
}


void    QueryModemQuality(void)
{
  InitPush(0);

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


bool    ReadModemQuality(void)
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryModemBaud(0);

    if (ModInputOK(1) == 1) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) ;

  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryModemCommon(0);

    if (ModInputOK(1) == 1) break;
    if (fKey == true) return(0);
    sprintf(szLo+15, "%1u", i+1);
  }

  if (i == MaxRepeats()) return(0);

  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryModemQuality();

    if (ModQualityOK(1) == 1) break;
    if (fKey == true) return(0);
    sprintf(szLo+15, "%1u", i+1);
  }

  return(1);
}


bool  SafeReadModemQuality(uchar  ibPrt)
{
  stream s = mppoPorts[ibPrt].enStream;
  mppoPorts[ibPrt].enStream = STR_MASTERDIRECT;
  bool f = ReadModemQuality();
  mppoPorts[ibPrt].enStream = s;

  return f;
}


void    ShowModemQuality(uchar  ibPrt)
{
  Clear();

  ibPort = ibPrt;
  diCurr.ibPort = ibPrt;

  if (SafeReadModemQuality(ibPrt) != 1)
    Error();
  else {
    uchar i;
    for (i=0; i<IndexInBuff()-1; i++)
    {
      szLo[i] = InBuff(i);
    }
  }
}
