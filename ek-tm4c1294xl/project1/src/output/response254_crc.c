/*------------------------------------------------------------------------------
RESPONSE254_CRC.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../include/states.h"
#include        "../serial/ports.h"
#include        "../output/response_crc.h"
#include        "../output/out_realtime.h"
#include        "../output/out_dataflash.h"
#include        "../output/out_health.h"



void    Response254_CRC(void)
{
  switch (bInBuff5)
  {
    case 0: OutRealtime(); break;

    case 1: OutDataFlashMap(); break;

    case 2: OutHealth(); break;

    default:
      ShowTestResponse(bSTA_BADCOMMAND);
      Result(bRES_BADCOMMAND);
      break;
  }
}
