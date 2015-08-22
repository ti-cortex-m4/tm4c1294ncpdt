/*------------------------------------------------------------------------------
RESPONSE255_CRC.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_limits.h"
#include "../include/states.h"
#include "../serial/ports.h"
#include "../output/response_crc.h"
#include "../flash/flash_control.h"
#include "../flash/records_dsbl.h"
#include "../tariffs/gaps.h"
#include "../output/out_correct.h"
#include "../time/correct2.h"
#include "../time/correct3.h"
#include "../output/out_groups.h"
#include "../output/out_relaxs.h"
#include "../digitals/extended/extended_1_out.h"
#include "../digitals/extended/extended_4_out.h"
#include "../digitals/extended/extended_4t_out.h"
#include "../digitals/extended/extended_5_out.h"
#include "../digitals/extended/extended_6_out.h"
#include "../digitals/extended/extended_7_out.h"
#include "../digitals/extended/diagram.h"
#include "../output/out_common.h"
#include "../output/out_settings.h"
#include "../output/out_phones.h"
#include "../output/out_gaps.h"
#include "../output/out_decret.h"
#include "../output/out_digitals.h"
#include "../output/out_max_power.h"
#include "../output/out_energy.h"
#include "../output/out_energy2.h"
#include "../output/out_impulse.h"
#include "../output/out_minute3.h"
#include "../output/out_minute30.h"
#include "../output/out_minute30_48.h"
#include "../output/out_addresses.h"
#include "../output/out_version.h"
#include "../output/out_ports.h"
#include "../output/out_names.h"
#include "../output/out_limits.h"
#include "../output/out_defects2.h"
#include "../output/out_defects3.h"
#include "../output/current/out_current.h"
#include "../output/current/out_current2.h"
#include "../output/profile/out_limits.h"
#include "../output/profile/out_schedule.h"
#include "../output/profile/out_profile.h"



void    Response255_CRC(void)
{
  switch (bInBuff5)
  {
    case bEXT_CORRECT1: OutCorrect1(); break;
    case bEXT_CORRECT2: OutCorrect2(); break;
    case bEXT_CORRECT20: OutCorrect20(); break;
    case bEXT_CORRECT21: OutCorrect21(); break;
    case bEXT_CORRECT3:  OutCorrect3();  break;

    case bEXT_GETPHONE: OutGetPhone(); break;
    case bEXT_SETPHONE: OutSetPhone(); break;

    case bINQ_GETTRANS_ENG: OutFloatOrDoubleCanExt(mpdbTransEng, false); break;
    case bINQ_GETTRANS_CNT: OutFloatOrDoubleCanExt(mpdbTransCnt, false); break;
    case bINQ_GETPULSE_HOU: OutFloatOrDoubleCanExt(mpdbPulseHou, false); break;
    case bINQ_GETPULSE_MNT: OutFloatOrDoubleCanExt(mpdbPulseMnt, false); break;
    case bINQ_GETCOUNT:     OutFloatOrDoubleCanExt(mpdbCount, false);    break;
    case bINQ_GETLOSSE:     OutFloatOrDoubleCanExt(mpdbLosse, false);    break;

    case bEXT_GET_ESC_S_VALUE: OutEscS_Value(false); break;
    case bEXT_GET_ESC_U_VALUE: OutEscU_Value();      break;
    case bEXT_GET_ESC_V_VALUE: OutEscV_Value(false); break;
    case bEXT_GET_ESC_S_TIME:  OutEscS_Time();       break;
    case bEXT_GET_ESC_V_TIME:  OutEscV_Time();       break;

    case bEXT_GETGROUPS: OutGetGroupsExt(); break;

    case bINQ_GETMAXPOWGRPDAY_ALL: OutMaxPowDayGrpExt(); break;
    case bINQ_GETMAXPOWGRPMON_ALL: OutMaxPowMonGrpExt(); break;

    case bINQ_GETENGGRPDAY_ALL: OutEngDayGrpExt(false); break;
    case bINQ_GETENGGRPMON_ALL: OutEngMonGrpExt(false); break;

    case bINQ_GETENGGRPDAY_ALLSUM: OutEngDayGrpExtSum(); break;
    case bINQ_GETENGGRPMON_ALLSUM: OutEngMonGrpExtSum(); break;

    case bINQ_GETIMPCANDAY_ALL: OutImpDayCanExt(); break;
    case bINQ_GETIMPCANMON_ALL: OutImpMonCanExt(); break;

    case bINQ_GETENGGRPHOU_ALL: OutEngGrpHouExt1(); break;
    case bEXT_GETENGGRPHOU_ALL: OutEngGrpHouExt2(); break;

    case bINQ_GETPOWGRPHOU_DAY: OutPowGrpHou48Ext(); break;
    case bINQ_GETIMPCANHOU_DAY: OutImpCanHou48Ext(); break;
    case bINQ_GETPOWCANHOU_DAY: OutPowCanHou48Ext(); break;
    case bINQ_GETDEFCANHOU_DAY: OutDefCanHou48Ext(); break;

    case bINQ_GETIMPCANMNT_ALL: OutImpMntCanExt(); break;
    case bINQ_GETPOWCANMNT_ALL: OutPowMntCanExt(); break;

    case bEXT_GETIMPCANHOU: OutImpCanHouExt(); break;
    case bEXT_GETIMPCANMNT: OutImpCanMntExt(); break;
    case bEXT_GETPOWCANMNT: OutPowCanMntExt(); break;

    case bEXT_GETADDRESS: OutGetAddress(); break;
    case bEXT_SETADDRESS: OutSetAddress(); break;
    case bEXT_GETADDRESSES: OutGetAddressesExt(); break;

    case bEXT_GETCURRENT: OutCurrentExt(); break;

    case bEXT_GETENG3MIN_DATA: OutEng3MinDataExt(); break;
    case bEXT_GETENG3MIN_TIME: OutEng3MinTimeExt(); break;

    case bEXT_GETDIGITALS: OutGetDigitalsExt(); break;
    case bEXT_GETPHONES: OutPhonesExt(); break;

    case bEXT_GETSTOPCAN: OutIntCanExt(mpcwStopCan); break;
    case bEXT_GETSTOPCAN2: OutStopCan2(); break;

    case bEXT_GETENBLCAN: OutBoolCanExt(mpboEnblCan); break;

    case bEXT_GETCTRLHOU: OutGetCtrlHou(); break;
    case bEXT_SETCTRLHOU: OutSetCtrlHou(); break;

    case bEXT_GETENBLPORTHOU: OutGetEnblPrtHou(); break;
    case bEXT_SETENBLPORTHOU: OutSetEnblPrtHou(); break;

    case bEXT_GETRECALC: OutGetRecalcHou(); break;
    case bEXT_SETRECALC1: OutSetRecalcHou1(); break;
    case bEXT_SETRECALC2: OutSetRecalcHou2(); break;

    case bEXT_GETEXTENDED40: OutExtended40(false); break;
    case bEXT_GETEXTENDED44: OutExtended44(false); break;
    case bEXT_GETEXTENDED41: OutExtended41(false); break;
    case bEXT_GETEXTENDED42: OutExtended42(false); break;
    case bEXT_GETEXTENDED43: OutExtended43(); break;

    case bEXT_GET_EXTENDED_4T: OutExtended4T(false); break;

    case bEXT_GETEXTENDED50: OutExtended50(false); break;
    case bEXT_GETEXTENDED51: OutExtended51(false); break;

    case bEXT_GETEXTENDED6: OutExtended6(false); break;

    case bEXT_GETEXTENDED7: OutExtended7(false); break;

    case bEXT_GETDIAGRAM: OutDiagram(false); break;

    case bEXT_GETENGCANDAY: OutEngDayCan(); break;
    case bEXT_GETENGCANMON: OutEngMonCan(); break;

    case bEXT_GETRELAXS: OutGetRelaxs(); break;
    case bEXT_SETRELAXS: OutSetRelaxs(); break;

    case bEXT_GETSTARTCAN: OutStartCan(); break;

    case bEXT_GETVERSION: OutVersion(); break;

    case bEXT_GETPORTS: OutPorts(); break;
    case bEXT_GETOUTPUTDELAY: OutOutputDelay(); break;

    case bEXT_GETCORRECTLIMIT: OutCorrectLimit(); break;
    case bEXT_GETLINKERRORS: OutLinkErrors(); break;

    case bEXT_GETHOUCANDEF: OutImpCanHou48Def(); break;
    case bEXT_GETHOUGRPDEF: OutPowGrpHou48Def(); break;
    case bEXT_GETDAYCANDEF_ALL: OutDayCanDefAll(); break;
    case bEXT_GETMONCANDEF_ALL: OutMonCanDefAll(); break;
    case bEXT_GETDAYGRPDEF_ALL: OutDayGrpDefAll(); break;
    case bEXT_GETMONGRPDEF_ALL: OutMonGrpDefAll(); break;
    case bEXT_GETDAYCANDEF: OutDayCanDef(); break;
    case bEXT_GETMONCANDEF: OutMonCanDef(); break;
    case bEXT_GETDAYGRPDEF: OutDayGrpDef(); break;
    case bEXT_GETMONGRPDEF: OutMonGrpDef(); break;

    case bINQ_GETENGGRPDAY_DEF: OutEngDayGrpDef(); break;
    case bINQ_GETENGGRPMON_DEF: OutEngMonGrpDef(); break;
    case bINQ_GETMAXPOWGRPDAY_DEF: OutMaxPowDayGrpDef(); break;
    case bINQ_GETMAXPOWGRPMON_DEF: OutMaxPowMonGrpDef(); break;
    case bINQ_GETENGGRPHOUPREV_DEF: OutPowHouGrpDef(1); break;
    case bINQ_GETPOWGRPHOUPREV_DEF: OutPowHouGrpDef(2); break;

    case bEXT_GETGAPS1: OutGaps1(); break;
    case bEXT_GETGAPS2: OutGaps2(); break;

    case bEXT_GETSTOPAUXCAN: OutStopAuxCan(); break;

    case bEXT_RECORDS_DSBL: OutRecordsDsbl(); break;

    case bEXT_GETDECRET: OutDecret(); break;

    case bEXT_GETSTART: OutStart(); break;

    case bEXT_GETOBJECTNAME: GetObjectNameExt(); break;
    case bEXT_SETOBJECTNAME: SetObjectNameExt(); break;
    case bEXT_GETCANALSNAME: GetCanalsNameExt(); break;
    case bEXT_SETCANALSNAME: SetCanalsNameExt(); break;
    case bEXT_GETGROUPSNAME: GetGroupsNameExt(); break;
    case bEXT_SETGROUPSNAME: SetGroupsNameExt(); break;

    case bEXT_OVERFLOW_HHR: OutGetOverflowHhr(); break;
    case bEXT_GET_ERROR_LINK: OutGetErrorLink(); break;
    case bEXT_GET_ENGFRAC: OutGetEngFrac(); break;
    case bEXT_GET_ENGFRACDIGCAN: OutGetEngFracDigCan(); break;
    case bEXT_RESET_ENGFRAC: OutResetEngFrac(); break;
    case bEXT_RESET_ENGFRACDIGCAN: OutResetEngFracDigCan(); break;

    case bEXT_FLASH_CONTROL: OutFlashControl(); break;

    default:
      ShowTestResponse(bSTA_BADCOMMAND);
      Result(bRES_BADCOMMAND);
      break;
  }
}
