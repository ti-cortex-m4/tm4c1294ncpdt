/*------------------------------------------------------------------------------
OUT_FLOW,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "../serial/flow.h"
#include "../digitals/wait_query.h"
#include "out_flow.h"



void    OutFlow(void)
{
  if (cbWaitQuery != 0)
    Result(bRES_BADMODE);
  else if (ibPort == 0)
  {
    RunFlow0();
    Result(bRES_OK);
  }
  else if (ibPort == 1)
  {
    RunFlow1();
    Result(bRES_OK);
  }
}
