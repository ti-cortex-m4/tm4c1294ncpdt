/*------------------------------------------------------------------------------
DEVICE36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "crc16_x25.h"
#include "io36.h"
#include "device36.h"



void    Query36_DISC(void)
{
  MonitorString("\n\n DISC");

  InitPush(0);

  PushChar(0x7E);
  
  PushChar(0xA0);
  PushChar(0x07);
  PushChar(0x03);
  PushChar(0x03);
  PushChar(0x53); // DISC

  PushIntLtl(MakeCRC16_X25OutBuff(1, 5));
//  PushChar(0x80);
//  PushChar(0xD7);

  PushChar(0x7E);

  Query36(1000, 9);
}


void    Query36_SNRM(void)
{
  MonitorString("\n\n Open 1");

  InitPush(0);

  PushChar(0x7E);
  
  PushChar(0xA0);
  PushChar(0x20);
  PushChar(0x03);
  PushChar(0x03);
  PushChar(0x93); // SNRM
  
  PushChar(0xFE); // CRC ?
  PushChar(0xC9);
  
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

  PushIntLtl(MakeCRC16_X25OutBuff(1, 30));
//  PushChar(0xCE);
//  PushChar(0x6A);

  PushChar(0x7E);

  Query36(1000, 34);
}


void    Query36_Open2(void) // the Green Book, 11.5 Encoding of the AARQ APDU
{
  MonitorString("\n\n Open 2");

  InitPush(0);

  PushChar(0x7E);
  
  PushChar(0xA0);
  PushChar(0x44);
  PushChar(0x03);
  PushChar(0x03);

  uchar bNR = 0;
  uchar bNS = 0;
  MonitorString("Control{N(R)=0,N(S)=0} 10 ? "); MonitorCharHex((bNR << 5) | 0x10 | (bNS << 1) | 0x00);
  PushChar(0x10); // I-frame
  
  PushChar(0x65); // CRC ?
  PushChar(0x94);

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
  
  PushChar(0xAF); // CRC ?
  PushChar(0xDF);
  
  PushChar(0x7E);

  Query36(1000, 70);
}


void    Query36_Open3(void)
{
  MonitorString("\n\n Open 3");

  InitPush(0);

  PushChar(0x7E);
  
  PushChar(0xA0);
  PushChar(0x07);
  PushChar(0x03);
  PushChar(0x03);

  uchar bNR = 1;
  MonitorString("Control{R(R)=1} 31 ? "); MonitorCharHex((bNR << 5) | 0x10 | 0x01);
  PushChar(0x31); //
  
  PushIntLtl(MakeCRC16_X25OutBuff(1, 5));
//  PushChar(0x94); // CRC ?
//  PushChar(0x97);
  
  PushChar(0x7E);

  Query36(1000, 9);
}


void    Query36_GetTime(void)
{
  MonitorString("\n\n GetTime");

  InitPush(0);

  PushChar(0x7E);
  
  PushChar(0xA0);
  PushChar(0x19);
  PushChar(0x03);
  PushChar(0x03);

  uchar bNR = 1;
  uchar bNS = 1;
  MonitorString("Control{N(R)=1,N(S)=1} 32 ? "); MonitorCharHex((bNR << 5) | 0x10 | (bNS << 1) | 0x00);
  PushChar(0x32);
  
  PushChar(0xEC); // CRC ?
  PushChar(0xC8);

  // DLMS start
  
  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);
  
  PushChar(0xC0); // Get-Request
  PushChar(0x01); // Get-Request-Normal ?
  PushChar(0x83); // Invoke-Id-And-Priority ???
  
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

  PushChar(0x47); // CRC
  PushChar(0x7C);
  
  PushChar(0x7E);

  Query36(1000, 27);
}


void    Query36_Open5(void)
{
  MonitorString("\n\n Open 5");

  InitPush(0);

  PushChar(0x7E);
  
  PushChar(0xA0);
  PushChar(0x07);
  PushChar(0x03);
  PushChar(0x03);

  uchar bNR = 2;
  MonitorString("Control{N(R)=2} 51 ? "); MonitorCharHex((bNR << 5) | 0x10 | 0x01);
  PushChar(0x51); //
  
  PushIntLtl(MakeCRC16_X25OutBuff(1, 5));
//  PushChar(0x92); // CRC ?
//  PushChar(0xF4);
  
  PushChar(0x7E);

  Query36(1000, 9);
}


time    ReadTime36(void)
{
  InitPop(8 + 9);

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
