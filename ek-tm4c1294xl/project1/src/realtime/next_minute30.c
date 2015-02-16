/*------------------------------------------------------------------------------
NEXT_MINUTE30.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy.h"
#include        "../power.h"
#include        "../energy2.h"



void    MakeCurrHouCan(void)
{
//uchar   c;
//
//  for (c=0; c<bCANALS; c++)
//  {
//    if ((GetDigitalDevice(c) != 0) && (IsSpecCurrent(GetDigitalDevice(c)) == 0))
//      SetCanInt(mpwImpHouCan[ibSoftHou], c, 0xFFFF);
//  }
}



void    NextMinute30(void)
{
  cdwMinutes30++;

  MakeMaxPowAll();

  SaveImpHou(0,iwHardHou,ibSoftHou);

  if (++iwHardHou >= wHOURS) iwHardHou = 0;
  if (++ibSoftHou >= 2)      ibSoftHou = 0;

  memset(&mpwImpHouCan[ibSoftHou], 0, sizeof(uint)*bCANALS);

  MakeCurrHouCan();
}
