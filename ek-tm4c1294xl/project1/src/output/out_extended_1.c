/*------------------------------------------------------------------------------
OUT_EXTENDED_1.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_extended_1.h"
#include "../display/display.h"
#include "../serial/ports.h"
#include "../realtime/realtime.h"
#include "../digitals/digitals.h"
#include "../digitals/digitals_pause.h"
#include "../sensors/automatic2.h"
#include "../digitals/extended/extended_6.h"
#include "../time/timedate.h"
#include "../time/rtc.h"
#include "../energy.h"
#include "../energy2.h"



void    OutSimpleEscSExt(void)
{
uint    wSize;
real    re;

  SaveDisplay();
  sprintf(szHi,"Порт %u: CRC%03u ",ibPort+1,bInBuff5); Clear();

  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

  InitPushPtr();
  wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      sprintf(szHi+14,"%2u",c+1);

      if (GetDigitalDevice(c) == 0)
      {
        re = GetCntCurrImp(c);
        mptiEsc_S[c] = *GetCurrTimeDate();
      }
      else if (mpboEnblCan[c] == false)
      {
        re = 0;
        mptiEsc_S[c] = *GetCurrTimeDate();
      }
      else if ((boExtendedEscS == true) || (GetDigitalPhone(c) != 0))
        re = mpdbEsc_S[c];
      else
      {
        LoadCurrDigital(c);
        if (mpboChannelsA[diCurr.ibLine] == true)
          re = DoubleToFloat(mpdbChannelsC[diCurr.ibLine]);
        else
        {
          uchar p = ibPort;
          double2 db2 = ReadCntCurrCan(c);
          ibPort = p;

          if (!db2.fValid) re = 0;
        }

        mptiEsc_S[c] = *GetCurrTimeDate();
      }

      PushFloat(re);
      wSize += sizeof(real);
    }
  }

  OutptrOutBuff(wSize);      

  LoadDisplay();
  NextPause();                                    // внимание !
}


void    OutSimpleEscUExt(void)
{
uint    wSize;
time    ti1;
time    ti2;

  SaveDisplay();
  sprintf(szHi,"Порт %u: CRC%03u ",ibPort+1,bInBuff5); Clear();

  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

  InitPushPtr();
  wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      sprintf(szHi+14,"%2u",c+1);

      if (GetDigitalDevice(c) == 0)
      {
        ti1 = *GetCurrTimeDate();
        ti2 = ti1;
      }
      else if (mpboEnblCan[c] == false)
      {
        ti1 = tiZero;
        ti2 = ti1;
      }
      else if ((boExtendedEscU == true) || (GetDigitalPhone(c) != 0))
      {
        ti1 = mptiEsc_U1[c];
        ti2 = mptiEsc_U2[c];
      }
      else
      {
        LoadCurrDigital(c);
        if (mpboChannelsA[diCurr.ibLine] == true)
          ti1 = tiChannelC;
        else
        {
          uchar p = ibPort;
          bool f = ReadTimeCan(c);
          ibPort = p;

          if (f == 0) ti1 = tiZero; else ti1 = tiAlt;
        }

        ti2 = *GetCurrTimeDate();
      }

      PushTime(ti1);
      wSize += sizeof(time);

      PushTime(ti2);
      wSize += sizeof(time);
    }
  }

  OutptrOutBuff(wSize);      

  LoadDisplay();
  NextPause();                                    // внимание !
}


void    OutCntCanMonCurrExt(void)
{
uint    wSize;
real    re;

  SaveDisplay();
  sprintf(szHi,"Порт %u: CRC%03u ",ibPort+1,bInBuff5); Clear();

  uchar ibMon = ibHardMon;

  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

  InitPushPtr();
  wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      sprintf(szHi+14,"%2u",c+1);

      if (GetDigitalDevice(c) == 0)
      {
        if (LoadCntMon(ibMon) == true)
          re = mpdbCntMonCan[ PrevSoftMon() ][c];
        else
          re = 0;

        mptiEsc_V[c] = *GetCurrTimeDate();
      }
      else if (SupportedExtended6(c))
      {
        value6 vl = mpCntDayCan6[c];
        re = vl.dbValue;
      }
      else if (mpboEnblCan[c] == false)
      {
        re = 0;
        mptiEsc_V[c] = *GetCurrTimeDate();
      }
      else if ((boExtendedEscV == true) || (GetDigitalPhone(c) != 0))
        re = mpdbEsc_V[c];
      else
      {
        LoadCurrDigital(c);
        if (mpboChannelsA[diCurr.ibLine] == true)
          re = DoubleToFloat(mpdbChannelsC[diCurr.ibLine]);
        else
        {
          uchar p = ibPort;
          double2 db2 = ReadCntMonCan(ibMon, c);
          ibPort = p;

          if (!db2.fValid) re = 0;
        }

        mptiEsc_V[c] = *GetCurrTimeDate();
      }

      PushFloat(re);
      wSize += sizeof(real);
    }
  }

  OutptrOutBuff(wSize);      

  LoadDisplay();
  NextPause();                                    // внимание !
}



void    OutTimeEscSExt(void)
{
  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      PushTime(mptiEsc_S[c]);
      wSize += sizeof(time);
    }
  }

  OutptrOutBuff(wSize);      
}


void    OutTimeEscVExt(void)
{
  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      if (SupportedExtended6(c))
      {
        value6 vl = mpCntDayCan6[c];
        PushTime(vl.tiUpdate);
      }
      else
      {
        PushTime(mptiEsc_V[c]);
      }

      wSize += sizeof(time);
    }
  }

  OutptrOutBuff(wSize);      
}
