/*------------------------------------------------------------------------------
serial_flow.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "serial_flow.h"



volatile serial     mpSerialF[2];

volatile uchar      mpbInBuffF[2][wINBUFF_SIZE];

volatile uint       iwInBuffF[2];

volatile uint       cwInDelayF[2];



void    InitSerialFlow(void)
{
  uchar p;
  for (p=0; p<2; p++)
  {
    mpSerialF[p] = SER_BEGIN;
  }
}



void    InSerialFlow(uchar  p, uchar  b)
{
  if (mpSerialF[p] == SER_BEGIN)
  {
    mpSerialF[p] = SER_INPUT_SLAVE;
    iwInBuffF[p] = 0;
  }

  if (mpSerialF[p] == SER_INPUT_SLAVE)
  {
    if (iwInBuffF[p] >= wINBUFF_SIZE)
    {
      mpSerialF[p] = SER_BEGIN;
    }
    else
    {
      cwInDelayF[p] = mpwMinorInDelay[p];
      mpbInBuffF[p][ iwInBuffF[p]++ ] = b;
    }
  }
}



void    InDelay_SerialFlow_Timer0(void)
{
  uchar p;
  for (p=0; p<2; p++)
  {
    if (mpSerialF[p] == SER_INPUT_SLAVE)
    {
      if (cwInDelayF[p] == 0)
        mpSerialF[p] = SER_POSTINPUT_SLAVE;
      else
        cwInDelayF[p]--;
    }
  }
}
