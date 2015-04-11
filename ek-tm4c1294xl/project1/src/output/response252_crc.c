/*------------------------------------------------------------------------------
RESPONSE252_CRC.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../include/states.h"
#include        "../hardware/beep.h"
#include        "../serial/ports.h"
#include        "../output/response_crc.h"
#include        "../output/out_delay.h"
#include        "../output/out_realtime.h"
#include        "../output/out_flash_map.h"
#include        "../output/out_health.h"



void    Response252_CRC(void)
{
  switch (bInBuff5)
  {
    case 0: Beep(); break;

    case 1: OutDelay(); break;

    case 2: OutRealtime(); break;

    case 3: OutFlashMap(); break;

    case 4: OutHealth(); break;

    default:
      ShowTestResponse(bSTA_BADCOMMAND);
      Result(bRES_BADCOMMAND);
      break;
  }
}
