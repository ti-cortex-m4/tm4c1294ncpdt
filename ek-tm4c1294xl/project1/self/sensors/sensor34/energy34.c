/*------------------------------------------------------------------------------
energy34.c


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../console.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_digitals.h"
//#include "../../serial/ports.h"
//#include "../../serial/ports_devices.h"
//#include "../../serial/monitor.h"
#include "../../devices/devices.h"
//#include "unix_time_gmt34.h"
//#include "energy_dates34.h"
//#include "monitor34.h"
#include "device34.h"
#include "energy34.h"



uint64_t                mpddwChannels34[8+2];



void    ReadEngWithTrans34(void)
{
  ReadEng34();

  double dbTrans = mpdbTransCnt[ibDig];

  uchar i;
  for (i=0; i<MAX_LINE_N34; i++)
  {
    mpdbChannelsC[i] = (double)mpddwChannels34[i] / 1000000;
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }
}
