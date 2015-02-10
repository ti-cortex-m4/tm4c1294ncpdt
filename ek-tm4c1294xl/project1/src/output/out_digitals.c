/*------------------------------------------------------------------------------
OUT_DIGITALS.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_digitals0.h"
#include        "../digitals/digitals.h"
#include        "../ports.h"



void    OutGetDigital(void)
{
  if (bInBuff5 < bCANALS)
  {
    InitPushCRC();
    Push(&mpdiDigital[ bInBuff5 ],sizeof(digital));

    Output(sizeof(digital));
  }
  else Result(bRES_BADADDRESS);
}


void    OutSetDigital(void)
{
digital  di;

  if (enGlobal == GLB_PROGRAM)
  {
    if (bInBuff5 < bCANALS)
    {
    	di.ibPort   = bInBuff6;
    	di.ibPhone  = bInBuff7;
      di.bDevice  = bInBuff8;
      di.bAddress = bInBuff9;
      di.ibLine   = bInBuffA;

      if (TrueDigital(&di))
      {
      	SetDigital(bInBuff5, &di);
        LongResult(bRES_OK);
      }
      else Result(bRES_BADDATA);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDPROGRAM);
}



void    OutDigitalsExt(void)
{
uchar   i;
uint		w;

  InitPushPtr();
  w = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0)
    {
      Push(&mpdiDigital[i], sizeof(digital));
      w += sizeof(digital);
    }
  }

  OutptrOutBuff(w);
}
