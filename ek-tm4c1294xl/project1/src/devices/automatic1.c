/*------------------------------------------------------------------------------
_AUTOMATIC1.C
              

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../keyboard/keyboard.h"
#include        "../serial/ports_stack.h"
#include        "../serial/ports_devices.h"
#include        "../engine.h"
/*
#include        "xdata.h"
#include        "display.h"
#include        "beep.h"
#include        "keyboard.h"
#include        "engine.h"
#include        "device_a.h"
#include        "device_b.h"
#include        "device_c.h"
#include        "device_d.h"
#include        "device_d2.h"
#include        "device_e.h"
#include        "device_f.h"
#include        "device_g.h"
#include        "device_h.h"
#include        "device_i.h"
#include        "device_k.h"
#include        "device_m.h"
#include        "device_n.h"
#include        "device_o.h"
#include        "device_p.h"
#include        "device_s.h"
#include        "device_t.h"
#include        "automatic_r.h"
#include        "automatic_s.h"
#include        "digitals.h"
#include        "queries.h"
#include        "energy.h"
#include        "delay.h"
#include        "esc.h"
#include        "ports.h"
#include        "speed.h"      
#include        "sensors.h"
#include        "modems.h"



//                                         0123456789ABCDEF
message         code    szAutomatic     = "Заполнение      ",
                        szCana1s        = "Каналы:         ",
                        szCana1FromMask = " от: __",
                        szCana1ToMask   = " до: __";



#ifndef SKIP_A

// чтение коэффициентов для счётчика СЭТ-4ТМ
bit     ReadKoeffDeviceA(void)                 
{
uchar   i;

  if (QueryOpenA_Full(25) == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    InitPush();
    PushChar(diCurr.bAddress);           
    PushChar(8);           
    PushChar(2);                        // чтение коэффициентов

    DelayOff();
    QueryIO(1+10+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break; 
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);


  // K трансформации
  reBuffB = (InBuff(1)*0x100 + InBuff(2)) * (InBuff(3)*0x100 + InBuff(4));  


  for (i=0; i<bMINORREPEATS; i++)
  {
    InitPush();
    PushChar(diCurr.bAddress);           
    PushChar(8);           
    PushChar(0x12);                     // чтение постоянной счётчика

    DelayOff();
    QueryIO(1+3+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break; 
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);


  switch (InBuff(2) & 0x0F)             // K преобразования
  {
    case 0:  reBuffA = 10000;  break;
    case 1:  reBuffA = 50000;  break;
    case 2:  reBuffA =  2500;  break;
    case 3:  reBuffA =  1000;  break;   // 12500
    case 4:  reBuffA =  2000;  break;   // ?
    case 5:  reBuffA =   500;  break;   // ?

    default: return(0);  
  }

  return(1);
}

#endif



#ifndef SKIP_B

// чтение коэффициентов для счётчика Меркурий-230
bit     ReadKoeffDeviceB(void)                 
{
uchar   i;

  if (QueryOpenB_Full(25) == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    InitPush();
    PushChar(diCurr.bAddress);           
    PushChar(8);           
    PushChar(2);                        // чтение коэффициентов

    DelayOff();
    QueryIO(1+4+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break; 
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);


  // K трансформации
  reBuffB = (InBuff(1)*0x100 + InBuff(2)) * (InBuff(3)*0x100 + InBuff(4));  


  for (i=0; i<bMINORREPEATS; i++)
  {
    // первый вариант: ответ 3 байта
    InitPush();
    PushChar(diCurr.bAddress);           
    PushChar(8);           
    PushChar(0x12);                     // чтение постоянной счётчика

    DelayOff();
    QueryIO(1+3+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break; 
    if (fKey == 1) return(0);
                                        
    // второй вариант: ответ 6 байт
    InitPush();
    PushChar(diCurr.bAddress);           
    PushChar(8);           
    PushChar(0x12);                     // чтение постоянной счётчика

    DelayOff();
    QueryIO(1+6+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break; 
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);

  switch (InBuff(3) & 0x0F)             // K преобразования
  {
    case 1:  reBuffA = 10000;  break;
    case 2:  reBuffA =  2000;  break;
    case 3:  reBuffA =  1000;  break;
    case 4:  reBuffA =  2000;  break;

    default: return(0);  
  }

  mpreLevelDiv[ibDig] = reBuffA / 1000;

  return(1);
}
*/

// чтение коэффициентов для счётчика Меркурий-230
bool    ReadKoeffDeviceB_Special(void)
{
uchar   i;

  if (QueryOpenB_Full(25) == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    InitPush(0);
    PushChar(diCurr.bAddress);           
    PushChar(8);           
    PushChar(2);                        // чтение коэффициентов

    DelayOff();
    QueryIO(1+4+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break; 
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);


  // K трансформации
  reBuffB = (InBuff(1)*0x100 + InBuff(2)) * (InBuff(3)*0x100 + InBuff(4));  

  // K преобразования
  reBuffA = 2000;

  return(1);
}
/*
#endif



#ifndef SKIP_C

// чтение коэффициентов для счётчика СС-301
bit     ReadKoeffDeviceC(void)                 
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryOpenC();                       // открытие канала связи

    if (RevInput() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(25);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();

    InitPush();
    PushChar(diCurr.bAddress);           
    PushChar(3);
    PushChar(34);

    PushChar(0);
    PushChar(0);
    PushChar(0);

    RevQueryIO(4+18+2, 3+3+2);

    if (RevInput() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);


  coTrue.mpbBuff[3] = InBuff(4);
  coTrue.mpbBuff[2] = InBuff(5);
  coTrue.mpbBuff[1] = InBuff(6);
  coTrue.mpbBuff[0] = InBuff(7);

  reBuffB = coTrue.dwBuff; 

  coTrue.mpbBuff[3] = InBuff(8);
  coTrue.mpbBuff[2] = InBuff(9);
  coTrue.mpbBuff[1] = InBuff(10);
  coTrue.mpbBuff[0] = InBuff(11);

  reBuffB *= coTrue.dwBuff;             // K трансформации


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();

    InitPush();
    PushChar(diCurr.bAddress);
    PushChar(3);
    PushChar(24);

    PushChar(0);
    PushChar(0);
    PushChar(0);

    RevQueryIO(4+8+2, 3+3+2);

    if (RevInput() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(60);


  reBuffA = InBuff(8) + InBuff(9)*0x100;
  reBuffA = 1000000/reBuffA;            // K преобразования

  return(1);
}

#endif



#ifndef SKIP_G

bit     ReadKoeffDeviceG(void)                 
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryOpenG();

    if (CodInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  if (ReadOpenG() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
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
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);


  InitPop(3);
  for (i=0; i<9; i++) PopChar();

  if (ExtVersionCod()) PopRealExt_G(); else PopRealBCD_G();
  reBuffB = reBuffA;

  if (ExtVersionCod()) PopRealExt_G(); else PopRealBCD_G();  
  reBuffB *= reBuffA;                   // K трансформации
  
  reBuffA = 10000;                      // K преобразования

  return(1);
}

#endif



#ifndef SKIP_H

bit     ReadKoeffDeviceH(void)                 
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryOpenH();

    if (CodInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  if (ReadOpenH() == 0) return(0);


  reBuffB = 1;                          // K трансформации

  if (bVersionCod == 43)
    reBuffA = 1000;                     // K преобразования
  else
    reBuffA = 10000;

  return(1);
}

#endif



#ifndef SKIP_P

bit     ReadKoeffDeviceP(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryRegisterP();

    if (ElsInput(0) != SER_GOODCHECK) continue; else break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(60);

  ReadRegisterP();

  return(1);
}

#endif



#if (defined SKIP_A && defined SKIP_B && defined SKIP_C && defined SKIP_E)
#else

// сохранение К преобразования и К трасформации
void    SetCanalsAll(void)
{
  SetCanReal(mprePulseHou,ibDig);    
  SetCanReal(mprePulseMnt,ibDig);    
  reBuffA = reBuffB;

  SetCanReal(mpreTransEng,ibDig);  
  SetCanReal(mpreTransCnt,ibDig);  
}

#endif


/ *
#if (defined SKIP_A && defined SKIP_B && defined SKIP_C)
#else

// сохранение показаний счётчиков
void    SetEnergyAll(void)
{
  reBuffA  = *PGetCanReal(mpreTransCnt,ibDig) / *PGetCanReal(mprePulseHou,ibDig);
  reBuffA *= coEnergy.dwBuff;

  SetCanReal(mpreCount,ibDig);    
}

#endif
* /


#ifndef SKIP_A

// задание параметров для счётчиков СЭТ-4ТМ
bit     AutomaticA(void)                 
{
  if (ReadKoeffDeviceA() == 0) return(0);


  SetCanalsAll();                        // сохранение К преобразования и К трасформации

  if (QueryEnergyA_Full(0,100) == 0) return(0);

  return(1);
}

#endif



#ifndef SKIP_B

// задание параметров для счётчиков Меркурий-230
bit     AutomaticB(void)                
{
  if (ReadKoeffDeviceB() == 0) return(0);


  SetCanalsAll();                        // сохранение К преобразования и К трасформации

  if (QueryEnergyB_Full(0,100) == 0) return(0);

  return(1);
}


// задание параметров для счётчиков Меркурий-230
bit     AutomaticJ(void)                
{
  if (ReadKoeffDeviceB_Special() == 0) return(0);
  mpreLevelDiv[ibDig] = reBuffA / 1000;


  SetCanalsAll();                        // сохранение К преобразования и К трасформации

  if (QueryEnergyB_Full(0,100) == 0) return(0);

  return(1);
}

#endif



#ifndef SKIP_C

// задание параметров для счётчиков СС-301
bit     AutomaticC(void)                
{
  if (ReadKoeffDeviceC() == 0) return(0);


  SetCanalsAll();                       // сохранение К преобразования и К трасформации

  DelayOff();
  QueryEnergyAbsC();                    // чтение накопленной энергии

  if (RevInput() != SER_GOODCHECK) return(0);
  ShowPercent(100);
/ *
  ReadEnergyC();
  SetEnergyAll();                       // сохранение показаний счётчиков
* /
  return(1);
}

#endif



#ifndef SKIP_D

// открытие канала для счётчиков ABB Альфа
bit     OpenDeviceD(void)                 
{
uchar   i;

  for (i=0; i<bMAJORREPEATS; i++)
  {
    ShowPercent(i);

    DelayOff();
    QueryOpenD();

    if (ExtInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMAJORREPEATS) return(0);
  ShowPercent(48);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryPasswordD();

    if (ExtInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(49);

  if (InBuff(2) != 0) return(0);
  ShowPercent(50);


  return(1);
}

#endif



#ifndef SKIP_E

// открытие канала для сумматоров СЭМ-2
bit     OpenDeviceE(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    if (diCurr.bAddress <= 16)
    {   
      QueryBreakE();

      InitPush();
      PushChar(0x1B);          
      PushChar('0'+diCurr.bAddress);            

      Query(1+1, 2, 1);

      if (EscInput() == SER_GOODCHECK) break;
      if (fKey == 1) return(0);
    }
    else return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  return(1);
}

#endif



#ifndef SKIP_G

// открытие канала для счётчиков Энергия-9 a
bit     OpenDeviceG(void)                
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryOpenG();

    if (CodInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);


  if (ReadOpenG() == 0) return(0);

  return(1);
}

#endif



#ifndef SKIP_H

// открытие канала для счётчиков Энергия-9 a
bit     OpenDeviceH(void)                
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryOpenH();

    if (CodInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);


  if (ReadOpenH() == 0) return(0);

  return(1);
}

#endif



#ifndef SKIP_D

// чтение вснй накопленной энергии для счётчиков ABB Альфа
bit     ReadAllEnergyD(void)                
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyD();

    if (ExtInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);

  ibMinor = 0;
  ReadEnergyD();


  while (ibMinor < GetEnergyBlocksD())
  {
    for (i=0; i<bMINORREPEATS; i++)
    {
      DelayOff();
      QueryContinueD();

      if (ExtInput() == SER_GOODCHECK) break;
      if (fKey == 1) return(0);
    }

    if (i == bMINORREPEATS) return(0);
    ShowPercent(76 + ibMinor);

    ReadEnergyD();
  }


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryStopD();

    if (ExtInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);

  ReadQuadrantsD();


  return(1);
}

#endif



#ifndef SKIP_P

// открытие канала для счётчиков Elster A1140
bit     OpenDeviceP(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryOpenP();

    if (ElsInput(1) == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(20);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryModeP();

    if (ElsInput(0) == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(30);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryPasswordP();

    if (ElsInput(2) == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(40);


  return(1);
}

#endif



#ifndef SKIP_D

// задание параметров для счётчиков ABB Альфа
bit     AutomaticD(void)                
{
uchar   i;

  if (OpenDeviceD() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryConfigD();

    if (ExtInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
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
bit     AutomaticE(void)                
{
uchar   i;

  if (OpenDeviceE() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    InitPush();
    PushChar(0x1B);          
    PushChar('w');            

    Query(300+1, 2, 1);  

    if (EscInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);


  InitPop((uint)132 + diCurr.ibLine*3); // K трансформации
  PopRealBCD();

  reBuffB = reBuffA;                    


  InitPop((uint)180 + diCurr.ibLine*3); // K преобразования
  PopRealBCD();

  SetCanalsAll();                        // сохранение К преобразования и К трасформации


  DelayOff();

  for (i=0; i<bMINORREPEATS; i++)       // чтение накопленной энергии
  {
    InitPush();
    PushChar(0x1B);          
    PushChar('S');            

    Query(64+1, 2, 1);  

    if (EscInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
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
bit     AutomaticF(void)                
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryBreakF();
    QueryKoeffF();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  ReadKoeffF();


  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryRealExtendedF(bEXT_GETSIMPLE_ESC_S);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);

  ReadRealExtendedF();

  SetCanReal(mpreCount,ibDig);  


  return(1);
}

#endif



#ifndef SKIP_G

bit     AutomaticG(void)                
{
  if (ReadKoeffDeviceG() == 0) return(0);
  ShowPercent(100);

  SetCanalsAll();                       // сохранение К преобразования и К трасформации

  return(1);
}

#endif



#ifndef SKIP_H

bit     AutomaticH(void)                
{
  if (ReadKoeffDeviceH() == 0) return(0);
  ShowPercent(100);

  SetCanalsAll();                       // сохранение К преобразования и К трасформации

  return(1);
}

#endif



#ifndef SKIP_I

bit     AutomaticI(void)                
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryOpenI();

    if (TxtInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ReadOpenI();

  reBuffB = 1;                          // K трансформации
  reBuffA = 5000;                       // K преобразования

  ShowPercent(100);

  SetCanalsAll();                       // сохранение К преобразования и К трасформации

  return(1);
}

#endif



#ifndef SKIP_K

bit     AutomaticK(void)                
{
uchar   i,bT;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryCloseK();
    QueryOpenK();

    if (BccInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);

    bT = InBuff(IndexInBuff() - 1) & 0x7F;
    if ((bT == '\r') || (bT == '\n')) 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ReadOpenK();

  QueryCloseK();


  reBuffB = 1;                          // K трансформации
  reBuffA = 5000;                       // K преобразования

  Delay(1000);

  SetCanalsAll();                       // сохранение К преобразования и К трасформации

  return(1);
}

#endif



#ifndef SKIP_M

bit     AutomaticM(void)                
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryEnergyAbsM();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  reBuffB = 1;                          // K трансформации
  reBuffA = 100;                        // K преобразования

  ShowPercent(100);

  SetCanalsAll();                       // сохранение К преобразования и К трасформации

  return(1);
}

#endif



#ifndef SKIP_N

bit     AutomaticN(void)                
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    InitPush();
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
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  sprintf(szLo+1,"версия:");
  szLo[ 9] = InBuff(3); 
  szLo[10] = InBuff(4); 
  szLo[11] = InBuff(5); 
  szLo[12] = InBuff(6); 
  szLo[13] = InBuff(7); 

  DelayInf(); Clear();
  

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryEnergyAbsN();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  ReadEnergyN();

  mpdwBase[ibDig] = *PGetCanLong(mpdwChannelsA, 0);

  return(1);
}

#endif



#ifndef SKIP_O

bit     AutomaticO(void)                
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryOpenO();

    if (TxtInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ReadOpenO();

  reBuffB = 1;                          // K трансформации
  reBuffA = 5000;                       // K преобразования

  ShowPercent(100);

  SetCanalsAll();                       // сохранение К преобразования и К трасформации

  return(1);
}

#endif



#ifndef SKIP_T

bit     AutomaticT(void)                
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryVersionT();

    if (TxtInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ReadVersionT();

  Delay(1000); Clear();

  reBuffB = 1;                          // K трансформации
  reBuffA = 5000;                       // K преобразования

  ShowPercent(100);

  SetCanalsAll();

  return(1);
}

#endif



#ifndef SKIP_P

bit     AutomaticP(void)
{
uchar   i;

  Clear();
  if (OpenDeviceP() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTransP();

    if (ElsInput(0) != SER_GOODCHECK) continue; else break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  ReadTransP();                         // K трансформации
  QueryCloseP();


  reBuffA = 5000;                       // K преобразования
  SetCanalsAll();                       // сохранение К преобразования и К трансформации

  return(1);
}

#endif



#ifndef SKIP_R

bit     AutomaticR(void)
{
  Clear();

  if (ReadSensorR() == 0) return(0);

  reBuffA = 1;                          // K преобразования
  reBuffB = 1;                          // K трансформации
  SetCanalsAll();                       // сохранение К преобразования и К трансформации

  return(1);
}

#endif



#ifndef SKIP_S

bit     AutomaticS(void)
{
  Clear();

  if (QueryConfigS_Full(50) == 0) return(0);

  reBuffA = wDividerS;                  // K преобразования
  reBuffB = 1;                          // K трансформации
  SetCanalsAll();                       // сохранение К преобразования и К трансформации

  return(1);
}

#endif



void    Automatic(uchar  ibMin, uchar  ibMax)
{
uchar   i;

      enKeyboard = KBD_POSTENTER;

      ShowHi(szAutomatic);
      Clear(); DelayInf();

      for (ibPort=0; ibPort<bPORTS; ibPort++)
      {
        ShowPortDelayLo();
        DelayInf(); fKey = 0;
      }

      Clear();
      InitConnectKey();
      
      ibX = 0;

      for (i=ibMin; i<ibMax; i++)
      {
        if (GetDigitalDevice(i) == 0) continue;

        ibZ = 0;

        LoadCurrDigital(i);
        ibPort = diCurr.ibPort;

        if (GetDigitalDevice(i) != 0)
        {
          if (StreamPortCan(GetDigitalPort(i),i) == 0) 
          { ibZ = 0xEE; break; }
        }

        ShowCanalHi(i); 
        ShowProgress(12,(ulong)100*i/(bCANALS-1)); DelayInf();

        if (LoadConnect(i) == 0) break;
        Clear();

        if (mpboEnblCan[i] == boFalse)
        { 
          ShowLo(szBlocking); 
          DelayMsg();
        }
        else switch (diCurr.bDevice)
        {
#ifndef SKIP_A
          case 15:
          case 1:  if (AutomaticA() != 1) ibZ = 0xEE; break;
#endif

#ifndef SKIP_B
          case 12: if (AutomaticJ() != 1) ibZ = 0xEE; break;                

          case 8:
          case 2:  if (AutomaticB() != 1) ibZ = 0xEE; break;                
#endif

#ifndef SKIP_C
          case 3:  if (AutomaticC() != 1) ibZ = 0xEE; break;
#endif

#ifndef SKIP_D
          case 4:  if (AutomaticD() != 1) ibZ = 0xEE; break;
#endif

#ifndef SKIP_E
          case 7: 
          case 5:  if (AutomaticE() != 1) ibZ = 0xEE; break;
#endif

#ifndef SKIP_F
          case 6:  if (AutomaticF() != 1) ibZ = 0xEE; break;
#endif             

#ifndef SKIP_G
          case 9:  if (AutomaticG() != 1) ibZ = 0xEE; break;
#endif

#ifndef SKIP_H
          case 10: if (AutomaticH() != 1) ibZ = 0xEE; break;
#endif

#ifndef SKIP_I
          case 11: if (AutomaticI() != 1) ibZ = 0xEE; break;
#endif

#ifndef SKIP_K
          case 14:
          case 13: if (AutomaticK() != 1) ibZ = 0xEE; break;
#endif

#ifndef SKIP_L
          case 17:
          case 16: if (AutomaticK() != 1) ibZ = 0xEE; break;
#endif

#ifndef SKIP_M
          case 18: if (AutomaticM() != 1) ibZ = 0xEE; break;
#endif

#ifndef SKIP_N
          case 19: if (AutomaticN() != 1) ibZ = 0xEE; break;
#endif

#ifndef SKIP_O
          case 20: if (AutomaticO() != 1) ibZ = 0xEE; break;
#endif

#ifndef SKIP_P
          case 21: if (AutomaticP() != 1) ibZ = 0xEE; break;
#endif

#ifndef SKIP_Q
          case 22: if (AutomaticK() != 1) ibZ = 0xEE; break;
#endif

#ifndef SKIP_R
          case 23: if (AutomaticR() != 1) ibZ = 0xEE; break;
#endif

#ifndef SKIP_S
          case 24: if (AutomaticS() != 1) ibZ = 0xEE; break;
#endif

#ifndef SKIP_T
          case 25: if (AutomaticT() != 1) ibZ = 0xEE; break;
#endif
        }            

        SaveConnect();

        if (ibZ == 0xEE) 
        {
          ibX++;
          Error(); Beep(); DelayMsg();
        }

        if (fKey == 1) ibZ = 0xFF;
        fKey = 0;

        if (ibZ == 0xFF) break;
      }

      ShowHi(szAutomatic);
      if (ibX != 0) { sprintf(szLo, "   ошибок: %-2bu   ", ibX); LongBeep(); DelayMsg(); }  else OK();

      DelayMsg();
      KeyBreakConnect();
}



void    key_Automatic(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      Automatic(0,bCANALS);
    } 
  }
}


void    key_Automatic2(void)
{ 
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;

      ShowHi(szAutomatic);
      Clear(); DelayInf();

      ShowHi(szCana1s);
      strcpy(szLo+0,szCana1FromMask);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      ibXmin = GetChar(5,6) - 1;
      if (ibXmin < bCANALS)
      {
        enKeyboard = KBD_INPUT2;
        strcpy(szLo+8,szCana1ToMask);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ibXmax = GetChar(13,14) - 1;
      if ((ibXmax < bCANALS) && (ibXmax >= ibXmin))
      {
        Automatic(ibXmin,ibXmax+1);
      }
      else Beep();
    }
    else Beep();
  }



  else if (bKey < 10)
  {        
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(5,6);
    }
    else 
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(13,14);
    }
    else Beep(); 
  }
  else Beep();
}
*/
