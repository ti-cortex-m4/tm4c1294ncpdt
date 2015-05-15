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
#include "../tariffs/gaps.h"
#include "../output/out_correct.h"
#include "../time/correct2.h"
#include "../time/correct3.h"
#include "../output/out_groups.h"
#include "../output/out_relaxs.h"
#include "../devices/extended_4.h"
#include "../devices/extended_4t.h"
#include "../devices/extended_5.h"
#include "../devices/extended_6.h"
#include "../devices/extended_7.h"
#include "../output/out_common.h"
#include "../output/out_phones.h"
#include "../output/out_gaps.h"
#include "../output/out_decret.h"
#include "../output/out_digitals.h"
#include "../output/out_max_power.h"
#include "../output/out_energy.h"
#include "../output/out_impulse.h"
#include "../output/out_minute3.h"
#include "../output/out_minute30.h"
#include "../output/out_minute30_48.h"
#include "../output/out_addresses.h"
#include "../output/out_current.h"
#include "../output/out_version.h"
#include "../output/out_ports.h"
#include "../output/out_names.h"
#include "../output/out_limits.h"
#include "../output/profile/out_limits.h"
#include "../output/profile/out_schedule.h"
#include "../output/out_extended_1.h"



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

    case bINQ_GETTRANS_ENG: OutFloatCanMap(mpreTransEng); break;
    case bINQ_GETTRANS_CNT: OutFloatCanMap(mpreTransCnt); break;
    case bINQ_GETPULSE_HOU: OutFloatCanMap(mprePulseHou); break;
    case bINQ_GETPULSE_MNT: OutFloatCanMap(mprePulseMnt); break;
    case bINQ_GETCOUNT:     OutFloatCanMap(mpreCount);    break;
    case bINQ_GETLOSSE:     OutFloatCanMap(mpreLosse);    break;

    case bINQ_GETCNTCANMONCURR_ALL: OutCntCanMonCurrExt(); break;
    case bEXT_GETSIMPLE_ESC_S:      OutSimpleEscSExt();    break;
    case bEXT_GETSIMPLE_ESC_U:      OutSimpleEscUExt();    break;
    case bEXT_GETTIME_ESC_S:        OutTimeEscSExt();      break;
    case bEXT_GETTIME_ESC_V:        OutTimeEscVExt();      break;

    case bEXT_GETGROUPS: OutGetGroupsExt(); break;

    case bINQ_GETMAXPOWGRPDAY_ALL:  OutMaxPowDayGrpExt();  break;
    case bINQ_GETMAXPOWGRPMON_ALL:  OutMaxPowMonGrpExt();  break;

    case bINQ_GETENGGRPDAY_ALL: OutEngDayGrpExt0(false); break;
    case bINQ_GETENGGRPMON_ALL: OutEngMonGrpExt0(false); break;

    case bINQ_GETENGGRPDAY_ALLSUM:  OutEngDayGrpExt1();    break;
    case bINQ_GETENGGRPMON_ALLSUM:  OutEngMonGrpExt1();    break;

    case bINQ_GETIMPCANDAY_ALL:     OutImpDayCanExt();     break;
    case bINQ_GETIMPCANMON_ALL:     OutImpMonCanExt();     break;

    case bINQ_GETPOWGRPHOU_DAY:     OutPowGrpHou48Ext();   break;
    case bINQ_GETIMPCANHOU_DAY:     OutImpCanHou48Ext();   break;
    case bINQ_GETPOWCANHOU_DAY:     OutPowCanHou48Ext();   break;

    case bINQ_GETIMPCANMNT_ALL:     OutImpMntCanExt();     break;
    case bINQ_GETPOWCANMNT_ALL:     OutPowMntCanExt();     break;

    case bEXT_GETIMPCANHOU:         OutImpCanHouExt();     break;
    case bEXT_GETIMPCANMNT:         OutImpCanMntExt();     break;
    case bEXT_GETPOWCANMNT:         OutPowCanMntExt();     break;

    case bEXT_GETADDRESS: OutGetAddress(); break;
    case bEXT_SETADDRESS: OutSetAddress(); break;
    case bEXT_GETADDRESSES: OutGetAddressesExt(); break;

    case bEXT_GETCURRENT:           OutCurrentExt();       break;

    case bEXT_GETDIGITALS: OutGetDigitalsExt(); break;

    case bEXT_GETSTOPCAN: OutIntCanMap(mpcwStopCan); break;
    case bEXT_GETSTOPCAN2: OutStopCan2(); break;

    case bEXT_GETENBLCAN: OutBoolCanMap(mpboEnblCan); break;

    case bEXT_GETCTRLHOU: OutGetCtrlHou(); break;
    case bEXT_SETCTRLHOU: OutSetCtrlHou(); break;

    case bEXT_GETENBLPORTHOU: OutGetEnblPrtHou(); break;
    case bEXT_SETENBLPORTHOU: OutSetEnblPrtHou(); break;

    case bEXT_GETRECALC: OutGetRecalcHou(); break;
    case bEXT_SETRECALC1: OutSetRecalcHou1(); break;
    case bEXT_SETRECALC2: OutSetRecalcHou2(); break;

    case bEXT_GETEXTENDED40:  OutExtended40();  break;
    case bEXT_GETEXTENDED401: OutExtended401(); break;
    case bEXT_GETEXTENDED41:  OutExtended41();  break;
    case bEXT_GETEXTENDED42:  OutExtended42();  break;
    case bEXT_GETEXTENDED43:  OutExtended43();  break;

    case bEXT_GETEXTENDED6:   OutExtended6();   break;

    case bEXT_GETRELAXS: OutGetRelaxs(); break;
    case bEXT_SETRELAXS: OutSetRelaxs(); break;

    case bEXT_GETEXTENDED50: OutExtended50(); break;
    case bEXT_GETEXTENDED51: OutExtended51(); break;

    case bEXT_GETSTARTCAN: OutStartCan(); break;

    case bEXT_GETVERSION: OutVersion(); break;
    case bEXT_GETPORTS: OutPorts(); break;
/*
    case bEXT_GETHOUCANDEF:         OutImpCanHou48Def();  break;
    case bEXT_GETHOUGRPDEF:         OutPowGrpHou48Def();  break;
    case bEXT_GETDAYCANDEF_ALL:     OutDayCanDefAll();    break;
    case bEXT_GETMONCANDEF_ALL:     OutMonCanDefAll();    break;
    case bEXT_GETDAYGRPDEF_ALL:     OutDayGrpDefAll();    break;
    case bEXT_GETMONGRPDEF_ALL:     OutMonGrpDefAll();    break;
    case bEXT_GETDAYCANDEF:         OutDayCanDef();       break;
    case bEXT_GETMONCANDEF:         OutMonCanDef();       break;
    case bEXT_GETDAYGRPDEF:         OutDayGrpDef();       break;
    case bEXT_GETMONGRPDEF:         OutMonGrpDef();       break;

    case bINQ_GETENGGRPDAY_DEF:     OutEngDayGrpDef();    break;
    case bINQ_GETENGGRPMON_DEF:     OutEngMonGrpDef();    break;
    case bINQ_GETMAXPOWGRPDAY_DEF:  OutMaxPowDayGrpDef(); break;
    case bINQ_GETMAXPOWGRPMON_DEF:  OutMaxPowMonGrpDef(); break;
    case bINQ_GETENGGRPHOUPREV_DEF: OutPowHouGrpDef(1);   break;
    case bINQ_GETPOWGRPHOUPREV_DEF: OutPowHouGrpDef(2);   break;
*/
    case bEXT_GETGAPS1: OutGaps1(); break;
    case bEXT_GETGAPS2: OutGaps2(); break;

    case bEXT_GETEXTENDED7: OutExtended7(); break;

    case bEXT_GETSTOPAUXCAN: OutStopAuxCan(); break;

    case bEXT_GETDECRET: OutDecret(); break;
/*
    case bEXT_GETSTART:
      InitPushCRC();
      Push(&tiStart, sizeof(time));
      Push(&tiPowerOff, sizeof(time));
      Push(&tiPowerOn,  sizeof(time));
      PushChar(cbPowerOn);
      Output(6+6+6+1);
      break;

    case bEXT_GETBULK:
      InitPushCRC();
      PushChar(boEnableBulk);
      PushChar(bMaxBulk);
      Push(&cbBulk, sizeof(cbBulk));
      PushInt(wMaxBulkDelay);
      Push(&cwBulkDelay, sizeof(cwBulkDelay));
      Push(&mpSerial, sizeof(mpSerial));
      Push(&mpSerial_Bulk, sizeof(mpSerial_Bulk));
      Output(1+1+4*1+2+4*2+4*1+4*1);
      break;
*/
    case bEXT_GETOBJECTNAME: GetObjectNameExt(); break;
    case bEXT_SETOBJECTNAME: SetObjectNameExt(); break;
    case bEXT_GETCANALSNAME: GetCanalsNameExt(); break;
    case bEXT_SETCANALSNAME: SetCanalsNameExt(); break;
    case bEXT_GETGROUPSNAME: GetGroupsNameExt(); break;
    case bEXT_SETGROUPSNAME: SetGroupsNameExt(); break;

    case bEXT_GETEXTENDED40_T: OutExtended40T(); break;

    case bEXT_FLASH_CONTROL:
      OutFlashControl();
      break;

    default:
      ShowTestResponse(bSTA_BADCOMMAND);
      Result(bRES_BADCOMMAND);
      break;
  }
}
