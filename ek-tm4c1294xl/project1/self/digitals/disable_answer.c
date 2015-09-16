/*------------------------------------------------------------------------------
DISABLE_ANSWER.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "disable_answer.h"


cache const             chDsblAnswer = {DSBL_ANSWER, &boAnswerDisable, sizeof(bool)};



void    InitDisableAnswer(void)
{
  LoadCacheBool(&chDsblAnswer, false);
}


void    ResetDisableAnswer(void)
{
	boAnswerDisable = false;
  SaveCache(&chDsblAnswer);
}



void    EnableAnswer(void)
{
//  boAnswerFlag = true;
//  cdwAnswerEnable++; tiAnswerEnable = tiCurr;
}


void    DisableAnswer(void)
{
//  boAnswerFlag = false;
//  cdwAnswerDisable++; tiAnswerDisable = tiCurr;
}


bool   AnswerDisabled(void)
{
  return 0; // boAnswerFlag != true;
}

