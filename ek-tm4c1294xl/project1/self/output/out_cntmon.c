/*------------------------------------------------------------------------------
OUT_CNTMON.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "../sensors/automatic2.h"
#include "../digitals/digitals.h"
#include "../digitals/digitals_pause.h"
#include "../display/display.h"



void    OutCntCanMonExt(void)
{
  SaveDisplay();
  sprintf(szHi,"—четчики: %02u-%02u",bInBuff6+1,bInBuff7+1); Clear();

  if ((bInBuff6 < bCANALS) && (bInBuff7 < 12))
  {
    InitPushPtr();

    if (GetDigitalPhone(bInBuff6) != 0)
    {
      PushChar(3);
      PushChar(0xFF);
      PushChar(0xFF);
      PushChar(0xFF);
      PushChar(0xFF);
    }
    else if (mpboEnblCan[bInBuff6] == false)
    {
      PushChar(2);
      PushChar(0xFF);
      PushChar(0xFF);
      PushChar(0xFF);
      PushChar(0xFF);
    }
    else
    {
      uchar p = ibPort;
      double2 db2 = ReadCntMonCan(bInBuff7,bInBuff6);
      ibPort = p;

      if (db2.fValid == false)
      {
        PushChar(1);
        PushChar(0xFF);
        PushChar(0xFF);
        PushChar(0xFF);
        PushChar(0xFF);
      }
      else
      {
        PushChar(0);
        PushFloat(db2.dbValue);
      }
    }

    OutptrOutBuff(1+sizeof(float));
  }
  else Result(bRES_BADADDRESS);

  LoadDisplay();
  NextPause(); // внимание !
}
