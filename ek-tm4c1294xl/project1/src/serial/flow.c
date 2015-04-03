/*------------------------------------------------------------------------------
FLOW.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_serial0.h"
#include        "../memory/mem_serial1.h"
#include        "../memory/mem_serial2.h"
#include        "../memory/mem_serial3.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_flow.h"
#include        "../isr/serial0.h"
#include        "../isr/serial1.h"
#include        "../isr/serial2.h"
#include        "../isr/serial3.h"
#include        "../serial/ports.h"
#include        "../flash/files.h"
#include        "flow.h"



file const              flFlowPortFrom = {FLS_FLOW_PORT_FROM, &ibPortFrom, sizeof(uchar)};
file const              flFlowPortTo = {FLS_FLOW_PORT_TO, &ibPortTo, sizeof(uchar)};



void    InitFlow(void)
{
  fFlow = 0;
  cbFlowDelay = 0;

  LoadFile(&flFlowPortFrom);
  LoadFile(&flFlowPortTo);

  if ((ibPortTo != 2+1) && (ibPortTo != 3+1))
  {
    ibPortTo = 2+1;
    SaveFile(&flFlowPortTo);
  }
}


void    ResetFlow(void)
{
  ibPortFrom = 0;
  SaveFile(&flFlowPortFrom);

  ibPortTo = 2+1;
  SaveFile(&flFlowPortTo);
}



void    RepeatFlow(void) {
}



void    RunFlow(void)
{
//  if (bProgram == bGET_ANALYSIS2)
//  {
//    sprintf(szHi,"Порт %bu: лимит   ",ibPortFrom+1);
//    Clear();
//    NoShowTime(0);
//  }
//
//  cbFlowDelay = cbMaxFlowDelay;
//  fFlow = 1;
}


void    RunFlow0(void)
{
  ibPortFrom = 0;
  RunFlow();
}


void    RunFlow1(void)
{
  ibPortFrom = 1;
  RunFlow();
}


uchar   IsFlow0(void) {
  return(0);
}


uchar   IsFlow1(void) {
  return(0);
}


uchar   IsFlow2(void) {
  return(0);
}


uchar   IsFlow3(void) {
  return(0);
}



void    CloseFlow(void)
{
//  if (fFlow == 1)
//  {
//    cbFlowDelay = 0;
//    fFlow = 0;
//
//    NextPause(); // внимание !
//  }
}



void    RunResponseFlow2(void)
{
  if ((fFlow == 0) || (ibPortTo != 2+1)) return;

  if (ibPortFrom == 0)
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

  if (ibPortFrom == 1)
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


void    RunResponseFlow3(void)
{
  if ((fFlow == 0) || (ibPortTo != 3+1)) return;

  if (ibPortFrom == 0)
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

  if (ibPortFrom == 1)
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


void    RunResponseFlow_All(void)
{
  RunResponseFlow2();
  RunResponseFlow3();
}
