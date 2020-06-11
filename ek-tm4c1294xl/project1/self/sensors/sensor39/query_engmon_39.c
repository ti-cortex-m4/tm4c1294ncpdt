/*------------------------------------------------------------------------------
query_engmon_39*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "crc16x25.h"
#include "io39.h"
#include "hdlc.h"
#include "dlms_push.h"
#include "query_engmon_39.h"



/*
<GetRequest>
  <GetRequestNormal>
    <!--Priority: HIGH ServiceClass: UN_CONFIRMED invokeID: 6-->
    <InvokeIdAndPriority Value="86" />
    <AttributeDescriptor>
      <!--PROFILE_GENERIC-->
      <ClassId Value="0007" />
      <!--0.0.98.1.0.255-->
      <InstanceId Value="0000620100FF" />
      <AttributeId Value="02" />
    </AttributeDescriptor>
    <AccessSelection>
      <AccessSelector Value="01" />
      <AccessParameters>
        <Structure Qty="04" >
          <Structure Qty="04" >
            <UInt16 Value="0008" />
            <!--0.0.1.0.0.255-->
            <OctetString Value="0000010000FF" />
            <Int8 Value="02" />
            <UInt16 Value="0000" />
          </Structure>
          <!--2020-03-01 00:00:01-->
          <OctetString Value="07E40301FF000001FF8000FF" />
          <!--2020-04-01 00:00:00-->
          <OctetString Value="07E40401FF000000FF8000FF" />
          <Array Qty="01" >
            <Structure Qty="04" >
              <UInt16 Value="0003" />
              <!--1.0.15.8.0.255-->
              <OctetString Value="01000F0800FF" />
              <Int8 Value="02" />
              <UInt16 Value="0000" />
            </Structure>
          </Array>
        </Structure>
      </AccessParameters>
    </AccessSelection>
  </GetRequestNormal>
</GetRequest>
*/
void    QueryEngMon39(uchar  bNS, uchar  bNR, uchar  bInvokeId, uchar  bMonth, uchar  bYear)
{
  MonitorString("\n\n QueryEngMon39 "); MonitorCharDec(bMonth); MonitorString(" "); MonitorCharDec(bYear);

  uint wSize = 92 + GetHdlcAddressesSize(); // 0x5E 94

  InitPush(0);
  PushChar(0x7E);

  PushFormatDLMS(wSize);
  PushHdlcAddresses();

  PushChar((bNR << 5) | 0x10 | (bNS << 1) | 0x00);

  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5

  // DLMS start

  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);

  PushChar(0xC0); // Get-Request
  PushChar(0x01); // Get-Request-Normal
  PushChar(0x80 | (bInvokeId % 16)); // Invoke-Id-And-Priority

  PushChar(0x00); // TODO ???

  PushChar(0x07); // <ClassId Value="0007" /> <!--PROFILE_GENERIC-->

  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x62);
  PushChar(0x01);
  PushChar(0x00);
  PushChar(0xFF);

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
  PushChar(0x00); // <!--0.0.1.0.0.255-->
  PushChar(0x00);
  PushChar(0x01);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0xFF);

  PushChar(0x0F); // <Int8 Value="02" />
  PushChar(0x02);

  PushChar(0x12); // <UInt16 Value="0000" />
  PushChar(0x00);
  PushChar(0x00);

  PushChar(0x09); // <OctetString Value="?" />
  PushChar(0x0C);
  PushTimeMonthYearDLMS(bMonth, bYear);

  PushChar(0x09); // <OctetString Value="?" />
  PushChar(0x0C);
  PushTimeMonthYearDLMS(bMonth, bYear);

  PushChar(0x01); // array
  PushChar(0x01);

  PushChar(0x02); // structure
  PushChar(0x04);

  PushChar(0x12); // <UInt16 Value="0003" />
  PushChar(0x00);
  PushChar(0x03);

  PushChar(0x09); // <OctetString Value="01000F0800FF" />
  PushChar(0x06);
  PushChar(0x01); // <!--1.0.15.8.0.255-->
  PushChar(0x00);
  PushChar(0x0F);
  PushChar(0x08);
  PushChar(0x00);
  PushChar(0xFF);

  PushChar(0x0F); // <Int8 Value="02" />
  PushChar(0x02);

  PushChar(0x12); // <UInt16 Value="0000" />
  PushChar(0x00);
  PushChar(0x00);

  // DLMS finish

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query39(1000, wSize+2);
}



/*
<PDU>
<GetResponse>
  <GetResponseNormal>
    <!--Priority: HIGH ServiceClass: UN_CONFIRMED invokeID: 6-->
    <InvokeIdAndPriority Value="86" />
    <Result>
      <Data>
        <Array Qty="01" >
          <Structure Qty="01" >
            <UInt64 Value="00000000000030B3" />
          </Structure>
        </Array>
      </Data>
    </Result>
  </GetResponseNormal>
</GetResponse>
</PDU>
*/
uint64_t ReadEngMon39(void)
{
  InitPop(18 + GetHdlcAddressesSize());
  return PopLongBig()*0x100000000 + PopLongBig();
}
