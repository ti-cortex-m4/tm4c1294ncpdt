/*------------------------------------------------------------------------------
monitor36*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "include38.h"
#include "hdlc.h"
#include "crc16x25.h"
#include "monitor38.h"



static void MonitorControl(uchar  bControl) {
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



void    MonitorOutput38(void)
{
  MonitorString("\n Output HDLC:");

  uint wFormat = OutBuff(1)*0x100 + OutBuff(2);
  MonitorString(" Format="); MonitorIntHex(wFormat); //MonitorCharHex(OutBuff(1)); MonitorCharHex(OutBuff(2));
  uint wSize = wFormat & 0x0FFF;
  MonitorString(" wSize="); MonitorIntHex(wSize);

  uint wCRCexpected = MakeCRC16_X25OutBuff(1, wSize-2);
  MonitorString(" CRC="); MonitorIntHex(wCRCexpected);
  int i = wSize-1;
  uint wCRCactual = OutBuff(i) + OutBuff(i+1)*0x100; //MonitorIntHex(wCRCactual);
  (wCRCexpected == wCRCactual) ? MonitorString(" CRC_ok") : MonitorString(" CRC_error");

  MonitorControl(OutBuff(3 + GetHdlcAddressesSize()));
}



bool    ValidInput38(void)
{
  MonitorString("\n Input HDLC:");
  InitPop(1);

  uint wFormat = PopIntBig();
  MonitorString(" Format="); MonitorIntHex(wFormat);
  uint wSize = wFormat & 0x07FF;
  MonitorString(" wSize="); MonitorIntHex(wSize);

  uint wCRCexpected = MakeCRC16_X25InBuff(1, wSize-2);
  MonitorString(" CRC="); MonitorIntHex(wCRCexpected);
  int i = wSize-1;
  uint wCRCactual = InBuff(i) + InBuff(i+1)*0x100; //MonitorIntHex(wCRCactual);

  if (wCRCexpected != wCRCactual) { //? MonitorString(" CRC_ok") : MonitorString(" CRC_error");
    MonitorString(" CRC_error");
    return false;
  } else {
    MonitorString(" CRC_ok");
  }

  MonitorControl(InBuff(3 + GetHdlcAddressesSize()));

  return true;
}
/*
void    MonitorInput36(void)
{
  MonitorString("\n Input HDLC:");
  InitPop(1);

  uint wFormat = PopIntBig();
  MonitorString(" Format="); MonitorIntHex(wFormat);
  uint wSize = wFormat & 0x0FFF;
  MonitorString(" wSize="); MonitorIntHex(wSize);

  uint wCRCexpected = MakeCRC16_X25InBuff(1, wSize-2);
  MonitorString(" CRC="); MonitorIntHex(wCRCexpected);
  int i = wSize-1;
  uint wCRCactual = InBuff(i) + InBuff(i+1)*0x100; //MonitorIntHex(wCRCactual);
  (wCRCexpected == wCRCactual) ? MonitorString(" CRC_ok") : MonitorString(" CRC_error");

  MonitorControl(InBuff(3 + GetDlmsAddressesSize()));
}
*/

bool    ValidateIframe(uchar  bNS_client, uchar  bNR_client)
{
  uchar bControl = InBuff(3 + GetHdlcAddressesSize());
  uchar bNS_server = (bControl & 0x0E) >> 1;
  uchar bNR_server = (bControl & 0xE0) >> 5;

  if (bNS_client != bNS_server) {
    MonitorString("I-frame N(S) client/server error"); MonitorCharHex(bNS_client); MonitorCharHex(bNS_server);
    return false;
  }

  if ((bNR_client + 1) != bNR_server) {
    MonitorString("I-frame N(R) client/server error"); MonitorCharHex(bNR_client); MonitorCharHex(bNR_server);
    return false;
  }

  return true;
}


bool    ValidateSframe(uchar  bNR_client)
{
  uchar bControl = InBuff(3 + GetHdlcAddressesSize());
  uchar bNR_server = (bControl & 0xE0) >> 5;

  if (bNR_client != bNR_server) {
    MonitorString("S-frame N(R) client/server error"); MonitorCharHex(bNR_client); MonitorCharHex(bNR_server);
    return false;
  }

  return true;
}



bool    LastSegmentDMLS(void)
{
  InitPop(1);
  uint wFormat = PopIntBig();
  bool fLastSegment = (wFormat & 0x0800) == 0;
  MonitorString(" Last_Segment="); MonitorBool(fLastSegment);
  return fLastSegment;
}



bool    UseBlocksDMLS(void)
{
  InitPop(9 + GetHdlcAddressesSize());
  uint w = PopIntBig();
  bool fUseBlocks = (w == 0xC402);
  MonitorString(" Use_Blocks="); MonitorIntHex(w); MonitorBool(fUseBlocks);
  return fUseBlocks;
}



bool    LastBlockDMLS(void)
{
  InitPop(12 + GetHdlcAddressesSize());
  uchar b = PopChar();
  bool fLastBlock = (b != 0);
  MonitorString(" Last_Block="); MonitorCharHex(b); MonitorBool(fLastBlock);
  return fLastBlock;
}
