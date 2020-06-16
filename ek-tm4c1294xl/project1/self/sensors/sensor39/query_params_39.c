/*------------------------------------------------------------------------------
query_params_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../kernel/wrappers.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "crc16x25.h"
#include "io39.h"
#include "hdlc_address.h"
#include "dlms_push.h"
#include "query_params_39.h"



void    QueryGetRequestDLMS(const obis_t  obis, uchar  bClass, uchar  bAttribute, caller39  r)
{
  uint wSize = 23 + GetHdlcAddressesSize(); // 0x19 25

  InitPush(0);
  PushChar(0x7E);

  PushFormatDLMS(wSize);
  PushHdlcAddresses();

  PushChar((r.bNR << 5) | 0x10 | (r.bNS << 1) | 0x00);

  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5

  // DLMS start

  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);

  PushChar(0xC0); // Get-Request
  PushChar(0x01); // Get-Request-Normal
  PushChar(0x80 | (r.bInvokeId % 16)); // Invoke-Id-And-Priority

  PushChar(0x00);
  PushChar(bClass); // class

  PushOBIS_DLMS(obis);

  PushChar(bAttribute); // attribute
  PushChar(0x00);

  // DLMS finish

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query39(1000, wSize+2); // 27
}



void    QueryGetRegisterValueDLMS(const obis_t  obis, caller39  r)
{
  QueryGetRequestDLMS(obis, 3, 2, r); // class 3, attribute 2: value
}

void    QueryGetRegisterScalerDLMS(const obis_t  obis, caller39  r)
{
  QueryGetRequestDLMS(obis, 3, 3, r); // class 3, attribute 3: scaler_unit
}
