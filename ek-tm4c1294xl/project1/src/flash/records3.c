/*------------------------------------------------------------------------------
RECORD3.C


------------------------------------------------------------------------------*/

#include "../main.h"



void    ResetRecordDisable(void)
{
//  memset(&mpboRecordDisable, 0, sizeof(mpboRecordDisable));
//
//  mpboRecordDisable[EVE_PROFILEOPEN] = boTrue;
//  mpboRecordDisable[EVE_PROFILE_OK2] = boTrue;
//  mpboRecordDisable[EVE_PROFILE2] = boTrue;
}


bool    IsRecordDisabled(uchar  ibCode)
{
  return false; //mpboRecordDisable[ibCode] != boFalse;
}



void    OutRecordDisable(void)
{
//  InitPushCRC();
//  Push(&mpboRecordDisable, sizeof(mpboRecordDisable));
//  Output(sizeof(mpboRecordDisable));
}
