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
#include "../serial/auto_flow.h"
#include "serial0.h"
#include "serial1.h"
#include "serial2.h"
#include "serial3.h"
#include "serial_flow.h"



volatile serial     mpSerialF[2];

uchar               mpbInBuffF[2][wINBUFF_SIZE];

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
      cwInDelayF[p] = mpwMinorInDelay[p] / 2;
      mpbInBuffF[p][ iwInBuffF[p]++ ] = b;
    }
  }
}



void    InDelaySerialFlow_Timer0(void)
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



void    RunResponseSerialFlow2(void)
{
    if (mpSerialF[0] == SER_POSTINPUT_SLAVE)
    {
      mpSerialF[0] = SER_BEGIN;

      if (!IsAutoFlowTo3()) return;
      if ((fFlow == 1) && (ibFlowPortFrom == 1)) return;

      fFlow = 1;
      ibFlowPortFrom = 0;

      cbInFlow0++;
      iwInFlow0 = iwInBuffF[0];

      memcpy(mpbOutBuff2,mpbInBuffF[0],iwInBuffF[0]);
      Query2(0xFFFF,iwInBuffF[0],1);
    }
    else if (mpSerial[2] == SER_BADLINK)
    {
      mpSerial[2] = SER_BEGIN;

      cbOutFlow0++;
      iwOutFlow0 = iwInBuff2;

      memcpy(mpbOutBuff0,mpbInBuff2,iwInBuff2);
      Answer0(iwInBuff2,SER_OUTPUT_SLAVE);
    }


    if (mpSerialF[1] == SER_POSTINPUT_SLAVE)
    {
      mpSerialF[1] = SER_BEGIN;

      if (!IsAutoFlowTo3()) return;
      if ((fFlow == 1) && (ibFlowPortFrom == 0)) return;

      fFlow = 1;
      ibFlowPortFrom = 1;

      cbInFlow1++;
      iwInFlow1 = iwInBuffF[1];

      memcpy(mpbOutBuff2,mpbInBuffF[1],iwInBuffF[1]);
      Query2(0xFFFF,iwInBuffF[1],1);
    }
    else if (mpSerial[2] == SER_BADLINK)
    {
      mpSerial[2] = SER_BEGIN;

      cbOutFlow1++;
      iwOutFlow1 = iwInBuff2;

      memcpy(mpbOutBuff1,mpbInBuff2,iwInBuff2);
      Answer1(iwInBuff2,SER_OUTPUT_SLAVE);
    }
}


void    RunResponseSerialFlow3(void)
{
    if (mpSerialF[0] == SER_POSTINPUT_SLAVE)
    {
      mpSerialF[0] = SER_BEGIN;

      if (!IsAutoFlowTo4()) return;

      fFlow = 1;
      ibFlowPortFrom = 0;

      cbInFlow0++;
      iwInFlow0 = iwInBuffF[0];

      memcpy(mpbOutBuff3,mpbInBuffF[0],iwInBuffF[0]);
      Query3(0xFFFF,iwInBuffF[0],1);
    }
    else if (mpSerial[3] == SER_BADLINK)
    {
      mpSerial[3] = SER_BEGIN;

      cbOutFlow0++;
      iwOutFlow0 = iwInBuff3;

      memcpy(mpbOutBuff0,mpbInBuff3,iwInBuff3);
      Answer0(iwInBuff3,SER_OUTPUT_SLAVE);
    }

    if (mpSerialF[1] == SER_POSTINPUT_SLAVE)
    {
      mpSerialF[1] = SER_BEGIN;

      if (!IsAutoFlowTo4()) return;

      fFlow = 1;
      ibFlowPortFrom = 1;

      cbInFlow1++;
      iwInFlow1 = iwInBuffF[1];

      memcpy(mpbOutBuff3,mpbInBuffF[1],iwInBuffF[1]);
      Query3(0xFFFF,iwInBuffF[1],1);
    }
    else if (mpSerial[3] == SER_BADLINK)
    {
      mpSerial[3] = SER_BEGIN;

      cbOutFlow1++;
      iwOutFlow1 = iwInBuff3;

      memcpy(mpbOutBuff1,mpbInBuff3,iwInBuff3);
      Answer1(iwInBuff3,SER_OUTPUT_SLAVE);
    }
}


void    RunResponseSerialFlow_All(void)
{
  RunResponseSerialFlow2();
  RunResponseSerialFlow3();
}
