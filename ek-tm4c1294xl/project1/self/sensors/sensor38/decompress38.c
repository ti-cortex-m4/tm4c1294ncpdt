/*------------------------------------------------------------------------------
unpack38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "unpack38.h"



void    Unpack38(void)
{
  uchar i = 1;
  uchar j = 1;

  while (i < IndexInBuff()) {
    if ((InBuff(i) == 0xDB) && (InBuff(i+1) == 0xDD)) {
      SetInBuff(j, 0xDB);
      i += 2;
      j++;
    } else if ((InBuff(i) == 0xDB) && (InBuff(i+1) == 0xDC)) {
      SetInBuff(j, 0xC0);
      i += 2;
      j++;
    } else {
      SetInBuff(j, InBuff(i));
      i++;
      j++;
    }
  }

  SetIndexInBuff(j);
}
