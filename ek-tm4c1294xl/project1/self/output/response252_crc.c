/*------------------------------------------------------------------------------
RESPONSE252_CRC,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_energy_spec.h"
#include "../hardware/beep.h"
#include "../serial/ports.h"
#include "../output/response_crc.h"
#include "../output/out_delay.h"
#include "../output/out_realtime.h"
#include "../output/out_flash_stack.h"
#include "../output/out_nvram_stack.h"
#include "../output/out_health.h"
#include "../output/out_tariffs.h"
#include "../output/out_defects1.h"
#include "../output/out_nvram.h"
#include "../output/out_flash.h"
#include "../kernel/asserts.h"
#include "../output/profile/out_profile_link.h"
#include "../serial/slave_modem.h"
#include "../realtime/throughput.h"
#include "../realtime/period30.h"
#include "../realtime/realtime_indices.h"
#include "../output/out_digitals.h"
#include "../digitals/review/review_out.h"
#include "../digitals/review/review_buff.h"
#include "../sensors/sensor35/timeout35.h"
#include "../sensors/sensor35/log35.h"
#include "../sensors/sensor40/log40.h"
#include "../output/out_echo.h"



void    Response252_CRC(void)
{
  switch (bInBuff5)
  {
    case 0: Beep(); break;

    case 1: OutDelay(); break;

    case 2: OutRealtime1(); break;

    case 3: OutFlashStack(); break;
    case 7: OutNvramStack(); break;

    case 4: OutHealth(); break;

    case 5: OutGetAllPowTariffs(); break;
    case 6: OutGetAllEngTariffs(); break;

    case 8: OutDefectsDay(); break;
    case 9: OutDefectsMon(); break;

    case 10: OutNvram(); break;
//    case 11: OutFlash(); break;

    case 12: OutNvramCounters(); break;
    case 13: ResetNvramCounters(); break;

    case 14: OutFlashCounters(); break;
    case 15: ResetFlashCounters(); break;

    case 16: OutAsserts(); break;

    case 17: OutGetProfileLinkWrn(); break;
    case 18: OutGetProfileLinkErr(); break;
    case 19: OutResetProfileLinkWrn(); break;
    case 20: OutResetProfileLinkErr(); break;

    case 21: OutSlaveModem(); break;

    case 22: OutThroughput(); break;
    case 23: OutPeriod30(); break;

    case 24: OutKeysExt(); break;

    case 25: OutReview(); break;
    case 26: OutReviewBuff(); break;

    case 27: OutRealtime2(); break;

    case 28: OutEchoNtoN(); break;
    case 29: OutEchoNto1(); break;
    case 30: OutEcho1toN(); break;

    case 31: OutTimeoutHistogramAll35(); break;
    case 32: OutResetTimeoutHistogramAll35(); break;
    case 33: OutResetTimeoutHistogramDay35(); break;

    case 34: OutLog35(); break;
    case 35: OutCounter35(); break;
    case 36: OutResetLog35(); break;

    case 37: OutLog40(); break;
    case 38: OutCounter40(); break;
    case 39: OutResetLog40(); break;

    case 40: OutRealtimeIndices(); break;

    default:
      ShowResponseCRC(bSTA_BADCOMMAND);
      Result(bRES_BADCOMMAND);
      break;
  }
}
