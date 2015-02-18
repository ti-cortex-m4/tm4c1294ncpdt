/*------------------------------------------------------------------------------
OUT_MINUTE30.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy.h"
#include        "../ports.h"
#include        "../realtime/realtime.h"
//#include        "../energy.h"
#include        "../energy2.h"
//#include        "../digitals/digitals.h"
//#include        "../digitals/sensors.h"
//#include        "../digitals/graph3.h"



void    OutImpCanHouExt(void)
{
uchar   i, j;
uint    w;

  InitPushPtr();
  w = 0;

  iwHou = bInBuff6*0x100 + bInBuff7;

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (iwHou >= wHOURS)
    Result(bRES_BADADDRESS);
  else
  {
    for (j=0; j<bInBuff8; j++)
    {
      tiAlt = tiCurr;
      dwBuffC = DateToHouIndex();

      dwBuffC -= iwHou;
      HouIndexToDate(dwBuffC);

      Push(&tiAlt, sizeof(time));
      w += sizeof(time);

      if (LoadImpHouFree((wHOURS+iwHardHou-iwHou) % wHOURS) == 0) break;
      else
      {
        for (i=0; i<bCANALS; i++)
        {
          if (iwHou >= wHOURS)
            PushInt(0);
          else
            PushInt( mpwImpHouCan[ PrevSoftHou() ][ i ] );

          w += sizeof(uint);
        }
      }

      iwHou++;
    }

    if (j == bInBuff8)
      OutptrOutBuff(w);
    else
      Result(bRES_BADFLASH);
  }
}
