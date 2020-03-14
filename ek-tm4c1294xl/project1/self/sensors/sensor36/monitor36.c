/*------------------------------------------------------------------------------
monitor36.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "monitor36.h"



void    MonitorOutput36(void)
{
}



void    MonitorInput36(void)
{
//  MonitorString("\n");
  InitPop(1);

  uint wFormat = PopIntLtl();
  MonitorString("\n Format"); MonitorIntHex(wFormat);

  PopChar();
  PopChar();

  uchar bControl = PopIntLtl();
  MonitorString("\n Control="); MonitorCharHex(bControl);

  if ((bControl & 0x01) == 0x00) {
    MonitorString(" I-frame");
  } else if ((bControl & 0x03) == 0x01) {
    MonitorString(" S-frame");
  } else if ((bControl & 0x03) == 0x03) {
    MonitorString(" U-frame");
  }

  if ((bControl & 0x10) == 0x00) {
    MonitorString(" F=0");
  } else {
    MonitorString(" F=1");
  }
}
