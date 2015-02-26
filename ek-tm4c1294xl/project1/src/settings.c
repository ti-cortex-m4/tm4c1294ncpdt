/*------------------------------------------------------------------------------
SETTINGS.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_settings.h"
#include        "flash/files.h"
#include        "settings.h"



file const              flLogical = {DF_LOGICAL, &bLogical, sizeof(uchar), FOR_DEFAULT};



void    InitSettings(void) {
  if (LoadPrivate() == FALSE) {
    wPrivate = 1;
    SavePrivate();
  }

  LoadGlobal();
  if ((enGlobal != GLB_PROGRAM) && (enGlobal != GLB_WORK)) // TODO LoadGlobal
  	enGlobal = GLB_PROGRAM;

  LoadFile(&flLogical);
}


void    ResetSettings(bool  fFullReset) {
	enGlobal = GLB_PROGRAM;
  SaveGlobal();

  if (fFullReset) {
  	bLogical = 0;
    SaveFile(&flLogical);
  }
}



boolean SavePrivate(void) {
	return SaveBuff(DF_PRIVATE, &wPrivate, sizeof(uint), FOR_DEFAULT);
}


boolean LoadPrivate(void) {
  return LoadBuff(DF_PRIVATE, &wPrivate, sizeof(uint));
}



boolean SaveGlobal(void) {
	return SaveBuff(DF_GLOBAL, &enGlobal, sizeof(global), FOR_DEFAULT);
}


boolean LoadGlobal(void) {
  return LoadBuff(DF_GLOBAL, &enGlobal, sizeof(global));
}
