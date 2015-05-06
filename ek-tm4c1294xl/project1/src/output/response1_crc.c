/*------------------------------------------------------------------------------
RESPONSE1_CRC.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_settings.h"
#include "../include/states.h"
#include "../serial/ports.h"
#include "out_common.h"
#include "out_rtc.h"
#include "out_groups.h"
#include "out_tariffs.h"
#include "out_factors.h"
#include "out_digitals.h"
#include "out_impulse.h"
#include "out_flash.h"
#include "out_transit.h"
#include "out_console.h"
#include "out_config.h"
#include "profile/out_params.h"
#include "response_crc.h"
#include "response252_crc.h"
#include "response255_crc.h"



void    Response1_CRC(void)
{
    switch (bInBuff4)
    {
      case bINQ_GETGLOBAL:
        LongResult(enGlobal);
        break;

      case bINQ_GETCURRTIME:
        OutGetCurrTimeDate();
        break;

      case bINQ_GETGROUP:
        OutGetGroup();
        break;

      case bINQ_SETGROUP:
        OutSetGroup();
        break;

      case bINQ_GETPUBLIC_TARIFFS: OutGetPublicTariffs(); break;
      case bINQ_SETPUBLIC_TARIFFS: OutSetPublicTariffs(); break;

      case bINQ_GETOLDPOWTARIFFS: OutGetOldPowTariffs(); break;
      case bINQ_SETOLDPOWTARIFFS: OutSetOldPowTariffs(); break;

      case bINQ_GETOLDENGTARIFFS: OutGetOldEngTariffs(); break;
      case bINQ_SETOLDENGTARIFFS: OutSetOldEngTariffs(); break;

      case bINQ_GETOLDPUBTARIFFS: OutGetOldPubTariffs(); break;
      case bINQ_SETOLDPUBTARIFFS: OutSetOldPubTariffs(); break;

      case bINQ_GETNEWPOWTARIFFS: OutGetNewPowTariffs(); break;
      case bINQ_SETNEWPOWTARIFFS: OutSetNewPowTariffs(); break;

      case bINQ_GETNEWENGTARIFFS: OutGetNewEngTariffs(); break;
      case bINQ_SETNEWENGTARIFFS: OutSetNewEngTariffs(); break;

      case bINQ_GETNEWPUBTARIFFS: OutGetNewPubTariffs(); break;
      case bINQ_SETNEWPUBTARIFFS: OutSetNewPubTariffs(); break;

      case bINQ_GETTRANS_ENG: OutFloatCan(mpreTransEng); break;
      case bINQ_GETTRANS_CNT: OutFloatCan(mpreTransCnt); break;
      case bINQ_GETPULSE_HOU: OutFloatCan(mprePulseHou); break;
      case bINQ_GETPULSE_MNT: OutFloatCan(mprePulseMnt); break;
      case bINQ_GETCOUNT: OutFloatCan(mpreCount); break;
      case bINQ_GETLOSSE: OutFloatCan(mpreLosse); break;
      case bINQ_GETLEVEL: OutFloatCan(mpreLevelDiv); break;

      case bINQ_GETKOEFF: OutAllFactors(); break;

      case bINQ_GETVALUE_ENGHOU: OutFloatCan_GlobalWork(mpreValueEngHou); break;
      case bINQ_GETVALUE_CNTHOU: OutFloatCan_GlobalWork(mpreValueCntHou); break;
      case bINQ_GETVALUE_ENGMNT: OutFloatCan_GlobalWork(mpreValueEngMnt); break;
      case bINQ_GETVALUE_CNTMNT: OutFloatCan_GlobalWork(mpreValueCntMnt); break;

      case bINQ_GETIMPCANDAY_ALL: OutImpDayCan(); break;
      case bINQ_GETIMPCANMON_ALL: OutImpMonCan(); break;

      case bINQ_GETDIGITAL: OutGetDigital(); break;
      case bINQ_SETDIGITAL: OutSetDigital(); break;

      case bINQ_GETPARAMS_100: OutGetParams100(); break;
      case bINQ_GETPARAM: OutGetParams(); break;
      case bINQ_SETPARAM: OutSetParam(); break;
      case bINQ_GETPARAM_DIV: OutGetParamDiv(); break;
      case bINQ_SETPARAM_DIV: OutSetParamDiv(); break;
      case bINQ_GETPARAM_CURR: OutGetParamCurr(); break;
      case bINQ_GETPARAM_BUFF: OutGetParamBuff(); break;
      case bINQ_GETPARAM_FULL: OutGetParamFull(); break;
      case bINQ_RESETDIVIDERS: OutGetParamDivs(); break;
      case bINQ_GETPARAMS_ALL: OutGetParamsAll(); break;

      case bINQ_GETTARIFFSDAY: OutGetTariffsDay(); break;

      case bINQ_TRANSIT_EXECUTE1: SafeTransitExecute1(); break;
      case bINQ_TRANSIT_EXECUTE2: SafeTransitExecute2(); break;
#ifndef SKIP_K
      case bINQ_TRANSIT_EXECUTE3: SafeTransitExecute3(); break;
#endif
      case bINQ_TRANSIT_EXECUTE4: SafeTransitExecute4(); break;

      case bINQ_GETFLASHPAGE:
        OutFlashPage();
        break;

      case bINQ_SETKEY: OutSetKey(); break;
      case bINQ_GETDISPLAY: OutGetDisplay(); break;

      case bINQ_GETCONFIG:
        OutGetConfig();
        break;

      case bINQ_RESPONSE_252:
      	Response252_CRC();
        break;

      case bINQ_RESPONSE_255:
      	Response255_CRC();
        break;

      default:
        ShowTestResponse(bSTA_BADCOMMAND);
        Result(bRES_BADCOMMAND);
        break;
  }
}
