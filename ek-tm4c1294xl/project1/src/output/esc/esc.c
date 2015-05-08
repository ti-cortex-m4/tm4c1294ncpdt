/*------------------------------------------------------------------------------
ESC.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_esc.h"
#include "../../flash/files.h"
#include "esc.h"



file const              flMaxMachineEsc = {MAX_MASHINE_ESC, &bMaxMachineEsc, sizeof(uchar)};



void    InitEsc(void)
{
  LoadFile(&flMaxMachineEsc);

  if ((bMaxMachineEsc == 0) || (bMaxMachineEsc > bMAXMACHINEESC))
  {
    bMaxMachineEsc = bMAXMACHINEESC;
    SaveFile(&flMaxMachineEsc);
  }
}


void    ResetEsc(void)
{
	bMaxMachineEsc = bMAXMACHINEESC;
  SaveFile(&flMaxMachineEsc);
}
