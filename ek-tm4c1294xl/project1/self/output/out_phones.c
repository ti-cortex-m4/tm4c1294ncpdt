/*------------------------------------------------------------------------------
OUT_PHONES,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_phones.h"
#include "../serial/ports.h"
#include "../digitals/phones.h"
#include "../nvram/cache.h"



void    OutGetPhone(void)
{
  if (bInBuff6 < bCANALS)
    Common(&mpphPhones[ bInBuff6 ], sizeof(line));
  else
    Result(bRES_BADADDRESS);
}


void    OutSetPhone(void)
{
  if (enGlobal == GLB_PROGRAM)
  {
    if (bInBuff6 < bCANALS)
    {
      static line ph;

      uchar i;
      for (i=0; i<bLINE_SIZE; i++)
      {
        ph.szLine[i] = InBuff(7+i);
      }

      if (IsValidPhone(&ph) == true)
      {
        mpphPhones[ bInBuff6 ] = ph;

        if (bInBuff6 == bCANALS - 1)
          SaveCache(&chPhones);

        LongResult(bRES_OK);
      }
      else Result(bRES_BADDATA);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDPROGRAM);
}



void    OutPhonesExt(void)
{
  InitPushPtr();
  uchar wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      Push(&mpphPhones[c], sizeof(line));
      wSize += sizeof(line);
    }
  }

  OutptrOutBuff(wSize);
}
