/*------------------------------------------------------------------------------
SETTINGS.C


------------------------------------------------------------------------------*/

#include "main.h"
#include "memory/mem_settings.h"
#include "memory/mem_program.h"
#include "flash/files.h"
#include "settings.h"



file const              flLogical = {LOGICAL, &bLogical, sizeof(uchar)};

file const              flFirstReset = {FIRST_RESET, &boFirstReset, sizeof(boolean)};

file const              flSetTime = {SET_TIME, &boSetTime, sizeof(boolean)};
file const              flSetDate = {SET_DATE, &boSetDate, sizeof(boolean)};
file const              flSetGroups = {SET_GROUPS, &boSetGroups, sizeof(boolean)};
file const              flSetPassword = {SET_PASSWORD, &boSetPassword, sizeof(boolean)};



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

  LoadFile(&flSetTime);
  LoadFile(&flSetDate);
  LoadFile(&flSetGroups);
  LoadFile(&flSetPassword);
}


void    ResetSettings(bool  fFullReset)
{
  enGlobal = GLB_PROGRAM;
  SaveGlobal();

  if (fFullReset)
  {
    bLogical = 1;
    SaveFile(&flLogical);
  }

  boFirstReset = FALSE;
  SaveFile(&flFirstReset);

  if (fFullReset)
  {
    boSetTime = FALSE;
    SaveFile(&flSetTime);

    boSetDate = FALSE;
    SaveFile(&flSetDate);

    boSetPassword = TRUE;
    SaveFile(&flSetPassword);
  }
}



boolean SavePrivate(void) {
	return SaveBuff(PRIVATE, &wPrivate, sizeof(uint));
}


boolean LoadPrivate(void) {
  return LoadBuff(PRIVATE, &wPrivate, sizeof(uint));
}


// TODO GlobalLabel
boolean SaveGlobal(void) {
	return SaveBuff(GLOBAL, &enGlobal, sizeof(global));
}


boolean LoadGlobal(void) {
  return LoadBuff(GLOBAL, &enGlobal, sizeof(global));
}
