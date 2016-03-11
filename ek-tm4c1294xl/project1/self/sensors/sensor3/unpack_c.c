/*------------------------------------------------------------------------------
UNPACK_C!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "unpack_c.h"



#ifndef SKIP_C

void    DecompressC(void)
{
  if ((IndexInBuff() == 6) && (InBuff(1) == 0x83) && (InBuff(2) == 0x24) && (InBuff(3) == 0x05))
  {
    SetCountInBuff(6);
    mpSerial[ibPort] = SER_POSTINPUT_MASTER;
  }
}

#endif
