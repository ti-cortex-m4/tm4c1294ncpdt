/*------------------------------------------------------------------------------
DEVICE_B.C
              
 
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals.h"
#include        "../display/lines.h"
#include        "../time/timedate.h"
#include        "../serial/ports_stack.h"
#include        "../serial/ports_devices.h"
#include        "../energy.h"
/*
#include        "xdata.h"
#include        "display.h"
#include        "lines.h"        
#include        "timedate.h"
#include        "delay.h"
#include        "engine.h"
#include        "energy.h"
#include        "digitals.h"
#include        "essential.h"
#include        "essential2.h"
#include        "ports.h"        
#include        "display.h"        
#include        "timer0.h"        
#include        "limits.h"
#include        "device_b2.h"
#include        "record.h"
#include        "_timedate.h"



#ifndef SKIP_B

// проверка сетевого адреса для счётчиков Меркурий-230
bit     ReadAddressB(void)
{
//  return(InBuff(0) == diCurr.bAddress);
  return(1);
}


// проверка результата операции для счётчиков Меркурий-230
bit     ReadResultB(void)
{
  TestResult(InBuff(1));
  return(ReadAddressB() && (InBuff(1) == 0));
}
*/


// открытие канала связи для счётчика Меркурий-230
void    QueryOpenB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);         
  PushChar(1);         

  PushChar(2);                          // пароль уровня 2

//  if (boEnableKeys != boTrue)
  {
    PushChar(2);
    PushChar(2);
    PushChar(2);
    PushChar(2);
    PushChar(2);
    PushChar(2);
  }
//  else
//  {
// 	 bool fAlt = 0;
//   phT = mpphKeys[ibDig];
//
//    uchar  i;
//    for (i=0; i<6; i++)
//    {
//      if (phT.szNumber[i] == 0) fAlt = 1;
//
//      if (fAlt == 0)
//        PushChar(phT.szNumber[i] - '0');
//      else
//        PushChar(0);
//    }
//  }

  QueryIO(2+2, 2+1+6+2);
}


/*
// посылка запроса на чтение версии для счётчика Меркурий-230
void    QueryVersionB(void)
{
  InitPush();

  PushChar(diCurr.bAddress);
  PushChar(8);
  PushChar(3);

  QueryIO(1+3+2, 3+0+2);
}


// чтение версии для счётчика Меркурий-230
void    ReadVersionB(void)
{
  InitPop(1);

  bVersionB1 = FromBCD( PopChar() );
  bVersionB2 = FromBCD( PopChar() );
  bVersionB3 = FromBCD( PopChar() );
  
  Clear();
  sprintf(szLo+1, "версия %bu.%bu.%bu", bVersionB1, bVersionB2, bVersionB3);
  (boShowMessages == boTrue) ? DelayMsg() : DelayInf();
}


// проверка версии для счётчика Меркурий-230: 7.1.0 и выше
bit     TestVersionB710(void)
{
  return ((uint)100*bVersionB1 + 10*bVersionB2 + bVersionB3 >= 710);
}



// посылка запроса на чтение логического номера для счётчика Меркурий-230
void    QueryIdB(void)
{
  InitPush();

  PushChar(diCurr.bAddress);
  PushChar(8);
  PushChar(5);

  QueryIO(1+2+2, 3+0+2);
}


// чтение логического номера для счётчика Меркурий-230
bit     ReadIdB(void)
{
  InitPop(0);
  if (PopChar() != diCurr.bAddress) return 0;
  if (PopChar() != 0) return 0;
  if ((PopChar() != diCurr.bAddress) && (0 != diCurr.bAddress)) return 0;

  return 1;
}
*/


// посылка запроса на чтение энергии для счётчиков Меркурий-230
void    QueryEnergyB(uchar  bTime)
{
  InitPush(0);

  PushChar(diCurr.bAddress);           
  PushChar(5);                          // чтение накопленной энергии

  PushChar(bTime);                      // вид энергии
  PushChar(0);                          // по всем тарифам

  QueryIO(1+16+2, 2+2+2);
}


// чтение энергии для счётчика Меркурий-230
void    ReadEnergyB(void)
{
uchar   i;

  InitPop(1);

  for (i=0; i<4; i++)
  {
    coEnergy.mpbBuff[1] = PopChar();
    coEnergy.mpbBuff[0] = PopChar();
    coEnergy.mpbBuff[3] = PopChar();
    coEnergy.mpbBuff[2] = PopChar();

    if ((coEnergy.mpbBuff[0] == 0xFF) &&
        (coEnergy.mpbBuff[1] == 0xFF) &&
        (coEnergy.mpbBuff[2] == 0xFF) &&
        (coEnergy.mpbBuff[3] == 0xFF)) coEnergy.dwBuff = 0;

    SetCanLong(mpdwChannelsA, i, coEnergy.dwBuff);
  }

  coEnergy.dwBuff = GetCanLong(mpdwChannelsA, diCurr.ibLine);
}


/*
// посылка запроса на коррекцию времени для счётчика Меркурий-230
void    QueryControlB(void)
{
  InitPush();

  PushChar(diCurr.bAddress);
  PushChar(3);      
  PushChar(0x0D);      

  PushChar( ToBCD(tiCurr.bSecond) );
  PushChar( ToBCD(tiCurr.bMinute) );
  PushChar( ToBCD(tiCurr.bHour)   );

  QueryIO(1+1+2, 3+3+2);
}


/ *
// посылка запроса на установку времени для счётчика Меркурий-230
void    QueryManageB(void)
{
  InitPush();

  PushChar(diCurr.bAddress);
  PushChar(3);      
  PushChar(0x0C);      

  PushChar( ToBCD(tiCurr.bSecond) );
  PushChar( ToBCD(tiCurr.bMinute) );
  PushChar( ToBCD(tiCurr.bHour)   );

  tiAlt = tiCurr;
  PushChar(Weekday()+1);

  PushChar( ToBCD(tiCurr.bDay)   );
  PushChar( ToBCD(tiCurr.bMonth) );
  PushChar( ToBCD(tiCurr.bYear)  );

  tiAlt = tiCurr;
  PushChar(Season());

  QueryIO(1+1+2, 3+8+2);
}
*/


// чтене времени/даты для счётчика Меркурий-230
void    QueryTimeB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);       
  PushChar(4);
  PushChar(0);

  QueryIO(1+8+2, 3+0+2);
}


// чтение времени/даты для счётчика Меркурий-230
void    ReadTimeAltB(void)
{
  InitPop(1);

  tiAlt.bSecond = FromBCD( PopChar() );
  tiAlt.bMinute = FromBCD( PopChar() );
  tiAlt.bHour   = FromBCD( PopChar() );

  PopChar();

  tiAlt.bDay    = FromBCD( PopChar() );
  tiAlt.bMonth  = FromBCD( PopChar() );
  tiAlt.bYear   = FromBCD( PopChar() );
}

/*
// чтение времени/даты для счётчика Меркурий-230
void    ReadTimeDigB(void)
{
  InitPop(1);

  tiDig.bSecond = FromBCD( PopChar() );
  tiDig.bMinute = FromBCD( PopChar() );
  tiDig.bHour   = FromBCD( PopChar() );

  PopChar();

  tiDig.bDay    = FromBCD( PopChar() );
  tiDig.bMonth  = FromBCD( PopChar() );
  tiDig.bYear   = FromBCD( PopChar() );
}



// посылка запроса на чтение вершины массива для счётчика Меркурий-230
void    QueryTopB(void)
{
  InitPush();

  PushChar(diCurr.bAddress);         
  PushChar(8);      
  PushChar(0x13);      

  QueryIO(1+9+2, 2+1+2);
}


// чтение вершины массива для счётчика Меркурий-230
void    ReadTopBOld(void)
{ 
  // адрес обрабатываемого блока
  if (!UseBounds())
  {
    wBaseCurr = InBuff(1)*0x100 + InBuff(2);
    ResetLimitsAux(ibDig);
  }
  else 
  {
    if (mpboStartCan[ibDig] == boFalse) 
    {
      wBaseCurr = InBuff(1)*0x100 + InBuff(2);
      if (boShowMessages == boTrue) sprintf(szLo,"  начало %04X * ",wBaseCurr);
      ResetLimitsAux(ibDig);
    }
    else 
    {
      wBaseCurr = mpcwStartAbsCan[ibDig];
      if (boShowMessages == boTrue) sprintf(szLo,"  начало %04X   ",wBaseCurr);
      iwMajor = wBaseCurr; AddDigRecord(EVE_PREVIOUS_TOP);
    }

    if (boShowMessages == boTrue) DelayMsg();
  }

  // индекс по получасовому массиву
  iwDigHou = 0;

  // счётчик получасов в выключенном состоянии
  iwMajor = 0;

  InitRefill();

#ifdef  DAYS100
  dwTmpPrev = 0;

  wBaseInit = InBuff(1)*0x100 + InBuff(2);
#endif
}



// посылка запроса на чтение заголовка часового блока для счётчика Меркурий-230
void    QueryHeaderB(void)
{
  InitPush();

  PushChar(diCurr.bAddress);         
  PushChar(6);      
  PushChar(3);      

  PushChar(wBaseCurr / 0x100);      
  PushChar(wBaseCurr % 0x100);      

  PushChar(15);      

  QueryIO(1+15+2, 3+3+2);
}


// посылка запроса на чтение заголовка часового блока для счётчика Меркурий-230
void    QueryHeaderB_Plus(uchar  bSize)
{
  ShowLo(szWaiting); 

  InitPush();

  PushChar(diCurr.bAddress);         
  PushChar(6);      
  PushChar(4);      

  PushChar(wBaseCurr / 0x100);      
  PushChar(wBaseCurr % 0x100);      

  PushChar(bSize);      

  QueryIO((uint)18*bSize+2, 3+3+2);
}



bit     TestHeaderB(uchar  ibBlock)
{
  tiDig.bHour   = FromBCD( InBuff((uint)2+ibBlock*18) );// время/дата часового блока
  tiDig.bMinute = FromBCD( InBuff((uint)3+ibBlock*18) );
  tiDig.bDay    = FromBCD( InBuff((uint)4+ibBlock*18) );
  tiDig.bMonth  = FromBCD( InBuff((uint)5+ibBlock*18) );
  tiDig.bYear   = FromBCD( InBuff((uint)6+ibBlock*18) );

  if ((tiDig.bHour   == 99) &&                          // ошибка преобразователя
      (tiDig.bMinute == 99) &&
      (tiDig.bDay    == 99) &&
      (tiDig.bMonth  == 99) &&
      (tiDig.bYear   == 99)) 
  {
    ShowLo(szNoDevice); DelayMsg();
    return(0);
  }

  return(1);
}


// чтение заголовка часового блока для счётчика Меркурий-230
bit     ReadHeaderB(uchar  ibBlock, bit  fDelay)
{
  NoShowTime(1);                                        // запрещаем автоматическое отображение времени
  
  tiDig.bHour   = FromBCD( InBuff((uint)2+ibBlock*18) );// время/дата часового блока
  tiDig.bMinute = FromBCD( InBuff((uint)3+ibBlock*18) );
  tiDig.bDay    = FromBCD( InBuff((uint)4+ibBlock*18) );
  tiDig.bMonth  = FromBCD( InBuff((uint)5+ibBlock*18) );
  tiDig.bYear   = FromBCD( InBuff((uint)6+ibBlock*18) );

  if ((tiDig.bHour   == 0) &&                           // обрабатываем пустой блок
      (tiDig.bMinute == 0) &&
      (tiDig.bDay    == 0) &&
      (tiDig.bMonth  == 0) &&
      (tiDig.bYear   == 0)) 
  {
    if (++iwMajor > 480) return(0);                     // если питание было выключено слишком долго
    sprintf(szLo," выключено: %-4u   ",iwMajor); if (fDelay == 1) DelayOff();

    if (iwDigHou != 0)
    {
       iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;

       ShowProgressDigHou();
       return(MakeStopHou(0));  
    }
    else return(1);
  }


  if ((tiDig.bDay   == tiSummer.bDay) &&
      (tiDig.bMonth == tiSummer.bMonth))
  {
    if ((tiDig.bHour   == 3) && 
        (tiDig.bMinute == 0))
    {
      tiDig.bHour   = 2;  
      tiDig.bMinute = 0;
    }
  }


  sprintf(szLo," %02bu    %02bu.%02bu.%02bu",           // показываем время/дату часового блока
          tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if ((tiDig.bMinute % 30) != 0)                        // обрабатываем неполный получасовой блок
  {
    tiDig.bMinute = (tiDig.bMinute / 30)*30;
    if (SearchDefHouIndex() == 0) { szLo[4] = '?'; if (fDelay == 1) DelayOff(); return(1); }

    iwDigHou = (wHOURS+iwDigHou+1)%wHOURS;   
  }
#ifdef  DAYS100
  else if (SearchDefHouIndex2(31*48) == 0) { szLo[4] = '?'; if (fDelay == 1) DelayOff(); return(1); } 

  if ((wBasePrev > wBaseInit) && (wBaseCurr <= wBaseInit)) return 0;
  wBasePrev = wBaseCurr;
#else
  else if (SearchDefHouIndex() == 0) { szLo[4] = '?'; if (fDelay == 1) DelayOff(); return(1); } 
#endif


  iwMajor = 0;                                          // обнуляем счётчик после получения правильных данных


  iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;                // время записи должно соответсвовать началу получасового блока

  tiAlt = tiCurr;
  dwBuffC = DateToHouIndex();

  dwBuffC -= (wHOURS + iwHardHou - iwDigHou) % wHOURS;
  HouIndexToDate(dwBuffC);


  ShowProgressDigHou();      
  if (fDelay == 1) DelayOff();
  
//  InitPop(8);                              
  for (ibCan=0; ibCan<4; ibCan++)        
  {
    wBuffD  = InBuff( (uint)8+ibBlock*18+ibCan*2 );         //PopChar();
    wBuffD += InBuff( (uint)9+ibBlock*18+ibCan*2 )*0x100;   //PopChar()*0x100;

    if (wBuffD == 0xFFFF) wBuffD = 0;

    mpwChannels[ibCan] = wBuffD;
  }

  MakeRefillWinter();
  MakePrevHou();  
  if (boRefillDisable == boFalse) MakeRefill();
  return(MakeStopHou(0));  
}



void    ReadCurrentB(void)
{
uchar   i;

  ReadEnergyB();
  reBuffA = *PGetCanReal(mpreLevelDiv, ibDig);

  for (i=0; i<4; i++)
  {
    dwBuffC = *PGetCanLong(mpdwChannelsA, i) * reBuffA;
    SetCanLong(mpdwBaseDig, i);
  }

  MakeCurrent();
}


bit     QueryIdB_Full(void)
{
  for (x=0; x<bMINORREPEATS; x++)
  {
    DelayOff();
    QueryIdB();

    if ((Input() == SER_GOODCHECK) && (ReadIdB() == 1)) break;
    if (fKey == 1) return(0);

    ShowLo(szFailure20); Delay(1000);
    mpcwFailure2[ibDig]++;
  }

  Clear();
  if (x == bMINORREPEATS) return(0);

  return(1);
}


bit     QueryEnergyB_Full2(uchar  bTime, uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyB(bTime);

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);

    if (QueryIdB_Full() == 0) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadEnergyB();
  return(1);
}

#endif
*/

