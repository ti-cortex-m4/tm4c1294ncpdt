/*------------------------------------------------------------------------------
unpack36.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "unpack36.h"



void    Decompress36(void)
{
  uchar i,j;

  if (mpSerial[ibPort] != SER_INPUT_MASTER) return;

  j = 0;
  for (i=0; i<IndexInBuff(); i++) if (InBuff(i) == 0x7E) j++;
  if (j != 2) return;

  if ((InBuff(0) != 0x7E) || (InBuff(IndexInBuff()-1) != 0x7E))
    return;

//  Unpack36(); // TODO
  MonitorIn();

  mpSerial[ibPort] = SER_POSTINPUT_MASTER;
}
