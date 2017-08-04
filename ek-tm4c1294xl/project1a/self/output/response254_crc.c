/*------------------------------------------------------------------------------
RESPONSE254_CRC,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
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

    case bINQ_SETTRANS_ENG: OutSetFloatOrDoubleCan(mpdbTransEng, &chTransEng, true); break;
    case bINQ_SETTRANS_CNT: OutSetFloatOrDoubleCan(mpdbTransCnt, &chTransCnt, true); break;
    case bINQ_SETPULSE_HOU: OutSetFloatOrDoubleCan(mpdbPulseHou, &chPulseHou, true); break;
    case bINQ_SETPULSE_MNT: OutSetFloatOrDoubleCan(mpdbPulseMnt, &chPulseMnt, true); break;
    case bINQ_SETCOUNT:     OutSetFloatOrDoubleCan(mpdbCount,    &chCount, true);    break;
    case bINQ_SETLOSSE:     OutSetFloatOrDoubleCan(mpdbLosse,    &chLosse, true);    break;
    case bINQ_SETLEVEL:     OutSetFloatOrDoubleCan(mpdbLevel,    &chLevel, true);    break;

    case bINQ_GETKOEFF: OutAllFactors(true); break;

    case bINQ_GETVALUE_ENGHOU: OutGetFloatOrDoubleCan_GlobalWork(mpdbValueEngHou, true); break;
    case bINQ_GETVALUE_CNTHOU: OutGetFloatOrDoubleCan_GlobalWork(mpdbValueCntHou, true); break;
    case bINQ_GETVALUE_ENGMNT: OutGetFloatOrDoubleCan_GlobalWork(mpdbValueEngMnt, true); break;
    case bINQ_GETVALUE_CNTMNT: OutGetFloatOrDoubleCan_GlobalWork(mpdbValueCntMnt, true); break;

    default:
      ShowResponseCRC(bSTA_BADCOMMAND);
      Result(bRES_BADCOMMAND);
      break;
  }
}
