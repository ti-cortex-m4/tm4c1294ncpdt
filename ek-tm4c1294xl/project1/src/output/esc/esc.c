/*------------------------------------------------------------------------------
ESC.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_esc.h"
#include "../../flash/files.h"
#include "esc.h"



file const              flMaxMachinesEsc = {MAX_MASHINES_ESC, &bMaxMachinesEsc, sizeof(uchar)};



void    InitEsc(void)
{
  LoadFile(&flMaxMachinesEsc);

  if ((bMaxMachinesEsc == 0) || (bMaxMachinesEsc > bMACHINES))
  {
    bMaxMachinesEsc = bMACHINES;
    SaveFile(&flMaxMachinesEsc);
  }
}


void    ResetEsc(void)
{
	bMaxMachinesEsc = bMACHINES;
  SaveFile(&flMaxMachinesEsc);
}
