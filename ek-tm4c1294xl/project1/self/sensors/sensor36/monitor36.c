/*------------------------------------------------------------------------------
monitor36.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "include36.h"
#include "dlms_addresses.h"
#include "monitor36.h"



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



void    MonitorOutput36(void)
{
  MonitorString("\n Output:");

  MonitorString(" Format="); MonitorCharHex(OutBuff(1)); MonitorCharHex(OutBuff(2));
  MonitorControl(OutBuff(3 + GetDlmsAddressesSize()));
}



void    MonitorInput36(void)
{
  MonitorString("\n Input:");
  InitPop(1);

  uint wFormat = PopIntBig();
  MonitorString(" Format="); MonitorIntHex(wFormat);

  uint wSize = wFormat & 0x0FFF;
  MonitorString(" wSize="); MonitorIntHex(wSize);

  MonitorString(" CRC="); MonitorIntHex(MakeCRC16_X25InBuff(1, wSize-2));

  uchar i;
  for (i=0; i<GetDlmsAddressesSize(); i++)
    PopChar();

  MonitorControl(PopChar());
}
