/*------------------------------------------------------------------------------
automatic_get_cntcurr_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
// #include "../../time/delay.h"
//#include "../../serial/ports.h"
//#include "../../serial/monitor.h"
#include "../../digitals/digitals.h"
#include "device39.h"
//#include "query_engabs_39.h"
#include "io39.h"
#include "fragment_open_39.h"
#include "automatic_get_cntcurr_39.h"



static const obis_t obisEngAbs  = {1, 0, 15, 8, 0, 255};



double2 ReadCntCurr39_Internal(void)
{
  caller39 c = InitCaller();

  uchar bError = FragmentOpen39(pc);
  if (bError != 0) return GetDouble2Error1(bError);

  double2 db2 = ReadRegisterValueWithScaler39(obisEngAbs, &c);
  if (!db2.fValid) return GetDouble2Error1(100);

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(101);

  return GetDouble0(db2.dbValue);
}



double2 ReadCntCurr39(void)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    double2 ddw2 = ReadCntCurr39_Internal();
    if (fKey == true) break;
    if (ddw2.fValid)
    {
      mpdwChannelsA[0] = ddw2.ddwValue % 0x100000000;
      mpdbChannelsC[0] = (double)mpdwChannelsA[0] / 1000;
      mpboChannelsA[0] = true;

      return GetDouble0(mpdbChannelsC[0]);
    }
  }

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(102);

  return GetDouble2Error1(103);
}
