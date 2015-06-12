/*------------------------------------------------------------------------------
SETTINGS.C


------------------------------------------------------------------------------*/

#include "main.h"
#include "memory/mem_settings.h"
#include "memory/mem_program.h"
#include "flash/files.h"
#include "label.h"
#include "settings.h"



file const              flLogical = {LOGICAL, &bLogical, sizeof(uchar)};

file const              flFirstReset = {FIRST_RESET, &boFirstReset, sizeof(bool)};

file const              flSetTime = {SET_TIME, &boSetTime, sizeof(bool)};
file const              flSetDate = {SET_DATE, &boSetDate, sizeof(bool)};
file const              flSetGroups = {SET_GROUPS, &boSetGroups, sizeof(bool)};
file const              flSetPassword = {SET_PASSWORD, &boSetPassword, sizeof(bool)};



void    InitSettings(void)
{
  if (LoadPrivate() == false)
  {
    wPrivate = 1;
    SavePrivate();
  }

//  LoadGlobal();
//  if ((enGlobal != GLB_PROGRAM) && (enGlobal != GLB_WORK)) // TODO LoadGlobal
//    enGlobal = GLB_PROGRAM;

  if (GetLabel())  enGlobal = GLB_WORK; else enGlobal = GLB_PROGRAM;

  LoadFile(&flLogical);

  LoadFile(&flFirstReset);

  LoadFile(&flSetTime);
  LoadFile(&flSetDate);
  LoadFile(&flSetGroups);
  LoadFile(&flSetPassword);
}


void    ResetSettings(bool  fFull)
{
//  enGlobal = GLB_PROGRAM;
//  SaveGlobal();

  if (fFull)
  {
    bLogical = 1;
    SaveFile(&flLogical);
  }

  boFirstReset = false;
  SaveFile(&flFirstReset);

  if (fFull)
  {
    boSetTime = false;
    SaveFile(&flSetTime);

    boSetDate = false;
    SaveFile(&flSetDate);

    boSetPassword = true;
    SaveFile(&flSetPassword);
  }
}



bool SavePrivate(void) {
	return SaveBuff(PRIVATE, &wPrivate, sizeof(uint));
}


bool LoadPrivate(void) {
  return LoadBuff(PRIVATE, &wPrivate, sizeof(uint));
}


// TODO GlobalLabel
/*
bool SaveGlobal(void) {
	return SaveBuff(GLOBAL, &enGlobal, sizeof(global));
}


bool LoadGlobal(void) {
  return LoadBuff(GLOBAL, &enGlobal, sizeof(global));
}
*/
