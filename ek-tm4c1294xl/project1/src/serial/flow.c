/*------------------------------------------------------------------------------
FLOW.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_flow.h"
#include        "flow.h"



file const              flFlowPortFrom = {FLS_FLOW_PORT_FROM, &ibPortFrom, sizeof(uchar)};
file const              flFlowPortTo = {FLS_FLOW_PORT_TO, &ibPortTo, sizeof(uchar)};



void    InitFlow(void)
{
  LoadFile(&flFlowPortFrom);
  LoadFile(&flFlowPortTo);
}


void    ResetFlow(void)
{
  ibPortFrom = 0;
  SavedFile(&flFlowPortFrom);

  ibPortTo = 2;
  SavedFile(&flFlowPortTo);
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
