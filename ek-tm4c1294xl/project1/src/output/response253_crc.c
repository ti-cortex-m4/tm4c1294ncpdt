/*------------------------------------------------------------------------------
RESPONSE253_CRC,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../include/states.h"
#include "../serial/ports.h"
#include "../output/response_crc.h"
#include "out_energy.h"
#include "response253_crc.h"



void    Response253_CRC(void)
{
  switch (bInBuff5)
  {
    case bINQ_GETENGGRPDAY_ALL: OutEngDayGrpExt(true); break;
    case bINQ_GETENGGRPMON_ALL: OutEngMonGrpExt(true); break;

    default:
      ShowTestResponse(bSTA_BADCOMMAND);
      Result(bRES_BADCOMMAND);
      break;
  }
}
