/*------------------------------------------------------------------------------
WAIT_ANSWER!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../display/display.h"
#include "../serial/ports.h"



// счётчики секунд
uchar                   cbWaitAnswer, cbWaitAnswerPrev;



void    WaitAnswer_1Hz(void)
{
  cbWaitAnswer++;
}


void    InitWaitAnswer(void)
{
  cbWaitAnswerPrev = 0;
  cbWaitAnswer = 0;
}


void    ShowWaitAnswer(bool  fShow)
{
  if ((fShow == 1) && (cbWaitAnswerPrev != cbWaitAnswer))
  {
    sprintf(szLo+13,"%3u",cbWaitAnswer);
    cbWaitAnswerPrev = cbWaitAnswer;
  }
}


bool    GetWaitAnswer(void)
{
uchar   i;

  if (mpwInDelay[ibPort]/wFREQUENCY_T0 < 2)
    i = 2;
  else
    i = mpwInDelay[ibPort]/wFREQUENCY_T0;

  return(cbWaitAnswer > i);
}

