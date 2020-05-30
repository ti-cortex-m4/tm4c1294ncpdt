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


  ulong dw1 = 0;
  uchar x = pucDecodeBitArr((uchar *) &dw1, &mpbInBuff3[11+0]);
  time ti = SecIndexToDate(dw1);
  ti.bYear += 12;
  MonitorTime(ti);

  ulong dw2 = 0;
  pucDecodeBitArr((uchar *) &dw2, &mpbInBuff3[11+4]);

  MonitorLongHex(dw2);
  MonitorLongHex(dw2 >> 3); MonitorString(" ");
  uchar bStatus = (dw2 % 0x100) & 0x03;
  MonitorCharDec(bStatus);
  MonitorLongDecimal(dw2 >> 3, 10000);


/*
  uchar in[8]; // E8 D5 C7 7E F0 22
  memset(&in, 0, sizeof(in));

  uchar out[8];
  memset(&out, 0, sizeof(out));

  in[0] = 0xE8;
  in[1] = 0xD5;
  in[2] = 0xC7;
  in[3] = 0x7E;
  in[4] = 0xF0;
  in[5] = 0x22;

  ulong out1 = 0;
  uchar x = pucDecodeBitArr((uchar *) &out1/ *&out[0]* /, &in[0]);
  time ti = SecIndexToDate(out1);
  ti.bYear += 12;
  MonitorTime(ti);

  ulong out2 = 0;
  pucDecodeBitArr((uchar *) &out2/ *&out[0]* /, &in[4]);

  MonitorLongHex(out2);
  MonitorLongHex(out2 >> 3); MonitorString(" ");
  MonitorLongDecimal(out2 >> 3, 10000);
*/

/*
  uint64_t ddw = DffDecodeLong64(mpbuff);
  MonitorString("\n 1 ");
  MonitorLong64Hex(ddw);

  ulong dw = ddw % 0x100000000;
  MonitorString("\n 2 ");
  MonitorLongHex(dw);
  MonitorString("\n 3 ");
  MonitorLongDec(dw);

  MonitorString("\n 4 ");
  MonitorLongHex(dw >> 3);
  MonitorString("\n 5 ");
  MonitorLongDec(dw >> 3);
*/
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
