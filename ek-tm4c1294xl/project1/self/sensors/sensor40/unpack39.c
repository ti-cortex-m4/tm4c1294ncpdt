/*------------------------------------------------------------------------------
unpack39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "unpack39.h"



void    Unpack39(void)
{
  if (mpSerial[ibPort] != SER_INPUT_MASTER)
    return;


  uchar c = 0;

  uchar i;
  for (i=0; i<IndexInBuff(); i++) {
    if (InBuff(i) == 0x7E) c++;
  }
  if (c < 2)
    return;


  if ((InBuff(0) != 0x7E) || (InBuff(IndexInBuff()-1) != 0x7E))
    return;


  uint wSize = (InBuff(1) & 0x07)*0x100 + InBuff(2) + 2;
  if (wSize != IndexInBuff())
    return;


  MonitorIn();

  mpSerial[ibPort] = SER_POSTINPUT_MASTER;
}
