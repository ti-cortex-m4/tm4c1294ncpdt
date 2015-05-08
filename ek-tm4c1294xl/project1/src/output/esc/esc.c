/*------------------------------------------------------------------------------
ESC.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_esc.h"
#include "../../flash/files.h"
#include "esc.h"



file const              flMachinesEsc = {MACHINES_ESC, &bMachineEsc, sizeof(uchar)};
file const              flBlockEsc = {BLOCK_ESC, &boBlockEsc, sizeof(boolean)};



void    InitEsc(void)
{
  LoadFile(&flMachinesEsc);
  if ((bMachineEsc == 0) || (bMachineEsc > bMAXMACHINES))
  {
    bMachineEsc = bMAXMACHINES;
    SaveFile(&flMachinesEsc);
  }

  LoadFile(&flBlockEsc);
}


void    ResetEsc(void)
{
  bMachineEsc = bMAXMACHINES;
  SaveFile(&flMachinesEsc);

  boBlockEsc = FALSE;
  SaveFile(&flBlockEsc);
}
