/*------------------------------------------------------------------------------
DEVICE36*C


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
#include "device39.h"



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

  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5
//  PushChar(0x80);
//  PushChar(0xD7);

  PushChar(0x7E);

  Query39(1000, wSize+2); // 9
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
  
  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5
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

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2)); // 30
//  PushChar(0xCE);
//  PushChar(0x6A);

  PushChar(0x7E);

  Query39(1000, wSize+2); // 34
}


// Green Book, 11.5 Encoding of the AARQ APDU
void    Query38_AARQ(uchar  bNS, uchar  bNR)
{
  MonitorString("\n\n AARQ ");

  uint wSize = 66 + GetHdlcAddressesSize(); // 0x44 68

  InitPush(0);
  PushChar(0x7E);
  
  PushFormatDLMS(wSize);
  PushHdlcAddresses();

  bNS = 0;
  bNR = 0;
//  MonitorString("Control{N(R)=0,N(S)=0} 10 ? ");
  PushChar((bNR << 5) | 0x10 | (bNS << 1) | 0x00);
  
  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5

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
  
  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));
  
  PushChar(0x7E);

  Query39(1000, wSize+2); // 70
}



void    Query38_RR(uchar  bNR)
{
  MonitorString("\n\n RR ");

  uint wSize = 5 + GetHdlcAddressesSize();

  InitPush(0);
  PushChar(0x7E);
  PushFormatDLMS(wSize);
  PushHdlcAddresses();

  PushChar((bNR << 5) | 0x10 | 0x01);
  
  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5
  PushChar(0x7E);

  Query39(1000, wSize+2); // 9
}



runner39 InitRunner(void)
{
  runner39 runner;

  runner.bNS = 0;
  runner.bNR = 0;
  runner.bInvokeId = 0;

  return runner;
}
