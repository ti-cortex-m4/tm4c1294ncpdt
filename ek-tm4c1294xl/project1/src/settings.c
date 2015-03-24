/*------------------------------------------------------------------------------
SETTINGS.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_settings.h"
#include        "memory/mem_program.h"
#include        "flash/files.h"
#include        "settings.h"



file const              flLogical = {FLS_LOGICAL, &bLogical, sizeof(uchar)};

file const              flFirstReset = {FLS_FIRST_RESET, &boFirstReset, sizeof(boolean)};



void    InitSettings(void)
{
  if (LoadPrivate() == FALSE)
  {
    wPrivate = 1;
    SavePrivate();
  }

  LoadGlobal();
  if ((enGlobal != GLB_PROGRAM) && (enGlobal != GLB_WORK)) // TODO LoadGlobal
    enGlobal = GLB_PROGRAM;

  LoadFile(&flLogical);

  LoadFile(&flFirstReset);
}


void    ResetSettings(bool  fFullReset)
{
  enGlobal = GLB_PROGRAM;
  SaveGlobal();

  if (fFullReset)
  {
    bLogical = 0;
    SaveFile(&flLogical);
  }

  boFirstReset = FALSE;
  SaveFile(&flFirstReset);
}



boolean SavePrivate(void) {
	return SaveBuff(FLS_PRIVATE, &wPrivate, sizeof(uint));
}


boolean LoadPrivate(void) {
  return LoadBuff(FLS_PRIVATE, &wPrivate, sizeof(uint));
}


// TODO GlobalLabel
boolean SaveGlobal(void) {
	return SaveBuff(FLS_GLOBAL, &enGlobal, sizeof(global));
}


boolean LoadGlobal(void) {
  return LoadBuff(FLS_GLOBAL, &enGlobal, sizeof(global));
}
