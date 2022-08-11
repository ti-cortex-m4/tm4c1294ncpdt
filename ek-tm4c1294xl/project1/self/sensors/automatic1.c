/*------------------------------------------------------------------------------
AUTOMATIC1!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_profile.h"
#include "../keyboard/keyboard.h"
#include "../display/display.h"
#include "../serial/ports_devices.h"
#include "../serial/ports.h"
#include "../devices/devices.h"
#include "../digitals/serials.h"
#include "../energy.h"
#include "sensor1/device_a.h"
#include "sensor2/device_b.h"
#include "sensor3/device_c.h"
#include "device_k.h"
#include "sensor21/device_p.h"
#include "device_v.h"
#include "sensor1/automatic_a.h"
#include "sensor2/automatic_b.h"
#include "sensor3/automatic_c.h"
#include "automatic_k.h"
#include "sensor21/input_p.h"
#include "sensor21/automatic_p.h"
#include "sensor24/automatic_s.h"
#include "automatic_v.h"
#include "automatic1.h"



double                  dbKtrans, dbKpulse;



#ifndef SKIP_A

// чтение коэффициентов для счётчика СЭТ-4ТМ
bool    ReadKoeffDeviceA(void)
{
uchar   i;

  if (QueryOpenA_Full(25) == 0) return(0);


  for (i=0; i<MaxRepeats(); i++)
  {
    InitPush(0);
    PushChar(diCurr.bAddress);
    PushChar(8);
    PushChar(2);                        // чтение коэффициентов

    DelayOff();
    QueryIO(1+10+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(50);


 // K трансформации
  dbKtrans = (InBuff(1)*0x100 + InBuff(2)) * (InBuff(3)*0x100 + InBuff(4));


  for (i=0; i<MaxRepeats(); i++)
  {
    InitPush(0);
    PushChar(diCurr.bAddress);
    PushChar(8);
    PushChar(0x12);                     // чтение постоянной счётчика

    DelayOff();
    QueryIO(1+3+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(75);


  switch (InBuff(2) & 0x0F)             // K преобразования
  {
    case 0:  dbKpulse = 10000;  break;
    case 1:  dbKpulse = 50000;  break;
    case 2:  dbKpulse =  2500;  break;
    case 3:  dbKpulse =  1000;  break;   // 12500
    case 4:  dbKpulse =  2000;  break;   // ?
    case 5:  dbKpulse =   500;  break;   // ?

    default: return(0);
  }

  return(1);
}

#endif



#ifndef SKIP_B

// чтение коэффициентов для счётчика Меркурий-230
bool    ReadKoeffDeviceB(uchar  ibCan)
{
  if (QueryOpenB_Full(ibCan, 25) == 0) return(0);


  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    InitPush(0);
    PushChar(diCurr.bAddress);
    PushChar(8);
    PushChar(2);                        // чтение коэффициентов

    DelayOff();
    QueryIO(1+4+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(50);


 // K трансформации
  dbKtrans = (InBuff(1)*0x100 + InBuff(2)) * (InBuff(3)*0x100 + InBuff(4));


  for (i=0; i<MaxRepeats(); i++)
  {
    // первый вариант: ответ 3 байта
    InitPush(0);
    PushChar(diCurr.bAddress);
    PushChar(8);
    PushChar(0x12);                     // чтение постоянной счётчика

    DelayOff();
    QueryIO(1+3+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);

    // второй вариант: ответ 6 байт
    InitPush(0);
    PushChar(diCurr.bAddress);
    PushChar(8);
    PushChar(0x12);                     // чтение постоянной счётчика

    DelayOff();
    QueryIO(1+6+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(75);

  switch (InBuff(3) & 0x0F)             // K преобразования
  {
    case 1:  dbKpulse = 10000;  break;
    case 2:  dbKpulse =  2000;  break;
    case 3:  dbKpulse =  1000;  break;
    case 4:  dbKpulse =  2000;  break;

    default: return(0);
  }

  mpdbLevel[ibDig] = dbKpulse / 1000;

  return(1);
}


// чтение коэффициентов для счётчика Меркурий-230
bool    ReadKoeffDeviceB_Special(uchar  ibCan)
{
  if (QueryOpenB_Full(ibCan, 25) == 0) return(0);


  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    InitPush(0);
    PushChar(diCurr.bAddress);
    PushChar(8);
    PushChar(2);                        // чтение коэффициентов

    DelayOff();
    QueryIO(1+4+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(50);


 // K трансформации
  dbKtrans = (InBuff(1)*0x100 + InBuff(2)) * (InBuff(3)*0x100 + InBuff(4));

  // K преобразования
  dbKpulse = 2000;

  return(1);
}

#endif



#ifndef SKIP_C

// чтение коэффициентов для счётчика СС-301
bool    ReadKoeffDeviceC(uchar  ibCan)
{
  if ((fSerialsManual == false) && (mfSerialFlags[ibCan] == false))
  {
    ulong2 dw2 = QuerySerialC_Full(ibCan);
    Clear();
    if (dw2.fValid == false) return false;
  }


  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryOpenC();                       // открытие канала связи

    if (RevInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(25);


  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();

    InitPush(0);
    PushChar(diCurr.bAddress);
    PushChar(3);
    PushChar(34);

    PushChar(0);
    PushChar(0);
    PushChar(0);

    RevQueryIO(4+18+2, 3+3+2);

    if (RevInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(50);


  combo32 co;

  co.mpbBuff[0] = InBuff(4);
  co.mpbBuff[1] = InBuff(5);
  co.mpbBuff[2] = InBuff(6);
  co.mpbBuff[3] = InBuff(7);

  dbKtrans = co.dwBuff;

  co.mpbBuff[0] = InBuff(8);
  co.mpbBuff[1] = InBuff(9);
  co.mpbBuff[2] = InBuff(10);
  co.mpbBuff[3] = InBuff(11);

  dbKtrans *= co.dwBuff;            // K трансформации


  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();

    InitPush(0);
    PushChar(diCurr.bAddress);
    PushChar(3);
    PushChar(24);

    PushChar(0);
    PushChar(0);
    PushChar(0);

    RevQueryIO(4+8+2, 3+3+2);

    if (RevInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(60);


  dbKpulse = InBuff(8) + InBuff(9)*0x100;
  dbKpulse = 1000000/dbKpulse;      // K преобразования

  return(1);
}

#endif



#ifndef SKIP_G

bool    ReadKoeffDeviceG(void)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    QueryOpenG();

    if (CodInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);

  if (ReadOpenG() == 0) return(0);


  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    InitPushCod();

    PushChar(0x7E);
    PushChar(0x03);
    PushChar(0x06);

    PushCharCod(0x03);
    PushCharCod(0x00);
    PushCharCod(0x00);

    CodQueryIO(3+25+1, 3+3+1);

    if (CodInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(50);


  InitPop(3);
  for (i=0; i<9; i++) PopChar();

  if (ExtVersionCod()) PopRealExt_G(); else PopRealBCD_G();
  dbKtrans = reBuffA;

  if (ExtVersionCod()) PopRealExt_G(); else PopRealBCD_G();
  dbKtrans *= reBuffA;                  // K трансформации

  reBuffA = 10000;                      // K преобразования

  return(1);
}

#endif



#ifndef SKIP_H

bool    ReadKoeffDeviceH(void)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    QueryOpenH();

    if (CodInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);

  if (ReadOpenH() == 0) return(0);


  dbKtrans = 1;                         // K трансформации

  if (bVersionCod == 43)
    reBuffA = 1000;                     // K преобразования
  else
    reBuffA = 10000;

  return(1);
}

#endif



#ifndef SKIP_P

bool    ReadKoeffDeviceP(void)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryRegisterP();

    if (ElsInput(0) != SER_GOODCHECK) continue; else break;
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(60);

  ReadRegisterP();

  return(1);
}

#endif



void    SetAllFactors(double  dbPulse, double  dbTrans)
{
  mpdbPulseHou[ibDig] = dbPulse;
  mpdbPulseMnt[ibDig] = dbPulse;

  mpdbTransEng[ibDig] = dbTrans;
  mpdbTransCnt[ibDig] = dbTrans;
}


void    SetupFactors(factors  fc)
{
  mpdbTransEng[ibDig] = fc.dbTrans;
  mpdbTransCnt[ibDig] = fc.dbTrans;

  mpdbPulseHou[ibDig] = fc.dbPulse;
  mpdbPulseMnt[ibDig] = fc.dbPulse;
}


/*
#if (defined SKIP_A && defined SKIP_B && defined SKIP_C)
#else

// сохранение показаний счётчиков
void    SetEnergyAll(void)
{
  reBuffA  = GetCanReal(mpreTransCnt,ibDig) / GetCanReal(mprePulseHou,ibDig);
  reBuffA *= coEnergy.dwBuff;

  SetCanReal(mpreCount,ibDig);
}

#endif
*/


#ifndef SKIP_A

// задание параметров для счётчиков СЭТ-4ТМ
bool    AutomaticA(void)
{
  if (ReadKoeffDeviceA() == 0) return(0);


  SetAllFactors(dbKpulse,dbKtrans);

  if (QueryEnergyA_Full(0,100) == 0) return(0);

  return(1);
}

#endif



#ifndef SKIP_B

// задание параметров для счётчиков Меркурий-230
bool    AutomaticB(uchar  ibCan)
{
  if (ReadKoeffDeviceB(ibCan) == 0) return(0);


  SetAllFactors(dbKpulse,dbKtrans);

  if (QueryEnergyB_Full(0,100) == 0) return(0);

  return(1);
}


// задание параметров для счётчиков Меркурий-230
bool    AutomaticJ(uchar  ibCan)
{
  if (ReadKoeffDeviceB_Special(ibCan) == 0) return(0);
  mpdbLevel[ibDig] = dbKpulse / 1000;


  SetAllFactors(dbKpulse,dbKtrans);

  if (QueryEnergyB_Full(0,100) == 0) return(0);

  return(1);
}

#endif



#ifndef SKIP_C

// задание параметров для счётчиков СС-301
bool    AutomaticC(uchar  ibCan)
{
  if (ReadKoeffDeviceC(ibCan) == 0) return(0);


  SetAllFactors(dbKpulse,dbKtrans);

  DelayOff();
  QueryEnergyAbsC();                    // чтение накопленной энергии

  if (RevInput() != SER_GOODCHECK) return(0);
  ShowPercent(100);
/*
  ReadEnergyC();
  SetEnergyAll();                       // сохранение показаний счётчиков
*/
  return(1);
}

#endif



#ifndef SKIP_D

// открытие канала для счётчиков ABB Альфа
bool    OpenDeviceD(void)
{
uchar   i;

  for (i=0; i<bMAJORREPEATS; i++)
  {
    ShowPercent(i);

    DelayOff();
    QueryOpenD();

    if (ExtInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMAJORREPEATS) return(0);
  ShowPercent(48);


  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryPasswordD();

    if (ExtInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(49);

  if (InBuff(2) != 0) return(0);
  ShowPercent(50);


  return(1);
}

#endif



#ifndef SKIP_E

// открытие канала для сумматоров СЭМ-2
bool    OpenDeviceE(void)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    if (diCurr.bAddress <= 16)
    {
      QueryBreakE();

      InitPush(0);
      PushChar(0x1B);
      PushChar('0'+diCurr.bAddress);

      Query(1+1, 2, 1);

      if (EscInput() == SER_GOODCHECK) break;
      if (fKey == true) return(0);
    }
    else return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(50);

  return(1);
}

#endif



#ifndef SKIP_G

// открытие канала для счётчиков Энергия-9 a
bool    OpenDeviceG(void)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    QueryOpenG();

    if (CodInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);


  if (ReadOpenG() == 0) return(0);

  return(1);
}

#endif



#ifndef SKIP_H

// открытие канала для счётчиков Энергия-9 a
bool    OpenDeviceH(void)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    QueryOpenH();

    if (CodInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);


  if (ReadOpenH() == 0) return(0);

  return(1);
}

#endif



#ifndef SKIP_D

// чтение вснй накопленной энергии для счётчиков ABB Альфа
bool    ReadAllEnergyD(void)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEnergyD();

    if (ExtInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(75);

  ibMinor = 0;
  ReadEnergyD();


  while (ibMinor < GetEnergyBlocksD())
  {
    for (i=0; i<MaxRepeats(); i++)
    {
      DelayOff();
      QueryContinueD();

      if (ExtInput() == SER_GOODCHECK) break;
      if (fKey == true) return(0);
    }

    if (i == MaxRepeats()) return(0);
    ShowPercent(76 + ibMinor);

    ReadEnergyD();
  }


  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryStopD();

    if (ExtInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(100);

  ReadQuadrantsD();


  return(1);
}

#endif



#ifndef SKIP_D

// задание параметров для счётчиков ABB Альфа
bool    AutomaticD(void)
{
uchar   i;

  if (OpenDeviceD() == 0) return(0);


  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryConfigD();

    if (ExtInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(51);

  if (InBuff(2) != 0) return(0);
  ShowPercent(52);

  ReadConfigD();


  if (ReadAllEnergyD() == 0) return(0);

  QueryCloseD(0);


  MakeEnergyD();

  SetCanReal(mpreCount,ibDig);

  return(1);
}

#endif



#ifndef SKIP_E

// задание параметров для сумматора СЭМ-2
bool    AutomaticE(void)
{
uchar   i;

  if (OpenDeviceE() == 0) return(0);


  for (i=0; i<MaxRepeats(); i++)
  {
    InitPush(0);
    PushChar(0x1B);
    PushChar('w');

    Query(300+1, 2, 1);

    if (EscInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(75);


  InitPop((uint)132 + diCurr.ibLine*3);// K трансформации
  PopRealBCD();

  dbKtrans = reBuffA;


  InitPop((uint)180 + diCurr.ibLine*3); // K преобразования
  PopRealBCD();

  SetAllFactors(dbKpulse,dbKtrans);


  DelayOff();

  for (i=0; i<MaxRepeats(); i++)       // чтение накопленной энергии
  {
    InitPush(0);
    PushChar(0x1B);
    PushChar('S');

    Query(64+1, 2, 1);

    if (EscInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(100);


  InitPop(diCurr.ibLine*4);

  coFloat.mpbBuff[0] = PopChar();
  coFloat.mpbBuff[1] = PopChar();
  coFloat.mpbBuff[2] = PopChar();
  coFloat.mpbBuff[3] = PopChar();

  ToReal();
  SetCanReal(mpreCount,ibDig);            // сохранение показаний счётчиков


  return(1);
}

#endif



#ifndef SKIP_F

// задание параметров для сумматора СЭМ+2
bool    AutomaticF(void)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    QueryBreakF();
    QueryKoeffF();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(50);

  ReadKoeffF();


  for (i=0; i<MaxRepeats(); i++)
  {
    QueryRealExtendedF(bEXT_GET_ESC_S_VALUE);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(100);

  ReadRealExtendedF();

  SetCanReal(mpreCount,ibDig);


  return(1);
}

#endif



#ifndef SKIP_G

bool    AutomaticG(void)
{
  if (ReadKoeffDeviceG() == 0) return(0);
  ShowPercent(100);

  SetAllFactors(dbKpulse,dbKtrans);

  return(1);
}

#endif



#ifndef SKIP_H

bool    AutomaticH(void)
{
  if (ReadKoeffDeviceH() == 0) return(0);
  ShowPercent(100);

  SetAllFactors(dbKpulse,dbKtrans);

  return(1);
}

#endif



#ifndef SKIP_I

bool    AutomaticI(void)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    QueryOpenI();

    if (TxtInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ReadOpenI();

  dbKtrans = 1;                         // K трансформации
  reBuffA = 5000;                       // K преобразования

  ShowPercent(100);

  SetAllFactors(dbKpulse,dbKtrans);

  return(1);
}

#endif



#ifndef SKIP_K

bool    AutomaticK(void)
{
uchar   i,bT;

  for (i=0; i<MaxRepeats(); i++)
  {
    QueryCloseK();
    QueryOpenK();

    if (BccInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);

    bT = InBuff(IndexInBuff() - 1) & 0x7F;
    if ((bT == '\r') || (bT == '\n'))
      break;
  }

  if (i == MaxRepeats()) return(0);
  ReadOpenK();

  QueryCloseK();


  dbKtrans = 1;                         // K трансформации
  dbKpulse = 5000;                      // K преобразования

  Delay(1000);

  SetAllFactors(dbKpulse,dbKtrans);

  return(1);
}

#endif



#ifndef SKIP_M

bool    AutomaticM(void)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    QueryEnergyAbsM();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);

  dbKtrans = 1;                         // K трансформации
  reBuffA = 100;                        // K преобразования

  ShowPercent(100);

  SetAllFactors(dbKpulse,dbKtrans);

  return(1);
}

#endif



#ifndef SKIP_N

bool    AutomaticN(void)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    InitPush(0);
    PushChar(0);
    PushChar(diCurr.bAddress);

    PushChar(8);

    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);

    QueryIO(5+8, 5+8);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);

  sprintf(szLo+1,"версия:");
  szLo[ 9] = InBuff(3);
  szLo[10] = InBuff(4);
  szLo[11] = InBuff(5);
  szLo[12] = InBuff(6);
  szLo[13] = InBuff(7);

  DelayInf(); Clear();


  for (i=0; i<MaxRepeats(); i++)
  {
    QueryEnergyAbsN();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(50);

  ReadEnergyN();

  mpdwBase[ibDig] = mpdwChannelsA[0];

  return(1);
}

#endif



#ifndef SKIP_O

bool    AutomaticO(void)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    QueryOpenO();

    if (TxtInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ReadOpenO();

  dbKtrans = 1;                         // K трансформации
  reBuffA = 5000;                       // K преобразования

  ShowPercent(100);

  SetAllFactors(dbKpulse,dbKtrans);

  return(1);
}

#endif



#ifndef SKIP_T

bool    AutomaticT(void)
{
uchar   i;

  for (i=0; i<MaxRepeats(); i++)
  {
    QueryVersionT();

    if (TxtInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ReadVersionT();

  Delay(1000); Clear();

  dbKtrans = 1;                         // K трансформации
  reBuffA = 5000;                       // K преобразования

  ShowPercent(100);

  SetAllFactors(dbKpulse,dbKtrans);

  return(1);
}

#endif



#ifndef SKIP_P

bool    AutomaticP(uchar  ibCan)
{
  Clear();
  if (QueryOpenSerialP_Full(ibCan) == 0) return(0);


  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryTransP();

    if (ElsInput(0) == SER_GOODCHECK) break;
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(50);

  ReadTransP();                         // K трансформации
  QueryCloseP();


  dbKpulse = 5000;                      // K преобразования
  SetAllFactors(dbKpulse,dbKtrans);

  return(1);
}

#endif



#ifndef SKIP_R

bool    AutomaticR(void)
{
  Clear();

  if (ReadCntCurrR() == 0) return(0);

  reBuffA = 1;                          // K преобразования
  dbKtrans = 1;                         // K трансформации
  SetAllFactors(dbKpulse,dbKtrans);                       // сохранение К преобразования и К трансформации

  return(1);
}

#endif



#ifndef SKIP_S

bool    AutomaticS(void)
{
  Clear();

  if (QueryConfigS_Full(50) == 0) return(0);

  dbKpulse = wDividerS;                 // K преобразования
  dbKtrans = 1;                         // K трансформации
  SetAllFactors(dbKpulse,dbKtrans);                       // сохранение К преобразования и К трансформации

  return(1);
}

#endif



#ifndef SKIP_V

bool    AutomaticV(void)
{
  Clear();

  if (QueryEngAbsV_Full(50) == 0) return(0);

  dbKpulse = wDividerV;
  dbKtrans = 1;
  SetAllFactors(dbKpulse,dbKtrans);

  return(1);
}

#endif
