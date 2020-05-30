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



#include "../../memory/mem_serial3.h"
#include "../../serial/monitor.h"
#include "../../time/calendar.h"
#include "bits2.h"
#include "profile38.h"
uint64_t DffDecodeLong64(uchar  *pb);
void    MonitorOpen(uchar  ibPrt);



double2 ReadCntCurr38(void)
{
  MonitorOpen(0);
  Delay(500);



  QueryProfile38(0);
  if (Input38() != SER_GOODCHECK) GetDouble2Error();



  uchar ibIdx = 10;

  uchar j;
  for (j=0; j<4; j++)
  {
    ibIdx++;

    uchar k;
    for (k=0; k<2; k++)
    {
      MonitorString("\n");
      ulong dw1 = 0;
      uchar i1 = pucDecodeBitArr((uchar *) &dw1, &mpbInBuff3[ibIdx]);
      ibIdx += i1; //0xFF
      MonitorString(" i1="); MonitorCharDec(i1); MonitorString(" ");
      time ti = SecIndexToDate(dw1);
      ti.bYear += 12;
      MonitorTime(ti);

      ulong dw2 = 0;
      uchar i2 = pucDecodeBitArr((uchar *) &dw2, &mpbInBuff3[ibIdx]);
      ibIdx += i2; //0xFF
      MonitorString(" i2="); MonitorCharDec(i2); MonitorString(" ");

      uchar bStatus = (dw2 % 0x100) & 0x03;
      MonitorString(" s=");MonitorCharDec(bStatus); MonitorString(" ");
      MonitorLongDecimal(dw2 >> 3, 10000);
    }
  }

  if (1+1 == 2) return GetDouble2(0, true);

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
