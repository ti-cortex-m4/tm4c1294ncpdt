/*------------------------------------------------------------------------------
dlms.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../time/delay.h"
#include "../../display/display.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../digitals/address/ascii_address.h"
#include "crc16x25.h"
#include "io39.h"
#include "error39.h"
#include "hdlc_address.h"
#include "dlms_push.h"
#include "dlms.h"



void    DISC(void)
{
#ifdef MONITOR_39_NAMES
  MonitorString("\n\n DISC ");
#endif

  InitPush(0);

  uint wSize = 5+GetHdlcAddressesSize(); // 7

  PushChar(0x7E);
  PushFormatDLMS(wSize);
  PushHdlcAddresses();
  PushChar(0x53); // DISC

  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5
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
  PushHdlcAddresses();
  PushChar(0x93); // SNRM
  
  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5
  
  PushChar(0x81); // format identifier
  PushChar(0x80); // group identifier
  PushChar(0x14); // group length
  
  PushChar(0x05); // parameter identifier (maximum information field length пїЅ transmit)
  PushChar(0x02); // parameter length
  PushChar(0x00);
  PushChar(0x80);
  
  PushChar(0x06); // parameter identifier (maximum information field length пїЅ receive)
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

  PushIntLtl(MakeCRC16X25OutBuff(1, wSize-2)); // 30
  PushChar(0x7E);

  Query39(1000, wSize+2); // 34
}


// Green Book, 11.5 Encoding of the AARQ APDU
void    AARQ(uchar  bNS, uchar  bNR)
{
#ifdef MONITOR_39_NAMES
  MonitorString("\n\n AARQ ");
#endif

  line Pass = mpphAsciiAddress[diCurr.bAddress-1];
  uchar bPassSize = strlen((char const *)Pass.szLine);

  uint wSize = 66 - 8 + bPassSize + GetHdlcAddressesSize(); // 0x44 68

  InitPush(0);
  PushChar(0x7E);
  
  PushFormatDLMS(wSize);
  PushHdlcAddresses();

  PushChar(((bNR & 0x07) << 5) | 0x10 | ((bNS & 0x07) << 1) | 0x00);
  
  PushIntLtl(MakeCRC16X25OutBuff(1, 3+GetHdlcAddressesSize())); // 5

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

  Query39(1000, wSize+2); // 70
}


/*
right password
7e a0 47 00 02 12 9d 03 10 cf 5e e6 e6 00 60 36 a1 09 06 07 60 85 74 05 08 01 01 8a 02 07 80 8b 07 60 85 74 05 08 02 01 ac 0a 80 08 78 52 77 50 62 45 78 46 be 10 04 0e 01 00 00 00 06 5f 1f 04 00 00 7e 1f 01 00 af df 7e
7e a0 3a 03 00 02 12 9d 30 fc 5c e6 e7 00 61 29 a1 09 06 07 60 85 74 05 08 01 01 a2 03 02 01 00 a3 05 a1 03 02 01 00 be 10 04 0e 08 00 06 5f 1f 04 00 00 18 1d 01 80 00 07 a1 dc 7e

wrong password
7e a0 47 00 02 12 9d 03 10 cf 5e e6 e6 00 60 36 a1 09 06 07 60 85 74 05 08 01 01 8a 02 07 80 8b 07 60 85 74 05 08 02 01 ac 0a 80 08 78 52 77 50 62 45 78 47 be 10 04 0e 01 00 00 00 06 5f 1f 04 00 00 7e 1f 01 00 e6 4c 7e
7e a0 3a 03 00 02 12 9d 30 fc 5c e6 e7 00 61 29 a1 09 06 07 60 85 74 05 08 01 01 a2 03 02 01 01 a3 05 a1 03 02 01 0d be 10 04 0e 08 00 06 5f 1f 04 00 00 18 1d 01 80 00 07 b2 65 7e
*/
bool    AARE_CheckPass_Internal(void)
{
  uint wSize = (InBuff(1) & 0x07)*0x100 + InBuff(2);

  uint i;
  for (i=6+GetHdlcAddressesSize(); i<wSize-4; i++)
  {
    if ((InBuff(i+0) == 0xA2) &&
        (InBuff(i+1) == 0x03) &&
        (InBuff(i+2) == 0x02) &&
        (InBuff(i+3) == 0x01))
    {
      uchar bResult = InBuff(i+4);

      if (bResult == 0)
        return true;
      else if (bResult == 1) {
        Error39_(1, bResult);
        return false;
      } else {
        Error39_(2, bResult);
        return false;
      }
    }
  }

  Error39(3);
  return false;
}


bool    AARE_CheckPass(void)
{
  bool fSuccess = AARE_CheckPass_Internal();
  if (!fSuccess) {
    Clear(); sprintf(szLo+4, "пароль ?"); Delay(1000);
  }
  return fSuccess;
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
