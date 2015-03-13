/*------------------------------------------------------------------------------
SENSORS.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../digitals/digitals.h"



ulong   GetMajorDelay(uchar  ibPort) {
  return (ulong)1000*mpwMajorInDelay[ibPort]/wFREQUENCY_T0;
}


ulong   GetMinorDelay(uchar  ibPort) {
  return (ulong)1000*mpwMinorInDelay[ibPort]/wFREQUENCY_T0;
}



bool    IsPulseCanal(uchar  ibCan)
{
  return (ibCan < 16) && (GetDigitalDevice(ibCan) == 0);
}



void    InitWaitAnswer(void)
{
  cbWaitAnswerPrev = cbWaitAnswer = 0;
}


void    ShowWaitAnswer(bool  fShow)
{
  if ((fShow == 1) && (cbWaitAnswerPrev != cbWaitAnswer))
  {
    sprintf(szLo+13,"%3bu",cbWaitAnswer);
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

