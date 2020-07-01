/*------------------------------------------------------------------------------
hdlc_monitor.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "include39.h"
#include "crc16x25.h"
#include "hdlc_address.h"
#include "hdlc_monitor.h"



#ifdef MONITOR_39_MONITOR

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

#endif



void    MonitorOutputHDLC(void)
{
#ifdef MONITOR_39_MONITOR

  uint wFormat = OutBuff(1)*0x100 + OutBuff(2);
  uint wSize = wFormat & 0x0FFF;

  uint wCRCexpected = MakeCRC16X25OutBuff(1, wSize-2);
  
  int i = wSize-1;
  uint wCRCactual = OutBuff(i) + OutBuff(i+1)*0x100;

  MonitorString("\n Output HDLC: ");

  MonitorString(" Format="); MonitorIntHex(wFormat); 
  MonitorString(" wSize="); MonitorIntHex(wSize);

#ifdef MONITOR_39_CRC
  MonitorString(" wCRCexpected="); MonitorIntHex(wCRCexpected);
  MonitorString(" wCRCactual="); MonitorIntHex(wCRCactual);
  (wCRCexpected == wCRCactual) ? MonitorString(" CRC_ok") : MonitorString(" CRC_error");
#endif

  MonitorControl(OutBuff(3 + GetHdlcAddressesSize()));
  
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

#ifdef MONITOR_39_MONITOR

  MonitorString("\n Input HDLC: ");
  MonitorString(" Format="); MonitorIntHex(wFormat);
  MonitorString(" wSize="); MonitorIntHex(wSize);

#ifdef MONITOR_39_CRC
  MonitorString(" wCRCexpected="); MonitorIntHex(wCRCexpected);
  MonitorString(" wCRCactual="); MonitorIntHex(wCRCactual);
  (wCRCexpected == wCRCactual) ? MonitorString(" CRC_ok") : MonitorString(" CRC_error");
#endif

#endif 

  if (wCRCexpected != wCRCactual) { 
    return false;
  }

#ifdef MONITOR_39_MONITOR
  MonitorControl(InBuff(3 + GetHdlcAddressesSize()));  
#endif 

  return true;
}



uchar   ValidateFrame(uchar  bNS_client, uchar  bNR_client)
{
  uchar bControl = InBuff(3 + GetHdlcAddressesSize());

  if ((bControl & 0x01) == 0x00) {
#ifdef MONITOR_39_MONITOR
    MonitorString(" I-frame validation ");
#endif
    uchar bNS_server = (bControl & 0x0E) >> 1;
    uchar bNR_server = (bControl & 0xE0) >> 5;

    if ((bNS_client + 1) % 8 != bNR_server % 8) {
#ifdef MONITOR_39_MONITOR
      MonitorString(" I-frame validation error: N(S) client / N(R) server "); MonitorCharHex((bNS_client + 1) % 8); MonitorCharHex(bNR_server % 8);
#endif
      return 10+0;
    }

    if (bNR_client % 8 != bNS_server % 8) {
#ifdef MONITOR_39_MONITOR
      MonitorString(" I-frame validation error: N(R) client / N(S) server "); MonitorCharHex(bNR_client % 8); MonitorCharHex(bNS_server % 8);
#endif
      return 10+1;
    }
  } else if ((bControl & 0x03) == 0x01) {
#ifdef MONITOR_39_MONITOR
    MonitorString(" S-frame validation ");
#endif
    uchar bNR_server = (bControl & 0xE0) >> 5;

    if ((bNS_client + 1) % 8 != bNR_server % 8) {
#ifdef MONITOR_39_MONITOR
      MonitorString(" S-frame validation error: N(S) client / N(R) server "); MonitorCharHex((bNS_client + 1) % 8); MonitorCharHex(bNR_server % 8);
#endif
      return 10+2;
    }
  } else if ((bControl & 0x03) == 0x03) {
#ifdef MONITOR_39_MONITOR
    MonitorString("U-frame validation ");
#endif
    return 10+3;
  }

  return 0;
}



bool    LastSegmentDMLS(void)
{
  InitPop(1);
  uint wFormat = PopIntBig();
  bool fLastSegment = (wFormat & 0x0800) == 0;

#ifdef MONITOR_39_MONITOR
  MonitorString("\n Last_Segment="); MonitorBool(fLastSegment);
#endif

  return fLastSegment;
}



bool    UseBlocksDMLS(void)
{
  InitPop(9 + GetHdlcAddressesSize());
  uint w = PopIntBig();
  bool fUseBlocks = (w == 0xC402);

#ifdef MONITOR_39_MONITOR
  MonitorString("\n Use_Blocks="); MonitorIntHex(w); MonitorBool(fUseBlocks);
#endif  

  return fUseBlocks;
}



bool    LastBlockDMLS(void)
{
  InitPop(12 + GetHdlcAddressesSize());
  uchar b = PopChar();
  bool fLastBlock = (b != 0);

#ifdef MONITOR_39_MONITOR
  MonitorString("\n Last_Block="); MonitorCharHex(b); MonitorBool(fLastBlock);
#endif  

  return fLastBlock;
}
