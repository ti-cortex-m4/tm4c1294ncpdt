/*------------------------------------------------------------------------------
SETTINGS.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_settings.h"
#include        "flash/files.h"
#include        "settings.h"



file const              flLogical = {FLS_LOGICAL, &bLogical, sizeof(uchar)};



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
