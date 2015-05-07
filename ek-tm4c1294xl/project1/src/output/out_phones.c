/*------------------------------------------------------------------------------
OUT_PHONES.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_tariffs.h"
#include "../serial/ports.h"
#include "../time/timedate.h"
#include "../keyboard/keyboard.h"
#include "../tariffs/relaxs.h"
#include "../flash/files.h"



void    OutGetPhones(void)
{
  if (bInBuff6 < bCANALS)
    Common(&mpphPhones[ bInBuff6 ], sizeof(phone));
  else
    Result(bRES_BADADDRESS);
}


void    OutSetPhones(void)
{
  if (enGlobal == GLB_PROGRAM)
  {
    if (bInBuff6 < bCANALS)
    {
      for (i=0; i<bPHONENUMBER; i++)
        phT.szNumber[i] = InBuff(7+i);

      if (TruePhone() == 1)
      {
        mpphPhones[ bInBuff6 ] = phT;
        LongResult(bRES_OK);
      }
      else Result(bRES_BADDATA);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDPROGRAM);
}
