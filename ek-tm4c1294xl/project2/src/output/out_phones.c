/*------------------------------------------------------------------------------
OUT_PHONES,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_phones.h"
#include "../serial/ports.h"
#include "../digitals/phones.h"
#include "../flash/files.h"



void    OutGetPhone(void)
{
  if (bInBuff6 < bCANALS)
    Common(&mpphPhones[ bInBuff6 ], sizeof(phone));
  else
    Result(bRES_BADADDRESS);
}


void    OutSetPhone(void)
{
  if (enGlobal == GLB_PROGRAM)
  {
    if (bInBuff6 < bCANALS)
    {
      static phone ph;

      uchar i;
      for (i=0; i<bPHONE_SIZE; i++)
      {
        ph.szNumber[i] = InBuff(7+i);
      }

      if (TruePhone(&ph) == true)
      {
        mpphPhones[ bInBuff6 ] = ph;

        if (bInBuff6 == bCANALS - 1)
          SaveFile(&flPhones);

        LongResult(bRES_OK);
      }
      else Result(bRES_BADDATA);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDPROGRAM);
}
