/*------------------------------------------------------------------------------
query_profile_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "crc16x25.h"
#include "io39.h"
#include "hdlc_address.h"
#include "dlms_push.h"
#include "query_profile_39.h"



/*
<GetRequest>
  <GetRequestNormal>
    <!--Priority: HIGH ServiceClass: UN_CONFIRMED invokeID: 10-->
    <InvokeIdAndPriority Value="8A" />
    <AttributeDescriptor>
      <!--PROFILE_GENERIC-->
      <ClassId Value="0007" />
      <!--1.0.99.1.0.255-->
      <InstanceId Value="0100630100FF" />
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
          <!--2020-04-14 00:00:00-->
          <OctetString Value="07E4040EFF000000FF8000FF" />
          <!--2020-04-14 23:59:59-->
          <OctetString Value="07E4040EFF173B3BFF8000FF" />
          <Array Qty="02" >
            <Structure Qty="04" >
              <UInt16 Value="0008" />
              <!--0.0.1.0.0.255-->
              <OctetString Value="0000010000FF" />
              <Int8 Value="02" />
              <UInt16 Value="0000" />
            </Structure>
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
void    QueryProfile39(uchar  bNS, uchar  bNR, uchar  bInvokeId, time  tm1, time  tm2)
{
#ifdef MONITOR_39  
  MonitorString("\n\n QueryProfile39 "); MonitorTime(tm1); MonitorTime(tm2);
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

//  <AttributeDescriptor>

  PushChar(0x07); // <ClassId Value="0007" /> <!--PROFILE_GENERIC-->

  PushOBIS_DLMS(obisProfile1); // <InstanceId Value="0100630100FF" /> <!--1.0.99.1.0.255-->

  PushChar(0x02); // <AttributeId Value="02" />

//  </AttributeDescriptor>

//  <AccessSelection>

  PushChar(0x01); //  <AccessSelector Value="01" />
  PushChar(0x01);

//    <AccessParameters>

//      <Structure Qty="04" >
  PushChar(0x02);
  PushChar(0x04);

//        <Structure Qty="04" >
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

//        </Structure>

  PushChar(0x09); // <OctetString Value="07E4040EFF000000FF8000FF" />
  PushChar(0x0C);
  PushTimeDLMS(tm1);

  PushChar(0x09); // <OctetString Value="07E4040EFF173B3BFF8000FF" />
  PushChar(0x0C);
  PushTimeDLMS(tm2);

//        <Array Qty="00" >

  PushChar(0x01);
  PushChar(0x00);
/*
//          <Structure Qty="04" >

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

//          </Structure>

//          <Structure Qty="04" >

  PushChar(0x02);
  PushChar(0x04);

  PushChar(0x12); // <UInt16 Value="0003" />
  PushChar(0x00);
  PushChar(0x03);

  PushChar(0x09); // <OctetString Value="01000F0800FF" />
  PushChar(0x06);
  PushOBIS_DLMS(obisEngAbs); // <!--1.0.15.8.0.255-->

  PushChar(0x0F); // <Int8 Value="02" />
  PushChar(0x02);

  PushChar(0x12); // <UInt16 Value="0000" />
  PushChar(0x00);
  PushChar(0x00);

//          </Structure>
*/
//        </Array>
//      </Structure>
//    </AccessParameters>
//  </AccessSelection>

  // DLMS finish

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query39(1000, wSize+2);
}

