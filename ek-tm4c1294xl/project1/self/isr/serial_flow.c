/*------------------------------------------------------------------------------
serial_flow.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_serial0.h"
#include "../memory/mem_serial1.h"
#include "../memory/mem_serial2.h"
#include "../memory/mem_serial3.h"
#include "../memory/mem_flow.h"
#include "../serial/ports.h"
#include "../serial/flow.h"
#include "../serial/auto_flow.h"
#include "serial0.h"
#include "serial1.h"
#include "serial2.h"
#include "serial3.h"
#include "serial_flow.h"



volatile serial     mpZerial[2];

uchar               mpbInBuffF[2][wINBUFF_SIZE];

volatile uint       iwInBuffF[2];

volatile uint       cwInDelayF[2];



void    InitSerialFlow(void)
{
  uchar p;
  for (p=0; p<2; p++)
  {
    mpZerial[p] = SER_BEGIN;
  }
}



void    InSerialFlow(uchar  p, uchar  b)
{
  if (mpZerial[p] == SER_BEGIN)
  {
    mpZerial[p] = SER_INPUT_SLAVE;
    iwInBuffF[p] = 0;
  }

  if (mpZerial[p] == SER_INPUT_SLAVE)
  {
    if (iwInBuffF[p] >= wINBUFF_SIZE)
    {
      mpZerial[p] = SER_BEGIN;
    }
    else
    {
      cwInDelayF[p] = mpwMinorInDelay[p] * 10;
      mpbInBuffF[p][ iwInBuffF[p]++ ] = b;
    }
  }
}


void    StopSerialFlow(uchar  p)
{
  mpZerial[p] = SER_BEGIN;
}


void    InDelaySerialFlow_Timer0(void)
{
  uchar p;
  for (p=0; p<2; p++)
  {
    if (mpZerial[p] == SER_INPUT_SLAVE)
    {
      if (cwInDelayF[p] == 0)
        mpZerial[p] = SER_POSTINPUT_SLAVE;
      else
        cwInDelayF[p]--;
    }
  }
}



void    RunResponseSerialFlow2(void)
{
  if (mpZerial[0] == SER_POSTINPUT_SLAVE)
  {
    mpZerial[0] = SER_BEGIN;

    if (!IsAutoFlowTo3()) return;
    if ((fFlow == 1) && (ibFlowPortFrom == 1)) return;

    ibFlowPortTo = 2+1;
    RunFlow0();
  }


  if (mpZerial[1] == SER_POSTINPUT_SLAVE)
  {
    mpZerial[1] = SER_BEGIN;

    if (!IsAutoFlowTo3()) return;
    if ((fFlow == 1) && (ibFlowPortFrom == 0)) return;

    ibFlowPortTo = 2+1;
    RunFlow1();
  }
}


void    RunResponseSerialFlow3(void)
{
  if (mpZerial[0] == SER_POSTINPUT_SLAVE)
  {
    mpZerial[0] = SER_BEGIN;

    if (!IsAutoFlowTo4()) return;
    if ((fFlow == 1) && (ibFlowPortFrom == 1)) return;

    ibFlowPortTo = 3+1;
    RunFlow0();
  }

  if (mpZerial[1] == SER_POSTINPUT_SLAVE)
  {
    mpZerial[1] = SER_BEGIN;

    if (!IsAutoFlowTo4()) return;
    if ((fFlow == 1) && (ibFlowPortFrom == 0)) return;

    ibFlowPortTo = 3+1;
    RunFlow1();
  }
}


void    RunResponseSerialFlow_All(void)
{
  RunResponseSerialFlow2();
  RunResponseSerialFlow3();
}
