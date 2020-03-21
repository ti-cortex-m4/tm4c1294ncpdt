/*------------------------------------------------------------------------------
DEVICE36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "include36.h"
#include "crc16_x25.h"
#include "io36.h"
#include "device36.h"



#define ADDR_4


static addr36 GetAddr(void)
{
#ifndef ADDR_4
  addr36 addr;
  addr.cBuff.mpbBuff[0] = 0x03;
  addr.cBuff.mpbBuff[1] = 0x03;
  addr.bSize = 1+1;
  return addr;
#else
  addr36 addr;
  addr.cBuff.mpbBuff[0] = 0x00;
  addr.cBuff.mpbBuff[1] = 0x02;

  uint wAddr = 1230;

  addr.cBuff.mpbBuff[3] = wAddr / 0x100;
  addr.cBuff.mpbBuff[4] = wAddr % 0x100;

  addr.cBuff.mpbBuff[3]   = (addr.cBuff.mpbBuff[3] << 2) & 0xFC;
  if(addr.cBuff.mpbBuff[4] & 0x80) addr.cBuff.mpbBuff[3] |= 0x02;
  addr.cBuff.mpbBuff[4] = (addr.cBuff.mpbBuff[4] << 1) | 0x01;

  addr.bSize = 4+1;
  return addr;
#endif

}


static void PushFormat(uint  wSize)
{
  PushIntBig(wSize | 0xA000);
}


static void PushAddr(addr36 addr)
{
#ifndef ADDR_4
  PushChar(addr.cBuff.mpbBuff[0]);
  PushChar(addr.cBuff.mpbBuff[1]);
#else
  PushChar(addr.cBuff.mpbBuff[0]);
  PushChar(addr.cBuff.mpbBuff[1]);
  PushChar(addr.cBuff.mpbBuff[2]);
  PushChar(addr.cBuff.mpbBuff[3]);
  PushChar((bLogical << 1) + 0x01);
#endif
}



void    Query36_DISC(void)
{
  MonitorString("\n\n DISC");

  InitPush(0);

  addr36 addr = GetAddr();
  uint wSize = 5 + addr.bSize; // 7

  PushChar(0x7E);
  PushFormat(wSize);
//  PushChar(0xA0);
//  PushChar(0x07);
  PushAddr(addr);
//  PushChar(0x03);
//  PushChar(0x03);
  PushChar(0x53); // DISC

  PushIntLtl(MakeCRC16_X25OutBuff(1, wSize-2)); // 5
//  PushChar(0x80);
//  PushChar(0xD7);

  PushChar(0x7E);

  Query36(1000, wSize+2); // 9
}


void    Query36_SNRM(void)
{
  MonitorString("\n\n SNRM");

  addr36 addr = GetAddr();
  uint wSize = 30 + addr.bSize; // 32

  InitPush(0);
  PushChar(0x7E);
  
  PushFormat(wSize);
//  PushChar(0xA0);
//  PushChar(0x20);
  PushAddr(addr);
//  PushChar(0x03);
//  PushChar(0x03);
  PushChar(0x93); // SNRM
  
  PushIntLtl(MakeCRC16_X25OutBuff(1, 5));
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
void    Query36_Open2(uchar  bNS, uchar  bNR)
{
  MonitorString("\n\n Open 2 ");

  addr36 addr = GetAddr();
  uint wSize = 66 + addr.bSize; // 0x44 68

  InitPush(0);
  PushChar(0x7E);
  
  PushFormat(wSize);
//  PushChar(0xA0);
//  PushChar(0x44);
  PushAddr(addr);
//  PushChar(0x03);
//  PushChar(0x03);

  bNS = 0;
  bNR = 0;
  MonitorString("Control{N(R)=0,N(S)=0} 10 ? "); MonitorCharHex((bNR << 5) | 0x10 | (bNS << 1) | 0x00);
  PushChar(0x10); // I-frame
  
  PushIntLtl(MakeCRC16_X25OutBuff(1, 5));
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


void    Query36_RR(uchar  bNR)
{
  MonitorString("\n\n RR");

  addr36 addr = GetAddr();
  uint wSize = 5 + addr.bSize;

  InitPush(0);
  PushChar(0x7E);
  PushFormat(wSize);
//  PushChar(0xA0);
//  PushChar(0x07);
  PushAddr(addr);
//  PushChar(0x03);
//  PushChar(0x03);

  //MonitorString("Control{R(R)=1} 31 ? "); MonitorCharHex((bNR << 5) | 0x10 | 0x01);
  PushChar((bNR << 5) | 0x10 | 0x01);
  
  PushIntLtl(MakeCRC16_X25OutBuff(1, wSize-2)); // 5
  PushChar(0x7E);

  Query36(1000, wSize+2); // 9
}


void    Query36_GetTime(uchar  bNS, uchar  bNR)
{
  MonitorString("\n\n GetTime ");

  addr36 addr = GetAddr();
  uint wSize = 23 + addr.bSize; // 0x19 25

  InitPush(0);
  PushChar(0x7E);
  
  PushFormat(wSize);
//  PushChar(0xA0);
//  PushChar(0x19);
  PushAddr(addr);
//  PushChar(0x03);
//  PushChar(0x03);

  MonitorString("Control{N(R)=1,N(S)=1} 32 ? "); MonitorCharHex((bNR << 5) | 0x10 | (bNS << 1) | 0x00);
  PushChar(0x32);
  
  PushIntLtl(MakeCRC16_X25OutBuff(1, 5));
//  PushChar(0xEC); // CRC ?
//  PushChar(0xC8);

  // DLMS start
  
  PushChar(0xE6); // LLC
  PushChar(0xE6);
  PushChar(0x00);
  
  PushChar(0xC0); // Get-Request
  PushChar(0x01); // Get-Request-Normal ?
  PushChar(0x83); // Invoke-Id-And-Priority TODO ??? 0x81
  
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
//  PushChar(0x47); // CRC
//  PushChar(0x7C);
  
  PushChar(0x7E);

  Query36(1000, wSize+2); // 27
}

/*
void    Query36_Open5(uchar  bNR)
{
  MonitorString("\n\n Open 5 ");

  InitPush(0);

  PushChar(0x7E);
  
  PushChar(0xA0);
  PushChar(0x07);
  PushChar(0x03);
  PushChar(0x03);

  MonitorString("Control{N(R)=2} 51 ? "); MonitorCharHex((bNR << 5) | 0x10 | 0x01);
  PushChar((bNR << 5) | 0x10 | 0x01);
  
  PushIntLtl(MakeCRC16_X25OutBuff(1, 5));
  
  PushChar(0x7E);

  Query36(1000, 9);
}
*/

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
