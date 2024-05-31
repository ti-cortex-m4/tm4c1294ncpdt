/*------------------------------------------------------------------------------
RESPONSE0_CRC,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../realtime/realtime.h"
#include "../serial/ports.h"
#include "../impulses/factors.h"
#include "../digitals/dsbl_answer.h"
#include "out_common.h"
#include "out_rtc.h"
#include "out_correct.h"
#include "out_groups.h"
#include "out_tariffs.h"
#include "out_factors.h"
#include "out_digitals.h"
#include "out_impulse.h"
#include "out_cnt.h"
#include "out_minute3.h"
#include "out_minute30.h"
#include "out_minute30_48.h"
#include "out_energy.h"
#include "out_max_power.h"
#include "out_flash.h"
#include "out_transit.h"
#include "out_console.h"
#include "out_config.h"
#include "out_params.h"
#include "out_flow.h"
#include "out_test_time.h"
#include "response_crc.h"
#include "response252_crc.h"
#include "response253_crc.h"
#include "response254_crc.h"
#include "response255_crc.h"
#include "response0_crc.h"



void    Response0_CRC(void)
{
    switch (bInBuff4)
    {
      case bINQ_GETGLOBAL: LongResult(enGlobal); break;

      case bINQ_GETCURRTIME: OutGetCurrTimeDate(); break;
      case bINQ_GETLOGICAL: LongResult(bLogical); break;
      case bINQ_GETPRIVATE: Common(&wPrivate, sizeof(uint)); break;

      case bINQ_GETGROUP: OutGetGroup(); break;
      case bINQ_SETGROUP: OutSetGroup(); break;

      case bINQ_CORRECT1: OutCorrect1(); break;
      case bINQ_CORRECT2: OutCorrect2(); break;
      case bINQ_CORRECT3: OutCorrect3(); break;
      case bINQ_CORRECT4: OutCorrect4(); break;

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

      case bINQ_GETTRANS_ENG: OutGetFloatOrDoubleCan(mpdbTransEng, false); break;
      case bINQ_GETTRANS_CNT: OutGetFloatOrDoubleCan(mpdbTransCnt, false); break;
      case bINQ_GETPULSE_HOU: OutGetFloatOrDoubleCan(mpdbPulseHou, false); break;
      case bINQ_GETPULSE_MNT: OutGetFloatOrDoubleCan(mpdbPulseMnt, false); break;
      case bINQ_GETCOUNT:     OutGetFloatOrDoubleCan(mpdbCount, false);    break;
      case bINQ_GETLOSSE:     OutGetFloatOrDoubleCan(mpdbLosse, false);    break;
      case bINQ_GETLEVEL:     OutGetFloatOrDoubleCan(mpdbLevel, false);    break;

      case bINQ_SETTRANS_ENG: OutSetFloatOrDoubleCan(mpdbTransEng, &chTransEng, false); break;
      case bINQ_SETTRANS_CNT: OutSetFloatOrDoubleCan(mpdbTransCnt, &chTransCnt, false); break;
      case bINQ_SETPULSE_HOU: OutSetFloatOrDoubleCan(mpdbPulseHou, &chPulseHou, false); break;
      case bINQ_SETPULSE_MNT: OutSetFloatOrDoubleCan(mpdbPulseMnt, &chPulseMnt, false); break;
      case bINQ_SETCOUNT:     OutSetFloatOrDoubleCan(mpdbCount,    &chCount, false);    break;
      case bINQ_SETLOSSE:     OutSetFloatOrDoubleCan(mpdbLosse,    &chLosse, false);    break;
      case bINQ_SETLEVEL:     OutSetFloatOrDoubleCan(mpdbLevel,    &chLevel, false);    break;

      case bINQ_GETKOEFF: OutAllFactors(false); break;

      case bINQ_GETVALUE_ENGHOU: OutGetFloatOrDoubleCan_GlobalWork(mpdbValueEngHou, false); break;
      case bINQ_GETVALUE_CNTHOU: OutGetFloatOrDoubleCan_GlobalWork(mpdbValueCntHou, false); break;
      case bINQ_GETVALUE_ENGMNT: OutGetFloatOrDoubleCan_GlobalWork(mpdbValueEngMnt, false); break;
      case bINQ_GETVALUE_CNTMNT: OutGetFloatOrDoubleCan_GlobalWork(mpdbValueCntMnt, false); break;

      case bINQ_GETCNTCANNEW: OutCntCanNew(); break;
      case bINQ_GETCNTCANOLD: OutCntCanOld(); break;

      case bINQ_GETCNTCANNEW_ALL: OutCntCanNewAll(); break;
      case bINQ_GETCNTCANOLD_ALL: OutCntCanOldAll(); break;

      case bINQ_GETIMPCANMNT: OutImpMntCan(); break;
      case bINQ_GETIMPCANHOU: OutImpHhrCan(); break;
      case bINQ_GETIMPCANDAY: OutImpDayCan(); break;
      case bINQ_GETIMPCANMON: OutImpMonCan(); break;
      case bINQ_GETIMPCANABS: OutImpAbsCan(); break;

      case bINQ_GETIMPCANMNT_ALL: OutImpMntCanAll(); break;
      case bINQ_GETIMPCANHOU_ALL: OutImpHhrCanAll(); break;
      case bINQ_GETIMPCANDAY_ALL: OutImpDayCanAll(); break;
      case bINQ_GETIMPCANMON_ALL: OutImpMonCanAll(); break;
      case bINQ_GETIMPCANABS_ALL: OutImpAbsCanAll(); break;

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

      case bINQ_GETIMPCANMNTCURR: OutImpMntCurrCan(); break;
      case bINQ_GETIMPCANMNTCURR_ALL: OutImpMntCurrCanAll(); break;

      case bINQ_GETPOWGRPMNTPREV: OutPowMntGrp(0, PrevSoftMnt(), 20); break;
      case bINQ_GETPOWGRPMNT:     OutPowMntGrp(0, bInBuff6,      20); break;

      case bINQ_GETENGGRPMNTPREV_ALL: OutPowMntGrp(1, PrevSoftMnt(), 1); break;
      case bINQ_GETENGGRPMNT_ALL:     OutPowMntGrp(1, bInBuff5,      1); break;

      case bINQ_GETPOWGRPMNTPREV_ALL: OutPowMntGrp(1, PrevSoftMnt(), 20); break;
      case bINQ_GETPOWGRPMNT_ALL:     OutPowMntGrp(1, bInBuff5, 20);      break;

      case bINQ_GETPOWGRPHOUCURR: OutPowHouGrp(0, iwHardHou,                 2); break;
      case bINQ_GETPOWGRPHOUPREV: OutPowHouGrp(0, PrevHardHou(),             2); break;
      case bINQ_GETPOWGRPHOU:     OutPowHouGrp(0, bInBuff6*0x100 + bInBuff7, 2); break;

      case bINQ_GETENGGRPHOUCURR_ALL: OutPowHouGrp(1, iwHardHou,                 1); break;
      case bINQ_GETENGGRPHOUPREV_ALL: OutPowHouGrp(1, PrevHardHou(),             1); break;
      case bINQ_GETENGGRPHOU_ALL:     OutPowHouGrp(1, bInBuff5*0x100 + bInBuff6, 1); break;

      case bINQ_GETPOWGRPHOUCURR_ALL: OutPowHouGrp(1, iwHardHou,                 2); break;
      case bINQ_GETPOWGRPHOUPREV_ALL: OutPowHouGrp(1, PrevHardHou(),             2); break;
      case bINQ_GETPOWGRPHOU_ALL:     OutPowHouGrp(1, bInBuff5*0x100 + bInBuff6, 2); break;

      case bINQ_GETENGGRPDAYCURR: OutEngDayGrp(0, ibHardDay,     0); break;
      case bINQ_GETENGGRPDAYPREV: OutEngDayGrp(0, PrevHardDay(), 0); break;
      case bINQ_GETENGGRPDAY:     OutEngDayGrp(0, bInBuff6,      0); break;

      case bINQ_GETENGGRPDAYCURR_ALL: OutEngDayGrp(1, ibHardDay,     0); break;
      case bINQ_GETENGGRPDAYPREV_ALL: OutEngDayGrp(1, PrevHardDay(), 0); break;
      case bINQ_GETENGGRPDAY_ALL:     OutEngDayGrp(1, bInBuff5,      0); break;

      case bINQ_GETENGGRPDAYCURR_ALLSUM: OutEngDayGrp(1, ibHardDay,     1); break;
      case bINQ_GETENGGRPDAYPREV_ALLSUM: OutEngDayGrp(1, PrevHardDay(), 1); break;
      case bINQ_GETENGGRPDAY_ALLSUM:     OutEngDayGrp(1, bInBuff5,      1); break;

      case bINQ_GETENGGRPMONCURR: OutEngMonGrp(0, ibHardMon,     0); break;
      case bINQ_GETENGGRPMONPREV: OutEngMonGrp(0, PrevHardMon(), 0); break;
      case bINQ_GETENGGRPMON:     OutEngMonGrp(0, bInBuff6,      0); break;

      case bINQ_GETENGGRPMONCURR_ALL: OutEngMonGrp(1, ibHardMon,     0); break;
      case bINQ_GETENGGRPMONPREV_ALL: OutEngMonGrp(1, PrevHardMon(), 0); break;
      case bINQ_GETENGGRPMON_ALL:     OutEngMonGrp(1, bInBuff5,      0); break;

      case bINQ_GETENGGRPMONCURR_ALLSUM: OutEngMonGrp(1, ibHardMon,     1); break;
      case bINQ_GETENGGRPMONPREV_ALLSUM: OutEngMonGrp(1, PrevHardMon(), 1); break;
      case bINQ_GETENGGRPMON_ALLSUM:     OutEngMonGrp(1, bInBuff5,      1); break;

      case bINQ_GETMAXPOWGRPDAYCURR: OutMaxPowDayGrp(0, ibHardDay);     break;
      case bINQ_GETMAXPOWGRPDAYPREV: OutMaxPowDayGrp(0, PrevHardDay()); break;
      case bINQ_GETMAXPOWGRPDAY:     OutMaxPowDayGrp(0, bInBuff6);      break;

      case bINQ_GETMAXPOWGRPMONCURR: OutMaxPowMonGrp(0, ibHardMon);     break;
      case bINQ_GETMAXPOWGRPMONPREV: OutMaxPowMonGrp(0, PrevHardMon()); break;
      case bINQ_GETMAXPOWGRPMON:     OutMaxPowMonGrp(0, bInBuff6);      break;

      case bINQ_GETMAXPOWGRPDAYCURR_ALL: OutMaxPowDayGrp(1, ibHardDay);     break;
      case bINQ_GETMAXPOWGRPDAYPREV_ALL: OutMaxPowDayGrp(1, PrevHardDay()); break;
      case bINQ_GETMAXPOWGRPDAY_ALL:     OutMaxPowDayGrp(1, bInBuff5);      break;

      case bINQ_GETMAXPOWGRPMONCURR_ALL: OutMaxPowMonGrp(1, ibHardMon);     break;
      case bINQ_GETMAXPOWGRPMONPREV_ALL: OutMaxPowMonGrp(1, PrevHardMon()); break;
      case bINQ_GETMAXPOWGRPMON_ALL:     OutMaxPowMonGrp(1, bInBuff5);      break;

      case bINQ_GETPOWGRPHOU_DAY: OutPowGrpHou48(); break;
      case bINQ_GETIMPCANHOU_DAY: OutImpCanHou48(); break;

      case bINQ_GETTARIFFSDAY: OutGetTariffsDay(); break;

      case bINQ_TRANSIT_EXECUTE1: SafeTransitExecute1(); break;
      case bINQ_TRANSIT_EXECUTE2: SafeTransitExecute2(); break;
      case bINQ_TRANSIT_EXECUTE3: SafeTransitExecute3(); break;
      case bINQ_TRANSIT_EXECUTE4: SafeTransitExecute4(); break;
      case bINQ_TRANSIT_W:        SafeTransitExecuteW(); break;
      case bINQ_TRANSIT_DEVICE40: SafeTransitDevice40(); break;

      case bINQ_FLOW: OutFlow(); break;
      case bINQ_ENBL_ANSWER: OutEnableAnswer(); break;

      case bINQ_SETKEY: OutSetKey(); break;
      case bINQ_GETDISPLAY: OutGetDisplay(); break;

      case bINQ_GETCONFIG: OutGetConfig(); break;

      case bINQ_GETFLASHPAGE: OutFlashPage(); break;

      case bINQ_RESPONSE_252: Response252_CRC(); break;
      case bINQ_RESPONSE_253: Response253_CRC(); break;
      case bINQ_RESPONSE_254: Response254_CRC(); break;
      case bINQ_RESPONSE_255: Response255_CRC(); break;

//      case 250: OutTestMinute3(); break;
//      case 230: OutTestMinute15(); break;
//      case 251: OutTestMinute30(); break;
//      case 252: OutTestDay(); break;
//      case 253: OutTestMonth(); break;
//      case 254: OutTestYear(); break;

      default:
        ShowResponseCRC(bSTA_BADCOMMAND);
        Result(bRES_BADCOMMAND);
        break;
  }
}

#ifdef NO_DISPLAY
void    Response0_CRC_Panel(void)
{
    switch (bInBuff4)
    {
      case bINQ_GETGLOBAL: LongResult(enGlobal); break;

      case bINQ_GETCURRTIME: OutGetCurrTimeDate(); break;
      case bINQ_GETLOGICAL: LongResult(bLogical); break;
      case bINQ_GETPRIVATE: Common(&wPrivate, sizeof(uint)); break;

      case bINQ_SETKEY: OutSetKey(); break;
      case bINQ_GETDISPLAY: OutGetDisplay(); break;

      case bINQ_RESPONSE_255: Response255_CRC_Panel(); break;

      default:
        ShowResponseCRC(bSTA_BADCOMMAND);
        Result(bRES_BADCOMMAND);
        break;
  }
}
#endif
