/*------------------------------------------------------------------------------
DEVICE_A!C
              
 Подпрограммы доступа к цифровому счётчику СЭТ-4ТМ
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy_spec.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_limits.h"
#include "../../display/display.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../time/decret.h"
#include "../../time/delay.h"
#include "../../realtime/realtime.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports_common.h"
#include "../../serial/save_in_buff.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
#include "../../digitals/current/current_run.h"
#include "../../digitals/digitals_messages.h"
#include "../../digitals/limits.h"
#include "../../digitals/profile/refill.h"
#include "../../special/special.h"
#include "../../flash/records.h"
#include "../../energy.h"
#include "device_a.h"



#ifndef SKIP_A

// проверка сетевого адреса для счётчиков СЭТ-4ТМ
bool    ReadAddressA(void)
{
//  return(InBuff(0) == diCurr.bAddress);
  return(1);
}


// проверка результата операции для счётчиков СЭТ-4ТМ
bool    ReadResultA(void)
{
  TestResult(InBuff(1));
  return(ReadAddressA() && (InBuff(1) == 0));
}



// посылка запроса на открытие канала связи
void    QueryOpenA(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);         
  PushChar(1);      

  if (boEnblKeys != true)
  {
    PushChar('0');                        
    PushChar('0');         
    PushChar('0');
    PushChar('0');
    PushChar('0');
    PushChar('0');
  }
  else
  {
    line ln = mpphKeys[ibDig];
    bool f = 0;

    uchar i;
    for (i=0; i<6; i++)
    {
      if (ln.szLine[i] == 0) f = 1;

      if (f == 0)
        PushChar(ln.szLine[i]);
      else  
        PushChar(0);
    }
  }

  QueryIO(2+2, 2+6+2);
}
 


// посылка запроса на чтение логического номера
void    QueryIdA(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(8);
  PushChar(5);

  QueryIO(1+2+2, 3+0+2);
}


// чтение логического номера
bool    ReadIdA(void)
{
  InitPop(0);
  if (PopChar() != diCurr.bAddress) return 0;
  if (PopChar() != 0) return 0;
  if ((PopChar() != diCurr.bAddress) && (0 != diCurr.bAddress)) return 0;

  return 1;
}



// посылка запроса на чтение энергии для счётчиков СЭТ-4ТМ
void    QueryEnergyA(uchar  bTime)
{
  InitPush(0);

  PushChar(diCurr.bAddress);           
  PushChar(5);                          // чтение накопленной энергии

  PushChar(bTime);                      // вид энергии
  PushChar(0);                          // по всем тарифам

  QueryIO(1+16+2, 2+2+2);
}


// чтение энергии
void    ReadEnergyA(void)
{
uchar   i;

  InitPop(1);

  for (i=0; i<4; i++)
  {
    coEnergy.mpbBuff[3] = PopChar();
    coEnergy.mpbBuff[2] = PopChar();
    coEnergy.mpbBuff[1] = PopChar();
    coEnergy.mpbBuff[0] = PopChar();

    mpdwChannelsA[i] = coEnergy.dwBuff;
  }

  coEnergy.dwBuff = mpdwChannelsA[diCurr.ibLine];
}



// посылка запроса на коррекцию времени
void    QueryControlA(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(3);      
  PushChar(0x0D);      

  PushChar( ToBCD(tiCurr.bSecond) );
  PushChar( ToBCD(tiCurr.bMinute) );
  PushChar( ToBCD(tiCurr.bHour)   );

  QueryIO(1+1+2, 3+3+2);
}



// посылка запроса на установку времени
void    QueryManageA(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(3);      
  PushChar(0x0C);      

  PushChar( ToBCD(tiCurr.bSecond) );
  PushChar( ToBCD(tiCurr.bMinute) );
  PushChar( ToBCD(tiCurr.bHour)   );

  PushChar(GetWeekdayYMD(tiCurr.bYear, tiCurr.bMonth, tiCurr.bDay) + 1);

  PushChar( ToBCD(tiCurr.bDay)   );
  PushChar( ToBCD(tiCurr.bMonth) );
  PushChar( ToBCD(tiCurr.bYear)  );

  PushChar(GetSeasonMD(tiCurr.bMonth, tiCurr.bDay));

  QueryIO(1+1+2, 3+8+2);
}



// посылка запроса на чтене времени/даты
void    QueryTimeA(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);       
  PushChar(4);
  PushChar(0);

  QueryIO(1+8+2, 3+0+2);
}


// чтение времени/даты
time    ReadTimeA(void)
{
time  ti;

  InitPop(1);

  ti.bSecond = FromBCD( PopChar() );
  ti.bMinute = FromBCD( PopChar() );
  ti.bHour   = FromBCD( PopChar() );

  PopChar();

  ti.bDay    = FromBCD( PopChar() );
  ti.bMonth  = FromBCD( PopChar() );
  ti.bYear   = FromBCD( PopChar() );

  return ti;
}



// посылка запроса на чтение вершины массива
void    QueryTopA(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);         
  PushChar(8);      
  PushChar(4);      

  QueryIO(1+7+2, 2+1+2);
}


// чтение вершины массива
void    ReadTopA(void)
{
  // индекс текущего получаса
  bCurrHouIndex = FromBCD(InBuff(2))*2 + FromBCD(InBuff(1) & 0x7F)/30;


  // индекс текущего блока
  if (!UseBounds())
  {
    iwMajor = (InBuff(6)*0x100 + InBuff(7)) / 24;
    ResetLimitsAux(ibDig);
  }
  else 
  {
    if (mpboStartCan[ibDig] == false)
    {
      iwMajor = (InBuff(6)*0x100 + InBuff(7)) / 24;
      if (boShowMessages == true) sprintf(szLo,"  начало %04X * ",iwMajor);
      ResetLimitsAux(ibDig);
    }
    else 
    {
      iwMajor = mpcwStartAbs16Can[ibDig];
      if (boShowMessages == true) sprintf(szLo,"  начало %04X   ",iwMajor);
      AddDigRecord(EVE_PREVIOUS_TOP);
    }

    if (boShowMessages == true) DelayMsg();
  }

  // адрес заголовка текущего блока
  wBaseCurr = iwMajor*24;


  // счётчик прочитанных блоков
  cwDigHou = 0;

  // счётчик пропущенных записей
  ibMinor = 0;
}



void    QueryHeaderA(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);         
  PushChar(6);      
  PushChar(3);      

  wBaseLast = iwMajor*24;

  PushChar(wBaseLast / 0x100);      
  PushChar(wBaseLast % 0x100);      

  PushChar(8);      

  QueryIO(1+8+2, 3+3+2);
}


void    QueryHeaderA_Plus(uchar  bSize)
{
  ShowLo(szWaiting); 

  InitPush(0);

  PushChar(diCurr.bAddress);         
  PushChar(6);      
  PushChar(5);      

  wBaseLast = iwMajor*24;

  PushChar(wBaseLast / 0x100);      
  PushChar(wBaseLast % 0x100);      

  PushChar(bSize);      

  QueryIO((uint)30*bSize+2, 3+3+2);
}



void    ReadHeaderA(void)
{
  SaveInBuff();
}



void    QueryDataA(void)
{
uint    i;

  InitPush(0);

  PushChar(diCurr.bAddress);         
  PushChar(6);      
  PushChar(3);      

  i = iwMajor*24 + 8;

  PushChar(i / 0x100);      
  PushChar(i % 0x100);      

  PushChar(16);      

  QueryIO(1+16+2, 3+3+2);
}



bool    ReadDataBlockA(uchar  bOffset, uchar  ibRecord, uchar  ibBlock)
{
  if (++cwDigHou >= 8192/3) return(0);


  tiDig = tiDigPrev;                                    // восстанавливаем...
  tiDig.bMinute = ibRecord*30;                          // рассчитываем минуты записи из часового блока

  if (SearchDefHouIndex(tiDig) == 0)                    // выход: часовой блок не имеется в массиве получасового брака
  {
    if (++ibMinor > 48) return(0);
    if (ibMinor > 2) sprintf(szLo," выключено: %-2u   ",ibMinor);
    
    return(1);
  }
  else ibMinor = 0;


  time ti = tiDig;

  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  ShowProgressDigHou();        
    
  if ((wBaseCurr == wBaseLast) && (GetCurrHouIndex() != bCurrHouIndex))
    return(1);                                          // выход: часовой блок не готов


  InitPop(bOffset+ibRecord*8+ibBlock*30);

  uchar i;
  for (i=0; i<4; i++)
  {
    mpwChannels[i] = (PopChar()*0x100 + PopChar()) & 0x7FFF;
  }

  MakeSpecial(ti);
  return(MakeStopHou(0));  
}


bool    ReadDataA(void)
{
  HideCurrTime(1);                                   
    
  tiDig.bHour  = FromBCD( mpbInBuffSave[1] );           // время/дата часового блока
  tiDig.bDay   = FromBCD( mpbInBuffSave[2] );
  tiDig.bMonth = FromBCD( mpbInBuffSave[3] );
  tiDig.bYear  = FromBCD( mpbInBuffSave[4] );
 
  tiDigPrev = tiDig;                                    // сохраняем...

  if (mpbInBuffSave[1] +                                // выход: неправильная контрольная сумма часового блока
      mpbInBuffSave[2] +                                
      mpbInBuffSave[3] + 
      mpbInBuffSave[4] + 
      mpbInBuffSave[5] + 
      mpbInBuffSave[6] != mpbInBuffSave[7]) return(1);

  if (mpbInBuffSave[6] != 30) return(1);                // выход: неправильный период интегрирования
  
  if (ReadDataBlockA(1,0,0) == 0) return(0);
  if (ReadDataBlockA(1,1,0) == 0) return(0);

  return(1);
}



bool    TestDataA_Plus(uchar  ibBlock)
{
  tiDig.bHour  = FromBCD( InBuff((uint)1+ibBlock*30) ); // время/дата часового блока
  tiDig.bDay   = FromBCD( InBuff((uint)2+ibBlock*30) );
  tiDig.bMonth = FromBCD( InBuff((uint)3+ibBlock*30) );
  tiDig.bYear  = FromBCD( InBuff((uint)4+ibBlock*30) );

  if ((tiDig.bHour   == 99) &&                          // ошибка преобразователя
      (tiDig.bDay    == 99) &&
      (tiDig.bMonth  == 99) &&
      (tiDig.bYear   == 99)) 
  {
    ShowLo(szNoDevice); DelayMsg();
    return(0);
  }

  return(1);
}


bool    ReadDataA_Plus(uchar  ibBlock)
{
  HideCurrTime(1);                                   
  DelayOff();
        
  tiDig.bHour  = FromBCD( InBuff((uint)1+ibBlock*30) ); // время/дата часового блока
  tiDig.bDay   = FromBCD( InBuff((uint)2+ibBlock*30) );
  tiDig.bMonth = FromBCD( InBuff((uint)3+ibBlock*30) );
  tiDig.bYear  = FromBCD( InBuff((uint)4+ibBlock*30) );

  tiDigPrev = tiDig;                                    // сохраняем...
 
  if (InBuff((uint)1+ibBlock*30) +                      // выход: неправильная контрольная сумма часового блока
      InBuff((uint)2+ibBlock*30) +                      
      InBuff((uint)3+ibBlock*30) + 
      InBuff((uint)4+ibBlock*30) + 
      InBuff((uint)5+ibBlock*30) + 
      InBuff((uint)6+ibBlock*30) != InBuff((uint)7+ibBlock*30)) return(1);

  if (InBuff((uint)6+ibBlock*30) != 30) return(1);      // выход: неправильный период интегрирования
  
  if (ReadDataBlockA(12,0,ibBlock) == 0) return(0);
  if (ReadDataBlockA(12,1,ibBlock) == 0) return(0);

  return(1);
}



void    ReadCurrentA(void)
{
uchar   i;

  ReadEnergyA();

  for (i=0; i<4; i++)
  {
    mpdwBaseDig[i] = mpdwChannelsA[i];
  }

  MakeCurrent();
}

#endif

