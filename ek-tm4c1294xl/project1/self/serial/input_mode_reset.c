/*------------------------------------------------------------------------------
INPUT_MODE_RESET.C

 ('Отчет №83a от 17.06.2012')
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../realtime/realtime.h"
#include "../isr/serial2.h"
#include "../isr/serial3.h"
#include "../serial/speeds.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "input_mode_reset.h"



cache const             chInputModeReset = {INPUT_MODE_RESET, &bInputModeReset, sizeof(uchar)};



void    InitInputModeReset(void)
{
  LoadCache(&chInputModeReset);
}


void    ResetInputModeReset(void)
{
  bInputModeReset = 0;
  SaveCache(&chInputModeReset);
}



void    NextHhrInputModeReset(void)
{
  if (fActive == true)
  {
    if (bInputModeReset == 0) return;
    if (GetCurrHouIndex() % bInputModeReset != 0) return;

    tiInputModeReset = tiCurr;
    dwInputModeReset++;

    if (IsSlave(2)) InputMode2();
    if (IsSlave(3)) InputMode3();
  }
}
