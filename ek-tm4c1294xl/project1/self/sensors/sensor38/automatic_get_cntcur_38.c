/*------------------------------------------------------------------------------
automatic_get_cntcur_38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../serial/ports.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "device38.h"
#include "io38.h"
#include "automatic_get_cntcur_38.h"



double2 ReadCntCurr38(void)
{
  uchar mpbuff[8];

  mpbuff[0] = 0xD5;
  mpbuff[1] = 0xEC;
  mpbuff[2] = 0xFD;
  mpbuff[3] = 0xC1;
  mpbuff[4] = 0x7E;
  mpbuff[5] = 0x98;
  mpbuff[6] = 0x09;

  MonitorString("\n before ");
//  MonitorArrayHex(mpbuff,8);

  MonitorString("\n 1 ");
  MonitorLong64Hex(DffDecodeLong64(mpbuff[0]));

  MonitorString("\n 1 ");
  MonitorLong64Hex(DffDecodeLong64(mpbuff[1]));

//  MonitorString("\n after ");
//  MonitorArrayHex(mpbuff,8);

  Clear();

  uchar i;
  for (i=0; i<4; i++)
  {
    uchar r;
    for (r=0; r<MaxRepeats(); r++)
    {
      ShowPercent(50 + i);
      QueryEngAbs38(i);

      if (Input38() == SER_GOODCHECK) break;
      if (fKey == true) return GetDouble2Error();
    }

    if (r == MaxRepeats()) return GetDouble2Error();

    mpdwChannelsA[i] = ReadEng38(11) % 0x100000000;
    mpdbChannelsC[i] = (double)mpdwChannelsA[i] / 10000;
  }


  for (i=0; i<4; i++)
  {
    mpdbChannelsC[i] *= mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}
