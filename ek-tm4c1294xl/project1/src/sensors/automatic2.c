/*------------------------------------------------------------------------------
AUTOMATIC2.C
              

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_energy.h"
#include "../memory/mem_current.h"
#include "../memory/mem_realtime.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"
#include "../realtime/realtime.h"
#include "../time/timedate.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../digitals/digitals.h"
#include "../sensors/automatic2.h"
#include "../time/delay.h"
#include "../engine.h"
#include "../energy.h"
#include "../energy2.h"
#include "automatic1.h"
#include "device_a.h"
#include "device_b.h"
#include "device_c.h"
#include "automatic_a.h"
#include "automatic_b.h"
#include "automatic_c.h"



#ifndef SKIP_A

double2 ReadCntCurrA(void)
{
uchar   i;

  Clear();
  if (ReadKoeffDeviceA() == 0) return GetDouble2(0, false);

  double dbK = dbKtrans/dbKpulse;


  if (QueryEnergyA_Full(0,100) == 0) return GetDouble2(0, false);


  for (i=0; i<4; i++) 
  {
    mpdbChannelsC[i] = mpdwChannelsA[i] * dbK;
    mpboChannelsA[i] = true;     
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}

#endif



#ifndef SKIP_B

double2 ReadCntCurrB(void)
{
uchar   i;

  Clear();
  if (ReadKoeffDeviceB_Special() == 0) return GetDouble2(0, false);

  double dbK = dbKtrans/dbKpulse;


  if (QueryEnergyB_Full(0,100) == 0) return GetDouble2(0, false);


  for (i=0; i<4; i++) 
  {
    mpdbChannelsC[i] = mpdwChannelsA[i] * dbK * 2;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}

#endif



#ifndef SKIP_C

double2 ReadCntCurrC(void)
{
uchar   i;

  Clear();
  if (ReadKoeffDeviceC() == 0) return GetDouble2(0, false);

  double dbK = dbKtrans/dbKpulse;


  DelayOff();
  QueryEnergyAbsC();

  if (RevInput() != SER_GOODCHECK) return GetDouble2(0, false);
  ShowPercent(100);

  ReadEnergyC();


  for (i=0; i<4; i++) 
  {
    mpdbChannelsC[i] = mpdwChannelsA[i] * dbK;
    mpboChannelsA[i] = true;     
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}

#endif


/*
#ifndef SKIP_D

// чтение реальных показаний счЄтчиков дл€ счЄтчиков ABB јльфа
bool    ReadCntCurrD(void)
{
  Clear();
  if (OpenDeviceD() == 0) return(0);

  
  if (ReadAllEnergyD() == 0) return(0);

  QueryCloseD(0);


  MakeEnergyD();

  return(1);
}

#endif



#ifndef SKIP_E

bool    ReadCntCurrE(uchar  chEsc, bool fOpen)
{
uchar   i;

  if (fOpen == 1)
    if (OpenDeviceE() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    InitPush(0);
    PushChar(0x1B);          
    PushChar(chEsc);            

    Query(64+1, 2, 1);  

    if (EscInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(85);


  InitPop(0); 

  for (i=0; i<16; i++)
  {
    coFloat.mpbBuff[0] = PopChar();
    coFloat.mpbBuff[1] = PopChar();
    coFloat.mpbBuff[2] = PopChar();
    coFloat.mpbBuff[3] = PopChar();

    ToReal();
    SetCanReal(mpreChannelsB, i);

    mpboChannelsA[i] = true;                          
  }


  reBuffA = GetCanReal(mpreChannelsB, diCurr.ibLine);

  return(1);
}

#endif



#ifndef SKIP_F

// чтение реальных показаний счЄтчиков дл€ сумматора —Ёћ+2
bool    ReadCntCurrF(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryBreakF();
    QueryRealExtendedF(bEXT_GET_ESC_S_VALUE);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);


  ReadRealExtendedF();

  return(1);
}

#endif



#ifndef SKIP_G

// чтение реальных показаний счЄтчиков дл€ счЄтчиков Ёнерги€-9 a
bool    ReadCntCurrG(void)
{
uchar   i;

  Clear();
  if (OpenDeviceG() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyAbsG();                      // чтение накопленной энергии

    if (CodInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);


  ReadEnergyG();

  reKtrans = GetCanReal(mpreTransCnt,ibDig);
  reBuffA *= reKtrans;

  return(1);
}

#endif


#ifndef SKIP_H

// чтение реальных показаний счЄтчиков дл€ счЄтчиков Ёнерги€-9
bool    ReadCntCurrH(void)
{
uchar   i,j;

  Clear();
  if (OpenDeviceH() == 0) return(0);


  for (i=0; i<3; i++) mpreCodEng30[i] = 0;


  for (j=0; j<bTARIFFS; j++)                    // проходим по всем тарифам (в счЄтчике: 8)
  {
    if (fKey == true) return(0);

    for (i=0; i<bMINORREPEATS; i++)
    {
      DelayOff();
      QueryEnergyAbsH(j);

      ShowPercent(60+j);

      if (CodInput() != SER_GOODCHECK) continue; else break;
    }

    if (i == bMINORREPEATS) return(0);
    else 
    {
      if (ChecksumH(14) == 0) { sprintf(szLo," ошибка CRC: H5 "); Delay(1000); return(0); }

      InitPop(3);
      for (i=0; i<3; i++)
      {
        PopLongH();
        reBuffA = (real)dwBuffC/1000;

        mpreCodEng30[i] += reBuffA;
      }
    }
  }

  ShowPercent(100);


  reKtrans = GetCanReal(mpreTransCnt,ibDig);

  for (i=0; i<1; i++) 
  {
    reBuffA = mpreCodEng30[0] * reKtrans;
    SetCanReal(mpreChannelsB, i);

    mpboChannelsA[i] = true;     
  }

  reBuffA = GetCanReal(mpreChannelsB, diCurr.ibLine);

  return(1);
}

#endif



#ifndef SKIP_I

// чтение реальных показаний счЄтчиков дл€ счЄтчиков —ЁЅ-2ј.07
bool    ReadCntCurrI(void)
{
uchar   i,j;

  Clear();

  reKtrans = 0;

  for (j=0; j<bTARIFFS; j++)                    // проходим по всем тарифам (в счЄтчике: 4)
  {
    if (fKey == true) return(0);

    for (i=0; i<bMINORREPEATS; i++)
    {
      DelayOff();
      QueryEnergyAbsI(j);

      ShowPercent(60+j);

      if (TxtInput() != SER_GOODCHECK) 
        continue;
      else 
        break;
    }

    if (i == bMINORREPEATS) return(0);
    else 
    {
      ReadEnergyI();
      reKtrans += reBuffA;
    }
  }

  ShowPercent(100);


  reBuffA = reKtrans * GetCanReal(mpreTransCnt,ibDig);
  SetCanReal(mpreChannelsB, 0);

  mpboChannelsA[0] = true;     


  reBuffA = GetCanReal(mpreChannelsB, 0);

  return(1);
}

#endif



#ifndef SKIP_K

// чтение реальных показаний счЄтчиков дл€ счЄтчиков ÷Ё6850ћ
bool    ReadCntCurrK(uchar  bMaxLines)
{
uchar   i,j;

  Clear();

  for (j=0; j<bMaxLines; j++) 
  {
    for (i=0; i<bMINORREPEATS; i++)
    {
      QueryCloseK();
      QueryEnergyAbsK(j);

      if (BccInput() == SER_GOODCHECK) break;
      if (fKey == true) return(0);
    }

    if (i == bMINORREPEATS) return(0);
    ShowPercent(50+j);

    ReadEnergyK(j);
  }


  QueryCloseK();


  reKtrans = GetCanReal(mpreTransCnt,ibDig);

  for (i=0; i<bMaxLines; i++) 
  {
    reBuffA = GetCanReal(mpreChannelsB, i) * reKtrans;
    SetCanReal(mpreChannelsB, i);

    mpboChannelsA[i] = true;     
  }

  reBuffA = GetCanReal(mpreChannelsB, diCurr.ibLine);

  return(1);
}

#endif



#ifndef SKIP_M

// чтение реальных показаний счЄтчиков дл€ счЄтчиков ћеркурий-200
bool    ReadCntCurrM(void)
{
uchar   i;

  Clear();

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryEnergyAbsM();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  ReadEnergyM();



  reBuffA = GetCanReal(mpreChannelsB, 0) * GetCanReal(mpreTransCnt,ibDig);
  SetCanReal(mpreChannelsB, 0);

  mpboChannelsA[0] = true;     


  reBuffA = GetCanReal(mpreChannelsB, 0);

  return(1);
}

#endif



#ifndef SKIP_N

// чтение реальных показаний счЄтчиков дл€ преобразователей ѕ»-1.4
bool    ReadCntCurrN(void)
{
uchar   i;

  Clear();

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryEnergyAbsN();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  ReadEnergyN();


  reBuffA = mpdwChannelsA[0] * GetCanReal(mpreValueCntHou,ibDig);
  reBuffA += GetCanReal(mpreCount,ibDig);
  SetCanReal(mpreChannelsB, 0);

  mpboChannelsA[0] = true;     


  reBuffA = GetCanReal(mpreChannelsB, 0);

  return(1);
}

#endif



#ifndef SKIP_O

// чтение реальных показаний счЄтчиков дл€ счЄтчиков ѕ—„-4“ј.04
bool    ReadCntCurrO(void)
{
uchar   i,j;

  Clear();

  reKtrans = 0;

  for (j=0; j<bTARIFFS; j++)                    // проходим по всем тарифам (в счЄтчике: 4)
  {
    if (fKey == true) return(0);

    for (i=0; i<bMINORREPEATS; i++)
    {
      DelayOff();
      QueryEnergyAbsO(j);

      ShowPercent(60+j);

      if (TxtInput() != SER_GOODCHECK) 
        continue;
      else 
        break;
    }

    if (i == bMINORREPEATS) return(0);
    else 
    {
      ReadEnergyO();
      reKtrans += reBuffA;
    }
  }

  ShowPercent(100);


  reBuffA = reKtrans * GetCanReal(mpreTransCnt,ibDig);
  SetCanReal(mpreChannelsB, 0);

  mpboChannelsA[0] = true;     


  reBuffA = GetCanReal(mpreChannelsB, 0);

  return(1);
}

#endif



#ifndef SKIP_P

bool    ReadCntCurrP(void)
{
uchar   i;

  Clear();
  if (OpenDeviceP() == 0) return(0);


  if (ReadKoeffDeviceP() == 0) return(0);

  if (QueryEnergyP_Full(0) == 0) return(0);
  if (QueryEnergyP_Full(1) == 0) return(0);

  QueryCloseP();


  reKtrans = mpreTransCnt[ibDig];
  for (i=0; i<16; i++) 
  {
    mpreChannelsB[i] *= reKtrans;
  }

  for (i=0; i<4; i++) 
  {
    if (mpbMappingEls[i] >= 16)
      mpreChannelsEls[i] = 0;
    else
      mpreChannelsEls[i] = mpreChannelsB[mpbMappingEls[i]];
  }

  for (i=0; i<4; i++) 
  {
    mpreChannelsB[i] = mpreChannelsEls[i];
    mpboChannelsA[i] = true;
  }

  reBuffA = mpreChannelsB[diCurr.ibLine];

  return(1);
}

#endif
*/


#ifndef SKIP_A

//  чтение значение времени/даты дл€ счЄтчиков —Ё“-4“ћ
bool    ReadTimeCanA(void)
{
uchar   i;

  Clear();

  if (QueryOpenA_Full(25) == 0) return(0);

  if (QueryTimeAltA_Full(75) == 0) return(0);

  tiChannelC = tiAlt;
  for (i=0; i<4; i++) mpboChannelsA[i] = true;     

  return(1);
}

#endif



#ifndef SKIP_B

//  чтение значение времени/даты дл€ счЄтчиков ћеркурий-230
bool    ReadTimeCanB(void)
{
uchar   i;

  Clear();

  if (QueryOpenB_Full(25) == 0) return(0);

  if (QueryTimeAltB_Full(75) == 0) return(0);

  tiChannelC = tiAlt;
  for (i=0; i<4; i++) mpboChannelsA[i] = true;

  return(1);
}

#endif



#ifndef SKIP_C

//  чтение значение времени/даты дл€ счЄтчиков CC-301
bool    ReadTimeCanC(void)
{
uchar   i;

  Clear();

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeC();

    if (RevInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);

  ReadTimeAltC();


  tiChannelC = tiAlt;
  for (i=0; i<4; i++) mpboChannelsA[i] = true;     

  return(1);
}

#endif


/*
#ifndef SKIP_D

// чтение значение времени/даты дл€ счЄтчиков ABB јльфа
bool    ReadTimeCanD(void)
{
uchar   i;

  Clear();
  if (OpenDeviceD() == 0) return(0);

  
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeD();

    if (ExtInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);

  ReadTimeD();

  QueryCloseD(0);


  tiChannelC = tiAlt;
  for (i=0; i<4; i++) mpboChannelsA[i] = true;       

  return(1);
}

#endif



#ifndef SKIP_E

// чтение значение времени/даты дл€ сумматора —Ёћ-2
bool    ReadTimeCanE(void)
{
uchar   i;

  if (OpenDeviceE() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    InitPush(0);
    PushChar(0x1B);          
    PushChar('T');            

    Query(6+1, 2, 1);  

    if (EscInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);


  ReadTimeAltE();


  tiChannelC = tiAlt;
  for (i=0; i<16; i++) mpboChannelsA[i] = true;     

  return(1);
}

#endif



#ifndef SKIP_F

// чтение значение времени/даты дл€ сумматора —Ёћ+2
bool    ReadTimeCanF(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryBreakF();
    QueryTimeF();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);


  ReadTimeAltF();


  tiChannelC = tiAlt;
  for (i=0; i<bCANALS; i++) mpboChannelsA[i] = true;       

  return(1);
}

#endif



#ifndef SKIP_G

//  чтение значение времени/даты дл€ счЄтчиков Ёнерги€-9 a
bool    ReadTimeCanG(void)
{
uchar   i;

  Clear();
  if (OpenDeviceG() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeG();

    if (CodInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);

  ReadTimeAltG();


  tiChannelC = tiAlt;
  for (i=0; i<6; i++) mpboChannelsA[i] = true;     

  return(1);
}

#endif



#ifndef SKIP_H

//  чтение значение времени/даты дл€ счЄтчиков Ёнерги€-9
bool    ReadTimeCanH(void)
{
uchar   i;

  Clear();
  if (OpenDeviceH() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeH();

    if (CodInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);

  ReadTimeAltH();


  tiChannelC = tiAlt;
  for (i=0; i<6; i++) mpboChannelsA[i] = true;     

  return(1);
}

#endif



#ifndef SKIP_I

//  чтение значение времени/даты дл€ счЄтчиков —ЁЅ-2ј.07
bool    ReadTimeCanI(void)
{
uchar   i;

  Clear();

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeI();

    if (TxtInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);

  ReadTimeAltI();


  tiChannelC = tiAlt;
  for (i=0; i<4; i++) mpboChannelsA[i] = true;     

  return(1);
}

#endif



#ifndef SKIP_K

//  чтение значение времени/даты дл€ счЄтчиков ÷Ё6850ћ
bool    ReadTimeCanK(void)
{
uchar   i;

  Clear();

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryCloseK();
    QueryTimeK();

    if (BccInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(25);

  ReadTimeAltK();


  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryCloseK();
    QueryDateK();

    if (BccInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  ReadDateAltK();


  QueryCloseK();


  tiChannelC = tiAlt;
  for (i=0; i<4; i++) mpboChannelsA[i] = true;     

  return(1);
}

#endif



#ifndef SKIP_O

//  чтение значение времени/даты дл€ счЄтчиков ѕ—„-4“ј.04
bool    ReadTimeCanO(void)
{
uchar   i;

  Clear();

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeO();

    if (TxtInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);

  ReadTimeAltO();


  tiChannelC = tiAlt;
  for (i=0; i<4; i++) mpboChannelsA[i] = true;     

  return(1);
}

#endif



#ifndef SKIP_P

bool    ReadTimeCanP(void)
{
uchar   i;

  Clear();
  if (OpenDeviceP() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeP();

    if (ElsInput(0) != SER_GOODCHECK) continue; else break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  ReadTimeAltP();
  QueryCloseP();


  tiChannelC = tiAlt;
  for (i=0; i<4; i++) mpboChannelsA[i] = true;       

  return(1);
}

#endif



#ifndef SKIP_Z

//  чтение значение времени/даты
bool    ReadTimeCanZ(void)
{
uchar   i;

  Clear();

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeZ();

    if (ZetInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);


  ReadTimeAltZ();

  tiChannelC = tiAlt;
  mpboChannelsA[0] = true;     

  return(1);
}

#endif
*/


#ifndef SKIP_A

double2 ReadCntMonCanA(uchar  ibMonth)
{ 
uchar   i,j;
ulong   dw;

  Clear();
  if (ReadKoeffDeviceA() == 0) return GetDouble2(0, false);

  double dbK = dbKtrans/dbKpulse;


  if (QueryTimeAltA_Full(76) == 0) return GetDouble2(0, false);


  if (tiAlt.bMonth == ibMonth+1)        // значени€е счЄтчиков на начало текущего мес€ца
  {
    if (QueryEnergyA_Full2(0x40,98) == 0) return GetDouble2(0, false);
    for (i=0; i<4; i++)
    {
      dw = mpdwChannelsA[i];
      mpdwChannelsB[i] = dw;
    }

    if (QueryEnergyA_Full2(0,99) == 0) return GetDouble2(0, false);
    for (i=0; i<4; i++)
    {
      dw  = mpdwChannelsA[i];
      dw -= mpdwChannelsB[i];

      mpdwChannelsB[i] = dw;
    }
  }
  else
  {
    dw = 0;
    for (i=0; i<4; i++) mpdwChannelsB[i] = dw;

    j = ibMonth + 2;
    do
    {
      if (QueryEnergyA_Full2( 0x30 | ((j - 1) % 12 + 1), 76 + j ) == 0) return GetDouble2(0, false);
      for (i=0; i<4; i++)
      {
        dw  = mpdwChannelsA[i];
        dw += mpdwChannelsB[i];

        mpdwChannelsB[i] = dw;
      }
    }
    while ((bMONTHS + tiAlt.bMonth - j++) % bMONTHS != 0 );

    if (QueryEnergyA_Full2(0,99) == 0) return GetDouble2(0, false);
    for (i=0; i<4; i++)
    {
      dw  = mpdwChannelsA[i];
      dw -= mpdwChannelsB[i];

      mpdwChannelsB[i] = dw;
    }
  }


  for (i=0; i<4; i++) 
  {
    if (mpdwChannelsB[i] > 0xF0000000) mpdwChannelsB[i] = 0;
    mpdbChannelsC[i] = mpdwChannelsB[i] * dbK;
    mpboChannelsA[i] = true;     
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}

#endif



#ifndef SKIP_B

double2 ReadCntMonCanB(uchar  ibMonth)
{ 
uchar   i,j;
ulong   dw;

  Clear();
  if (ReadKoeffDeviceB_Special() == 0) return GetDouble2(0, false);

  double dbK = dbKtrans/dbKpulse;


  if (QueryTimeAltB_Full(76) == 0) return GetDouble2(0, false);


  if (tiAlt.bMonth == ibMonth+1)        // значени€е счЄтчиков на начало текущего мес€ца
  {
    if (QueryEnergyB_Full2(0x40,98) == 0) return GetDouble2(0, false);
    for (i=0; i<4; i++)
    {
      dw = mpdwChannelsA[i];
      mpdwChannelsB[i] = dw;
    }

    if (QueryEnergyB_Full2(0,99) == 0) return GetDouble2(0, false);
    for (i=0; i<4; i++)
    {
      dw  = mpdwChannelsA[i];
      dw -= mpdwChannelsB[i];

      mpdwChannelsB[i] = dw;
    }
  }
  else
  {
    dw = 0;
    for (i=0; i<4; i++) mpdwChannelsB[i] = dw;

    j = ibMonth + 2;
    do
    {
      if (QueryEnergyB_Full2( 0x30 | ((j - 1) % 12 + 1), 76 + j ) == 0) return GetDouble2(0, false);
      for (i=0; i<4; i++)
      {
        dw  = mpdwChannelsA[i];
        dw += mpdwChannelsB[i];

        mpdwChannelsB[i] = dw;
      }
    }
    while ((bMONTHS + tiAlt.bMonth - j++) % bMONTHS != 0 );

    if (QueryEnergyB_Full2(0,99) == 0) return GetDouble2(0, false);
    for (i=0; i<4; i++)
    {
      dw  = mpdwChannelsA[i];
      dw -= mpdwChannelsB[i];

      mpdwChannelsB[i] = dw;
    }
  }


  for (i=0; i<4; i++) 
  {
    if (mpdwChannelsB[i] > 0xF0000000) mpdwChannelsB[i] = 0;
    mpdbChannelsC[i] = mpdwChannelsB[i] * dbK * 2;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}

#endif



#ifndef SKIP_C

double2 ReadCntMonCanC(uchar  ibMonth)
{ 
uchar   i,j;

  Clear();
  if (ReadKoeffDeviceC() == 0) return GetDouble2(0, false);

  double dbK = dbKtrans/dbKpulse;


  DelayOff();
  QueryTimeC();                   

  if (RevInput() != SER_GOODCHECK) return GetDouble2(0, false);
  if (fKey == true) return GetDouble2(0, false);

  ShowPercent(76);

  ReadTimeAltC();                        


  if (tiAlt.bMonth == ibMonth+1)        // значени€е счЄтчиков на начало текущего мес€ца
  {
    if (QueryEnergyDayC_Full2(0, 98) == 0) return GetDouble2(0, false);
    for (i=0; i<4; i++)
    {
      ulong dw = mpdwChannelsA[i];
      mpdwChannelsB[i] = dw;
    }


    if (QueryEnergyAbsC_Full2(99) == 0) return GetDouble2(0, false);
    for (i=0; i<4; i++)
    {
      ulong dw  = mpdwChannelsA[i];
      dw -= mpdwChannelsB[i];

      mpdwChannelsB[i] = dw;
    }
  }
  else
  {
    ulong dw = 0;
    for (i=0; i<4; i++) mpdwChannelsB[i] = dw;

    j = (ibMonth + 1)%12;
    do
    {
      if (QueryEnergyMonC_Full2(-((12-1+tiAlt.bMonth-j)%12), 76+j) == 0) return GetDouble2(0, false);
      for (i=0; i<4; i++)
      {
        ulong dw = mpdwChannelsA[i];
        dw += mpdwChannelsB[i];

        mpdwChannelsB[i] = dw;
      }
    }
    while ((bMONTHS + tiAlt.bMonth - ++j) % bMONTHS != 0 );


    if (QueryEnergyAbsC_Full2(99) == 0) return GetDouble2(0, false);
    for (i=0; i<4; i++)
    {
      ulong dw = mpdwChannelsA[i];
      dw -= mpdwChannelsB[i];

      mpdwChannelsB[i] = dw;
    }
  }


  for (i=0; i<4; i++) 
  {
    mpdbChannelsC[i] = mpdwChannelsB[i] * dbK;
    mpboChannelsA[i] = true;     
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}

#endif



#ifndef SKIP_D

bool    ReadCntMonCanD(uchar  ibMonth)
{ 
uchar	i,j;

  Clear();
  if (OpenDeviceD() == 0) return(0);

  
  DelayOff();
  QueryTimeD();                   

  if (ExtInput() != SER_GOODCHECK) return(0);
  ShowPercent(50);

  ReadTimeD();                        


  if (tiAlt.bMonth == ibMonth+1) 
  {  
    if (ReadAllEnergyD() == 0) return(0);

    QueryCloseD(0);
    MakeEnergyD();
  
    if (LoadImpDay( ibHardDay ) == 0) return(0);

    for (i=0; i<4; i++) {
      for (ibCan=0; ibCan<bCANALS; ibCan++) {
        if ((GetDigitalPort(ibCan)    == GetDigitalPort(ibDig))    &&
            (GetDigitalPhone(ibCan)   == GetDigitalPhone(ibDig))   &&
            (GetDigitalDevice(ibCan)  == GetDigitalDevice(ibDig))  &&
            (GetDigitalAddress(ibCan) == GetDigitalAddress(ibDig)) &&
            (GetDigitalLine(ibCan)    == i)) {

          reBuffA = *PGetCanImp2RealEng(mpimDayCan[ PrevSoftDay() ],ibCan,0x0F);
          reBuffA /= mpreTransEng[ibCan];

          mpreChannelsB[i] -= reBuffA;
        }
      }
    }
  }
  else
  { 
    if (ReadAllEnergyD() == 0) return(0);

    QueryCloseD(0);
    MakeEnergyD();

    j = ibHardMon;
    do
    {
      if (LoadImpMon(j) == 0) return(0);

      for (i=0; i<4; i++) {
        for (ibCan=0; ibCan<bCANALS; ibCan++) {
          if ((GetDigitalPort(ibCan)    == GetDigitalPort(ibDig))    &&
              (GetDigitalPhone(ibCan)   == GetDigitalPhone(ibDig))   &&
              (GetDigitalDevice(ibCan)  == GetDigitalDevice(ibDig))  &&
              (GetDigitalAddress(ibCan) == GetDigitalAddress(ibDig)) &&
              (GetDigitalLine(ibCan)    == i)) {

            reBuffA = *PGetCanImp2RealEng(mpimMonCan[ PrevSoftMon() ],ibCan,0x0F);
            reBuffA /= mpreTransEng[ibCan];

            mpreChannelsB[i] -= reBuffA;
          }
        }
      }  

      j = (bMONTHS + j - 1) % bMONTHS;
    }
    while (j != ibMonth);
  }

  reBuffA = mpreChannelsB[diCurr.ibLine];
  return(1);
}

#endif



#ifndef SKIP_E

// чтение реальных показаний счЄтчиков по мес€цам дл€ сумматора —Ёћ-2
bool    ReadCntMonCanE(uchar  ibMonth)
{
  Clear();
  if (ReadTimeCanE() == 0) return(0);


  ibMonth = (bMONTHS+tiAlt.bMonth-1-ibMonth) % bMONTHS;

  if (ibMonth > 6-1) 
  { 
    reBuffA = 0; 
    return(1); 
  }


  if (ReadAllIndexesE('v',ibMonth) == 0) return(0);


  Clear();
  //ShowPercent(80);

  if (ReadCntCurrE('V',0) == 0) return(0);


  return(1);
}

#endif



#ifndef SKIP_F

//  чтение значение показаний счЄтчиков дл€ сумматоров —Ёћ+2
bool    ReadCntMonCanF(uchar  ibMonth)
{
uchar   i;

  Clear(); 

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryBreakF();
    QueryTimeF();                   

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);


  ReadTimeAltF();                        
  if (tiAlt.bMonth != ibMonth+1) return(0);     // значени€е счЄтчиков на начало текущего мес€ца


  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryRealExtendedF(bINQ_GETCNTCANMONCURR_ALL);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);


  ReadRealExtendedF();

  return(1);
}

#endif



#ifndef SKIP_G

//  чтение значение показаний счЄтчиков дл€ счЄтчиков Ёнерги€-9
bool    ReadCntMonCanG(uchar  ibMonth)
{
uchar   i;

  Clear();
  if (ReadKoeffDeviceG() == 0) return(0);
  reBuffX = dbKtrans;


  DelayOff();
  QueryTimeG();                   

  if (CodInput() != SER_GOODCHECK) return(0);  if (fKey == true) return(0);
  ShowPercent(55);

  ReadTimeAltG();                        


  for (i=0; i<30; i++) mpreCodEng30[i] = 0;

  if (ExtVersionCod()) 
  {
    if (tiAlt.bMonth != ibMonth+1) 
    {
      if (bVersionCod == 49) 
        return ReadCntMonCanExt_G(ibMonth); 
      else
        { sprintf(szLo,"   необходима   "); Delay(1000); sprintf(szLo,"   верси€ 49    "); Delay(1000); return(0); }
    }                                           
    else                                        // значени€е счЄтчиков на начало текущего мес€ца
    {
      if (ReadEnergyExt_G() == 0) return(0); 
    } 
  }
  else
  {
    if (tiAlt.bMonth != ibMonth+1) 
    {
      { sprintf(szLo,"   необходима   "); Delay(1000); sprintf(szLo,"   верси€ 49    "); Delay(1000); return(0); }
    }                                           
    else                                        // значени€е счЄтчиков на начало текущего мес€ца
    {
      if (ReadEnergyBCD_G() == 0) return(0); 
    }
  }

  ShowPercent(100);


  for (i=0; i<6; i++) 
  {
    mpreChannelsB[i] = mpreCodEng30[i*5+0] - mpreCodEng30[i*5+3];

    reBuffA = GetCanReal(mpreChannelsB, i) * dbKtrans;
    SetCanReal(mpreChannelsB, i);

    mpboChannelsA[i] = true;     
  }

  reBuffA = GetCanReal(mpreChannelsB, diCurr.ibLine);

  return(1);
}

#endif



#ifndef SKIP_H

//  чтение значение показаний счЄтчиков дл€ счЄтчиков Ёнерги€-9
bool    ReadCntMonCanH(uchar  ibMonth)
{
uchar   i,j;

  Clear();
  if (ReadKoeffDeviceH() == 0) return(0);
  reBuffX = dbKtrans;


  DelayOff();
  QueryTimeH();                   

  if (CodInput() != SER_GOODCHECK) return(0);  if (fKey == true) return(0);
  ShowPercent(55);

  ReadTimeAltH();                        

  if (tiAlt.bMonth != ibMonth+1) 
  {
    if ((bVersionCod == 43) || (bVersionCod == 45) || (bVersionCod == 47))
      return ReadCntMonCanExt_H(ibMonth); 
    else
      { sprintf(szLo,"   необходимы   "); Delay(1000); sprintf(szLo,"версии 43,45,47 "); Delay(1000); return(0); }
  }                                           
                                                // значени€е счЄтчиков на начало текущего мес€ца

  for (i=0; i<3; i++) mpreCodEng30[i] = 0;


  for (j=0; j<bTARIFFS; j++)                    // проходим по всем тарифам (в счЄтчике: 8)
  {
    if (fKey == true) return(0);

    for (i=0; i<bMINORREPEATS; i++)
    {
      DelayOff();
      QueryEnergyAbsH(j);

      ShowPercent(60+j);

      if (CodInput() != SER_GOODCHECK) continue; else break;
    }

    if (i == bMINORREPEATS) return(0);
    else 
    {
      if (ChecksumH(14) == 0) { sprintf(szLo," ошибка CRC: H7 "); Delay(1000); return(0); }

      InitPop(3);
      for (i=0; i<3; i++)
      {
        PopLongH();
        reBuffA = (real)dwBuffC/1000;

        mpreCodEng30[i] += reBuffA;
      }
    }
  }

  ShowPercent(100);


  // энерги€ за текущие сутки рассчитываетс€, а не запрашиваетс€ со счЄтчика (как должно быть) !
  if (LoadImpDay( ibHardDay ) == 0) return(0);

  reBuffA = *PGetCanImp2RealEng(mpimDayCan[ PrevSoftDay() ],ibDig,0x0F);
  reBuffA = reBuffA / GetCanReal(mpreTransEng,ibDig);

  reBuffA = mpreCodEng30[0] * GetCanReal(mpreTransCnt,ibDig) - reBuffA;
  SetCanReal(mpreChannelsB, 0);

  mpboChannelsA[0] = true;     


  reBuffA = GetCanReal(mpreChannelsB, diCurr.ibLine);

  return(1);
}

#endif



#ifndef SKIP_I

bool    ReadCntMonCanI(uchar  ibMonth)
{ 
uchar   i,j;

  Clear();

  DelayOff();
  QueryTimeI();                   

  if (TxtInput() != SER_GOODCHECK) return(0);
  ShowPercent(50);

  ReadTimeAltI();                        

  if (tiAlt.bMonth != ibMonth+1) return(0);     // значени€е счЄтчиков на начало текущего мес€ца


  dbKtrans = 0;

  for (j=0; j<bTARIFFS; j++)                    // проходим по всем тарифам (в счЄтчике: 4)
  {
    if (fKey == true) return(0);

    for (i=0; i<bMINORREPEATS; i++)
    {
      DelayOff();
      QueryEnergyAbsI(j);

      ShowPercent(60+j);

      if (TxtInput() != SER_GOODCHECK) 
        continue;
      else 
        break;
    }

    if (i == bMINORREPEATS) return(0);
    else 
    {
      ReadEnergyI();
      dbKtrans += reBuffA;
    }
  }

  ShowPercent(100);


  // энерги€ за текущие сутки рассчитываетс€, а не запрашиваетс€ со счЄтчика (как должно быть) !
  if (LoadImpDay( ibHardDay ) == 0) return(0);

  reBuffA = *PGetCanImp2RealEng(mpimDayCan[ PrevSoftDay() ],ibDig,0x0F);
  reBuffA = reBuffA / GetCanReal(mpreTransEng,ibDig);

  reBuffA = dbKtrans * GetCanReal(mpreTransCnt,ibDig) - reBuffA;
  SetCanReal(mpreChannelsB, 0);

  mpboChannelsA[0] = true;     


  reBuffA = GetCanReal(mpreChannelsB, 0);

  return(1);
}

#endif



#ifndef SKIP_K

// чтение значение показаний счЄтчиков дл€ счЄтчиков ÷Ё6850ћ
bool    ReadCntMonCanK(void)
{
  if (ReadTimeCanK() == 0) return(0);
  if (tiAlt.bMonth != ibMon+1) return(0);     // значени€е счЄтчиков на начало текущего мес€ца


  if (ReadCntCurrK(4) == 0) return(0);

  // энерги€ за текущие сутки рассчитываетс€, а не запрашиваетс€ со счЄтчика (как должно быть) !
  if (LoadImpDay( ibHardDay ) == 0) return(0);

  for (ibMinor=0; ibMinor<ibMinorMax; ibMinor++) 
  {
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
       if (GetDigitalLine(ibCan) == ibMinor)
       {
         reBuffA = *PGetCanImp2RealEng(mpimDayCan[ PrevSoftDay() ],ibCan,0x0F);
         reBuffA = reBuffA / GetCanReal(mpreTransEng,ibCan);

         dbKtrans = GetCanReal(mpreChannelsB, ibMinor);
         reBuffA = dbKtrans * GetCanReal(mpreTransCnt,ibCan) - reBuffA;
         SetCanReal(mpreChannelsB, ibMinor);
       }  
    }
  }

  reBuffA = GetCanReal(mpreChannelsB, diCurr.ibLine);

  return(1);
}

#endif



#ifndef SKIP_O

bool    ReadCntMonCanO(uchar  ibMonth)
{ 
uchar   i,j;

  Clear();

  DelayOff();
  QueryTimeO();                   

  if (TxtInput() != SER_GOODCHECK) return(0);
  ShowPercent(50);

  ReadTimeAltO();                        

  if (tiAlt.bMonth != ibMonth+1) 
  {
    dbKtrans = 0;
    for (j=0; j<bTARIFFS; j++) 
    {
      if (fKey == true) return(0);
      for (i=0; i<bMINORREPEATS; i++)
      {
        DelayOff();
        QueryEnergyAbsMonO(j, (ibMonth+1)%12+1);

        ShowPercent(60+j);
        if (TxtInput() != SER_GOODCHECK) continue; else break;
      }

      if (i == bMINORREPEATS) return(0);
      else 
      {
        ReadEnergyO();
        dbKtrans += reBuffA;
      }
    }

    reBuffA = dbKtrans * GetCanReal(mpreTransCnt,ibDig);
    SetCanReal(mpreChannelsB, 0);
 
    mpboChannelsA[0] = true;     
    reBuffA = GetCanReal(mpreChannelsB, 0);
  }
  else 
  {
    dbKtrans = 0;
    for (j=0; j<bTARIFFS; j++) 
    {
      if (fKey == true) return(0);
      for (i=0; i<bMINORREPEATS; i++)
      {
        DelayOff();
        QueryEnergyAbsO(j);

        ShowPercent(60+j);
        if (TxtInput() != SER_GOODCHECK) continue; else break;
      }

      if (i == bMINORREPEATS) return(0);
      else 
      {
        ReadEnergyO();
        dbKtrans += reBuffA;
      }
    }

    // энерги€ за текущие сутки рассчитываетс€, а не запрашиваетс€ со счЄтчика (как должно быть) !
    if (LoadImpDay( ibHardDay ) == 0) return(0);

    reBuffA = *PGetCanImp2RealEng(mpimDayCan[ PrevSoftDay() ],ibDig,0x0F);
    reBuffA = reBuffA / GetCanReal(mpreTransEng,ibDig);

    reBuffA = dbKtrans * GetCanReal(mpreTransCnt,ibDig) - reBuffA;
    SetCanReal(mpreChannelsB, 0);
 
    mpboChannelsA[0] = true;     
    reBuffA = GetCanReal(mpreChannelsB, 0);
  }

  ShowPercent(100);

  return(1);
}

#endif



// прочитать показани€ счЄтчиков текущие с цифровых счЄтчиков
double2 ReadCntCurrCan(uchar  ibCan)
{
  Clear();

  LoadCurrDigital(ibCan);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
    case 0:  return GetDouble2(GetCntCurrImp(ibCan), true);

#ifndef SKIP_A
    case 15:
    case 1:  return ReadCntCurrA();
#endif

#ifndef SKIP_B
    case 8:
    case 2:  return ReadCntCurrB();

    case 12: return GetDouble2(mpdwBase[ibCan] * mpdbValueCntHou[ibCan], true);
#endif

#ifndef SKIP_C
    case 3:  return ReadCntCurrC();
#endif

    default: return GetDouble2(0, false);
  }
}


// прочитать значение времени/даты с цифровых счЄтчиков
bool    ReadTimeCan(uchar  ibCan)
{
  Clear();

  LoadCurrDigital(ibCan);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_A
    case 15:
    case 1:  return( ReadTimeCanA() );
#endif

#ifndef SKIP_B
    case 8:
    case 2:  return( ReadTimeCanB() );

    case 12: tiAlt = tiCurr; return(1);
#endif

#ifndef SKIP_C
    case 3:  return( ReadTimeCanC() );
#endif

    default: tiAlt = tiZero; return(0);
  }
}



// прочитать показани€ счЄтчиков по мес€цам с цифровых счЄтчиков
double2 ReadCntMonCan(uchar  ibMon, uchar  ibCan)
{
  Clear();

  LoadCurrDigital(ibCan);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
    case 0:  if (LoadCntMon(ibMon) == false)
               return GetDouble2(0, false);
             else
               return GetDouble2(mpdbCntMonCan[ PrevSoftMon() ][ibCan], true);

#ifndef SKIP_A
    case 15:
    case 1:  return ReadCntMonCanA(ibMon);
#endif

#ifndef SKIP_B
    case 8:
    case 2:  return ReadCntMonCanB(ibMon);

    case 12: if (LoadCntMon(ibMon) == false)
               return GetDouble2(0, false);
             else
               return GetDouble2(mpdbCntMonCan[ PrevSoftMon() ][ibCan], true);
#endif

#ifndef SKIP_C
    case 3:  return ReadCntMonCanC(ibMon);
#endif

#ifndef SKIP_D
    case 4:  return( ReadCntMonCanD(ibMon) ); break;
#endif

#ifndef SKIP_E
    case 7:  
    case 5:  return( ReadCntMonCanE(ibMon) ); break;
#endif

#ifndef SKIP_F
    case 6:  return( ReadCntMonCanF(ibMon) ); break;
#endif

#ifndef SKIP_G
    case 9:  return( ReadCntMonCanG(ibMon) ); break;
#endif

#ifndef SKIP_H
    case 10: return( ReadCntMonCanH(ibMon) ); break;
#endif

#ifndef SKIP_I
    case 11: return( ReadCntMonCanI(ibMon) ); break;
#endif

#ifndef SKIP_K
    case 13: return( ReadCntMonCanK2(ibMon) ); break;

    case 14: ibMon = ibMon; ibMinorMax = 1;
             return( ReadCntMonCanK() ); break;
#endif

#ifndef SKIP_L
    case 17:
    case 16: if (LoadCntMon(ibMon) == 0) return(0);
             reBuffA = GetCanReal(mpreCntMonCan[ PrevSoftMon() ], ibCan);
             return(1); break;
#endif

#ifndef SKIP_M
    case 18: if (LoadCntMon(ibMon) == 0) return(0);
             reBuffA = GetCanReal(mpreCntMonCan[ PrevSoftMon() ], ibCan);
             return(1); break;
#endif

#ifndef SKIP_N
    case 19: if (LoadCntMon(ibMon) == 0) return(0);
             reBuffA = GetCanReal(mpreCntMonCan[ PrevSoftMon() ], ibCan);
             return(1); break;
#endif

#ifndef SKIP_O
    case 20: return( ReadCntMonCanO(ibMon) ); break;
#endif

#ifndef SKIP_P
    case 21: return( ReadCntMonCanP(ibMon) ); break;
#endif

#ifndef SKIP_Q
    case 22: return( ReadCntMonCanQ(ibMon) ); break;
#endif

#ifndef SKIP_R
    case 23: if (LoadCntMon(ibMon) == 0) return(0);
             reBuffA = GetCanReal(mpreCntMonCan[ PrevSoftMon() ], ibCan);
             return(1); break;
#endif

#ifndef SKIP_S
    case 24: return( ReadCntMonCanS(ibMon) ); break;
#endif

#ifndef SKIP_T
    case 25: return( ReadCntMonCanT(ibMon) ); break;
#endif

#ifndef SKIP_U
    case 26: return( ReadCntMonCanU(ibMon) ); break;
#endif

#ifndef SKIP_Z
    case 99: reBuffA = 0; return(1);            break;
#endif

    default: return GetDouble2(0, false);
  }
}

