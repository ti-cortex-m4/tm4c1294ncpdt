/*------------------------------------------------------------------------------
RESPONSE253_CRC,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../include/states.h"
#include "../serial/ports.h"
#include "../digitals/extended/extended_4_out.h"
#include "../digitals/extended/extended_4t_out.h"
#include "../digitals/extended/extended_5_out.h"
#include "../digitals/extended/extended_6_out.h"
#include "../digitals/extended/extended_7_out.h"
#include "response_crc.h"
#include "out_energy.h"
#include "response253_crc.h"



void    Response253_CRC(void)
{
  switch (bInBuff5)
  {
    case bINQ_GETENGGRPDAY_ALL: OutEngDayGrpExt(true); break;
    case bINQ_GETENGGRPMON_ALL: OutEngMonGrpExt(true); break;

    case bEXT_GETEXTENDED40: OutExtended40(true); break;
    case bEXT_GETEXTENDED44: OutExtended44(true); break;
    case bEXT_GETEXTENDED41: OutExtended41(true); break;
    case bEXT_GETEXTENDED42: OutExtended42(true); break;

    case bEXT_GET_EXTENDED_4T: OutExtended4T(true); break;

    case bEXT_GETEXTENDED50: OutExtended50(true); break;
    case bEXT_GETEXTENDED51: OutExtended51(true); break;

    case bEXT_GETEXTENDED6: OutExtended6(true); break;

    case bEXT_GETEXTENDED7: OutExtended7(true); break;

    default:
      ShowTestResponse(bSTA_BADCOMMAND);
      Result(bRES_BADCOMMAND);
      break;
  }
}
