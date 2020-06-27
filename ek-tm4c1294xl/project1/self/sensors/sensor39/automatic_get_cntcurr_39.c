/*------------------------------------------------------------------------------
automatic_get_cntcurr_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../serial/ports.h"
#include "../../digitals/digitals.h"
#include "device39.h"
#include "device39_obis.h"
#include "io39.h"
#include "caller39.h"
#include "error39.h"
#include "fragment_open_39.h"
#include "dlms_read_register.h"
#include "automatic_get_cntcurr_39.h"



static time2 Fault(uchar  bError)
{
  return GetDouble2Error1(Error39(bError));
}



double2 ReadCntCurr39_Internal(void)
{
  caller39 c = InitCaller39();

  uchar bError = FragmentOpen39(&c);
  if (bError != 0) return Fault(bError);

  double2 db2 = ReadRegisterValueWithScaler39(obisEngAbs, &c);
  if (!db2.fValid) return Fault(80+0);

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return Fault(80+1);

  return GetDouble0(db2.dbValue);
}



double2 ReadCntCurr39(void)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    double2 db2 = ReadCntCurr39_Internal();
    if (fKey == true) break;
    if (db2.fValid)
    {
      mpdbChannelsC[0] = db2.dbValue / 1000;
      mpboChannelsA[0] = true;

      return GetDouble0(mpdbChannelsC[0]);
    }
  }

  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return Fault(80+2);

  return Fault(80+3);
}
