/*------------------------------------------------------------------------------
RESPONSE1_CRC.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_factors.h"
#include        "../memory/mem_settings.h"
#include        "../include/states.h"
#include        "../serial/ports.h"
#include        "out_common.h"
#include        "out_rtc.h"
#include        "out_groups.h"
#include        "out_tariffs.h"
#include        "out_digitals.h"
#include        "out_flash.h"
#include        "out_transit.h"
#include        "out_console.h"
#include        "out_config.h"
#include        "profile/out_params.h"
#include        "response_crc.h"
#include        "response252_crc.h"
#include        "response255_crc.h"



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

      case bINQ_GETTRANS_ENG: OutReal(mpreTransEng, bCANALS); break;
      case bINQ_GETTRANS_CNT: OutReal(mpreTransCnt, bCANALS); break;
      case bINQ_GETPULSE_HOU: OutReal(mprePulseHou, bCANALS); break;
      case bINQ_GETPULSE_MNT: OutReal(mprePulseMnt, bCANALS); break;
      case bINQ_GETCOUNT: OutReal(mpreCount, bCANALS); break;
      case bINQ_GETLOSSE: OutReal(mpreLosse, bCANALS); break;
      case bINQ_GETLEVEL: OutReal(mpreLevelDiv, bCANALS); break;
/*
      case bINQ_GETKOEFF:
        if (bInBuff5 < bCANALS)
        {
          InitPushCRC();

          reBuffA = *PGetCanReal(mpreTransEng, bInBuff5);
          PushReal();
          reBuffA = *PGetCanReal(mpreTransCnt, bInBuff5);
          PushReal();
          reBuffA = *PGetCanReal(mprePulseHou, bInBuff5);
          PushReal();
          reBuffA = *PGetCanReal(mprePulseMnt, bInBuff5);
          PushReal();

          Output(sizeof(real)*4);
        }
        else Result(bRES_BADADDRESS);
        break;

      case bINQ_GETVALUE_ENGHOU:
        if (enGlobal != GLB_PROGRAM)
          Common(mpreValueEngHou, sizeof(real)*bCANALS);
        else
          Result(bRES_NEEDWORK);
        break;

      case bINQ_GETVALUE_CNTHOU:
        if (enGlobal != GLB_PROGRAM)
          Common(mpreValueCntHou, sizeof(real)*bCANALS);
        else
          Result(bRES_NEEDWORK);
        break;

      case bINQ_GETVALUE_ENGMNT:
        if (enGlobal != GLB_PROGRAM)
          Common(mpreValueEngMnt, sizeof(real)*bCANALS);
        else
          Result(bRES_NEEDWORK);
        break;

      case bINQ_GETVALUE_CNTMNT:
        if (enGlobal != GLB_PROGRAM)
          Common(mpreValueCntMnt, sizeof(real)*bCANALS);
        else
          Result(bRES_NEEDWORK);
        break;
*/
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

      case bINQ_SETKEY:
        OutSetKey();
        break;

      case bINQ_GETDISPLAY:
        OutGetDisplay();
        break;

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
