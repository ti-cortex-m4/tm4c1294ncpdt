/*------------------------------------------------------------------------------
serial_flow.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "serial_flow.h"



volatile serial     mpSerialF[2];

volatile uchar      mpbInBuffF[2][wINBUFF_SIZE];

volatile uint       iwInBuffF[2];

volatile uint       cwInDelayF[2];



void    InitSerialFlow(void)
{
  uchar i;
  for (i=0; i<2; i++)
  {
    mpSerialF[i] = SER_BEGIN;
  }
}


void    InitSerialFlow(uchar  ibPrt, uchar  b)
{
  if (mpSerial[0] == SER_BEGIN)
  {
    cwInDelay0 = mpwMinorInDelay[0];

    mpSerial[0] = SER_INPUT_SLAVE;
    iwInBuff0 = 0;
  }

  if (mpSerial[0] == SER_INPUT_SLAVE)
  {
    if (iwInBuff0 >= wINBUFF_SIZE)
    {
      InputMode0();
      mpSerial[0] = SER_BEGIN;
    }
    else
    {
      cwInDelay0 = mpwMinorInDelay[0];
      mpbInBuff0[ iwInBuff0++ ] = bT;
    }
  }
}
