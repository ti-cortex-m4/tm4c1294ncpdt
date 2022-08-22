/*------------------------------------------------------------------------------
dlms_aare.c


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_digitals.h"
//#include "../../time/delay.h"
//#include "../../display/display.h"
//#include "../../serial/ports.h"
//#include "../../serial/ports2.h"
//#include "../../serial/ports_devices.h"
//#include "../../serial/monitor.h"
//#include "../../digitals/address/ascii_address.h"
//#include "crc16x25.h"
//#include "io40.h"
//#include "error40.h"
//#include "hdlc_address.h"
//#include "dlms_push.h"
#include "dlms_aare.h"



static bool Fault(uchar  bError, uint  wData)
{
  ErrorData40(bError, wData);
  return false;
}


bool    AARE_CheckPass_Internal(void)
{
  uint wSize = (InBuff(1) & 0x07)*0x100 + InBuff(2);

  uint i;
  for (i=6+GetHdlcAddressesSize(); i<wSize-4; i++)
  {
    if ((InBuff(i+0) == 0xA2) &&
        (InBuff(i+1) == 0x03) &&
        (InBuff(i+2) == 0x02) &&
        (InBuff(i+3) == 0x01))
    {
      uchar bResult = InBuff(i+4);

      if (bResult == 0)
        return true;
      else if (bResult == 1) {
        return Fault(0+1, bResult);
      } else {
        return Fault(0+2, bResult);
      }
    }
  }

  return Fault(0+3, wSize);
}


bool    AARE_CheckPass(void)
{
  bool success = AARE_CheckPass_Internal();
  if (!success) {
    Clear(); sprintf(szLo+4, "пароль ?"); Delay(1000);
  }
  return success;
}



/*
right password
7e a0 47 00 02 12 9d 03 10 cf 5e e6 e6 00 60 36 a1 09 06 07 60 85 74 05 08 01 01 8a 02 07 80 8b 07 60 85 74 05 08 02 01 ac 0a 80 08 78 52 77 50 62 45 78 46 be 10 04 0e 01 00 00 00 06 5f 1f 04 00 00 7e 1f 01 00 af df 7e
7e a0 3a 03 00 02 12 9d 30 fc 5c e6 e7 00 61 29 a1 09 06 07 60 85 74 05 08 01 01 a2 03 02 01 00 a3 05 a1 03 02 01 00 be 10 04 0e 08 00 06 5f 1f 04 00 00 18 1d 01 80 00 07 a1 dc 7e

wrong password
7e a0 47 00 02 12 9d 03 10 cf 5e e6 e6 00 60 36 a1 09 06 07 60 85 74 05 08 01 01 8a 02 07 80 8b 07 60 85 74 05 08 02 01 ac 0a 80 08 78 52 77 50 62 45 78 47 be 10 04 0e 01 00 00 00 06 5f 1f 04 00 00 7e 1f 01 00 e6 4c 7e
7e a0 3a 03 00 02 12 9d 30 fc 5c e6 e7 00 61 29 a1 09 06 07 60 85 74 05 08 01 01 a2 03 02 01 01 a3 05 a1 03 02 01 0d be 10 04 0e 08 00 06 5f 1f 04 00 00 18 1d 01 80 00 07 b2 65 7e
*/
