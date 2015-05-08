/*------------------------------------------------------------------------------
ESC.C


------------------------------------------------------------------------------*/
/*
#include        <string.h>
#include        <stdio.h>
#include        "main.h"
#include        "xdata.h"
#include        "queries.h"
#include        "display.h"
#include        "engine.h"
#include        "access.h"
#include        "rtc.h"
#include        "delay.h"
#include        "keyboard.h"
#include        "programs.h"
#include        "postinput.h"
#include        "nexttime.h"
#include        "energy.h"
#include        "power.h"
#include        "beep.h"
#include        "general.h"
#include        "timedate.h"
#include        "tariffs.h"
#include        "zones.h"
#include        "groups.h"
#include        "relaxs.h"
#include        "pause.h"
#include        "ports.h"
#include        "devices.h"
#include        "flow.h"
#include        "sensors.h"
#include        "defects.h"
#include        "memory.h"
#include        "at45d081.h"
#include        "gps2.h"
#include        "correct2.h"
#include        "correct3.h"
#include        "_automatic2.h"
#include        "_timedate.h"



//                                         0123456789ABCDEF
message         code    szCtrlZ         = "Ctrl Z          ";



void    InitEsc(void)
{
  if ((bMaxMachines == 0) || (bMaxMachines > bMACHINES)) 
    bMaxMachines = bMACHINES;
}



void    InitFloat(void)
{
uchar   i;

  reBuffA = 1.0;

  for(i=0; i<22; ++i)
  {
    reBuffA /= 2. ;
    mpreFloat[i] = reBuffA;
  }
}



void    ToFloat(void)
{
#ifndef QUICKESC

uchar   i,j,bSign,bDigit;
schar   bExponent;

  bExponent = 0;
  if (reBuffA < 0)
  {
    reBuffA = -reBuffA;
    bSign = 1;
  }
  else
    bSign = 0;

  if (reBuffA < 1.0)
  {
    while (reBuffA < 0.5)
    {
      reBuffA *= 2.;
      if (bExponent-- < -61)
        break;
    }
  }
  else
  {
    while (reBuffA >= 1.0)
    {
      reBuffA /= 2;
      if (bExponent++ > 122)
        break;
    }
  }

  if(bSign)
    bDigit = 2;
  else
    bDigit = 0;

  j = 1;
  reBuffB = 0.0;
  bSign = 2;

  for (i=0; i<22; ++i)
  {
    reBuffB += mpreFloat[i];
    bDigit *= 2;

    if (reBuffA < reBuffB)
      reBuffB -= mpreFloat[i];
    else
      bDigit += 1;

    if (++bSign % 8 == 0)
    {
      coFloat.mpbBuff[j++] = bDigit;
      bDigit = 0;
    }
  }

  if (bExponent < 0)
    bExponent = -bExponent + 128;

  coFloat.mpbBuff[0] = bExponent;

#else

  if (reBuffA == 0.)
    dwFloat = 0xBF000000;
  else
  {
    memcpy(&coFloat, &reBuffA, sizeof(ulong));

    dwFloat = (coFloat.dwBuff & 0x80000000) >> 8;       // знак
    coFloat.dwBuff <<= 1;

    if (coFloat.mpbBuff[0] >= 0x7E)                     // порядок
      coFloat.mpbBuff[0] -= 0x7E;
    else
      coFloat.mpbBuff[0] += (0x7F - coFloat.mpbBuff[0])*2;

    dwFloat |= (coFloat.dwBuff & 0xFF000000);

    coFloat.mpbBuff[0] = 0x01;                          // мантисса
    dwFloat += (coFloat.dwBuff >> 3);
  }

  coFloat.dwBuff = dwFloat;

#endif
}


#ifndef SKIP_E
void    ToReal(void)
{
uchar   i,j;

  i = coFloat.mpbBuff[1] & 0x80;                        // знак
  j = coFloat.mpbBuff[0];                               // порядок

  coFloat.dwBuff <<= 3;

  if (j < 0x80)
    coFloat.mpbBuff[0] = j + 126;
  else
    coFloat.mpbBuff[0] = 126 - (j & 0x7F);

  coFloat.dwBuff >>= 1;

  coFloat.mpbBuff[0] |= i;

  memcpy(&reBuffA, &coFloat, sizeof(ulong));
}
#endif


void    EscPtrReset(void)
{
  memset(&mpbEsc_j, '\0', sizeof(mpbEsc_j));
  memset(&mpbEsc_l, '\0', sizeof(mpbEsc_l));
  memset(&mpbEsc_v, '\0', sizeof(mpbEsc_v));
}



void    EscDisplay(void)
{
  InitPush();

  PushChar(0x0D); PushChar(0x0A); Push(&szHi,bDISPLAY);
  PushChar(0x0D); PushChar(0x0A); Push(&szLo,bDISPLAY);
  PushChar(0x0D); PushChar(0x0A);

  Esc(2*bDISPLAY+3*2);
}



void    EscError(uchar  chCode)
{
  InitPush();

  PushChar(0x1B);
  PushChar(bQuery);
  PushChar(chCode);

  Esc(3);
}



void    PushPowGrpMnt(uchar  ibMnt)
{
uchar   i;

  for (i=0; i<bFRAMES; i++)
  {
    PGetGrpMntInt2Real(mpwImpMntCan[ ibMnt ], i+bFRAMES*ibActives, 20);
    ToFloat();
    Push(&coFloat, sizeof(combo));
  }
}



void    EscPowGrpMnt(void)
{
  InitPush();

  PushPowGrpMnt( (bMINUTES+ibSoftMnt-1) % bMINUTES );
  PushPowGrpMnt( (bMINUTES+ibSoftMnt-2) % bMINUTES );

  Esc(2*4*bFRAMES);
}



void    EscEngGrpDay(uchar  ibDay, uchar  bMask)
{
uchar   i;

  if (LoadImpDay(ibDay) == 1)
  {
    InitPush();
    for (i=0; i<bFRAMES; i++)
    {
      PGetGrpImp2RealEng(mpimDayCan[ PrevSoftDay() ], i+bFRAMES*ibActives, bMask);
      ToFloat();
      Push(&coFloat, sizeof(combo));
    }
    Esc(4*bFRAMES);
  }
  else EscError(bESC_BADFLASH);
}


void    EscEngGrpMon(uchar  ibMon, uchar  bMask)
{
uchar   i;

  if (LoadImpMon(ibMon) == 1)
  {
    InitPush();
    for (i=0; i<bFRAMES; i++)
    {
      PGetGrpImp2RealEng(mpimMonCan[ PrevSoftMon() ], i+bFRAMES*ibActives, bMask);
      ToFloat();
      Push(&coFloat, sizeof(combo));
    }
    Esc(4*bFRAMES);
  }
  else EscError(bESC_BADFLASH);
}


void    EscEngGrpMonPrev(uchar  bMask)
{
  if ((mpbEsc_j[ ibActives ] & 0x80) == 0)
    EscEngGrpMon(PrevHardMon(), bMask);
  else
    EscEngGrpMon((bMONTHS+ibHardMon-(mpbEsc_j[ ibActives ] & 0x7F)) % bMONTHS, bMask);
}



void    EscImpCanMnt(uchar  bSize)
{
uchar   i,j;

  InitPush();
  for (i=0; i<bSize; i++)
  {
    for (j=0; j<16; j++)
      PushIntSwap( *PGetCanInt(mpwImpMntCan[ (bMINUTES+ibSoftMnt-i) % bMINUTES ], j+16*ibActives) );
  }
  Esc(32*bSize);
}



void    EscImpCanHou48(void)
{
uchar   i,j;

  // индекс на начало текущих суток
  wBuffD = (wHOURS+iwHardHou-GetHouIndex()) % wHOURS;

  // индекс на начало требуемых суток
  for (i=0; i<mpbEsc_l[ ibActives ]; i++)
    wBuffD = (wHOURS+wBuffD-48) % wHOURS;

  InitPush();

  for (i=0; i<48; i++)
  {
    if (LoadImpHou(wBuffD) == 0)
      break;
    else
    {
      if ((mpbEsc_l[ ibActives ] == 0) && (i > GetHouIndex()))
      {
        for (j=0; j<16; j++)
          PushInt(0);
      }
      else
      {
        for (j=0; j<16; j++)
          PushIntSwap( mpwImpHouCan[ PrevSoftHou() ][ j+16*ibActives ] );
      }

      if (++wBuffD >= wHOURS)
        wBuffD = 0;
    }
  }

  if (i == 48)
    Esc(48*32);
  else
    EscError(bESC_BADFLASH);
}



bit     EscDefCanHou(uchar  i)
{
  if ((mpbEsc_l[ibActives] == 0) && (i > GetHouIndex()))
    return(0);
  else if (GetDigitalDevice(ibCan+16*ibActives) == 0)
    return(1);
  else
    return(*PGetCanInt(mpwImpHouCan[ PrevSoftHou() ], ibCan+16*ibActives) != 0xFFFF);
}


void    EscDefCanHouSize768(void)
{
uchar   i;

  iwHou = PrevDayIndex(mpbEsc_l[ibActives]);

  InitPush();

  for (i=0; i<48; i++)
  {
    LoadImpHouFree(iwHou);

    for (ibCan=0; ibCan<16; ibCan++)
    {
      if (EscDefCanHou(i) == 1)
        PushChar(boTrue);
      else
        PushChar(FALSE);
    }

    if (++iwHou >= wHOURS) iwHou = 0;
  }

  Esc(48*16);
}


void    EscDefCanHouSize96(void)
{
uchar   i;
uint    j;

  iwHou = PrevDayIndex(mpbEsc_l[ibActives]);

  InitPush();

  for (i=0; i<48; i++)
  {
    LoadImpHouFree(iwHou);

    j = 0;
    for (ibCan=0; ibCan<16; ibCan++)
    {
      if (EscDefCanHou(i) == 1)
        j |= (1 << ibCan);
      else
        j |= (0 << ibCan);
    }
    PushInt(j);

    if (++iwHou >= wHOURS) iwHou = 0;
  }

  Esc(48*2);
}


void    EscDefCanHouSize16(void)
{
uchar   i;

  iwHou = PrevDayIndex(mpbEsc_l[ibActives]);

  InitPush();

  for (ibCan=0; ibCan<16; ibCan++)
    mpcbDefCan[ibCan] = 0;

  for (i=0; i<48; i++)
  {
    LoadImpHouFree(iwHou);

    for (ibCan=0; ibCan<16; ibCan++)
      if (EscDefCanHou(i) == 0) mpcbDefCan[ibCan]++;

    if (++iwHou >= wHOURS) iwHou = 0;
  }

  for (ibCan=0; ibCan<16; ibCan++)
    PushChar(mpcbDefCan[ibCan]);

  Esc(16);
}



void    EscImpCanMon(void)
{
uchar   i,j;

  InitPush();

  for (i=0; i<2; i++)
  {
    if (LoadImpMon((bMONTHS+ibHardMon-i) % bMONTHS) == 0)
      break;
    else
    {
      for (j=0; j<16; j++)
      {
        imAlt = mpimMonCan[ PrevSoftMon() ][ j+16*ibActives ];

        dwBuffC = imAlt.mpdwImp[0];
        PushIntSwap( dwBuffC % 0x10000 );
        PushIntSwap( dwBuffC / 0x10000 );

        dwBuffC = imAlt.mpdwImp[1];
        PushIntSwap( dwBuffC % 0x10000 );
        PushIntSwap( dwBuffC / 0x10000 );

        dwBuffC = imAlt.mpdwImp[2];
        PushIntSwap( dwBuffC % 0x10000 );
        PushIntSwap( dwBuffC / 0x10000 );

        dwBuffC = imAlt.mpdwImp[3];
        PushIntSwap( dwBuffC % 0x10000 );
        PushIntSwap( dwBuffC / 0x10000 );
      }
    }
  }

  if (i == 2)
    Esc(2*256);
  else
    EscError(bESC_BADFLASH);
}



void    EscEngGrpHou48(void)
{
uchar   i,j;

  // индекс на начало текущих суток
  wBuffD = (wHOURS+iwHardHou-GetHouIndex()) % wHOURS;

  // индекс на начало требуемых суток
  for (i=0; i<mpbEsc_l[ ibActives ]; i++)
    wBuffD = (wHOURS+wBuffD-48) % wHOURS;

  InitPush();

  for (i=0; i<48; i++)
  {
    if (LoadImpHou(wBuffD) == 0)
      break;
    else
    {
      if ((mpbEsc_l[ ibActives ] == 0) && (i > GetHouIndex()))
      {
        for (j=0; j<bFRAMES; j++)
        {
          reBuffA = 0.;
          ToFloat();
          Push(&coFloat, sizeof(combo));
        }
      }
      else
      {
        for (j=0; j<bFRAMES; j++)
        {
          reBuffA = *PGetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], j+bFRAMES*ibActives, 2);
          ToFloat();
          Push(&coFloat, sizeof(combo));
        }
      }

      if (++wBuffD >= wHOURS)
        wBuffD = 0;
    }
  }

  if (i == 48)
    Esc(48*4*bFRAMES);
  else
    EscError(bESC_BADFLASH);
}



void    EscEngGrpHou(void)
{
uchar   i,j;

  InitPush();

  for (i=0; i<2; i++)
  {
    if (LoadImpHou((wHOURS+iwHardHou-i) % wHOURS) == 0)
      break;
    else
    {
      for (j=0; j<bFRAMES; j++)
      {
        reBuffA = *PGetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ], j+bFRAMES*ibActives, 2);
        ToFloat();
        Push(&coFloat, sizeof(combo));
      }
    }
  }

  if (i == 2)
    Esc(2*4*bFRAMES);
  else
    EscError(bESC_BADFLASH);
}



bit     PushMaxPowGrpDayReal(uchar  ibDay, uchar  cbGroups)
{
uchar   i,j;

  if (LoadPowDay(ibDay) == 0)
    return(0);
  else
  {
    for (i=0; i<cbGroups; i++)
    {
      for (j=0; j<4; j++)
      {
        reBuffA = *PGetGrpMaxPowReal(&mppoDayGrp[ PrevSoftDay() ], i+bFRAMES*ibActives, j);
        ToFloat();
        Push(&coFloat, sizeof(combo));
      }
    }
    return(1);
  }
}


bit     PushMaxPowGrpDayTime(uchar  ibDay, uchar  cbGroups)
{
uchar   i,j;

  if (LoadPowDay(ibDay) == 0)
    return(0);
  else
  {
    for (i=0; i<cbGroups; i++)
    {
      for (j=0; j<4; j++)
      {
        tiAlt = *PGetGrpMaxPowTime(&mppoDayGrp[ PrevSoftDay() ], i+bFRAMES*ibActives, j);
        PushChar(tiAlt.bHour*2 + tiAlt.bMinute/30);
      }
    }
    return(1);
  }
}



void    EscMaxPowGrp6Day(uchar  ibDay)
{
  InitPush();

  if ((PushMaxPowGrpDayReal(ibDay,bFRAMES) == 1) &&
      (PushMaxPowGrpDayTime(ibDay,bFRAMES) == 1))  Esc(bFRAMES*4*(4+1));
  else
    EscError(bESC_BADFLASH);
}



void    EscMaxPowGrp2Day(void)
{
  InitPush();

  if ((PushMaxPowGrpDayReal(ibHardDay,    2) == 1) &&
      (PushMaxPowGrpDayReal(PrevHardDay(),2) == 1) &&
      (PushMaxPowGrpDayTime(ibHardDay,    2) == 1) &&
      (PushMaxPowGrpDayTime(PrevHardDay(),2) == 1))  Esc(80);
  else
    EscError(bESC_BADFLASH);
}



bit     PushMaxPowGrpMonReal(uchar  ibMon, uchar  cbGroups)
{
uchar   i,j;

  if (LoadPowMon(ibMon) == 0)
    return(0);
  else
  {
    for (i=0; i<cbGroups; i++)
    {
      for (j=0; j<4; j++)
      {
        reBuffA = *PGetGrpMaxPowReal(&mppoMonGrp[ PrevSoftMon() ], i+bFRAMES*ibActives, j);
        ToFloat();
        Push(&coFloat, sizeof(combo));
      }
    }
    return(1);
  }
}


bit     PushMaxPowGrpMonTime(uchar  ibMon, uchar  cbGroups)
{
uchar   i,j;

  if (LoadPowMon(ibMon) == 0)
    return(0);
  else
  {
    for (i=0; i<cbGroups; i++)
    {
      for (j=0; j<4; j++)
      {
        tiAlt = *PGetGrpMaxPowTime(&mppoMonGrp[ PrevSoftMon() ], i+bFRAMES*ibActives, j);
        PushChar( ToBCD(tiAlt.bDay) );
        PushChar(tiAlt.bHour*2 + tiAlt.bMinute/30);
      }
    }
    return(1);
  }
}



void    EscMaxPowGrp6Mon(uchar  ibMon)
{
  InitPush();

  if ((PushMaxPowGrpMonReal(ibMon,bFRAMES) == 1) &&
      (PushMaxPowGrpMonTime(ibMon,bFRAMES) == 1))  Esc(bFRAMES*4*(4+2));
  else
    EscError(bESC_BADFLASH);
}



void    EscMaxPowGrp2Mon(void)
{
  InitPush();

  if ((PushMaxPowGrpMonReal(ibHardMon,    2) == 1) &&
      (PushMaxPowGrpMonReal(PrevHardMon(),2) == 1) &&
      (PushMaxPowGrpMonTime(ibHardMon,    2) == 1) &&
      (PushMaxPowGrpMonTime(PrevHardMon(),2) == 1))  Esc(96);
  else
    EscError(bESC_BADFLASH);
}



void    PushZone(void)
{
uchar   i;

  for (i=0; i<GetZoneAltSize(); i++)
  {
    GetZoneAltBreak(i);

    PushChar( ToBCD(brAlt.bMinute) );
    PushChar( ToBCD(brAlt.bHour) | ((brAlt.ibTariff << 6) & 0xC0) );
  }

  for (i=GetZoneAltSize(); i<6; i++)
  {
    PushChar(0xAA);
    PushChar(0xAA);
  }
}



void    SimpleEscS(void)
{
uchar   i,j;

  SaveDisplay();
  sprintf(szHi,"Порт %bu: Esc S   ",ibPort+1); Clear();

  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

  InitPush();
  for (i=0; i<16; i++)
  {
    sprintf(szHi+14,"%2bu",i+1);

    if (GetDigitalDevice(i+16*ibActives) == 0)
    {
      reBuffA = *PGetCounterOld(i+16*ibActives);

      tiAlt = *PGetCurrTimeDate();
      SetCanTime(mptiEsc_S, i+16*ibActives);   
    }
    else if (mpboEnblCan[i+16*ibActives] == FALSE)
    {
      reBuffA = 0;

      tiAlt = *PGetCurrTimeDate();
      SetCanTime(mptiEsc_S, i+16*ibActives);   
    }
    else if ((boExtendedEscS == boTrue) || (GetDigitalPhone(i+16*ibActives) != 0))
      reBuffA = *PGetCanReal(mpreEsc_S, i+16*ibActives);
    else
    {
      LoadCurrDigital(i+16*ibActives);
      if (mpboChannelsA[diCurr.ibLine] == boTrue)
        reBuffA = *PGetCanReal(mpreChannelsB, diCurr.ibLine);
      else
      {
        j = ibPort;
        fAlt = ReadSensors(i+16*ibActives);
        ibPort = j;

        if (fAlt == 0) reBuffA = 0;
      }

      tiAlt = *PGetCurrTimeDate();
      SetCanTime(mptiEsc_S, i+16*ibActives);   
    }

    ToFloat();
    Push(&coFloat, sizeof(combo));
  }
  Esc(16*4);

  LoadDisplay();
  NextPause();                                    // внимание !
}



void    SimpleEscU(void)
{
uchar   i,j;

  SaveDisplay();
  sprintf(szHi,"Порт %bu: Esc U   ",ibPort+1); Clear();

  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

  InitPush();
  for (i=0; i<16; i++)
  {
    sprintf(szHi+14,"%2bu",i+1);

    if (GetDigitalDevice(i+16*ibActives) == 0)
    {
      moAlt.tiAlfa = *PGetCurrTimeDate();
      moAlt.tiBeta = moAlt.tiAlfa;
    }
    else if (mpboEnblCan[i+16*ibActives] == FALSE)
    {
      moAlt.tiAlfa = tiZero;
      moAlt.tiBeta = moAlt.tiAlfa;
    }
    else if ((boExtendedEscU == boTrue) || (GetDigitalPhone(i+16*ibActives) != 0))
      moAlt = *PGetCanMoment(mpmoEsc_U, i+16*ibActives);
    else
    {
      LoadCurrDigital(i+16*ibActives);
      if (mpboChannelsA[diCurr.ibLine] == boTrue)
        moAlt.tiAlfa = tiChannelC;
      else
      {
        j = ibPort;
        fAlt = ReadTimeDate(i+16*ibActives);
        ibPort = j;

        if (fAlt == 0) moAlt.tiAlfa = tiZero; else moAlt.tiAlfa = tiAlt;
      }

      moAlt.tiBeta = *PGetCurrTimeDate();
    }

    Push(&moAlt, sizeof(moment));
  }
  Esc(16*sizeof(moment));

  LoadDisplay();
  NextPause();                                    // внимание !
}



void    SimpleEscV(void)
{
uchar   i,j;

  SaveDisplay();
  sprintf(szHi,"Порт %bu: Esc V   ",ibPort+1); Clear();

  ibMon = (bMONTHS+ibHardMon-mpbEsc_v[ ibActives ]) % bMONTHS;

  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

  InitPush();
  for (i=0; i<16; i++)
  {
    sprintf(szHi+14,"%2bu",i+1);

    if (GetDigitalDevice(i+16*ibActives) == 0)
    {
      if (LoadCntMon(ibMon) == 1) 
        reBuffA = *PGetCanReal(mpreCntMonCan[ PrevSoftMon() ], i+16*ibActives);
      else
        reBuffA = 0;

      tiAlt = *PGetCurrTimeDate();
      SetCanTime(mptiEsc_V, i+16*ibActives);   
    }
    else if (mpboEnblCan[i+16*ibActives] == FALSE)
    {
      reBuffA = 0;

      tiAlt = *PGetCurrTimeDate();
      SetCanTime(mptiEsc_V, i+16*ibActives);   
    }
    else if ((boExtendedEscV == boTrue) || (GetDigitalPhone(i+16*ibActives) != 0))
    {
      if (mpbEsc_v[ ibActives ] == 0)
        reBuffA = *PGetCanReal(mpreEsc_V, i+16*ibActives);
      else
        reBuffA = 0;
    }
    else
    {
      LoadCurrDigital(i+16*ibActives);
      if (mpboChannelsA[diCurr.ibLine] == boTrue)
        reBuffA = *PGetCanReal(mpreChannelsB, diCurr.ibLine);
      else
      {
        j = ibPort;
        fAlt = ReadCntMonCan(ibMon, i+16*ibActives);
        ibPort = j;

        if (fAlt == 0) reBuffA = 0;
      }

      tiAlt = *PGetCurrTimeDate();
      SetCanTime(mptiEsc_V, i+16*ibActives);   
    }

    ToFloat();
    Push(&coFloat, sizeof(combo));
  }
  Esc(16*4);

  LoadDisplay();
  NextPause();                                    // внимание !
}



void    ShowInfoEsc(uchar  code  *szT)
{
  if (bProgram == bGET_ANALYSIS1)
  {
    sprintf(szHi,"Порт %bu: %s",ibPort+1,szT);
    Clear();
    NoShowTime(0);
  }
}


void    ShowCommandEsc(void)
{
  if (bProgram == bGET_ANALYSIS1)
  {
    sprintf(szHi,"Порт %bu: Esc %c",ibPort+1,bQuery);
    NoShowTime(0);
  }
}


void    ShowNumberEsc(uchar  i)
{
  if (bProgram == bGET_ANALYSIS1)
  {
    sprintf(szHi+14,"%2bu",i);
    NoShowTime(0);
  }
}



// базовая программа обработки запросов
void    EscSlave(void)
{
uchar   i,j;

  if (mpSerial[ibPort] == SER_CTRL_Z)
  {
    mpSerial[ibPort] = SER_BEGIN;
    EscPtrReset();

    ShowInfoEsc(szCtrlZ);
  }
  else
  if (mpSerial[ibPort] == SER_CHAR)
  {
    mpSerial[ibPort] = SER_BEGIN;

    if (enGlobal == GLB_PROGRAM)
      return;

    if (boBlockingEsc == (boolean)1)
      return;

    // номер функции
    bQuery = InBuff(0);

    ibActives = mpibActives[ibPort];

    switch (bQuery)
    {
      case 0x30:
        ibActives = 0xFF;
        mpibActives[ibPort] = ibActives;

        EscInfo();
        return;

      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
      case 0x38:
      case 0x39:
      case 0x3A:
      case 0x3B:
      case 0x3C:
      case 0x3D:
      case 0x3E:
      case 0x3F:
      case 0x40:
        for (i=0; i<bMaxMachines; i++)
        {
          if ((bQuery - 0x31) == (bLogical + i - 1))
            break;
        }

        if (i != bMaxMachines)
        {
          ibActives = (bQuery - 0x31) - (bLogical - 1);
          mpibActives[ibPort] = ibActives;

          InitPush();
          PushChar(bQuery);
          Esc(1);

          ShowCommandEsc();
        }
        else
        {
          ibActives = 0xFF;
          mpibActives[ibPort] = ibActives;
        }

        return;
    }

    if (bQuery == 'A')
    {
      Beep();
      ShowCommandEsc();
      return;
    }

    if (ibActives >= bMaxMachines) return;

    ShowCommandEsc();

    if (boBlockingEsc == boTrue) 
    {
      if (bQuery != 'R') 
      {
        InitPush();
        Push("Disabled !",10);
        Esc(10);
        return;
      } 
    }

    switch (bQuery)
    {
      case 'B':  EscEngGrpDay(PrevHardDay(), 0x0F);  break;
      case 'C':  EscEngGrpDay(PrevHardDay(), 0x0C);  break;
      case 'D':  EscEngGrpDay(PrevHardDay(), 0x02);  break;
      case 'E':  EscEngGrpDay(PrevHardDay(), 0x01);  break;

      case 'b':  EscEngGrpDay(ibHardDay,     0x0F);  break;
      case 'c':  EscEngGrpDay(ibHardDay,     0x0C);  break;
      case 'd':  EscEngGrpDay(ibHardDay,     0x02);  break;
      case 'e':  EscEngGrpDay(ibHardDay,     0x01);  break;

      case 'F':  EscEngGrpMonPrev(0x0F);             break;
      case 'G':  EscEngGrpMonPrev(0x0C);             break;
      case 'H':  EscEngGrpMonPrev(0x02);             break;
      case 'I':  EscEngGrpMonPrev(0x01);             break;

      case 'f':  EscEngGrpMon(ibHardMon,     0x0F);  break;
      case 'g':  EscEngGrpMon(ibHardMon,     0x0C);  break;
      case 'h':  EscEngGrpMon(ibHardMon,     0x02);  break;
      case 'i':  EscEngGrpMon(ibHardMon,     0x01);  break;

      case 'n':  EscImpCanMnt(2);                    break;
      case 'm':  EscImpCanMnt(40);                   break;

      case 'Y':  EscMaxPowGrp6Day( PrevHardDay() );  break;
      case 'y':  EscMaxPowGrp6Day( ibHardDay );      break;

      case 'Z':  EscMaxPowGrp6Mon( PrevHardMon() );  break;
      case 'z':  EscMaxPowGrp6Mon( ibHardMon );      break;

      case 'X':  EscMaxPowGrp2Mon();                 break;
      case 'x':  EscMaxPowGrp2Day();                 break;

      case 'N':  EscPowGrpMnt();                     break;

      case 'L':  EscImpCanHou48();                   break;
      case '$':  EscEngGrpHou48();                   break;

      case '^':  EscDefCanHouSize768();              break;
      case '[':  EscDefCanHouSize96();               break;
      case ']':  EscDefCanHouSize16();               break;

//      case 'P':  EscImpCanHou();                     break;
      case 'p':  EscEngGrpHou();                     break;
      case 'M':  EscImpCanMon();                     break;

      case 'S':  SimpleEscS();                       break;
      case 'U':  SimpleEscU();                       break;
      case 'V':  SimpleEscV();                       break;

      case 'j':
        i = mpbEsc_j[ ibActives ] & 0x7F;

        if (++i >= 6) i = 0;

        InitPush();
        PushChar('j');
        PushChar(i);
        Esc(2);

        mpbEsc_j[ ibActives ] = i | 0x80;

        ShowNumberEsc( mpbEsc_j[ ibActives ] );
        break;

      case 'K':
        if (Correct2Disable()) 
        { 
          Correct2(EVE_ESC_K);

          InitPush();
          Push("Correction disabled !",21);
          Esc(21);
          break;
        }

        if (Correct3Disable()) 
        { 
          Correct3(EVE_ESC_K);

          InitPush();
          Push("Correction blocked ! ",21);
          Esc(21);
          break;
        }

        CorrectTime(EVE_ESC_K);
        break;

      case 'k':
        if (Correct2Disable()) 
        { 
          Correct2(EVE_ESC_k);

          InitPush();
          Push("Correction disabled !",21);
          Esc(21);
          break;
        }

        if (Correct3Disable()) 
        { 
          Correct3(EVE_ESC_k);

          InitPush();
          Push("Correction blocked ! ",21);
          Esc(21);
          break;
        }

        InitPush();
        PushChar('k');

        if (CorrectTime(EVE_ESC_k) == 1)
          PushChar(0x55);
        else
          PushChar(0x80);

        Esc(2);
        break;

      case 'l':
        i = mpbEsc_l[ ibActives ];

        if (++i >= wHOURS/48) i = 0;

        mpbEsc_l[ ibActives ] = i;

        InitPush();
        PushChar('l');
        PushChar(i);
        Esc(2);

        ShowNumberEsc( mpbEsc_l[ ibActives ] );
        break;

      case 'v':
        i = mpbEsc_v[ ibActives ];

        if (++i >= 6) i = 0;

        mpbEsc_v[ ibActives ] = i;

        InitPush();
        PushChar('v');
        PushChar(i);
        Esc(2);

        ShowNumberEsc( mpbEsc_v[ ibActives ] );
        break;

      case '{':
        InitPush();
        for (i=0; i<16; i++)
        {
          tiAlt = *PGetCanTime(mptiEsc_S, i+16*ibActives);    
          Push(&tiAlt, sizeof(time));
        }
        Esc(16*sizeof(time));
        break;

      case '}':
        InitPush();
        for (i=0; i<16; i++)
        {
          tiAlt = *PGetCanTime(mptiEsc_V, i+16*ibActives);    
          Push(&tiAlt, sizeof(time));
        }
        Esc(16*sizeof(time));
        break;

      case 'T':
        InitPush();
        PushChar( ToBCD(tiCurr.bSecond) );
        PushChar( ToBCD(tiCurr.bMinute) );
        PushChar( ToBCD(tiCurr.bHour  ) );
        PushChar( ToBCD(tiCurr.bDay   ) );
        PushChar( ToBCD(tiCurr.bMonth ) );
        PushChar( ToBCD(tiCurr.bYear  ) );
        Esc(6);
        break;

      case 'W':
        InitPush();

        if (GetFlashStatus() == 0)
          i = 0x07;                            // норма
        else
          i = 0x01;                            // ошибка флэш-памяти

        if (cbPowerOn == 0)
          PushChar(i | 0x08);
        else
        if (cbPowerOn == 1)
          PushChar(i | 0x10);
        else
          PushChar(i);

        Push(&tiPowerOff, sizeof(time));       // время последнего выключения питания
        Push(&tiPowerOn,  sizeof(time));       // время последнего включения питания
        PushChar(cbPowerOn);                   // количество выключений питания

        PushChar(0);                           // время выключения за предыдущий месяц (дней, часов, минут)
        PushChar(0);
        PushChar(0);

        PushChar(0);                           // время выключения за текущий месяц (дней, часов, минут)
        PushChar(0);
        PushChar(0);

        Esc(20);
        break;

      case 'w':
        InitPush();

        // первый байт состояния
        i = bOldMode;

        tiAlt = *PGetCurrTimeDate();
        if (GetModeAlt != 0)
          i |= 0x04;

        if (enGlobal == GLB_REPROGRAM)
          i |= 0x20;

        PushChar(i);

        // второй байт состояния
        if (bOldMode == 4)
          PushChar(4);
        else
          PushChar(0);

        // дата/время первого запуска
        PushChar( ToBCD(tiStart.bSecond) );
        PushChar( ToBCD(tiStart.bMinute) );
        PushChar( ToBCD(tiStart.bHour  ) );
        PushChar( ToBCD(tiStart.bDay   ) );
        PushChar( ToBCD(tiStart.bMonth ) );
        PushChar( ToBCD(tiStart.bYear  ) );

        // тарифные зоны по кварталам
        ibMode = 0;
        for (ibMonth=12; ibMonth<16; ibMonth++)
        {
          zoAlt = *PGetZonePowMonthMode();
          PushZone();
        }

        // тарифные зоны текущего месяца
        ibMode  = 0;
        ibMonth = tiCurr.bMonth - 1;

        zoAlt = *PGetZonePowMonthMode();
        PushZone();

        // список праздников
        for (i=0; i<GetRelaxSize(); i++)
        {
          if (i >= 20) break;

          GetRelaxDate(i);
          PushChar( ToBCD(tiRelax.bDay)   );
          PushChar( ToBCD(tiRelax.bMonth) );
        }

        while (i++ < 20)
        {
          PushChar(0x55);
          PushChar(0x55);
        }

        // соcтав групп: все каналы
        for (i=bFRAMES*ibActives; i<bFRAMES*(1+ibActives); i++)
        {
          wBuffD = 0;

          for (j=0; j<GetGroupsSize(i); j++)
          {
            if (j > 16) break;
            wBuffD |= (uint)(0x01 << GetGroupsNodeCanal(i,j));
          }

          PushChar(wBuffD % 0x100);
          PushChar(wBuffD / 0x100);
        }

        // соcтав групп: каналы с отрицательным знаком
        for (i=bFRAMES*ibActives; i<bFRAMES*(1+ibActives); i++)
        {
          wBuffD = 0;

          for (j=0; j<GetGroupsSize(i); j++)
          {
            if (j > 16) break;
            if (GetGroupsNodeSign(i,j) == 1)
              wBuffD |= (uint)(0x01 << GetGroupsNodeCanal(i,j));
          }

          PushChar(wBuffD % 0x100);
          PushChar(wBuffD / 0x100);
        }

        // коэффициенты трансформации
        for (i=0; i<16; i++)
        {
          reBuffA = *PGetCanReal(mpreTransEng, i+16*ibActives);
          PushRealBCD();
        }

        // коэффициенты преобразования
        for (i=0; i<16; i++)
        {
          reBuffA = *PGetCanReal(mprePulseHou, i+16*ibActives);
          PushRealBCD();
        }

        // лимиты
        for (i=0; i<18; i++)  PushChar(0);

        // заводской номер
        PushChar( ToBCD(wPrivate % 100)         );
        PushChar( ToBCD((wPrivate % 10000)/100) );
        PushChar( ToBCD(wPrivate / 10000)       );

        // заводской номер
        PushChar( ToBCD(wPrivate % 100)         );
        PushChar( ToBCD((wPrivate % 10000)/100) );
        PushChar( ToBCD(wPrivate / 10000)       );

        // коэффициенты потерь
        for (i=0; i<16; i++)
        {
          reBuffA = *PGetCanReal(mpreLosse, i+16*ibActives) * 1000000;
          PushRealBCD();
        }

        Esc(300);
        break;

      case '*':
        InitPush();

        ibMode = 0;
        for (ibMonth=0; ibMonth<12; ibMonth++)
        {
          zoAlt = *PGetZonePowMonthMode();
          PushZone();
        }

        ibMode = 0;
        for (ibMonth=0; ibMonth<12; ibMonth++)
        {
          zoAlt = *PGetZoneEngMonthMode();
          PushZone();
        }

        PushChar(0);
        PushChar(0);
        PushChar(0);
        PushChar(0);

        if (boPublicCurr == FALSE)
          PushChar(1);
        else
          PushChar(0);

        if (boPublicPrev == FALSE)
          PushChar(1);
        else
          PushChar(0);

        Esc(300);
        break;

      case 'R':
        InitPush();
        Push("CќЊ+2 V.06 10.10.08!",20);
        PushChar(0x31+ibActives);
        Esc(21);
        break;

      case 'а':
      case 'б':
      case 'в':
      case 'г':
      case 'д':
      case 'е':
      case 'ж':
      case 'з':
      case 'и':
      case 'й':
      case 'к':
      case 'л':
      case 'м':
      case 'н':
        i = bQuery-'а';
        if (TrueKey(i) == 1)
        {
          bKey = mpbKeys[i];
          fKey = 1;

          EscDisplay();
        }
        else EscError(bESC_BADDATA);
        break;

      case 'о':
        EscDisplay();
        break;

#ifdef  FLOW
      case 0x1C:
        InitPush();

        for (i=0; i<16; i++)
          PushChar(GetDigitalDevice(i+16*ibActives));

        for (i=0; i<16; i++)
        {
          PushChar(GetDigitalAddress(i+16*ibActives));
          PushChar(GetDigitalLine(i+16*ibActives)+1);
        }

        Esc(16+32);
        break;

      case 0x1F:
        if (cbWaitQuery != 0)
        {
          InitPush();
          Push("Transit error: busy !",21);
          Esc(21);
        }
        else if (ibPort == 0) 
        {
          RunFlow0();

          InitPush();
          Push("Transit OK: 1 !",15);
          Esc(15);
        }
        else if (ibPort == 1)
        {
          RunFlow1();

          InitPush();
          Push("Transit OK: 1 !",15);
          Esc(15);
        }
        break;
#endif

      case 'Щ':
        InitPush();
        PushChar(bPortGPS);
        PushChar(bStatusGPS);
        PushChar(bVersionMaxGPS);
        PushChar(bVersionMinGPS);
        PushChar(bGMT);
        Push(mpboGPSRun, sizeof(mpboGPSRun));
        Push(mpcwGPSRun, sizeof(mpcwGPSRun));
        Push(&tiPrevCorrect, sizeof(time));
        Push(&tiPostCorrect, sizeof(time));
        Push(&mpcwPosValueCurr, sizeof(mpcwPosValueCurr));
        Push(&mpcwNegValueCurr, sizeof(mpcwNegValueCurr));
        Push(&mpcwPosCountCurr, sizeof(mpcwPosCountCurr));
        Push(&mpcwNegCountCurr, sizeof(mpcwNegCountCurr));
        Push(&mpcwPosValuePrev, sizeof(mpcwPosValuePrev));
        Push(&mpcwNegValuePrev, sizeof(mpcwNegValuePrev));
        Push(&mpcwPosCountPrev, sizeof(mpcwPosCountPrev));
        Push(&mpcwNegCountPrev, sizeof(mpcwNegCountPrev));
        PushChar(SeasonCurr());
        PushChar(boSeasonGPS);
        Esc(345+2);
        break;

      case 'Ъ':
        InitPush();
        for (i=0; i<bCANALS; i++)
        {
          PushChar(mpboDefEscV[i]); PushInt(mpcwEscV_OK[i]); PushInt(mpcwEscV_Error[i]);
          PushChar(mpboDefEscS[i]); PushInt(mpcwEscS_OK[i]); PushInt(mpcwEscS_Error[i]);
          PushChar(mpboDefEscU[i]); PushInt(mpcwEscU_OK[i]); PushInt(mpcwEscU_Error[i]);          
        }
        Esc(bCANALS*15);
        break;

      case 'Ь':
        InitPush();
        for (i=0; i<bCANALS; i++)
        {
          PushInt(mpcwDigital_OK[i]);
          PushInt(mpcwProfile_OK[i]); PushInt(mpcwProfile_Error[i]);
          PushInt(mpcwCalcDig[i]);
        }
        Esc(bCANALS*8);
        break;

      case 'Ю':
        InitPush();
        PushInt(GetCODEChecksum());
        PushInt(wPrivate);
        PushChar(bLogical);
        Esc(5);
        break;

      case 'Я':
        InitPush();
        PushInt(wPrivate);
        Esc(2);
        break;

      default:
//        EscPtrReset();
        EscInfo();
        break;
    }
  }
}



void    EscAT(void)
{
  InitPush();

  PushChar('A');
  PushChar('T');
  PushChar('\r');
  PushChar('\n');

  Answer(4,SER_OUTPUT_SLAVE);

  DelayMsg();

  InitPush();

  PushChar('A');
  PushChar('T');

  PushChar('&');                        // &D0 - игнорировать сигнал DTR
  PushChar('D');
  PushChar('0');

  PushChar('&');                        // &K0 - управление потоком запрещено
  PushChar('K');
  PushChar('0');

  PushChar('S');                        // S0=2 - подъём телефонной трубки на втором гудке
  PushChar('0');
  PushChar('=');
  PushChar('2');

  PushChar('\r');
  PushChar('\n');

  Answer(8,SER_OUTPUT_SLAVE);
}


void    SlaveModem(void)
{
  if ((boSlaveModem == boTrue) && (mpanSendAT[ibPort] == ANS_ANSWER))
  {
    mpanSendAT[ibPort] = ANS_BEGIN;

    SaveDisplay();

    sprintf(szHi,"Порт %bu: AT      ",ibPort+1);
    Clear();
    DelayMsg();

    LoadDisplay();

    EscAT();
    fSendAT = 0;
  }
}
*/
