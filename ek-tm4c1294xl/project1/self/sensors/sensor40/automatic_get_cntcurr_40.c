/*------------------------------------------------------------------------------
automatic_get_cntcurr_40.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../serial/ports.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "dlms.h"
#include "dlms_obis.h"
#include "io39.h"
#include "caller40.h"
#include "error40.h"
#include "fragment_open_39.h"
#include "dlms_read_register.h"
#include "automatic_get_cntcurr_40.h"



static double2 Fault(uchar  bError)
{
  return GetDouble2Error1(Error40(bError));
}



double2 ReadCntCurr39_Internal(void)
{
  caller40 c = InitCaller40();

  uchar bError = FragmentOpen40(&c);
  if (bError != 0) return Fault(60+0);

  uchar i;
  for (i=0; i<4; i++)
  {
    double2 db2 = ReadRegisterUnsignedValueWithScaler39(obisEngAbs[i], &c);
    if (!db2.fValid) return Fault(60+1+i);

    mpdbChannelsC[i] = (db2.dbValue / 1000) * mpdbTransCnt[ibDig];
  }

  DISC();
  if (Input39() != SER_GOODCHECK) return Fault(60+5);

  return GetDouble0(-1);
}



double2 ReadCntCurr40(void)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    double2 db2 = ReadCntCurr39_Internal();
    if (fKey == true) break;
    if (db2.fValid)
    {
      uchar i;
      for (i=0; i<4; i++)
        mpboChannelsA[i] = true;

      return GetDouble0(mpdbChannelsC[diCurr.ibLine]);
    }
  }

  DISC();
  if (Input39() != SER_GOODCHECK) return Fault(60+6);

  return Fault(60+7);
}
