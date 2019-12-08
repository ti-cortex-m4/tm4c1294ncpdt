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



void    RunResponseSerialFlow2(void)
{
  if (fFlow == 0) return;
  if ((ibFlowPortTo != 2+1) && (!IsAutoFlowTo3())) return;

  if (ibFlowPortFrom == 0)
  {
    if (mpSerial[0] == SER_POSTINPUT_SLAVE)
    {
      mpSerial[0] = SER_BEGIN;

      cbInFlow0++;
      iwInFlow0 = iwInBuff0;

      memcpy(mpbOutBuff2,mpbInBuff0,iwInBuff0);
      Query2(0xFFFF,iwInBuff0,1);
    }
    else if (mpSerial[2] == SER_BADLINK)
    {
      mpSerial[2] = SER_BEGIN;

      cbOutFlow0++;
      iwOutFlow0 = iwInBuff2;

      memcpy(mpbOutBuff0,mpbInBuff2,iwInBuff2);
      Answer0(iwInBuff2,SER_OUTPUT_SLAVE);
    }
  }

  if (ibFlowPortFrom == 1)
  {
    if (mpSerial[1] == SER_POSTINPUT_SLAVE)
    {
      mpSerial[1] = SER_BEGIN;

      cbInFlow1++;
      iwInFlow1 = iwInBuff1;

      memcpy(mpbOutBuff2,mpbInBuff1,iwInBuff1);
      Query2(0xFFFF,iwInBuff1,1);
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
}


void    RunResponseSerialFlow3(void)
{
  if (fFlow == 0) return;
  if ((ibFlowPortTo != 3+1) && (!IsAutoFlowTo4())) return;

  if (ibFlowPortFrom == 0)
  {
    if (mpSerial[0] == SER_POSTINPUT_SLAVE)
    {
      mpSerial[0] = SER_BEGIN;

      cbInFlow0++;
      iwInFlow0 = iwInBuff0;

      memcpy(mpbOutBuff3,mpbInBuff0,iwInBuff0);
      Query3(0xFFFF,iwInBuff0,1);
    }
    else if (mpSerial[3] == SER_BADLINK)
    {
      mpSerial[3] = SER_BEGIN;

      cbOutFlow0++;
      iwOutFlow0 = iwInBuff3;

      memcpy(mpbOutBuff0,mpbInBuff3,iwInBuff3);
      Answer0(iwInBuff3,SER_OUTPUT_SLAVE);
    }
  }

  if (ibFlowPortFrom == 1)
  {
    if (mpSerial[1] == SER_POSTINPUT_SLAVE)
    {
      mpSerial[1] = SER_BEGIN;

      cbInFlow1++;
      iwInFlow1 = iwInBuff1;

      memcpy(mpbOutBuff3,mpbInBuff1,iwInBuff1);
      Query3(0xFFFF,iwInBuff1,1);
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
}


void    RunResponseSerialFlow_All(void)
{
  RunResponseSerialFlow2();
  RunResponseSerialFlow3();
}
