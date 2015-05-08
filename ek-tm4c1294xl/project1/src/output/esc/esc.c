/*------------------------------------------------------------------------------
ESC.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../flash/files.h"
#include "esc.h"



file const              flEscMaxMachines = {ESC_MAX_MASHINES, &bEscMaxMachines, sizeof(uchar)};



void    InitEsc(void)
{
  LoadFile(&flEscMaxMachines);

  if ((bEscMaxMachines == 0) || (bEscMaxMachines > bMACHINES))
  {
    bEscMaxMachines = bMACHINES;
    SaveFile(&flEscMaxMachines);
  }
}


void    ResetEsc(void)
{
	bEscMaxMachines = bMACHINES;
  SaveFile(&flEscMaxMachines);
}
