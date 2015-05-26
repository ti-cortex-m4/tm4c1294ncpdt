/*------------------------------------------------------------------------------
RESPONSE254_CRC,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_factors.h"
#include "../include/states.h"
#include "../serial/ports.h"
#include "../output/response_crc.h"
#include "../output/out_common.h"
#include "response254_crc.h"



void    Response254_CRC(void)
{
  switch (bInBuff5)
  {
    case bINQ_GETVALUE_ENGHOU: OutGetFloatOrDoubleCan_GlobalWork(mpdbValueEngHou, true); break;
    case bINQ_GETVALUE_CNTHOU: OutGetFloatOrDoubleCan_GlobalWork(mpdbValueCntHou, true); break;
    case bINQ_GETVALUE_ENGMNT: OutGetFloatOrDoubleCan_GlobalWork(mpdbValueEngMnt, true); break;
    case bINQ_GETVALUE_CNTMNT: OutGetFloatOrDoubleCan_GlobalWork(mpdbValueCntMnt, true); break;

    default:
      ShowTestResponse(bSTA_BADCOMMAND);
      Result(bRES_BADCOMMAND);
      break;
  }
}
