/*------------------------------------------------------------------------------
OUT_DECRET.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_digitals.h"
#include        "../memory/mem_extended1.h"
#include        "../display/display.h"
#include        "../serial/ports.h"
#include        "../digitals/digitals.h"
#include        "../time/rtc.h"
#include        "../energy.h"



void    OutSimpleEscSExt(void)
{
uchar   j;
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
        re = *PGetCounterOld(c);

        tiAlt = *GetCurrTimeDate();
        SetCanTime(mptiEsc_S, c);
      }
      else if (mpboEnblCan[c] == FALSE)
      {
        re = 0;

        tiAlt = *GetCurrTimeDate();
        SetCanTime(mptiEsc_S, c);
      }
      else if ((boExtendedEscS == TRUE) || (GetDigitalPhone(c) != 0))
        re = GetCanReal(mpreEsc_S, c);
      else
      {
        LoadCurrDigital(c);
        if (mpboChannelsA[diCurr.ibLine] == TRUE)
          re = GetCanReal(mpreChannelsB, diCurr.ibLine);
        else
        {
          j = ibPort;
          fAlt = ReadSensors(c);
          ibPort = j;

          if (fAlt == 0) re = 0;
        }

        tiAlt = *GetCurrTimeDate();
        SetCanTime(mptiEsc_S, c);
      }

      PushReal(re);
      wSize += sizeof(real);
    }
  }

  OutptrOutBuff(wSize);      

  LoadDisplay();
  NextPause();                                    // внимание !
}


void    OutSimpleEscUExt(void)
{
uchar   j;
uint    wSize;

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
        moAlt.tiAlfa = *GetCurrTimeDate();
        moAlt.tiBeta = moAlt.tiAlfa;
      }
      else if (mpboEnblCan[c] == FALSE)
      {
        moAlt.tiAlfa = tiZero;
        moAlt.tiBeta = moAlt.tiAlfa;
      }
      else if ((boExtendedEscU == TRUE) || (GetDigitalPhone(c) != 0))
        moAlt = *PGetCanMoment(mpmoEsc_U, c);
      else
      {
        LoadCurrDigital(c);
        if (mpboChannelsA[diCurr.ibLine] == TRUE)
          moAlt.tiAlfa = tiChannelC;
        else
        {
          j = ibPort;
          fAlt = ReadTimeDate(c);
          ibPort = j;

          if (fAlt == 0) moAlt.tiAlfa = tiZero; else moAlt.tiAlfa = tiAlt;
        }

        moAlt.tiBeta = *GetCurrTimeDate();
      }

      Push(&moAlt, sizeof(moment));
      wSize += sizeof(moment);
    }
  }

  OutptrOutBuff(wSize);      

  LoadDisplay();
  NextPause();                                    // внимание !
}


void    OutCntCanMonCurrExt(void)
{
uchar   j;
uint    wSize;
real    re;

  SaveDisplay();
  sprintf(szHi,"Порт %u: CRC%03u ",ibPort+1,bInBuff5); Clear();

  ibMon = ibHardMon;

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
        if (LoadCntMon(ibMon) == 1) 
          re = GetCanReal(mpreCntMonCan[ PrevSoftMon() ], c);
        else
          re = 0;

        tiAlt = *GetCurrTimeDate();
        SetCanTime(mptiEsc_V, c);
      }
      else if (CheckDirectCnt1(c)) {
        LoadDirectCntReal(c);
      }
      else if (mpboEnblCan[c] == FALSE)
      {
        re = 0;

        tiAlt = *GetCurrTimeDate();
        SetCanTime(mptiEsc_V, c);
      }
      else if ((boExtendedEscV == TRUE) || (GetDigitalPhone(c) != 0))
        re = GetCanReal(mpreEsc_V, c);
      else
      {
        LoadCurrDigital(c);
        if (mpboChannelsA[diCurr.ibLine] == TRUE)
          re = GetCanReal(mpreChannelsB, diCurr.ibLine);
        else
        {
          j = ibPort;
          fAlt = ReadCntMonCan(ibMon, c);
          ibPort = j;

          if (fAlt == 0) re = 0;
        }

        tiAlt = *GetCurrTimeDate();
        SetCanTime(mptiEsc_V, c);
      }

      PushReal(re);
      wSize += sizeof(real);
    }
  }

  OutptrOutBuff(wSize);      

  LoadDisplay();
  NextPause();                                    // внимание !
}



void    OutTimeEscSExt(void)
{
uchar   i;
uint    wSize;

  InitPushPtr();
  wSize = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
    {
      tiAlt = mptiEsc_S[i];

      PushTime(&tiAlt, sizeof(time));
      wSize += sizeof(time);
    }
  }

  OutptrOutBuff(wSize);      
}


void    OutTimeEscVExt(void)
{
uchar   i;
uint    wSize;

  InitPushPtr();
  wSize = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
    {
      if (CheckDirectCnt1(i))
        LoadDirectCntTime(i);
      else
        tiAlt = *PGetCanTime(mptiEsc_V, i);

      Push(&tiAlt, sizeof(time));
      wSize += sizeof(time);
    }
  }

  OutptrOutBuff(wSize);      
}
