/*------------------------------------------------------------------------------
FLASH_CONTROL,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_flash.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "flash_control.h"



void    IncFlashControl(uint const  wPageOut)
{
  mpcwFlashControl[wPageOut]++;
}


void    OutFlashControl(void) 
{
  if (500*(bInBuff6+1) < wPAGES_TOTAL)
  {
    InitPushCRC();
    PushBuffInt(&mpcwFlashControl[500*bInBuff6], 500);
    Output(sizeof(uint)*500);
  }
  else 
  {
    InitPushCRC();
    PushBuffInt(&mpcwFlashControl[500*bInBuff6], wPAGES_TOTAL-500*bInBuff6);

    uint i;
    for (i=0; i<500*(bInBuff6+1)-wPAGES_TOTAL; i++) PushInt(0xFFFF);

    Output(sizeof(uint)*500);
  }
}
