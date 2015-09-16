/*------------------------------------------------------------------------------
DSBL_ANSWER.C

 'Отчет №69 от 11_11_2010'
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "../serial/ports.h"
#include "dsbl_answer.h"



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



void    OutDsblAnswer(void)
{
  InitPushCRC();
  PushBool(boAnswerDisable);
  PushBool(boAnswerFlag);
  PushLong(cdwAnswerDisable);
  PushTime(tiAnswerDisable);
  PushLong(cdwAnswerEnable);
  PushTime(tiAnswerEnable);
  Output(1+1+4+6+4+6);
}
