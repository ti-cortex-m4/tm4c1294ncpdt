/*------------------------------------------------------------------------------
OUT_COMMON.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../serial/ports.h"



void    OutReal(real  *mpe, uchar  bCount)
{
  InitPushCRC();
  uint wSize = 0;

  while (bCount-- > 0)
  {
    PushFloat(*mpe++);
    wSize += sizeof(real);
  }

  Output(wSize);
}
