/*------------------------------------------------------------------------------
RESPONSE254_CRC,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../include/states.h"
#include "../serial/ports.h"
#include "../impulses/factors.h"
#include "response_crc.h"
#include "out_common.h"
#include "out_factors.h"
#include "response254_crc.h"



void    Response254_CRC(void)
{
  switch (bInBuff5)
  {
    case bINQ_GETTRANS_ENG: OutGetFloatOrDoubleCan(mpdbTransEng, true); break;
    case bINQ_GETTRANS_CNT: OutGetFloatOrDoubleCan(mpdbTransCnt, true); break;
    case bINQ_GETPULSE_HOU: OutGetFloatOrDoubleCan(mpdbPulseHou, true); break;
    case bINQ_GETPULSE_MNT: OutGetFloatOrDoubleCan(mpdbPulseMnt, true); break;
    case bINQ_GETCOUNT:     OutGetFloatOrDoubleCan(mpdbCount, true);    break;
    case bINQ_GETLOSSE:     OutGetFloatOrDoubleCan(mpdbLosse, true);    break;
    case bINQ_GETLEVEL:     OutGetFloatOrDoubleCan(mpdbLevel, true);    break;

    case bINQ_SETTRANS_ENG: OutSetFloatOrDoubleCan(mpdbTransEng, &flTransEng, true); break;
    case bINQ_SETTRANS_CNT: OutSetFloatOrDoubleCan(mpdbTransCnt, &flTransCnt, true); break;
    case bINQ_SETPULSE_HOU: OutSetFloatOrDoubleCan(mpdbPulseHou, &flPulseHou, true); break;
    case bINQ_SETPULSE_MNT: OutSetFloatOrDoubleCan(mpdbPulseMnt, &flPulseMnt, true); break;
    case bINQ_SETCOUNT:     OutSetFloatOrDoubleCan(mpdbCount,    &flCount, true);    break;
    case bINQ_SETLOSSE:     OutSetFloatOrDoubleCan(mpdbLosse,    &flLosse, true);    break;
    case bINQ_SETLEVEL:     OutSetFloatOrDoubleCan(mpdbLevel,    &flLevel, true);    break;

    case bINQ_GETKOEFF: OutAllFactors(true); break;

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
