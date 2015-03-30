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
#include        "../energy.h"



void    OutSimpleEscSExt(void)
{
uchar   i,j;
uint    wSize;
real    re;

  SaveDisplay();
  sprintf(szHi,"Порт %bu: CRC%03bu ",ibPort+1,bInBuff5); Clear();

  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

  InitPushPtr();
  wSize = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
    {
      sprintf(szHi+14,"%2bu",i+1);

      if (GetDigitalDevice(i) == 0)
      {
        re = *PGetCounterOld(i);

        tiAlt = *GetCurrTimeDate();
        SetCanTime(mptiEsc_S, i);   
      }
      else if (mpboEnblCan[i] == FALSE)
      {
        re = 0;

        tiAlt = *GetCurrTimeDate();
        SetCanTime(mptiEsc_S, i);   
      }
      else if ((boExtendedEscS == TRUE) || (GetDigitalPhone(i) != 0))
        re = *GetCanReal(mpreEsc_S, i);
      else
      {
        LoadCurrDigital(i);
        if (mpboChannelsA[diCurr.ibLine] == TRUE)
          re = *GetCanReal(mpreChannelsB, diCurr.ibLine);
        else
        {
          j = ibPort;
          fAlt = ReadSensors(i);
          ibPort = j;

          if (fAlt == 0) re = 0;
        }

        tiAlt = *GetCurrTimeDate();
        SetCanTime(mptiEsc_S, i);   
      }

      PushReal();
      wSize += sizeof(real);
    }
  }

  OutptrOutBuff(wSize);      

  LoadDisplay();
  NextPause();                                    // внимание !
}


void    OutSimpleEscUExt(void)
{
uchar   i,j;
uint    wSize;
real    re;

  SaveDisplay();
  sprintf(szHi,"Порт %bu: CRC%03bu ",ibPort+1,bInBuff5); Clear();

  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

  InitPushPtr();
  wSize = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
    {
      sprintf(szHi+14,"%2bu",i+1);

      if (GetDigitalDevice(i) == 0)
      {
        moAlt.tiAlfa = *GetCurrTimeDate();
        moAlt.tiBeta = moAlt.tiAlfa;
      }
      else if (mpboEnblCan[i] == FALSE)
      {
        moAlt.tiAlfa = tiZero;
        moAlt.tiBeta = moAlt.tiAlfa;
      }
      else if ((boExtendedEscU == TRUE) || (GetDigitalPhone(i) != 0))
        moAlt = *PGetCanMoment(mpmoEsc_U, i);
      else
      {
        LoadCurrDigital(i);
        if (mpboChannelsA[diCurr.ibLine] == TRUE)
          moAlt.tiAlfa = tiChannelC;
        else
        {
          j = ibPort;
          fAlt = ReadTimeDate(i);
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
uchar   i,j;
uint    wSize;
real    re;

  SaveDisplay();
  sprintf(szHi,"Порт %bu: CRC%03bu ",ibPort+1,bInBuff5); Clear();

  ibMon = ibHardMon;

  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

  InitPushPtr();
  wSize = 0;

  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
    {
      sprintf(szHi+14,"%2bu",i+1);

      if (GetDigitalDevice(i) == 0)
      {
        if (LoadCntMon(ibMon) == 1) 
          re = *GetCanReal(mpreCntMonCan[ PrevSoftMon() ], i);
        else
          re = 0;

        tiAlt = *GetCurrTimeDate();
        SetCanTime(mptiEsc_V, i);   
      }
      else if (CheckDirectCnt1(i)) {
        LoadDirectCntReal(i);
      }
      else if (mpboEnblCan[i] == FALSE)
      {
        re = 0;

        tiAlt = *GetCurrTimeDate();
        SetCanTime(mptiEsc_V, i);   
      }
      else if ((boExtendedEscV == TRUE) || (GetDigitalPhone(i) != 0))
        re = *GetCanReal(mpreEsc_V, i);
      else
      {
        LoadCurrDigital(i);
        if (mpboChannelsA[diCurr.ibLine] == TRUE)
          re = *GetCanReal(mpreChannelsB, diCurr.ibLine);
        else
        {
          j = ibPort;
          fAlt = ReadCntMonCan(ibMon, i);
          ibPort = j;

          if (fAlt == 0) re = 0;
        }

        tiAlt = *GetCurrTimeDate();
        SetCanTime(mptiEsc_V, i);   
      }

      PushReal();
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
