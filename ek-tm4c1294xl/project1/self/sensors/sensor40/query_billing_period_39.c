/*------------------------------------------------------------------------------
query_billing_period_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "crc16x25.h"
#include "io39.h"
#include "hdlc_address.h"
#include "dlms_push.h"
#include "query_billing_period_39.h"



void    QueryBillingPeriod39(const obis_t  obisBillingPeriod, uchar  bNS, uchar  bNR, uchar  bInvokeId, date  dt)
{
#ifdef MONITOR_40_NAMES
  MonitorString("\n\n QueryEngMon39 "); MonitorCharDec(dt.bDay); MonitorString("."); MonitorCharDec(dt.bMonth); MonitorString("."); MonitorCharDec(dt.bYear);
#endif

  uint wSize = 74 + GetHdlcAddressesSize();

  InitPush(0);
  PushChar(0x7E);

  PushFormatDLMS(wSize);
  PushHdlcAddresses();

  PushChar(((bNR & 0x07) << 5) | 0x10 | ((bNS & 0x07) << 1) | 0x00);

  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize()));

  // DLMS start

  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);

  PushChar(0xC0); // Get-Request
  PushChar(0x01); // Get-Request-Normal
  PushChar(0xC0 | (bInvokeId % 16)); // Invoke-Id-And-Priority

  PushChar(0x00); // ?

  PushChar(0x07); // <ClassId Value="0007" /> <!--PROFILE_GENERIC-->
  PushOBIS_DLMS(obisBillingPeriod); // <!--0.0.98.1.0.255-->
  PushChar(0x02); // <AttributeId Value="02" />

  PushChar(0x01); // <AccessSelector Value="01" />
  PushChar(0x01);

  PushChar(0x02);
  PushChar(0x04);

  PushChar(0x02);
  PushChar(0x04);

  PushChar(0x12); // <UInt16 Value="0008" />
  PushChar(0x00);
  PushChar(0x08);

  PushChar(0x09); // <OctetString Value="0000010000FF" />
  PushChar(0x06);
  PushOBIS_DLMS(obisTime); // <!--0.0.1.0.0.255-->

  PushChar(0x0F); // <Int8 Value="02" />
  PushChar(0x02);

  PushChar(0x12); // <UInt16 Value="0000" />
  PushChar(0x00);
  PushChar(0x00);

  PushChar(0x09); // <OctetString Value="07E40301FF000001FF8000FF" />
  PushChar(0x0C);
  PushDateDLMS(dt);

  PushChar(0x09); // <OctetString Value="07E40401FF000000FF8000FF" />
  PushChar(0x0C);
  PushDateDLMS(dt);

  PushChar(0x01); // array
  PushChar(0x00);

  // DLMS finish

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query39(1000, wSize+2);
}



/*
<GetRequest>
  <GetRequestNormal>
    <!--Priority: HIGH ServiceClass: CONFIRMED invokeID: 1-->
    <InvokeIdAndPriority Value="193" />
    <AttributeDescriptor>
      <!--PROFILE_GENERIC-->
      <ClassId Value="7" />
      <!--1.0.98.1.0.255-->
      <InstanceId Value="0100620100FF" />
      <AttributeId Value="2" />
    </AttributeDescriptor>
    <AccessSelection>
      <AccessSelector Value="1" />
      <AccessParameters>
        <Structure Qty="4" >
          <Structure Qty="4" >
            <UInt16 Value="8" />
            <!--0.0.1.0.0.255-->
            <OctetString Value="0000010000FF" />
            <Int8 Value="2" />
            <UInt16 Value="0" />
          </Structure>
          <!--2022-08-01 00:00:00-->
          <OctetString Value="07E60801010000000000B4FF" />
          <!--2022-08-01 00:00:01-->
          <OctetString Value="07E60801010000010000B4FF" />
          <Array Qty="0" >
          </Array>
        </Structure>
      </AccessParameters>
    </AccessSelection>
  </GetRequestNormal>
</GetRequest>

<GetResponse>
  <GetResponseNormal>
    <!--Priority: HIGH ServiceClass: CONFIRMED invokeID: 1-->
    <InvokeIdAndPriority Value="193" />
    <Result>
      <Data>
        <Array Qty="1" >
          <Structure Qty="9" >
            <!--2022-08-01 00:00:00-->
            <OctetString Value="07E60801FF0000000000B480" />
            <UInt32 Value="4609470" />
            <UInt32 Value="3074769" />
            <UInt32 Value="1534701" />
            <UInt32 Value="0" />
            <UInt32 Value="0" />
            <UInt32 Value="0" />
            <UInt32 Value="5657" />
            <UInt32 Value="8481" />
          </Structure>
        </Array>
      </Data>
    </Result>
  </GetResponseNormal>
</GetResponse>
*/
