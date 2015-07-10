/*------------------------------------------------------------------------------
RESPONSE252_CRC,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_energy_spec.h"
#include "../include/states.h"
#include "../hardware/beep.h"
#include "../serial/ports.h"
#include "../output/response_crc.h"
#include "../output/out_delay.h"
#include "../output/out_realtime.h"
#include "../output/out_flash_stack.h"
#include "../output/out_nvram_stack.h"
#include "../output/out_health.h"
#include "../output/out_tariffs.h"
#include "../output/out_defects.h"
#include "../output/out_nvram.h"
#include "../output/out_flash.h"



void    Response252_CRC(void)
{
  switch (bInBuff5)
  {
    case 0: Beep(); break;

    case 1: OutDelay(); break;

    case 2: OutRealtime(); break;

    case 3: OutFlashStack(); break;
    case 7: OutNvramStack(); break;

    case 4: OutHealth(); break;

    case 5: OutGetAllPowTariffs(); break;
    case 6: OutGetAllEngTariffs(); break;

    case 8: OutDefectsDay(); break;
    case 9: OutDefectsMon(); break;

    case 10: OutNvram(); break;
    case 11: OutNvramCounters(); break;
    case 12: OutFlashCounters(); break;

    default:
      ShowTestResponse(bSTA_BADCOMMAND);
      Result(bRES_BADCOMMAND);
      break;
  }
}
