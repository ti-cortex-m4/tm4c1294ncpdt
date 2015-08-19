/*------------------------------------------------------------------------------
DIGITALS_DISPLAY.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "digitals.h"
#include "sensors.h"
#include "digitals_display.h"



//                                          0123456789ABCDEF
static char const       szPortDelays[]   = "Таймауты        ";



void    ShowDigital(uchar  ibCan)
{
  sprintf(szLo,"%1u.%02u.%02u.%03u.%02u  ",
               GetDigitalPort(ibCan)+1,
               GetDigitalPhone(ibCan),
               GetDigitalDevice(ibCan),
               GetDigitalAddress(ibCan),
               GetDigitalLine(ibCan)+1);

  sprintf(szHi+14,"%02u",ibCan+1);
  (mpboEnblCan[ibCan]) ? (szHi[13] = '+') : (szHi[13] = '-');
}


void    ShowCanalNumber(uchar  ibCan)
{
  ShowHi(szClear);
  sprintf(szHi,"Канал: %-2u",ibCan+1);
}


void    ShowPort(uchar  ibPort)
{
  ShowHi(szClear);
  sprintf(szHi,"Порт: %u",ibPort+1);
}



void    ShowPortDelayHi(uchar  ibPrt)
{
  ShowPort(ibPrt);

  if (GetMinorDelay(ibPrt) < 10000)
    sprintf(szHi+8,"%5lu мс", GetMinorDelay(ibPrt));
  else
    sprintf(szHi+8,"%5lu с ", GetMinorDelay(ibPrt)/1000);
}


void    ShowPortDelayLo(uchar  ibPrt)
{
  ShowHi(szPortDelays);
  Clear();
  sprintf(szLo,"порт: %u",ibPrt+1);

  if (GetMinorDelay(ibPrt) < 10000)
    sprintf(szLo+8,"%5lu мс", GetMinorDelay(ibPrt));
  else
    sprintf(szLo+8,"%5lu с ", GetMinorDelay(ibPrt)/1000);
}



void    ShowDeltaTimePositive(uchar  ibCan, ulong  dwSecond)
{
  ShowCanalNumber(ibCan);
  Clear();
  sprintf(szLo+1,"сдвиг: +%lu с", dwSecond); (boShowMessages == true) ? DelayMsg() : DelayInf();
}


void    ShowDeltaTimeNegative(uchar  ibCan, ulong  dwSecond)
{
  ShowCanalNumber(ibCan);
  Clear();
  sprintf(szLo+1,"сдвиг: -%lu с", dwSecond); (boShowMessages == true) ? DelayMsg() : DelayInf();
}


void    ShowDigitalDeltaTime(uchar  ibCan, ulong  dwSecond1, ulong  dwSecond2)
{
  ShowCanalNumber(ibCan);
  Clear();

  if (dwSecond1 > dwSecond2)
    sprintf(szLo+1,"сдвиг: -%lu с", dwSecond1 - dwSecond2);
  else
    sprintf(szLo+1,"сдвиг: +%lu с", dwSecond2 - dwSecond1);

  (boShowMessages == true) ? DelayMsg() : DelayInf();
}
