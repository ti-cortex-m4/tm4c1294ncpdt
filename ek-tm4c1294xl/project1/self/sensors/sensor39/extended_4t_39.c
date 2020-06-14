/*------------------------------------------------------------------------------
extended_4t_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
//#include "../../time/delay.h"
#include "../../time/timedate.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports2.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "device39.h"
#include "time39.h"
#include "query_engmon_39.h"
#include "io39.h"
#include "extended_4t_39.h"



static const obis_t obisEngTariff[4] = {
  {1, 0, 15, 8, 1, 255},
  {1, 0, 15, 8, 2, 255},
  {1, 0, 15, 8, 3, 255},
  {1, 0, 15, 8, 4, 255},
};


// TODO not present
ulong64_ CntMonCanTariff39_Internal(uchar  ibMon, uchar  ibTariff)
{
  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
  //DelayOff();

  Query39_SNRM();
  if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
  //DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;

  Query39_AARQ(bNS, bNR);
  if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
  if (!ValidateIframe(bNS, bNR)) return GetLong64Error(1);
  //DelayOff();

  bNR++;
  Query39_RR(bNR);
  if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
  if (!ValidateSframe(bNR)) return GetLong64Error(1);
  //DelayOff();


  bNS++;
  bInvokeId++;
  QueryTime39(bNS, bNR, bInvokeId);
  if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
  if (!ValidateIframe(bNS, bNR)) return GetLong64Error(1);
  time ti = ReadTime39();
  //DelayOff();

  bNR++;
  Query39_RR(bNR);
  if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
  if (!ValidateSframe(bNR)) return GetLong64Error(1);
  //DelayOff();


  uchar bMonth = ibMon + 1;
  uchar bYear = (bMonth > ti.bMonth) ? ti.bYear-1 : ti.bYear;

  bNS++;
  ASSERT(sizeof(obisEngTariff)/sizeof(obisEngTariff[0]) == 4);
  ASSERT(ibTariff < 4);
  QueryEngMon39(obisEngTariff[ibTariff], bNS, bNR, bInvokeId++, bMonth, bYear);
  if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
  if (!ValidateIframe(bNS, bNR)) return GetLong64Error(1);
  uint64_t ddw = ReadEngMon39();
  MonitorString("\n value="); MonitorLongDec(ddw % 0x100000000);
  //DelayOff();

  bNR++;
  Query39_RR(bNR);
  if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
  if (!ValidateSframe(bNR)) return GetLong64Error(1);
  //DelayOff();


  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
  //DelayOff();

  return GetLong64(ddw, true, 0);
}



status  ReadCntMonCanTariff39(uchar  ibMonAbs, uchar  ibTariff) // �� ������ ������
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    ulong64_ ddw2 = CntMonCanTariff39_Internal(ibMonAbs, ibTariff);
    if (fKey == true) break;
    if (ddw2.fValid)
    {
//      ShowPercent(50);

      mpdwChannelsA[0] = ddw2.ddwValue % 0x100000000;
      mpdbChannelsC[0] = ((double)mpdwChannelsA[0] / 1000) * mpdbTransCnt[ibDig];
      mpboChannelsA[0] = true;

      return ST_OK;
    }
  }

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return ST_BADDIGITAL;
  //DelayOff();

  return ST_BADDIGITAL;
}



#ifdef  MONITOR_39

double2 TestCntMonCanTariff39(void)
{
//  fMonitorLogBasic = false;
//  fMonitorLogHex = false;

  MonitorOpen(0);

  ReadCntMonCanTariff39(5, 0);
  ReadCntMonCanTariff39(4, 0);
  ReadCntMonCanTariff39(3, 0);
  ReadCntMonCanTariff39(2, 0);
  ReadCntMonCanTariff39(1, 0);
  ReadCntMonCanTariff39(0, 0);
  ReadCntMonCanTariff39(11, 0);
  ReadCntMonCanTariff39(10, 0);
  ReadCntMonCanTariff39(9, 0);
  ReadCntMonCanTariff39(8, 0);
  ReadCntMonCanTariff39(7, 0);

  return GetDouble2(0, true);
}

#endif
