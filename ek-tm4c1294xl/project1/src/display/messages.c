/*------------------------------------------------------------------------------
MESSAGES.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "display.h"



//                                         0123456789ABCDEF
char const              szClear[]       = "                ",
                        szWarning[]     = "Внимание: ошибка",
                        szError[]       = "    ошибка !    ",
                        szOK[]          = "       ОК       ",
                        szStop[]        = "     стоп !     ",
                        szWaiting[]     = "   ожидание...  ",
                        szCanal[]       = "   канал ?__    ",
                        szGroup[]       = "  группа ?__    ",
                        szParam[]       = "параметр ?___   ",
                        szNumber[]      = "   номер ?__    ",
                        szPort[]        = "    порт ?__    ",
                        szAddress[]     = "   адрес ?___   ",
                        szHour[]        = " получас ?__    ",
                        szDay[]         = "   сутки ?__    ",
                        szMonth[]       = "   месяц ?__    ",
                        szQuarter[]     = " квартал ?__    ",
                        szWork[]        = "Работа          ",
                        szSetting[]     = "Настройка       ",
                        szRun[]         = "Запуск          ",
                        szAlarm[]       = "Авария: ошибка  ",
                        szZones[]       = " Тарифные зоны  ",
                        szTariffs[]     = "Тарифные зоны   ",
                        szEnergy[]      = "    Энергия     ",
                        szPower[]       = "    Мощность    ",
                        szCounters[]    = "Счетчики        ",
                        szImpulseA[]    = "Импульсы        ",
                        szImpulseB[]    = "    Импульсы    ",
                        szOnCanals[]    = "   по каналам   ",
                        szOnGroups[]    = "   по группам   ",
                        szForPower[]    = "  для мощности  ",
                        szForEnergy[]   = "  для ~нергии   ",
                        szForDigital[]  = "   (цифровой)   ",
                        szOn12Months[]  = " за 12 месяцев  ",
                        szOnMinute[]    = "  за 3-мин      ",
                        szOnHour[]      = " за 30-мин      ",
                        szOnDay[]       = "  за сутки      ",
                        szOnMonth[]     = "  за месяц      ",
                        szMiddle[]      = "    средняя     ",
                        szCurrMnt[]     = " 3 мин. текущая ",
                        szCurrHou[]     = "30 мин. текущая ",
                        szPrevHou[]     = "30 мин. прошлая ",
                        szDayCurr[]     = "за текущие сутки",
                        szDayPrev[]     = "за прошлые сутки",
                        szMonCurr[]     = "за текущий месяц",
                        szMonPrev[]     = "за прошлый месяц",
                        szAbsolute[]    = "      всего     ",
                        szMaximum[]     = "  максимальная  ",
                        szFull[]        = " по всем зонам  ",
                        szMorning[]     = " в утренний пик ",
                        szEvening[]     = " в вечерний пик ",
                        szTops[]        = "в пиковых зонах ",
                        szMid[]         = "   в полупик    ",
                        szBottom[]      = "в ночной провал ",
                        szBadFlash[]    = "  фл~ш-памяти ! ",
                        szBadCODE[]     = "сегмента CODE ! ",
                        szBadNVRAM[]    = " памяти NVRAM ! ",
                        szBadRTC1[]     = "доступа к RTC ! ",
                        szBadRTC2[]     = "показаний RTC ! ",
                        szIsResetWDT[]  = "  сброс по WDT  ",
                        szEmpty[]       = "      нет       ",
                        szYes[]         = "да ",
                        szNo[]          = "нет";



void    Work(void)     {  ShowHi(szWork);     }
void    Setting(void)  {  ShowHi(szSetting);  }
void    Clear(void)    {  ShowLo(szClear);    }
void    Error(void)    {  ShowLo(szError);    }
void    OK(void)       {  ShowLo(szOK);       }
void    Stop(void)     {  ShowLo(szStop);     }
void    Waiting(void)  {  ShowLo(szWaiting);  }
void    Canal(void)    {  ShowLo(szCanal);    }
void    Group(void)    {  ShowLo(szGroup);    }
void    Param(void)    {  ShowLo(szParam);    }
void    Number(void)   {  ShowLo(szNumber);   }
void    Port(void)     {  ShowLo(szPort);     }
void    Address(void)  {  ShowLo(szAddress);  }
void    Hour(void )    {  ShowLo(szHour);     }
void    Day(void)      {  ShowLo(szDay);      }
void    Month(void)    {  ShowLo(szMonth);    }
void    Quarter(void)  {  ShowLo(szQuarter);  }
