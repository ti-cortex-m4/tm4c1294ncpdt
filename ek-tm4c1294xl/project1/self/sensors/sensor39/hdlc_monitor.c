/*------------------------------------------------------------------------------
hdlc_monitor.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "hdlc_address.h"
#include "crc16x25.h"
#include "hdlc_monitor.h"



//#define MONITOR_HDLC  1



void    MonitorControl(uchar  bControl) {
  MonitorString(" Control="); MonitorCharHex(bControl);

  if ((bControl & 0x01) == 0x00) {
    MonitorString("I-frame");
    MonitorString(" N(R)=");  MonitorCharDec((bControl & 0xE0) >> 5);
    MonitorString(" N(S)=");  MonitorCharDec((bControl & 0x0E) >> 1);
  } else if ((bControl & 0x03) == 0x01) {
    MonitorString("S-frame");
    MonitorString(" N(R)=");  MonitorCharDec((bControl & 0xE0) >> 5);
  } else if ((bControl & 0x03) == 0x03) {
    MonitorString("U-frame");
  }

  if ((bControl & 0x10) == 0x00) {
    MonitorString(" F=0");
  } else {
    MonitorString(" F=1");
  }

  if ((bControl & 0x01) == 0x00) {
    MonitorString(" I");
  } else if ((bControl & 0x0F) == 0x01) {
    MonitorString(" RR");
  } else if ((bControl & 0x0F) == 0x05) {
    MonitorString(" RNR");
  } else if ((bControl & 0xEF) == 0x83) {
    MonitorString(" SNRM");
  } else if ((bControl & 0xEF) == 0x43) {
    MonitorString(" DISC");
  } else if ((bControl & 0xEF) == 0x63) {
    MonitorString(" UA");
  } else if ((bControl & 0xEF) == 0x0F) {
    MonitorString(" DM");
  } else if ((bControl & 0xEF) == 0x87) {
    MonitorString(" FRMR");
  } else if ((bControl & 0xEF) == 0x03) {
    MonitorString(" UI");
  } else {
    MonitorString(" ?");
  }
}



void    MonitorOutputHDLC(void)
{
#ifdef MONITOR_39
#ifdef MONITOR_HDLC

  uint wFormat = OutBuff(1)*0x100 + OutBuff(2);
  uint wSize = wFormat & 0x0FFF;

  uint wCRCexpected = MakeCRC16X25OutBuff(1, wSize-2);
  
  int i = wSize-1;
  uint wCRCactual = OutBuff(i) + OutBuff(i+1)*0x100;

  MonitorString("\n Output HDLC: ");

  MonitorString(" Format="); MonitorIntHex(wFormat); 
  MonitorString(" wSize="); MonitorIntHex(wSize);

  MonitorString(" wCRCexpected="); MonitorIntHex(wCRCexpected);
  MonitorString(" wCRCactual="); MonitorIntHex(wCRCactual);
  (wCRCexpected == wCRCactual) ? MonitorString(" CRC_ok") : MonitorString(" CRC_error");

  MonitorControl(OutBuff(3 + GetHdlcAddressesSize()));
  
#endif  
#endif  
}



bool    ValidateInputHDLC(void)
{
  InitPop(1);

  uint wFormat = PopIntBig();
  uint wSize = wFormat & 0x07FF;

  uint wCRCexpected = MakeCRC16X25InBuff(1, wSize-2);
  
  int i = wSize-1;
  uint wCRCactual = InBuff(i) + InBuff(i+1)*0x100; 

#ifdef MONITOR_39
#ifdef MONITOR_HDLC

  MonitorString("\n Input HDLC: ");
  MonitorString(" Format="); MonitorIntHex(wFormat);
  MonitorString(" wSize="); MonitorIntHex(wSize);

  MonitorString(" wCRCexpected="); MonitorIntHex(wCRCexpected);
  MonitorString(" wCRCactual="); MonitorIntHex(wCRCactual);
  (wCRCexpected == wCRCactual) ? MonitorString(" CRC_ok") : MonitorString(" CRC_error");

#endif  
#endif 

  if (wCRCexpected != wCRCactual) { 
    return false;
  }

#ifdef MONITOR_39
#ifdef MONITOR_HDLC
  MonitorControl(InBuff(3 + GetHdlcAddressesSize()));  
#endif  
#endif 

  return true;
}



bool    ValidateIframe(uchar  bNS_client, uchar  bNR_client)
{
  uchar bControl = InBuff(3 + GetHdlcAddressesSize());
  uchar bNS_server = (bControl & 0x0E) >> 1;
  uchar bNR_server = (bControl & 0xE0) >> 5;

  if (bNS_client % 8 != bNS_server % 8) {
#ifdef MONITOR_39    
    MonitorString(" I-frame N(S) client/server error "); MonitorCharHex(bNS_client); MonitorCharHex(bNS_server);
#endif    
    return false;
  }

  if ((bNR_client + 1) % 8 != bNR_server % 8) {
#ifdef MONITOR_39    
    MonitorString(" I-frame N(R) client/server error "); MonitorCharHex(bNR_client); MonitorCharHex(bNR_server);
#endif    
    return false;
  }

  return true;
}


bool    ValidateSframe(uchar  bNR_client)
{
  uchar bControl = InBuff(3 + GetHdlcAddressesSize());
  uchar bNR_server = (bControl & 0xE0) >> 5;

  if (bNR_client % 8 != bNR_server % 8) {
#ifdef MONITOR_39    
    MonitorString("S-frame N(R) client/server error "); MonitorCharHex(bNR_client); MonitorCharHex(bNR_server);
#endif
    return false;
  }

  return true;
}



void    ValidateFrame(uchar  bNS_client, uchar  bNR_client)
{
  uchar bControl = InBuff(3 + GetHdlcAddressesSize());

  if ((bControl & 0x01) == 0x00) {
    MonitorString(" I-frame validation ");
    uchar bNS_server = (bControl & 0x0E) >> 1;
    uchar bNR_server = (bControl & 0xE0) >> 5;

    if ((bNS_client + 1) % 8 != bNR_server % 8) {
  #ifdef MONITOR_39
      MonitorString(" I-frame validation error: N(S) client / N(R) server "); MonitorCharHex((bNS_client + 1) % 8); MonitorCharHex(bNR_server % 8);
  #endif
    }

    if (bNR_client % 8 != bNS_server % 8) {
  #ifdef MONITOR_39
      MonitorString(" I-frame validation error: N(R) client / N(S) server "); MonitorCharHex(bNR_client % 8); MonitorCharHex(bNS_server % 8);
  #endif
    }
  } else if ((bControl & 0x03) == 0x01) {
    MonitorString(" S-frame validation ");
    uchar bNR_server = (bControl & 0xE0) >> 5;

    if ((bNS_client + 1) % 8 != bNR_server % 8) {
  #ifdef MONITOR_39
      MonitorString(" S-frame validation error: N(S) client / N(R) server "); MonitorCharHex((bNS_client + 1) % 8); MonitorCharHex(bNR_server % 8);
  #endif
    }
  } else if ((bControl & 0x03) == 0x03) {
    MonitorString("U-frame validation ");
  }
}



void    ShowSframe(uchar  bNR_client)
{
  uchar bControl = InBuff(3 + GetHdlcAddressesSize());
  uchar bNR_server = (bControl & 0xE0) >> 5;

  if (bNR_client % 8 != bNR_server % 8) {
#ifdef MONITOR_39
    MonitorString("S-frame N(R) client/server "); MonitorCharHex(bNR_client); MonitorCharHex(bNR_server);
#endif
  }
}



bool    LastSegmentDMLS(void)
{
  InitPop(1);
  uint wFormat = PopIntBig();
  bool fLastSegment = (wFormat & 0x0800) == 0;

#ifdef MONITOR_39  
  MonitorString("\n Last_Segment="); MonitorBool(fLastSegment);
#endif

  return fLastSegment;
}



bool    UseBlocksDMLS(void)
{
  InitPop(9 + GetHdlcAddressesSize());
  uint w = PopIntBig();
  bool fUseBlocks = (w == 0xC402);

#ifdef MONITOR_39
  MonitorString("\n Use_Blocks="); MonitorIntHex(w); MonitorBool(fUseBlocks);
#endif  

  return fUseBlocks;
}



bool    LastBlockDMLS(void)
{
  InitPop(12 + GetHdlcAddressesSize());
  uchar b = PopChar();
  bool fLastBlock = (b != 0);

#ifdef MONITOR_39  
  MonitorString("\n Last_Block="); MonitorCharHex(b); MonitorBool(fLastBlock);
#endif  

  return fLastBlock;
}
