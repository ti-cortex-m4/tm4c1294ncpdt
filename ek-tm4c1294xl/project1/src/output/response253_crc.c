/*------------------------------------------------------------------------------
RESPONSE253_CRC,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_factors.h"
#include "../include/states.h"
#include "../serial/ports.h"
#include "../digitals/extended/extended_1_out.h"
#include "../digitals/extended/extended_4_out.h"
#include "../digitals/extended/extended_4t_out.h"
#include "../digitals/extended/extended_5_out.h"
#include "../digitals/extended/extended_6_out.h"
#include "../digitals/extended/extended_7_out.h"
#include "response_crc.h"
#include "out_energy.h"
#include "out_common.h"
#include "out_records.h"
#include "response253_crc.h"



void    Response253_CRC(void)
{
  switch (bInBuff5)
  {
    case bINQ_GETTRANS_ENG: OutFloatOrDoubleCanExt(mpdbTransEng, true); break;
    case bINQ_GETTRANS_CNT: OutFloatOrDoubleCanExt(mpdbTransCnt, true); break;
    case bINQ_GETPULSE_HOU: OutFloatOrDoubleCanExt(mpdbPulseHou, true); break;
    case bINQ_GETPULSE_MNT: OutFloatOrDoubleCanExt(mpdbPulseMnt, true); break;
    case bINQ_GETCOUNT:     OutFloatOrDoubleCanExt(mpdbCount, true);    break;
    case bINQ_GETLOSSE:     OutFloatOrDoubleCanExt(mpdbLosse, true);    break;

    case bEXT_GET_ESC_S_VALUE: OutEscS_Value(true); break;
    case bEXT_GET_ESC_V_VALUE: OutEscV_Value(true); break;

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

    case bEXT_GETRECORD:        OutRecordExt();        break;
    case bEXT_GETRECORDSBLOCK:  OutRecordsBlockExt();  break;
    case bEXT_GETRECORDSBLOCK2: OutRecordsBlockExt2(); break;

    default:
      ShowTestResponse(bSTA_BADCOMMAND);
      Result(bRES_BADCOMMAND);
      break;
  }
}
