/*------------------------------------------------------------------------------
SLIDES!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../time/delay.h"
#include "display.h"



bool                    fSlide, fSlideSave;

char const              **ppszCurr;

char const              **ppszFirst;

int                     cwSlide;



void    InitSlide(void)
{
  Delay(500); // TODO
  fSlide = false;

  ShowHiDirect(szRun);
  ShowLoDirect(szClear);
}


void    LoadSlide(char const  *ppszT[])
{
  fSlide = false;

  ppszCurr  = ppszT;
  ppszFirst = ppszT;

  strncpy(szHi, *ppszCurr, bDISPLAY);

  cwSlide = 0;
  fSlide  = true;
}


void    ShowSlide(char  szT[])
{
  fSlide = false;
  ppszCurr = ppszFirst;

  while (strcmp(*ppszCurr,"") != 0)
  {
    if (*ppszCurr == szT) break;
    ppszCurr++;
  }

  cwSlide = 0;
  fSlide  = true;
}


void    Slides_1Hz(void) {
  if (fSlide == true)
  {
    if (cwSlide == 0)
    {
      if (strcmp(*ppszCurr, "") == 0)
        ppszCurr = ppszFirst;

      strncpy(szHi, *ppszCurr, bDISPLAY);
      ppszCurr++;
    }

    if (++cwSlide > 3)
      cwSlide = 0;
  }
}
