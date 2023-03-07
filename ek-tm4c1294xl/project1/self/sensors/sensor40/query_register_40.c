/*------------------------------------------------------------------------------
query_register_40.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../kernel/wrappers.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "crc16x25.h"
#include "io40.h"
#include "hdlc_address.h"
#include "dlms_push.h"
#include "query_register_40.h"



void    QueryGetRequestDLMS(const obis_t  obis, uchar  bClass, uchar  bAttribute, caller40  c)
{
  uint wSize = 23 + GetHdlcAddressesSize();

  InitPush(0);
  PushChar(0x7E);

  PushFormatDLMS(wSize);
  PushHdlcAddresses();

  PushChar(((c.bNR & 0x07) << 5) | 0x10 | ((c.bNS & 0x07) << 1) | 0x00);

  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize()));

  // DLMS start

  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);

  PushChar(0xC0); // Get-Request
  PushChar(0x01); // Get-Request-Normal
  PushChar(0x80 | (c.bInvokeId % 16)); // Invoke-Id-And-Priority

  PushChar(0x00);
  PushChar(bClass); // class

  PushOBIS_DLMS(obis);

  PushChar(bAttribute); // attribute
  PushChar(0x00);

  // DLMS finish

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query40(1000, wSize+2);
}



void    QueryGetRegisterValueDLMS(const obis_t  obis, caller40  c)
{
  QueryGetRequestDLMS(obis, 3, 2, c); // class 3: register, attribute 2: value
}


void    QueryGetRegisterScalerDLMS(const obis_t  obis, caller40  c)
{
  QueryGetRequestDLMS(obis, 3, 3, c); // class 3: register, attribute 3: scaler_unit
}