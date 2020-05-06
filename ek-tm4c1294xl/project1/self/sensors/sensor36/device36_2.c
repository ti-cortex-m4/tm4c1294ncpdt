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

  uint wSize = 92 + GetHdlcAddressesSize(); // 0x5E 94

  InitPush(0);
  PushChar(0x7E);

  PushFormat(wSize);
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

  PushChar(0x00);
  PushChar(0x07);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x62);
  PushChar(0x01);
  PushChar(0x00);
  PushChar(0xFF);
  PushChar(0x02);
  PushChar(0x01);
  PushChar(0x01);
  PushChar(0x02);
  PushChar(0x04);
  PushChar(0x02);
  PushChar(0x04);
  PushChar(0x12);
  PushChar(0x00);
  PushChar(0x08);
  PushChar(0x09);
  PushChar(0x06);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x01);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0xFF);
  PushChar(0x0F);
  PushChar(0x02);
  PushChar(0x12);
  PushChar(0x00);
  PushChar(0x00);

  PushChar(0x09);
  PushChar(0x0C);
  PushTime36(bMonth, bYear);

  PushChar(0x09);
  PushChar(0x0C);
  PushTime36(bMonth, bYear);

  PushChar(0x01);
  PushChar(0x01);
  PushChar(0x02);
  PushChar(0x04);
  PushChar(0x12);
  PushChar(0x00);
  PushChar(0x03);
  PushChar(0x09);
  PushChar(0x06);
  PushChar(0x01);
  PushChar(0x00);
  PushChar(0x0F);
  PushChar(0x08);
  PushChar(0x00);
  PushChar(0xFF);
  PushChar(0x0F);
  PushChar(0x02);
  PushChar(0x12);
  PushChar(0x00);
  PushChar(0x00);

/*
  PushChar(0x00);
  PushChar(0x03); // class

  PushChar(1); // 1-0:1.8.0*255
  PushChar(0);
  PushChar(1 + ibLine);
  PushChar(8);
  PushChar(0);
  PushChar(255);

  PushChar(0x02);
  PushChar(0x00);
*/
  // DLMS finish

  PushIntLtl(MakeCRC16_X25OutBuff(1, wSize-2));

  PushChar(0x7E);

  Query36(1000, wSize+2);
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
uint64_t ReadEngMon36(void)
{
  InitPop(18 + GetHdlcAddressesSize());
  return PopLongBig()*0x100000000 + PopLongBig();
}
