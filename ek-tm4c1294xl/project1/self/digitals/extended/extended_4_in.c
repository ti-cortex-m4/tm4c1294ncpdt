/*------------------------------------------------------------------------------
EXTENDED_4_IN,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../digitals/digitals.h"
#include "../../sensors/device_f.h"
#include "extended_4.h"
#include "extended_4_in.h"



uchar                   bStatus4;
double                  dbValue4;
time                    tiUpdate4;



bool    ReadCntMonCanF_Curr(uchar  ibMon, uchar  ibCan)
{
  Clear();

  LoadCurrDigital(ibCan);
  ibPort = diCurr.ibPort;

  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    QueryBreakF();

    InitPushPck();
    PushChar(diCurr.bAddress);          
    PushChar(0);

    PushChar((5+3+2) % 0x100);
    PushChar((5+3+2) / 0x100);

    PushChar(0xFD);
    PushChar(bEXT_GETEXTENDED42);         
    PushChar(ibMon);         
    PushChar(ibCan);         

    PckQueryIO(bHEADER+(1+2+2+8+6)+2, 5+3+2);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (i == MaxRepeats()) return false;
  ShowPercent(100);


  InitPop(bHEADER);
  bStatus4 = PopChar();
  PopChar(); PopChar();
  PopChar(); PopChar();
  dbValue4 = PopDouble();
  Pop(&tiUpdate4, sizeof(time));

  return true;
}


bool    ReadCntMonCanF_Buff(uchar  ibMon, uchar  ibCan)
{
  Clear();

  LoadCurrDigital(ibCan);
  ibPort = diCurr.ibPort;

  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    QueryBreakF();

    InitPushPck();
    PushChar(diCurr.bAddress);          
    PushChar(0);

    PushChar((5+10+2) % 0x100);
    PushChar((5+10+2) / 0x100);

    PushChar(0xFD);
    PushChar(bEXT_GETEXTENDED40);         
    PushChar(ibMon);         

    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);

    PckQueryIO(bHEADER+(1+2+2+8+6)*bCANALS+2, 5+10+2);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (i == MaxRepeats()) return false;
  ShowPercent(100);


  return true;
}
