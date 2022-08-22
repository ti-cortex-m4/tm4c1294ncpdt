/*------------------------------------------------------------------------------
dlms.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../digitals/address/ascii_address.h"
#include "crc16x25.h"
#include "io40.h"
#include "hdlc_address.h"
#include "dlms_push.h"
#include "dlms.h"



void    DISC(void)
{
#ifdef MONITOR_40_NAMES
  MonitorString("\n\n DISC ");
#endif

  InitPush(0);

  uint wSize = 5+GetHdlcAddressesSize();

  PushChar(0x7E);
  PushFormatDLMS(wSize);
  PushHdlcAddresses();
  PushChar(0x53); // DISC

  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize()));
  PushChar(0x7E);

  Query40(1000, wSize+2);
}


void    SNRM(void)
{
#ifdef MONITOR_40_NAMES
  MonitorString("\n\n SNRM ");
#endif

  uint wSize = 30 + GetHdlcAddressesSize();

  InitPush(0);
  PushChar(0x7E);
  
  PushFormatDLMS(wSize);
  PushHdlcAddresses();
  PushChar(0x93); // SNRM
  
  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize()));
  
  PushChar(0x81); // format identifier
  PushChar(0x80); // group identifier
  PushChar(0x14); // group length
  
  PushChar(0x05); // parameter identifier (maximum information field length � transmit)
  PushChar(0x02); // parameter length
  PushChar(0x00);
  PushChar(0x80);
  
  PushChar(0x06); // parameter identifier (maximum information field length � receive)
  PushChar(0x02); // parameter length
  PushChar(0x00);
  PushChar(0x80);
  
  PushChar(0x07); // parameter identifier (window size, transmit)
  PushChar(0x04); // parameter length
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x01);
  
  PushChar(0x08); // parameter identifier (window size, receive)
  PushChar(0x04); // parameter length
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x00);
  PushChar(0x01);

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2));
  PushChar(0x7E);

  Query40(1000, wSize+2);
}


// Green Book, 11.5 Encoding of the AARQ APDU
void    AARQ(uchar  bNS, uchar  bNR)
{
#ifdef MONITOR_40_NAMES
  MonitorString("\n\n AARQ ");
#endif

  line Pass = mpphAsciiAddress[diCurr.bAddress-1];
  uchar bPassSize = strlen((char const *)Pass.szLine);

  uint wSize = 58 + bPassSize + GetHdlcAddressesSize();

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

  PushChar(0x60); // AARQ
  PushChar(0x36-0x0A+bPassSize+2); // length
  
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
  PushChar(bPassSize+2); // length
  PushChar(0x80);
#if true
  PushChar(bPassSize);
  Push(Pass.szLine, bPassSize);
#else
  PushChar(0x08); // length
  PushChar(0x78); // xRwPbExF
  PushChar(0x52);
  PushChar(0x77);
  PushChar(0x50);
  PushChar(0x62);
  PushChar(0x45);
  PushChar(0x78);
  PushChar(0x46);
#endif

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

  Query40(1000, wSize+2);
}



void    RR(uchar  bNR)
{
#ifdef MONITOR_40_NAMES
  MonitorString("\n\n RR ");
#endif

  uint wSize = 5 + GetHdlcAddressesSize();

  InitPush(0);
  PushChar(0x7E);
  PushFormatDLMS(wSize);
  PushHdlcAddresses();

  PushChar(((bNR & 0x07) << 5) | 0x10 | 0x01);
  
  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize()));
  PushChar(0x7E);

  Query40(1000, wSize+2);
}
