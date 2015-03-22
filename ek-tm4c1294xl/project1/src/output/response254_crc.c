/*------------------------------------------------------------------------------
RESPONSE254_CRC.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../include/states.h"
#include        "../serial/ports.h"
#include        "../output/response_crc.h"
#include        "../output/out_delay.h"
#include        "../output/out_realtime.h"
#include        "../output/out_dataflash.h"
#include        "../output/out_health.h"



void    Response254_CRC(void)
{
  switch (bInBuff5)
  {
    case 0: OutDelay(); break;

    case 1: OutRealtime(); break;

    case 2: OutDataFlashMap(); break;

    case 3: OutHealth(); break;

    default:
      ShowTestResponse(bSTA_BADCOMMAND);
      Result(bRES_BADCOMMAND);
      break;
  }
}
