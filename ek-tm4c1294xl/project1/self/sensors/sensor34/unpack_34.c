/*------------------------------------------------------------------------------
UNPACK_34.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "unpack_34.h"



#ifndef SKIP_34

void    Unpack34(void)
{

  if (IndexInBuff() > 6) {
    uint wSize = InBuff(4) + 0x100*InBuff(5);
    if (IndexInBuff() == 4+2+2+wSize*24+2)
    {
      SetCountInBuff(IndexInBuff());
      mpSerial[ibPort] = SER_POSTINPUT_MASTER;
    }
  }
}

#endif
