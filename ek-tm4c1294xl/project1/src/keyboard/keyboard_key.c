/*------------------------------------------------------------------------------
KEYBOARD_KEY.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../include/programs.h"
#include        "keyboard.h"
#include        "key_speeds.h"
#include        "key_timedate.h"
#include        "key_password.h"
#include        "key_logical.h"
#include        "key_private.h"
#include        "key_start.h"
#include        "key_version.h"
#include        "digitals/key_digitals.h"
#include        "digitals/schedule/key_enbl_hours.h"
#include        "digitals/schedule/key_ctrl_hours.h"
#include        "digitals/schedule/key_recalc.h"
#include        "digitals/schedule/key_recalc_always.h"
#include        "digitals/key_enbl_canals.h"
#include        "digitals/key_enbl_current.h"
#include        "digitals/profile/key_enbl_profile.h"
#include        "digitals/key_timeout_current.h"
#include        "digitals/profile/key_timeout_profile.h"
#include        "digitals/key_addresses.h"
#include        "digitals/key_enbl_keys.h"
#include        "digitals/key_keys.h"
#include        "sensors/key_keys_level_b.h"
#include        "digitals/key_search.h"
#include        "digitals/key_automatic.h"
#include        "digitals/profile/key_run_profile.h"
#include        "digitals/key_show_messages.h"
#include        "digitals/key_separate_can.h"
#include        "digitals/profile/key_control_time.h"
#include        "digitals/profile/key_manage_time.h"
#include        "digitals/profile/key_limits.h"
#include        "digitals/profile/key_limits2.h"
#include        "digitals/profile/key_limits30.h"
#include        "digitals/profile/key_limits31.h"
#include        "digitals/profile/key_limits32.h"
#include        "digitals/profile/key_limits33.h"
#include        "phones/key_phones.h"
#include        "phones/key_max_connect.h"
#include        "phones/key_custom_modem.h"
#include        "key_decret.h"
#include        "key_season.h"
#include        "key_groups.h"
#include        "tariffs/key_dayzone.h"
#include        "tariffs/key_public_tariffs.h"
#include        "tariffs/key_oldyearzone.h"
#include        "tariffs/key_tariffs_mode.h"
#include        "tariffs/key_oldprogram5.h"
#include        "tariffs/key_relaxs_flag.h"
#include        "tariffs/key_relaxs_tariff.h"
#include        "tariffs/key_relaxs.h"
#include        "key_factors.h"
#include        "key_delays.h"
#include        "impulses/key_single.h"
#include        "impulses/key_single2.h"
#include        "impulses/key_fullyear.h"
#include        "impulses/key_oldprogram73.h"
#include        "impulses/key_oldprogram74.h"
#include        "key_reset.h"
#include        "test/key_test_direct.h"
#include        "test/key_test_response.h"
#include        "test/key_test_flow.h"
#include        "test/key_test_ports_io.h"
#include        "test/key_test_uni.h"
#include        "test/key_test_flash.h"
#include        "test/key_test_impulses.h"
#include        "test/key_test_keys.h"
#include        "test/key_test_rtc.h"
#include        "key_gaps_flag.h"
#include        "key_gaps.h"
#include        "digitals/key_hide_messages.h"
#include        "sensors/key_short_profile_c.h"
#include        "digitals/profile/key_dsbl_refill.h"
#include        "digitals/key_max_repeats.h"
#include        "digitals/key_dsbl_esc.h"
#include        "unified/key_strict_uni.h"
#include        "unified/key_dsbl_password_uni.h"
#include        "unified/key_max_delay_uni.h"
#include        "unified/key_repeat_flow_uni.h"
#include        "digitals/key_mnt_esc_s.h"
#include        "digitals/key_extended_esc.h"
#include        "serial/key_flow.h"
#include        "serial/key_max_flow_delay.h"
#include        "digitals/params/key_enbl_params.h"
#include        "digitals/params/key_mnt_params.h"
#include        "digitals/params/key_params.h"
#include        "digitals/params/key_params_div.h"
#include        "digitals/params/key_params_all.h"
#include        "digitals/params/key_fix_params_bugs.h"
#include        "digitals/params/key_use_params_div.h"
#include        "devices/key_ext_4_flag.h"
#include        "devices/key_ext_4_months.h"
#include        "devices/key_ext_4_enbl_can.h"
#include        "devices/key_ext_4t_flag.h"
#include        "devices/key_ext_4t_months.h"
#include        "devices/key_ext_4t_reset1.h"
#include        "devices/key_ext_4t_reset2.h"



void    Keyboard_Key(void)
{
  if (enGlobal == GLB_PROGRAM)
  {
    switch (wProgram)
    {
      case bSET_SPEED:          key_SetSpeeds();        break;

      case bSET_CURRTIME:       key_SetCurrTime();      break;
      case bSET_CURRDATE:       key_SetCurrDate();      break;

      case bSET_GROUPS:         key_SetGroups();        break;

      case bSET_TRANS_ENG:
      case bSET_TRANS_CNT:
      case bSET_PULSE_HOU:
      case bSET_PULSE_MNT:
      case bSET_LOSSE:
      case bSET_LEVEL:
      case bSET_COUNT:          key_SetFactors();       break;

      case bSET_DAY_ZONE:       key_SetDayZone();       break;
      case bSET_PUBLIC_TARIFFS: key_SetPublicTariffs(); break;
      case bSET_TARIFFS_MODE:   key_SetTariffsMode();   break;

      case bSET_PROGRAM10:
      case bSET_PROGRAM17:
      case bSET_PROGRAM20:
      case bSET_PROGRAM27:      key_SetOldYearZone();   break;

      case bSET_RELAXS_FLAG:    key_SetRelaxsFlag();    break;
      case bSET_RELAXS_TARIFF:  key_SetRelaxsTariff();  break;
      case bSET_RELAXS:         key_SetRelaxs();        break;

      case bSET_PASSWORD:       key_SetPassword();      break;
      case bSET_LOGICAL:        key_SetLogical();       break;
      case bSET_PRIVATE:        key_SetPrivate();       break;

      case bSET_STARTHOU:
      case bSET_START:          key_Start();            break;
      case bSET_DEBUG:          key_Debug();            break;

      case bSET_VERSION:        key_GetVersion();       break;

      case bSET_RESETCUSTOM:
      case bSET_RESETFULL:      key_SetReset();         break;

      case bSEARCH_BY_NUMBER:   key_SearchByNumber();   break;
      case bSEARCH_BY_SPEED:    key_SearchBySpeed();    break;

      case bSET_AUTOMATIC1:     key_Automatic1();       break;
      case bSET_AUTOMATIC2:     key_Automatic2();       break;

      case bSET_MAJOR_DELAYS:
      case bSET_MINOR_DELAYS:   key_SetDelays();        break;

      case bSET_DIGITALS:       key_SetDigitals();      break;
      case bSET_ENBL_HOURS:     key_SetEnblHours();     break;
      case bSET_CONTROL_HOURS:  key_SetCtrlHours();     break;
      case bSET_ENBL_CANALS:    key_SetEnblCanals();    break;

      case bSET_ENBL_PARAMS:    key_SetEnblParams();    break;
      case bSET_MNT_PARAMS:     key_SetMntParams();     break;
      case bSET_PARAMS:         key_SetParams();        break;
      case bSET_PARAMS_DIV:     key_SetParamsDiv();     break;
      case bGET_PARAMS_CURR:
      case bGET_PARAMS_BUFF:
      case bGET_PARAMS_FULL:    key_GetParamsAll();     break;
      case wSET_FIX_PARAMS_BUGS:key_SetFixParamsBugs(); break;
      case wSET_USE_PARAMS_DIV: key_SetUseParamsDiv();  break;

      case bSET_LIMITS:         key_SetLimits();        break;
      case bSET_LIMITS2:        key_SetLimits2();       break;
      case bSET_LIMITS30:       key_SetLimits30();      break;
      case bSET_LIMITS31:       key_SetLimits31();      break;
      case bSET_LIMITS32:       key_SetLimits32();      break;
      case bSET_LIMITS33:       key_SetLimits33();      break;

      case bSET_FLOW_PORT_TO:   key_FlowPortTo();       break;
      case bSET_MAX_FLOW_DELAY: key_SetMaxFlowDelay();  break;
      case bSET_FLOW_PORT_FROM: key_FlowPortFrom();     break;

      case bSET_ENBL_CURRENT:   key_SetEnblCurrent();   break;
      case bSET_ENBL_PROFILE:   key_SetEnblProfile();   break;
      case bSET_TIMEOUT_PROFILE:key_SetTimeoutProfile();break;
      case bSET_TIMEOUT_CURRENT:key_SetTimeoutCurrent();break;
      case bSET_CONTROL_TIME:   key_SetControlTime();   break;
      case bSET_MANAGE_TIME:    key_SetManageTime();    break;

      case bSET_EXTENDED_ESC_S: key_SetExtendedEscS();  break;
      case bSET_EXTENDED_ESC_V: key_SetExtendedEscV();  break;
      case bSET_EXTENDED_ESC_U: key_SetExtendedEscU();  break;

      case bSET_ADDRESSES:      key_SetAddresses();     break;
      case bSET_ENBL_KEYS:      key_SetEnblKeys();      break;
      case bSET_KEYS:           key_SetKeys();          break;
      case wSET_KEYS_LEVEL_B:   key_SetKeysLevelB();    break;

      case bSET_PHONES:         key_SetPhones();        break;
      case bSET_MAX_CONNECT:    key_SetMaxConnect();    break;
      case bSET_CUSTOM_MODEM:   key_SetCustomModem();   break;

      case bSET_SHOW_MESSAGES:  key_SetShowMessages();  break;

      case bSET_SEPARATE_CAN:   key_SetSeparateCan();   break;

      case bSET_RECALC:         key_SetRecalc();        break;
      case bSET_RECALC_ALWAYS:  key_SetRecalcAlways();  break;

      case bGET_CNTCURR_110:
      case bGET_READTIMEDATE1:
      case bGET_READTIMEDATE2:  key_GetSingle(CANALS);  break;

      case bSET_DECRET:         key_SetDecret();        break;
      case bSET_WINTER:
      case bSET_SUMMER:         key_SetSeason();        break;

      case bTEST_DIRECT:        key_TestDirect();       break;

      case bTEST_RESPONSE:      key_TestResponse();     break;
      case bTEST_FLOW:          key_TestFlow();         break;
      case bTEST_PORTS_IO:      key_TestPortsIO();      break;
      case bTEST_UNI:           key_TestUni();          break;
      case bTEST_FLASH:         key_TestFlash();        break;

      case bTEST_IMPULSES:      key_TestImpulses();     break;
      case bTEST_KEYS:          key_TestKeys();         break;
      case bTEST_RTC:           key_TestRTC();          break;


      case wSET_HIDE_MESSAGES:  key_SetHideMessages();  break;

      case wSET_GAPS_FLAG:      key_SetGapsFlag();      break;
      case wSET_GAPS:           key_SetGaps();          break;

      case wSET_SHORT_PROFILE_C:key_SetShortProfileC(); break;
      case wSET_DSBL_REFILL:    key_SetDsblRefill();    break;
      case wSET_MAX_REPEATS:    key_SetMaxRepeats();    break;

      case wSET_DSBL_ESC:       key_SetDsblEsc();       break;

      case wSET_STRICT_UNI:         key_SetStrictUni();        break;
      case wSET_DSBL_PASSWORD_UNI:  key_SetDsblPasswordUni();  break;
      case wSET_MAX_DELAY_UNI:      key_SetMaxDelayUni();      break;
      case wSET_REPEAT_FLOW_UNI:    key_SetRepeatFlowUni();    break;

      case wSET_MNT_ESC_S:      key_SetMntEscS();       break;

      case bSET_EXT4_FLAG:      key_SetExt4Flag();      break;
      case bSET_EXT4_MONTHS:    key_SetExt4Months();    break;
      case bSET_EXT4_ENBL_CAN:  key_SetExt4EnblCan();   break;

      case wSET_EXT4T_FLAG:     key_SetExt4TFlag();     break;
      case wSET_EXT4T_MONTHS:   key_SetExt4TMonths();   break;
      case wSET_EXT4T_RESET1:   key_SetExt4TReset1();   break;
      case wSET_EXT4T_RESET2:   key_SetExt4TReset2();   break;

      default:                  NoProgram();            break;
    }
  }

  else if (enGlobal == GLB_WORK)
  {
    switch (wProgram)
    {
      case bGET_SPEED:          key_SetSpeeds();        break;

      case bGET_CURRTIME:       key_SetCurrTime();      break;
      case bGET_CURRDATE:       key_SetCurrDate();      break;

      case bGET_GROUPS:         key_GetGroups();        break;

      case bGET_PUBLIC_TARIFFS: key_SetPublicTariffs(); break;
      case bGET_TARIFFS_MODE:   key_SetTariffsMode();   break;

      case bGET_PROGRAM5:       key_GetOldProgram5();   break;
      case bGET_PROGRAM84:
      case bGET_PROGRAM85:      key_GetOldProgram84();  break;

      case bSET_RELAXS_FLAG:    key_SetRelaxsFlag();    break;
      case bSET_RELAXS_TARIFF:  key_SetRelaxsTariff();  break;
      case bSET_RELAXS:         key_GetRelaxs();        break;

      case bGET_TRANS_ENG:
      case bGET_TRANS_CNT:
      case bGET_PULSE_HOU:
      case bGET_PULSE_MNT:
      case bGET_LOSSE:
      case bSET_LEVEL:          key_GetFactors();       break;

//      case bGET_PROGRAM18:      key_GetProgram18();     break;
//      case bGET_PROGRAM19:      key_GetProgram19();     break;

      case bSET_PASSWORD:       key_GetPassword();      break;
      case bSET_LOGICAL:        key_SetLogical();       break;
      case bSET_PRIVATE:        key_SetPrivate();       break;

      case bSET_VERSION:
      case bGET_VERSION:        key_GetVersion();       break;

      case bSET_MAJOR_DELAYS:
      case bSET_MINOR_DELAYS:   key_SetDelays();        break;

      case bSET_DIGITALS:       key_SetDigitals();      break;
      case bSET_ENBL_HOURS:     key_SetEnblHours();     break;
      case bSET_CONTROL_HOURS:  key_SetCtrlHours();     break;
      case bSET_ENBL_CANALS:    key_SetEnblCanals();    break;

      case bSET_ENBL_PARAMS:    key_SetEnblParams();    break;
      case bSET_MNT_PARAMS:     key_SetMntParams();     break;
      case bSET_PARAMS:         key_SetParams();        break;
      case bSET_PARAMS_DIV:     key_SetParamsDiv();     break;
      case bGET_PARAMS_CURR:
      case bGET_PARAMS_BUFF:
      case bGET_PARAMS_FULL:    key_GetParamsAll();     break;
      case wSET_FIX_PARAMS_BUGS:key_SetFixParamsBugs(); break;
      case wSET_USE_PARAMS_DIV: key_SetUseParamsDiv();  break;

      case bSET_LIMITS:         key_SetLimits();        break;
      case bSET_LIMITS2:        key_SetLimits2();       break;
      case bSET_LIMITS30:       key_SetLimits30();      break;
      case bSET_LIMITS31:       key_SetLimits31();      break;
      case bSET_LIMITS32:       key_SetLimits32();      break;
      case bSET_LIMITS33:       key_SetLimits33();      break;

      case bSET_FLOW_PORT_TO:   key_FlowPortTo();       break;
      case bSET_MAX_FLOW_DELAY: key_SetMaxFlowDelay();  break;
      case bSET_FLOW_PORT_FROM: key_FlowPortFrom();     break;

      case bSET_ENBL_CURRENT:   key_SetEnblCurrent();   break;
      case bSET_ENBL_PROFILE:   key_SetEnblProfile();   break;
      case bSET_TIMEOUT_PROFILE:key_SetTimeoutProfile();break;
      case bSET_TIMEOUT_CURRENT:key_SetTimeoutCurrent();break;
      case bSET_CONTROL_TIME:   key_SetControlTime();   break;
      case bSET_MANAGE_TIME:    key_SetManageTime();    break;

      case bSET_EXTENDED_ESC_S: key_SetExtendedEscS();  break;
      case bSET_EXTENDED_ESC_V: key_SetExtendedEscV();  break;
      case bSET_EXTENDED_ESC_U: key_SetExtendedEscU();  break;

      case bSET_ADDRESSES:      key_SetAddresses();     break;
      case bSET_ENBL_KEYS:      key_SetEnblKeys();      break;
      case bSET_KEYS:           key_SetKeys();          break;
      case wSET_KEYS_LEVEL_B:   key_SetKeysLevelB();    break;

      case bSET_PHONES:         key_SetPhones();        break;
      case bSET_MAX_CONNECT:    key_SetMaxConnect();    break;
      case bSET_CUSTOM_MODEM:   key_SetCustomModem();   break;

      case bSET_SHOW_MESSAGES:  key_SetShowMessages();  break;

      case bSET_SEPARATE_CAN:   key_SetSeparateCan();   break;

      case bSET_RECALC:         key_SetRecalc();        break;
      case bSET_RECALC_ALWAYS:  key_SetRecalcAlways();  break;

      case bGET_CNTCURR_10:
      case bGET_CNTCURR_110:
      case bGET_READTIMEDATE1:
      case bGET_READTIMEDATE2:
      case bGET_IMPCANCURRMNT:  key_GetSingle(CANALS);  break;

      case bGET_POWGRPPREVHOU:
      case bGET_POWGRPCURRHOU:

      case bGET_POWGRPDAYPREV_ABCD:
      case bGET_POWGRPDAYPREV_C:
      case bGET_POWGRPDAYPREV_D:

      case bGET_POWGRPDAYCURR_ABCD:
      case bGET_POWGRPDAYCURR_C:
      case bGET_POWGRPDAYCURR_D:

      case bGET_POWGRPMONPREV_ABCD:
      case bGET_POWGRPMONPREV_C:
      case bGET_POWGRPMONPREV_D:

      case bGET_POWGRPMONCURR_ABCD:
      case bGET_POWGRPMONCURR_C:
      case bGET_POWGRPMONCURR_D:

      case bGET_ENGGRPDAYPREV_ABCD:
      case bGET_ENGGRPDAYPREV_CD:
      case bGET_ENGGRPDAYPREV_B:
      case bGET_ENGGRPDAYPREV_A:

      case bGET_ENGGRPDAYCURR_ABCD:
      case bGET_ENGGRPDAYCURR_CD:
      case bGET_ENGGRPDAYCURR_B:
      case bGET_ENGGRPDAYCURR_A:

      case bGET_ENGGRPMONPREV_ABCD:
      case bGET_ENGGRPMONPREV_CD:
      case bGET_ENGGRPMONPREV_B:
      case bGET_ENGGRPMONPREV_A:

      case bGET_ENGGRPMONCURR_ABCD:
      case bGET_ENGGRPMONCURR_CD:
      case bGET_ENGGRPMONCURR_B:
      case bGET_ENGGRPMONCURR_A:

      case bGET_POWGRPCURRMNT:  key_GetSingle(GROUPS);  break;

      case bGET_POWCANPREVHOU:
      case bGET_POWCANCURRHOU:

      case bGET_ENGCANDAYPREV_ABCD:
      case bGET_ENGCANDAYPREV_CD:
      case bGET_ENGCANDAYPREV_B:
      case bGET_ENGCANDAYPREV_A:

      case bGET_ENGCANDAYCURR_ABCD:
      case bGET_ENGCANDAYCURR_CD:
      case bGET_ENGCANDAYCURR_B:
      case bGET_ENGCANDAYCURR_A:

      case bGET_ENGCANMONPREV_ABCD:
      case bGET_ENGCANMONPREV_CD:
      case bGET_ENGCANMONPREV_B:
      case bGET_ENGCANMONPREV_A:

      case bGET_ENGCANMONCURR_ABCD:
      case bGET_ENGCANMONCURR_CD:
      case bGET_ENGCANMONCURR_B:
      case bGET_ENGCANMONCURR_A:

      case bGET_POWCANCURRMNT:  key_GetSingle2();       break;

      case bGET_ENGGRPYEAR_ABCD:
      case bGET_ENGGRPYEAR_CD:
      case bGET_ENGGRPYEAR_B:
      case bGET_ENGGRPYEAR_A:  key_GetValuesYear(GROUPS); break;

      case bGET_CNTCANYEAR1:
      case bGET_CNTCANYEAR10:
      case bGET_CNTCANYEAR2:
      case bGET_CNTCANYEAR20:  key_GetValuesYear(CANALS); break;

      case wGET_CNTCANYEAR6:    key_GetCntCanYear6();   break;

      case bRUN_PROFILE:        key_RunProfile();       break;

      case bGET_PROGRAM73:      key_GetOldProgram73();  break;
      case bGET_PROGRAM74:      key_GetOldProgram74();  break;

      case bSET_DECRET:         key_SetDecret();        break;
      case bSET_WINTER:
      case bSET_SUMMER:         key_SetSeason();        break;

      case bTEST_DIRECT:        key_TestDirect();       break;

      case bTEST_RESPONSE:      key_TestResponse();     break;
      case bTEST_FLOW:          key_TestFlow();         break;
      case bTEST_PORTS_IO:      key_TestPortsIO();      break;
      case bTEST_UNI:           key_TestUni();          break;
      case bTEST_FLASH:         key_TestFlash();        break;

      case bTEST_IMPULSES:      key_TestImpulses();     break;
      case bTEST_KEYS:          key_TestKeys();         break;
      case bTEST_RTC:           key_TestRTC();          break;


      case wSET_HIDE_MESSAGES:  key_SetHideMessages();  break;

      case wSET_GAPS_FLAG:      key_SetGapsFlag();      break;
      case wSET_GAPS:           key_SetGaps();          break;

      case wSET_SHORT_PROFILE_C:key_SetShortProfileC(); break;
      case wSET_DSBL_REFILL:    key_SetDsblRefill();    break;
      case wSET_MAX_REPEATS:    key_SetMaxRepeats();    break;

      case wSET_DSBL_ESC:       key_SetDsblEsc();       break;

      case wSET_STRICT_UNI:         key_SetStrictUni();        break;
      case wSET_DSBL_PASSWORD_UNI:  key_SetDsblPasswordUni();  break;
      case wSET_MAX_DELAY_UNI:      key_SetMaxDelayUni();      break;
      case wSET_REPEAT_FLOW_UNI:    key_SetRepeatFlowUni();    break;

      case wSET_MNT_ESC_S:      key_SetMntEscS();       break;

      case bSET_EXT4_FLAG:      key_SetExt4Flag();      break;
      case bSET_EXT4_MONTHS:    key_SetExt4Months();    break;
      case bSET_EXT4_ENBL_CAN:  key_SetExt4EnblCan();   break;

      case wSET_EXT4T_FLAG:     key_SetExt4TFlag();     break;
      case wSET_EXT4T_MONTHS:   key_SetExt4TMonths();   break;

      default:                  NoProgram();            break;
    }
  }

  else if (enGlobal == GLB_REPROGRAM)
  {
    switch (wProgram)
    {
      case bSET_SPEED:          key_SetSpeeds();        break;

      case bSET_CURRTIME:       key_SetCurrTime();      break;
      case bSET_CURRDATE:       key_SetCurrDate();      break;

      case bSET_GROUPS:         key_SetGroups();        break;

      case bSET_DAY_ZONE:       key_SetDayZone();       break;
      case bSET_PUBLIC_TARIFFS: key_SetPublicTariffs(); break;
      case bSET_TARIFFS_MODE:   key_SetTariffsMode();   break;

      case bSET_PROGRAM10:
      case bSET_PROGRAM17:
      case bSET_PROGRAM20:
      case bSET_PROGRAM27:      key_SetOldYearZone();   break;

      case bSET_RELAXS_FLAG:    key_SetRelaxsFlag();    break;
      case bSET_RELAXS_TARIFF:  key_SetRelaxsTariff();  break;
      case bSET_RELAXS:         key_SetRelaxs();        break;

      case bSET_PASSWORD:       key_SetPassword();      break;
      case bSET_LOGICAL:        key_SetLogical();       break;
      case bSET_PRIVATE:        key_SetPrivate();       break;

      case bSET_START:          key_Restart();          break;

      case bSET_VERSION:        key_GetVersion();       break;

      case bSET_RESETCUSTOM:
      case bSET_RESETFULL:      key_SetReset();         break;

      case bSEARCH_BY_NUMBER:   key_SearchByNumber();   break;
      case bSEARCH_BY_SPEED:    key_SearchBySpeed();    break;

      case bSET_AUTOMATIC1:     key_Automatic1();       break;
      case bSET_AUTOMATIC2:     key_Automatic2();       break;

      case bSET_MAJOR_DELAYS:
      case bSET_MINOR_DELAYS:   key_SetDelays();        break;

      case bSET_DIGITALS:       key_SetDigitals();      break;
      case bSET_ENBL_HOURS:     key_SetEnblHours();     break;
      case bSET_CONTROL_HOURS:  key_SetCtrlHours();     break;
      case bSET_ENBL_CANALS:    key_SetEnblCanals();    break;

      case bSET_ENBL_PARAMS:    key_SetEnblParams();    break;
      case bSET_MNT_PARAMS:     key_SetMntParams();     break;
      case bSET_PARAMS:         key_SetParams();        break;
      case bSET_PARAMS_DIV:     key_SetParamsDiv();     break;
      case bGET_PARAMS_CURR:
      case bGET_PARAMS_BUFF:
      case bGET_PARAMS_FULL:    key_GetParamsAll();     break;
      case wSET_FIX_PARAMS_BUGS:key_SetFixParamsBugs(); break;
      case wSET_USE_PARAMS_DIV: key_SetUseParamsDiv();  break;

      case bSET_LIMITS:         key_SetLimits();        break;
      case bSET_LIMITS2:        key_SetLimits2();       break;
      case bSET_LIMITS30:       key_SetLimits30();      break;
      case bSET_LIMITS31:       key_SetLimits31();      break;
      case bSET_LIMITS32:       key_SetLimits32();      break;
      case bSET_LIMITS33:       key_SetLimits33();      break;

      case bSET_FLOW_PORT_TO:   key_FlowPortTo();       break;
      case bSET_MAX_FLOW_DELAY: key_SetMaxFlowDelay();  break;
      case bSET_FLOW_PORT_FROM: key_FlowPortFrom();     break;

      case bSET_ENBL_CURRENT:   key_SetEnblCurrent();   break;
      case bSET_ENBL_PROFILE:   key_SetEnblProfile();   break;
      case bSET_TIMEOUT_PROFILE:key_SetTimeoutProfile();break;
      case bSET_TIMEOUT_CURRENT:key_SetTimeoutCurrent();break;
      case bSET_CONTROL_TIME:   key_SetControlTime();   break;
      case bSET_MANAGE_TIME:    key_SetManageTime();    break;

      case bSET_EXTENDED_ESC_S: key_SetExtendedEscS();  break;
      case bSET_EXTENDED_ESC_V: key_SetExtendedEscV();  break;
      case bSET_EXTENDED_ESC_U: key_SetExtendedEscU();  break;

      case bSET_ADDRESSES:      key_SetAddresses();     break;
      case bSET_ENBL_KEYS:      key_SetEnblKeys();      break;
      case bSET_KEYS:           key_SetKeys();          break;
      case wSET_KEYS_LEVEL_B:   key_SetKeysLevelB();    break;

      case bSET_PHONES:         key_SetPhones();        break;
      case bSET_MAX_CONNECT:    key_SetMaxConnect();    break;
      case bSET_CUSTOM_MODEM:   key_SetCustomModem();   break;

      case bSET_SHOW_MESSAGES:  key_SetShowMessages();  break;

      case bSET_SEPARATE_CAN:   key_SetSeparateCan();   break;

      case bSET_RECALC:         key_SetRecalc();        break;
      case bSET_RECALC_ALWAYS:  key_SetRecalcAlways();  break;

      case bGET_CNTCURR_110:
      case bGET_READTIMEDATE1:
      case bGET_READTIMEDATE2:  key_GetSingle(CANALS);  break;

      case bSET_DECRET:         key_SetDecret();        break;
      case bSET_WINTER:
      case bSET_SUMMER:         key_SetSeason();        break;

      case bTEST_DIRECT:        key_TestDirect();       break;

      case bTEST_RESPONSE:      key_TestResponse();     break;
      case bTEST_FLOW:          key_TestFlow();         break;
      case bTEST_PORTS_IO:      key_TestPortsIO();      break;
      case bTEST_UNI:           key_TestUni();          break;
      case bTEST_FLASH:         key_TestFlash();        break;

      case bTEST_IMPULSES:      key_TestImpulses();     break;
      case bTEST_KEYS:          key_TestKeys();         break;
      case bTEST_RTC:           key_TestRTC();          break;


      case wSET_HIDE_MESSAGES:  key_SetHideMessages();  break;

      case wSET_GAPS_FLAG:      key_SetGapsFlag();      break;
      case wSET_GAPS:           key_SetGaps();          break;

      case wSET_SHORT_PROFILE_C:key_SetShortProfileC(); break;
      case wSET_DSBL_REFILL:    key_SetDsblRefill();    break;
      case wSET_MAX_REPEATS:    key_SetMaxRepeats();    break;

      case wSET_DSBL_ESC:       key_SetDsblEsc();       break;

      case wSET_STRICT_UNI:         key_SetStrictUni();        break;
      case wSET_DSBL_PASSWORD_UNI:  key_SetDsblPasswordUni();  break;
      case wSET_MAX_DELAY_UNI:      key_SetMaxDelayUni();      break;
      case wSET_REPEAT_FLOW_UNI:    key_SetRepeatFlowUni();    break;

      case wSET_MNT_ESC_S:      key_SetMntEscS();       break;

      case bSET_EXT4_FLAG:      key_SetExt4Flag();      break;
      case bSET_EXT4_MONTHS:    key_SetExt4Months();    break;
      case bSET_EXT4_ENBL_CAN:  key_SetExt4EnblCan();   break;

      case wSET_EXT4T_FLAG:     key_SetExt4TFlag();     break;
      case wSET_EXT4T_MONTHS:   key_SetExt4TMonths();   break;
      case wSET_EXT4T_RESET1:   key_SetExt4TReset1();   break;
      case wSET_EXT4T_RESET2:   key_SetExt4TReset2();   break;

      default:                  NoProgram();            break;
    }
  }
}
