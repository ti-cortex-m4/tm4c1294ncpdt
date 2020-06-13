/*------------------------------------------------------------------------------
unpack36*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "unpack39.h"



void    Decompress39(void)
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

/*
 *  Output: out=9 in=1000
 7e a0 07 03 03 91 9e 32 7e
 Input: in=7
 7e a0 41 03 03 58 7e
 Input HDLC:  Format=a041 wSize=0041 wCRCexpected=eac1 wCRCactual=3f00 CRC_error error1=2
 error 11
 */
 */
