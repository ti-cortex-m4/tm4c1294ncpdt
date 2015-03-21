/*------------------------------------------------------------------------------
FLASH_CONTROL.C


------------------------------------------------------------------------------*/

#include        <string.h>
#include        "../main.h"
#include        "../memory/mem_flash.h"
#include        "../memory/mem_ports.h"
#include        "../serial/ports.h"



void    IncFlashControl(void) 
{
  mpcwFlashControl[wPageOut]++;
}


void    OutFlashControl(void) 
{
uint    i;

  if (500*(bInBuff6+1) < wPAGES)
  {
    InitPushCRC();
    Push(&mpcwFlashControl[500*bInBuff6], sizeof(uint)*500);
    Output(sizeof(uint)*500);
  }
  else 
  {
    InitPushCRC();
    Push(&mpcwFlashControl[500*bInBuff6], sizeof(uint)*(wPAGES-500*bInBuff6));
    for (i=0; i<500*(bInBuff6+1)-wPAGES; i++) PushInt(0xFFFF);
    Output(sizeof(uint)*500);
  }
}
