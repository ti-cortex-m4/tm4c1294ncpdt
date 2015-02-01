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
