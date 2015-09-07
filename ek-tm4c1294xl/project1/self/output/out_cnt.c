/*------------------------------------------------------------------------------
OUT_CNT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "out_cnt.h"



void    OutCntCanOld(void)
{
        if (enGlobal != GLB_PROGRAM)
        {
          if (bInBuff5 < bCANALS)
          {
            InitPushPtr();

            PGetCounterOld( bInBuff5 );
            PushReal();

            OutptrOutBuff(sizeof(real));
          }
          else Result(bRES_BADADDRESS);
        }
        else Result(bRES_NEEDWORK);
}


void    OutCntCanNew(void)
{
        if (enGlobal != GLB_PROGRAM)
        {
          if (bInBuff5 < bCANALS)
          {
            InitPushPtr();

            PGetCounterOld( bInBuff5 );
            PushReal();

            OutptrOutBuff(sizeof(real));
          }
          else Result(bRES_BADADDRESS);
        }
        else Result(bRES_NEEDWORK);
}



void    OutCntCanOldAll(void)
{
        if (enGlobal != GLB_PROGRAM)
        {
          InitPushPtr();
          for (i=0; i<bCANALS; i++)
          {
            PGetCounterOld(i);
            PushReal();
          }
          OutptrOutBuff(sizeof(real)*bCANALS);
        }
        else Result(bRES_NEEDWORK);
}


void    OutCntCanNewAll(void)
{
        if (enGlobal != GLB_PROGRAM)
        {
          InitPushPtr();
          for (i=0; i<bCANALS; i++)
          {
            if (GetDigitalDevice(i) == 0)
              reBuffA = *PGetCounterOld(i);
            else
            if ((GetDigitalDevice(i) == 5) ||
                (GetDigitalDevice(i) == 6))
              reBuffA = *PGetCanReal(mpreEsc_S,i);
            else
            {
              if (boTrue == boLoadMnt)
                reBuffA = *PGetCanReal(mpreValueCntHou,i) * mpdwBase[i];
              else
                reBuffA = *PGetCanReal(mpreEsc_S,i);
            }

            PushReal();
          }
          OutptrOutBuff(sizeof(real)*bCANALS);
        }
        else Result(bRES_NEEDWORK);
}
