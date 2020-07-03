/*------------------------------------------------------------------------------
DEVICE36*C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "crc16x25.h"
#include "io39.h"
#include "hdlc_address.h"
#include "dlms_push.h"
#include "device39.h"



void    DISC(void)
{
#ifdef MONITOR_39_NAMES
  MonitorString("\n\n DISC");
#endif

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


void    SNRM(void)
{
#ifdef MONITOR_39_NAMES
  MonitorString("\n\n SNRM ");
#endif

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
void    AARQ(uchar  bNS, uchar  bNR)
{
#ifdef MONITOR_39_NAMES
  MonitorString("\n\n AARQ ");
#endif

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

  PushChar(0x60); // AARQ
  PushChar(0x36); // length
  
  PushChar(0xA1); // application-context-name
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
  
  PushChar(0x8A); // acse-requirements
  PushChar(0x02); // length
  PushChar(0x07);
  PushChar(0x80);
  
  PushChar(0x8B); // mechanism-name
  PushChar(0x07); // length
  PushChar(0x60);
  PushChar(0x85);
  PushChar(0x74);
  PushChar(0x05);
  PushChar(0x08);
  PushChar(0x02);
  PushChar(0x01);
  
  PushChar(0xAC); // calling-authentication-value
  PushChar(0x0A); // length
  PushChar(0x80);
  PushChar(0x08); // length
  PushChar(0x78);
  PushChar(0x52);
  PushChar(0x77);
  PushChar(0x50);
  PushChar(0x62);
  PushChar(0x45);
  PushChar(0x78);
  PushChar(0x46);
  
  PushChar(0xBE); // user-information
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



void    RR(uchar  bNR)
{
#ifdef MONITOR_39_NAMES
  MonitorString("\n\n RR ");
#endif

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
