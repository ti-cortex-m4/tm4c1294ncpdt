/*------------------------------------------------------------------------------
OUT_CNTMON.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"



void    OutCntCanMonExt(void)
{
uchar   i;

  SaveDisplay();
  sprintf(szHi,"—четчики: %02bu-%02bu",bInBuff6+1,bInBuff7+1); Clear();

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
    else if (mpboEnblCan[bInBuff6] == boFalse)
    {
      PushChar(2);
      PushChar(0xFF);
      PushChar(0xFF);
      PushChar(0xFF);
      PushChar(0xFF);
    }
    else
    {
      i = ibPort;
      fAlt = ReadCntMonCan(bInBuff7,bInBuff6);
      ibPort = i;

      if (fAlt == 0) 
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
        PushReal();
      }
    }

    OutptrOutBuff(1+sizeof(real));       
  }
  else Result(bRES_BADADDRESS);

  LoadDisplay();
  NextPause();                                    // внимание !
}
