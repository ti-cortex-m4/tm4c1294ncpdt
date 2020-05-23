/*------------------------------------------------------------------------------
decompress38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "unpack38.h"
#include "decompress38.h"



void    Decompress38(void)
{
  uchar i,j;

  if (mpSerial[ibPort] != SER_INPUT_MASTER) return;

  j = 0;
  for (i=0; i<IndexInBuff(); i++) if (InBuff(i) == 0xC0) j++;
  if (j != 2) return;

  if ((InBuff(0) != 0xC0) || (InBuff(IndexInBuff()-1) != 0xC0))
    return;

  Unpack38();

  mpSerial[ibPort] = SER_POSTINPUT_MASTER;
}
