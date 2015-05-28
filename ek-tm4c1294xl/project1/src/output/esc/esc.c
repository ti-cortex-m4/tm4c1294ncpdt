/*------------------------------------------------------------------------------
ESC,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_esc.h"
#include "../../flash/files.h"
#include "../../flash/files2.h"
#include "esc.h"



file const              flMachinesEsc = {MACHINES_ESC, &bMachinesEsc, sizeof(uchar)};
file const              flBlockEsc = {BLOCK_ESC, &boBlockEsc, sizeof(bool)};



void    InitEsc(void)
{
  LoadFileChar(&flMachinesEsc, 1, bMAXMACHINES, bMAXMACHINES);
  LoadFileBoolean(&flBlockEsc, false);
}


void    ResetEsc(void)
{
  bMachinesEsc = bMAXMACHINES;
  SaveFile(&flMachinesEsc);

  boBlockEsc = false;
  SaveFile(&flBlockEsc);
}
