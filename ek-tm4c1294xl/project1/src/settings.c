/*------------------------------------------------------------------------------
SETTINGS.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_settings.h"
#include        "flash/files.h"
#include        "settings.h"



void    InitSettings(void) {
  if (LoadPrivate() == 0) {
    wPrivate = 1;
    SavePrivate();
  }

  LoadGlobal();
  if ((enGlobal != GLB_PROGRAM) && (enGlobal != GLB_WORK))
  	enGlobal = GLB_PROGRAM;

  LoadLogical();
}


void    ResetSettings(void) {
	enGlobal = GLB_PROGRAM;
  SaveGlobal();
}



bool    SavePrivate(void) {
	return SaveBuff(wFLA_PRIVATE, &wPrivate, sizeof(uint));
}


bool    LoadPrivate(void) {
  return LoadBuff(wFLA_PRIVATE, &wPrivate, sizeof(uint));
}



bool    SaveGlobal(void) {
	return SaveBuff(wFLA_GLOBAL, &enGlobal, sizeof(global));
}


bool    LoadGlobal(void) {
  return LoadBuff(wFLA_GLOBAL, &enGlobal, sizeof(global));
}



bool    SaveLogical(void) {
	return SaveBuff(wFLA_LOGICAL, &bLogical, sizeof(uchar));
}


bool    LoadLogical(void) {
  return LoadBuff(wFLA_LOGICAL, &bLogical, sizeof(uchar));
}
