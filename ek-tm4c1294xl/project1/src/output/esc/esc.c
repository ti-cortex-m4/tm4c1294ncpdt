/*------------------------------------------------------------------------------
ESC.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_esc.h"
#include "../../flash/files.h"
#include "esc.h"



file const              flMaxMachineEsc = {MAX_MACHINE_ESC, &bMaxMachineEsc, sizeof(uchar)};
file const              flDsblEsc = {DSBL_ESC, &boDsblEsc, sizeof(boolean)};



void    InitEsc(void)
{
  LoadFile(&flMaxMachineEsc);
  if ((bMaxMachineEsc == 0) || (bMaxMachineEsc > bMAXMACHINEESC))
  {
    bMaxMachineEsc = bMAXMACHINEESC;
    SaveFile(&flMaxMachineEsc);
  }

  LoadFile(&flDsblEsc);
}


void    ResetEsc(void)
{
  bMaxMachineEsc = bMAXMACHINEESC;
  SaveFile(&flMaxMachineEsc);

  boDsblEsc = FALSE;
  SaveFile(&flDsblEsc);
}
