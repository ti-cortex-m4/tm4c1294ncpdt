/*------------------------------------------------------------------------------
DEVICE36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "include38.h"
#include "crc16x25.h"
#include "io36.h"
#include "hdlc.h"
#include "push_dlms.h"
#include "device36.h"



void    Query38_DISC(void)
{
  MonitorString("\n\n DISC");

  InitPush(0);

  uint wSize = 5+GetHdlcAddressesSize(); // 7

  PushChar(0x7E);
  PushFormatDLMS(wSize);
//  PushChar(0xA0);
//  PushChar(0x07);
  PushHdlcAddresses();
//  PushChar(0x03);
//  PushChar(0x03);
  PushChar(0x53); // DISC

  PushIntLtl(MakeCRC16_X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5
//  PushChar(0x80);
//  PushChar(0xD7);

  PushChar(0x7E);

  Query36(1000, wSize+2); // 9
}


void    Query38_SNRM(void)
{
  MonitorString("\n\n SNRM");

  uint wSize = 30 + GetHdlcAddressesSize(); // 32

  InitPush(0);
  PushChar(0x7E);
  
  PushFormatDLMS(wSize);
//  PushChar(0xA0);
//  PushChar(0x20);
  PushHdlcAddresses();
//  PushChar(0x03);
//  PushChar(0x03);
  PushChar(0x93); // SNRM
  
  PushIntLtl(MakeCRC16_X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5
//  PushChar(0xFE); // CRC ?
//  PushChar(0xC9);
  
  PushChar(0x81);
  PushChar(0x80);
  PushChar(0x14); // length
  
  PushChar(0x05);
  PushChar(0x02); // length
  PushChar(0x00);
  PushChar(0x80);
  
  PushChar(0x06);
  PushChar(0x02); // length
  PushChar(0x00);
  PushChar(0x80);
  
  PushChar(0x07);
  PushChar(0x04); // length
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x01);
  
  PushChar(0x08);
  PushChar(0x04); // length
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x01);

  PushIntLtl(MakeCRC16_X25OutBuff(1, wSize-2)); // 30
//  PushChar(0xCE);
//  PushChar(0x6A);

  PushChar(0x7E);

  Query36(1000, wSize+2); // 34
}


// Green Book, 11.5 Encoding of the AARQ APDU
void    Query38_Open2(uchar  bNS, uchar  bNR)
{
  MonitorString("\n\n Open 2 ");

  uint wSize = 66 + GetHdlcAddressesSize(); // 0x44 68

  InitPush(0);
  PushChar(0x7E);
  
  PushFormatDLMS(wSize);
//  PushChar(0xA0);
//  PushChar(0x44);
  PushHdlcAddresses();
//  PushChar(0x03);
//  PushChar(0x03);

  bNS = 0;
  bNR = 0;
  MonitorString("Control{N(R)=0,N(S)=0} 10 ? "); MonitorCharHex((bNR << 5) | 0x10 | (bNS << 1) | 0x00);
  PushChar(0x10); // I-frame
  
  PushIntLtl(MakeCRC16_X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5
//  PushChar(0x65); // CRC ?
//  PushChar(0x94);

  // DLMS start

  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);

  PushChar(0x60);
  PushChar(0x36); // length
  
  PushChar(0xA1);
  PushChar(0x09); // length
  PushChar(0x06);
  PushChar(0x07);
  PushChar(0x60);
  PushChar(0x85);
  PushChar(0x74);
  PushChar(0x05);
  PushChar(0x08);
  PushChar(0x01);
  PushChar(0x01);
  
  PushChar(0x8A);
  PushChar(0x02); // length
  PushChar(0x07);
  PushChar(0x80);
  
  PushChar(0x8B);
  PushChar(0x07); // length
  PushChar(0x60);
  PushChar(0x85);
  PushChar(0x74);
  PushChar(0x05);
  PushChar(0x08);
  PushChar(0x02);
  PushChar(0x01);
  
  PushChar(0xAC);
  PushChar(0x0A); // length
  PushChar(0x80);
  PushChar(0x08);
  PushChar(0x78);
  PushChar(0x52);
  PushChar(0x77);
  PushChar(0x50);
  PushChar(0x62);
  PushChar(0x45);
  PushChar(0x78);
  PushChar(0x46);
  
  PushChar(0xBE);
  PushChar(0x10); // length
  PushChar(0x04);
  PushChar(0x0E);
  PushChar(0x01);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x06);
  PushChar(0x5F);
  PushChar(0x1F);
  PushChar(0x04);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x7E);
  PushChar(0x1F);
  PushChar(0x01);
  PushChar(0x00);
  
  // DLMS finish
  
  PushIntLtl(MakeCRC16_X25OutBuff(1, wSize-2));
//  PushChar(0xAF); // CRC ?
//  PushChar(0xDF);
  
  PushChar(0x7E);

  Query36(1000, wSize+2); // 70
}



void    Query38_RR(uchar  bNR)
{
  MonitorString("\n\n RR");

  uint wSize = 5 + GetHdlcAddressesSize();

  InitPush(0);
  PushChar(0x7E);
  PushFormatDLMS(wSize);
  PushHdlcAddresses();

  PushChar((bNR << 5) | 0x10 | 0x01);
  
  PushIntLtl(MakeCRC16_X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5
  PushChar(0x7E);

  Query36(1000, wSize+2); // 9
}



void    QueryTime38(uchar  bNS, uchar  bNR, uchar  bInvokeId)
{
  MonitorString("\n\n GetTime");

  uint wSize = 23 + GetHdlcAddressesSize(); // 0x19 25

  InitPush(0);
  PushChar(0x7E);
  
  PushFormatDLMS(wSize);
  PushHdlcAddresses();

  PushChar(((bNR << 5) | 0x10 | (bNS << 1) | 0x00));
  
  PushIntLtl(MakeCRC16_X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5

  // DLMS start
  
  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);
  
  PushChar(0xC0); // Get-Request
  PushChar(0x01); // Get-Request-Normal
  PushChar(0x80 | (bInvokeId % 16)); // Invoke-Id-And-Priority
  
  PushChar(0x00);
  PushChar(0x08); // class
  
  PushChar(0x00); // 0-0:1.0.0*255
  PushChar(0x00);
  PushChar(0x01);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0xFF);
  
  PushChar(0x02); // index  
  PushChar(0x00);

  // DLMS finish

  PushIntLtl(MakeCRC16_X25OutBuff(1, wSize-2));
  
  PushChar(0x7E);

  Query36(1000, wSize+2); // 27
}


time    ReadTime36(void)
{
  InitPop(15 + GetHdlcAddressesSize());

  time ti;
  ti.bYear   = PopIntBig() - 2000;
  ti.bMonth  = PopChar();
  ti.bDay    = PopChar();

  PopChar();

  ti.bHour   = PopChar();
  ti.bMinute = PopChar();
  ti.bSecond = PopChar();

  return ti;
}




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
void    QueryEngMon36(uchar  bNS, uchar  bNR, uchar  bInvokeId, uchar  bMonth, uchar  bYear)
{
  MonitorString("\n\n Get EngMon ");

  uint wSize = 92 + GetHdlcAddressesSize(); // 0x5E 94

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
  PushTimeMonthDLMS(bMonth, bYear);

  PushChar(0x09);
  PushChar(0x0C);
  PushTimeMonthDLMS(bMonth, bYear);

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
