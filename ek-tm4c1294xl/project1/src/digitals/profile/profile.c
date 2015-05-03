/*------------------------------------------------------------------------------
PROFILE.C

 Чтение получасовых графиков с цифровых счетчиков
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_energy.h"
#include "../../memory/mem_realtime.h"
#include "../../energy.h"
#include "../current/current.h"
#include "../digitals.h"



void    MakeCurrHouCan(void)
{
uchar   c;

  for (c=0; c<bCANALS; c++)
  {
    if ((GetDigitalDevice(c) != 0) && (IsSpecCurrent(GetDigitalDevice(c)) == 0))
      mpwImpHouCan[ibSoftHou][c] = 0xFFFF;
  }
}
