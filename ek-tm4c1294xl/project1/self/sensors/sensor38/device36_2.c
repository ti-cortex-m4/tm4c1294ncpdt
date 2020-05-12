/*------------------------------------------------------------------------------
DEVICE36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "include36.h"
#include "crc16_x25.h"
#include "io36.h"
#include "hdlc.h"
#include "push_dlms.h"
#include "device36.h" //
#include "device36_2.h"




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
void    QueryEngCurrDay36(uchar  bNS, uchar  bNR, uchar  bInvokeId)
{
  MonitorString("\n\n Get EngCurrDay ");

  uint wSize = 110 + GetHdlcAddressesSize(); // 0x70 112

  InitPush(0);
  PushChar(0x7E);

  PushFormatDLMS(wSize);
//  PushChar(0xA0);
//  PushChar(0x19);
  PushHdlcAddresses();
//  PushChar(0x03);
//  PushChar(0x03);

//  MonitorString("Control{N(R)=1,N(S)=1} 32 ? "); MonitorCharHex((bNR << 5) | 0x10 | (bNS << 1) | 0x00);
  PushChar((bNR << 5) | 0x10 | (bNS << 1) | 0x00);

  PushIntLtl(MakeCRC16_X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5
//  PushChar(0xEC); // CRC ?
//  PushChar(0xC8);

  // DLMS start

  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);

  PushChar(0xC0); // Get-Request
  PushChar(0x01); // Get-Request-Normal
  PushChar(0x80 | (bInvokeId % 16)); // Invoke-Id-And-Priority

  PushChar(0x00); // TODO ???

//  <AttributeDescriptor>

  PushChar(0x07); // <ClassId Value="0007" /> <!--PROFILE_GENERIC-->

  PushChar(0x01); // <InstanceId Value="0100630100FF" /> <!--1.0.99.1.0.255-->
  PushChar(0x00);
  PushChar(0x63);
  PushChar(0x01);
  PushChar(0x00);
  PushChar(0xFF);

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

//        </Structure>

  PushChar(0x09); //  <OctetString Value="07E4040EFF000000FF8000FF" />
  PushChar(0x0C);

  time ti1;
  ti1.bYear = 20;
  ti1.bMonth = 4;
  ti1.bDay = 14;
  ti1.bHour = 0;
  ti1.bMinute = 0;
  ti1.bSecond = 0;
  PushTimeDLMS(ti1);
/*
  PushChar(0x07); // <!--2020-04-14 00:00:00-->
  PushChar(0xE4);
  PushChar(0x04);
  PushChar(0x0E);
  PushChar(0xFF);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0xFF);
  PushChar(0x80);
  PushChar(0x00);
  PushChar(0xFF);
*/
  PushChar(0x09); // <OctetString Value="07E4040EFF173B3BFF8000FF" />
  PushChar(0x0C);

  time ti2;
  ti2.bYear = 20;
  ti2.bMonth = 4;
  ti2.bDay = 14;
  ti2.bHour = 23;
  ti2.bMinute = 59;
  ti2.bSecond = 59;
  PushTimeDLMS(ti2);
/*
  PushChar(0x07); // <!--2020-04-14 23:59:59-->
  PushChar(0xE4);
  PushChar(0x04);
  PushChar(0x0E);
  PushChar(0xFF);
  PushChar(0x17);
  PushChar(0x3B);
  PushChar(0x3B);
  PushChar(0xFF);
  PushChar(0x80);
  PushChar(0x00);
  PushChar(0xFF);
*/
//        <Array Qty="02" >

  PushChar(0x01);
  PushChar(0x02);

//          <Structure Qty="04" >

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

//          </Structure>

//          <Structure Qty="04" >

  PushChar(0x02);
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

//          </Structure>
//        </Array>
//      </Structure>
//    </AccessParameters>
//  </AccessSelection>

  // DLMS finish

  PushIntLtl(MakeCRC16_X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query36(1000, wSize+2);
}


/*
<GetRequest>
  <GetRequestForNextDataBlock>
    <!--Priority: HIGH ServiceClass: UN_CONFIRMED invokeID: 10-->
    <InvokeIdAndPriority Value="8A" />
    <BlockNumber Value="00000001" />
  </GetRequestForNextDataBlock>
</GetRequest>
*/
void    QueryNextBlock36(uchar  bNS, uchar  bNR, uchar  bInvokeId, uchar  bBlockNumber)
{
  MonitorString("\n\n NextBlock"); // TODO ???

  uint wSize = 17 + GetHdlcAddressesSize();

  InitPush(0);
  PushChar(0x7E);
  PushFormatDLMS(wSize);
  PushHdlcAddresses();

//MonitorString("Control{R(R)=1} 31 ? "); MonitorCharHex((bNR << 5) | 0x10 | 0x01);
  PushChar((bNR << 5) | 0x10 | (bNS << 1) | 0x00);

  PushIntLtl(MakeCRC16_X25OutBuff(1, 3+GetHdlcAddressesSize()));

  // DLMS start

  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);

  PushChar(0xC0); // Get-Request
  PushChar(0x02); // Get-Request-Normal /// TODO ???
  PushChar(0x80 | (bInvokeId % 16)); // Invoke-Id-And-Priority

  PushLongBig(bBlockNumber); // <BlockNumber Value="00000001" /> TODO ???

  // DLMS finish

  PushIntLtl(MakeCRC16_X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query36(1000, wSize+2); // 0x13
}
