/*------------------------------------------------------------------------------
KEYBOARD_KEY!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../include/programs.h"
#include "keyboard.h"
#include "key_speeds.h"
#include "time/key_timedate.h"
#include "time/key_correct.h"
#include "key_password.h"
#include "key_logical.h"
#include "key_private.h"
#include "key_start.h"
#include "key_version.h"
#include "digitals/key_digitals.h"
#include "digitals/schedule/key_enbl_hours.h"
#include "digitals/schedule/key_ctrl_hours.h"
#include "digitals/schedule/key_recalc_time.h"
#include "digitals/schedule/key_recalc_always.h"
#include "digitals/schedule/key_recalc3.h"
#include "digitals/schedule/key_recalc.h"
#include "digitals/key_enbl_canals.h"
#include "digitals/current/key_enbl_current.h"
#include "digitals/current/key_enbl_current2.h"
#include "digitals/profile/key_enbl_profile.h"
#include "digitals/current/key_timeout_current.h"
#include "digitals/profile/key_timeout_profile.h"
#include "digitals/key_addresses.h"
#include "digitals/key_enbl_keys.h"
#include "digitals/key_keys.h"
#include "digitals/key_serials_manual.h"
#include "digitals/key_serials1.h"
#include "digitals/key_serials2.h"
#include "sensors/key_keys_level_b.h"
#include "digitals/key_search.h"
#include "digitals/key_automatic.h"
#include "digitals/profile/key_run_profile.h"
#include "digitals/key_show_messages.h"
#include "digitals/key_separate_can.h"
#include "key_enbl_wdt.h"
#include "digitals/profile/key_control_time.h"
#include "digitals/profile/key_manage_time.h"
#include "digitals/profile/key_limits.h"
#include "digitals/profile/key_limits2.h"
#include "digitals/profile/key_limits30.h"
#include "digitals/profile/key_limits31.h"
#include "digitals/profile/key_limits32.h"
#include "digitals/profile/key_limits33.h"
#include "digitals/profile/key_profile_interval.h"
#include "digitals/profile/key_profile_interval_direct.h"
#include "digitals/profile/key_profile_interval_modem.h"
#include "digitals/extended/key_enbl_diagram.h"
#include "phones/key_modems2.h"
#include "phones/key_phones.h"
#include "phones/key_max_connect.h"
#include "phones/key_custom_modem.h"
#include "phones/key_modem_atdp.h"
#include "phones2/key_phones20.h"
#include "phones2/key_phones21.h"
#include "phones2/key_phones22.h"
#include "phones2/key_phones23.h"
#include "time/key_decret.h"
#include "time/key_season.h"
#include "key_groups.h"
#include "tariffs/key_dayzone.h"
#include "tariffs/key_public_tariffs.h"
#include "tariffs/key_oldyearzone.h"
#include "tariffs/key_tariffs_mode.h"
#include "tariffs/key_oldprogram5.h"
#include "tariffs/key_relaxs_flag.h"
#include "tariffs/key_relaxs_tariff.h"
#include "tariffs/key_relaxs.h"
#include "key_factors.h"
#include "key_delays.h"
#include "impulses/key_single_can.h"
#include "impulses/key_single_grp.h"
#include "impulses/key_single2.h"
#include "impulses/key_eng_year.h"
#include "impulses/key_cnt_year.h"
#include "impulses/key_oldprogram73.h"
#include "impulses/key_oldprogram74.h"
#include "impulses/key_clear_canals.h"
#include "impulses/key_set_profiles.h"
#include "key_reset.h"
#include "key_reset_wdt.h"
#include "test/key_test_uart.h"
#include "test/key_test_direct.h"
#include "test/key_test_request.h"
#include "test/key_test_response.h"
#include "test/key_test_flow.h"
#include "test/key_test_ports_io.h"
#include "test/key_test_uni.h"
#include "serial/key_monitor_log_basic.h"
#include "serial/key_monitor_log_hex.h"
#include "serial/key_monitor_log_char7.h"
#include "serial/key_monitor_log_char8.h"
#include "serial/key_monitor_open.h"
#include "test/key_test_monitor.h"
#include "test/key_test_impulses.h"
#include "test/key_test_keys.h"
#include "test/key_test_rtc.h"
#include "test/key_test_power_off.h"
#include "tariffs/key_gaps_flag.h"
#include "tariffs/key_gaps.h"
#include "digitals/key_hide_messages.h"
#include "sensors/key_control_q.h"
#include "sensors/key_control_k.h"
#include "sensors/key_short_profile_c.h"
#include "digitals/profile/key_dsbl_refill.h"
#include "digitals/key_dsbl_answer.h"
#include "digitals/key_max_repeats.h"
#include "digitals/key_max_shutdown.h"
#include "sensors/key_control_w.h"
#include "sensors/key_time_zone34.h"
#include "sensors/key_max_timer35.h"
#include "sensors/key_ignore_status38.h"
#include "sensors/key_short_profile_b.h"
#include "sensors/key_modem_disconnet_bd.h"
#include "digitals/review/key_review_flag.h"
#include "digitals/review/key_review_can.h"
#include "digitals/review/key_review_read_id.h"
#include "digitals/review/key_review_repeats.h"
#include "digitals/review/key_review_borders.h"
#include "digitals/review/key_review_margins.h"
#include "digitals/review/key_review_wrn_trend.h"
#include "digitals/review/key_review_wrn_top.h"
#include "digitals/schedule/key_auto_flow_enbl.h"
#include "digitals/schedule/key_auto_flow_hours.h"
#include "digitals/key_dsbl_esc.h"
#include "key_records_dsbl.h"
#include "esc/key_machines_esc.h"
#include "esc/key_block_esc.h"
#include "serial/key_input_mode_reset.h"
#include "serial/key_slave_modem.h"
#include "../serial/bulk.h"
#include "serial/key_bulk_enbl.h"
#include "serial/key_bulk_size.h"
#include "serial/key_bulk_max_delay.h"
#include "unified/key_strict_uni.h"
#include "unified/key_enbl_pass_uni.h"
#include "unified/key_max_delay_uni.h"
#include "unified/key_repeat_flow_uni.h"
#include "digitals/key_mnt_esc_s.h"
#include "digitals/key_correct_limit.h"
#include "digitals/key_extended_esc.h"
#include "serial/key_flow.h"
#include "serial/key_max_flow_delay.h"
#include "serial/key_output_delay.h"
#include "serial/key_tx_delay.h"
#include "digitals/params/key_params_flag.h"
#include "digitals/params/key_mnt_params.h"
#include "digitals/params/key_params.h"
#include "digitals/params/key_params_div.h"
#include "digitals/params/key_params_all.h"
#include "digitals/params/key_fix_params_bugs.h"
#include "digitals/params/key_use_params_div.h"
#include "devices/key_ext_0_flag.h"
#include "devices/key_ext_0_counter.h"
#include "devices/key_ext_3_reset.h"
#include "devices/key_ext_3_flag.h"
#include "devices/key_ext_3_a.h"
#include "devices/key_ext_3_b.h"
#include "devices/key_ext_4_flag.h"
#include "devices/key_ext_4_months.h"
#include "devices/key_ext_4_enbl_can.h"
#include "devices/key_ext_4t_flag.h"
#include "devices/key_ext_4t_months.h"
#include "devices/key_ext_4t_reset_full.h"
#include "devices/key_ext_4t_reset_custom.h"
#include "devices/key_ext_5_flag.h"
#include "devices/key_ext_6_flag.h"
#include "digitals/key_skip_failure_enbl.h"
#include "digitals/key_skip_failure_repeats.h"
#include "time/key_correct2_flag.h"
#include "time/key_correct3_flag.h"
#include "time/key_correct3_value.h"
#include "time/key_correct3_info.h"
#include "sensors/key_plc_u_flag.h"
#include "sensors/key_plc_u_size.h"
#include "sensors/key_plc_u_shutdown.h"
#include "sensors/key_device19.h"
#include "gps/key_gps_config.h"
#include "gps/key_gps_data.h"
#include "gps/key_gps_gmt.h"
#include "gps/key_gps_correct.h"
#include "gps/key_gps_schedule.h"
#include "gps/key_gps_season.h"
#include "key_health.h"



#include "digitals/address/key_ascii_addresses.h"



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

      case bSET_START_MINUTES30:
      case bSET_START:          key_Start();            break;

      case bSET_DEBUG:          key_Debug();            break;

      case bSET_VERSION:        key_GetVersion();       break;

      case bSET_RESETCUSTOM:
      case bSET_RESETFULL:      key_SetReset();         break;

      case bSET_RESET_WDT:      key_ResetWatchdog();         break;

      case bSEARCH_BY_NUMBER:   key_SearchByNumber();   break;
      case bSEARCH_BY_SPEED:    key_SearchBySpeed();    break;

      case bSET_AUTOMATIC1:     key_Automatic1();       break;
      case bSET_AUTOMATIC2:     key_Automatic2();       break;

      case bSET_MAJOR_DELAYS:
      case bSET_MINOR_DELAYS:   key_SetDelays();        break;

      case bSET_PHONES20:       key_SetPhones20();      break;
      case bSET_PHONES21:       key_SetPhones21();      break;
      case bSET_PHONES22:       key_SetPhones22();      break;
      case bSET_PHONES23:       key_SetPhones23();      break;

      case bSET_CORRECT2_FLAG:  key_SetCorrect2Flag();  break;
      case bSET_CORRECT3_FLAG:  key_SetCorrect3Flag();  break;
      case bSET_CORRECT3_VALUE: key_SetCorrect3Value(); break;
      case bSET_CORRECT3_INFO:  key_SetCorrect3Info();  break;

      case bSET_DIGITALS:       key_SetDigitals();      break;
      case bSET_ENBL_HOURS:     key_SetEnblHours();     break;
      case bSET_CONTROL_HOURS:  key_SetCtrlHours();     break;
      case bSET_ENBL_CANALS:    key_SetEnblCanals();    break;

      case bSET_PARAMS_FLAG:    key_SetParamsFlag();    break;
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

      case bSET_GPS_CONFIG:     key_SetGpsConfig();     break;
      case bSET_GPS_GMT:        key_SetGpsGmt();        break;
      case bGET_GPS_DATA:       key_GetGpsData();       break;
      case bGET_GPS_CORRECT:    key_GetGpsCorrect();    break;
      case bSET_GPS_SCHEDULE:   key_SetGpsSchedule();   break;
      case bSET_GPS_SEASON:     key_SetGpsSeason();     break;

      case bSET_FLOW_PORT_TO:   key_FlowPortTo();       break;
      case bSET_MAX_FLOW_DELAY: key_SetMaxFlowDelay();  break;
      case bSET_FLOW_PORT_FROM: key_FlowPortFrom();     break;

      case bSET_ENBL_CURRENT:   key_SetEnblCurrent();   break;
      case bSET_ENBL_CURRENT2:  key_SetEnblCurrent2();  break;
      case bSET_ENBL_PROFILE:   key_SetEnblProfile();   break;
      case bSET_TIMEOUT_PROFILE:key_SetTimeoutProfile();break;
      case bSET_TIMEOUT_CURRENT:key_SetTimeoutCurrent();break;
      case bSET_CONTROL_TIME:   key_SetControlTime();   break;
      case bSET_MANAGE_TIME:    key_SetManageTime();    break;

      case bSET_MACHINES_ESC:   key_SetMachinesEsc();   break;
      case bSET_BLOCK_ESC:      key_SetBlockEsc();      break;

      case bSET_EXTENDED_ESC_S: key_SetExtendedEscS();  break;
      case bSET_EXTENDED_ESC_V: key_SetExtendedEscV();  break;
      case bSET_EXTENDED_ESC_U: key_SetExtendedEscU();  break;

      case bSET_ADDRESSES:      key_SetAddresses();     break;
      case bSET_ASCII_ADDRESSES:key_SetAsciiAddresses();break;
      case bSET_ENBL_KEYS:      key_SetEnblKeys();      break;
      case bSET_KEYS:           key_SetKeys();          break;
      case wSET_KEYS_LEVEL_B:   key_SetKeysLevelB();    break;
      case bSET_SERIALS_MANUAL: key_SetSerialsManual(); break;
      case bSET_SERIALS1:       key_SetSerials1();      break;
      case bSET_SERIALS2:       key_SetSerials2();      break;

      case bGET_MODEMS_QUALITY: key_GetModemsQuality(); break;
      case bSET_PHONES:         key_SetPhones();        break;
      case bSET_MAX_CONNECT:    key_SetMaxConnect();    break;
      case bSET_CUSTOM_MODEM:   key_SetCustomModem();   break;
      case bSET_MODEM_ATDP:     key_SetModemATDP();     break;

      case bSET_SHOW_MESSAGES:  key_SetShowMessages();  break;

      case bSET_SEPARATE_CAN:   key_SetSeparateCan();   break;
      case bSET_ENBL_WDT:       key_SetEnblWDT();       break;

      case bSET_RECALC_TIME:    key_SetRecalcTime();    break;
      case bSET_RECALC_ALWAYS:  key_SetRecalcAlways();  break;
      case wSET_RECALC_3:       key_SetRecalc3();       break;

      case bGET_CNTCURR_110:
      case bGET_READTIMEDATE1:
      case bGET_READTIMEDATE2:  key_GetSingleCan();     break;

      case bSET_DECRET:         key_SetDecret();        break;
      case bSET_WINTER:
      case bSET_SUMMER:         key_SetSeason();        break;

      case bTEST_DIRECT:        key_TestDirect();       break;

      case bTEST_UART:          key_TestUART();         break;
      case bTEST_REQUEST:       key_TestRequest();      break;
      case bTEST_RESPONSE:      key_TestResponse();     break;
      case bTEST_FLOW:          key_TestFlow();         break;
      case bTEST_PORTS_IO:      key_TestPortsIO();      break;
      case bTEST_UNI:           key_TestUni();          break;

      case wSET_MONITOR_LOG_BASIC: key_MonitorLogBasic(); break;
      case wSET_MONITOR_LOG_HEX:   key_MonitorLogHex();   break;
      case wSET_MONITOR_LOG_CHAR7: key_MonitorLogChar7(); break;
      case wSET_MONITOR_LOG_CHAR8: key_MonitorLogChar8(); break;
      case wSET_MONITOR_OPEN:   key_MonitorOpen();      break;
      case wTEST_MONITOR:       key_TestMonitor();      break;

      case bTEST_IMPULSES:      key_TestImpulses();     break;
      case bTEST_KEYS:          key_TestKeys();         break;
      case bTEST_RTC:           key_TestRTC();          break;
      case bTEST_POWER_OFF:     key_TestPowerOff();     break;


      case wSET_OUTPUT_DELAY:   key_SetOutputDelay();   break;
      case wSET_TX_DELAY:       key_SetTxDelay();       break;
      case wSET_HIDE_MESSAGES:  key_SetHideMessages();  break;

      case wSET_GAPS_FLAG:      key_SetGapsFlag();      break;
      case wSET_GAPS:           key_SetGaps();          break;

      case wSET_CONTROL_Q:      key_SetControlQ();      break;
      case wSET_CONTROL_K:      key_SetControlK();      break;
      case wSET_SHORT_PROFILE_C:key_SetShortProfileC(); break;
      case wSET_DSBL_REFILL:    key_SetDsblRefill();    break;
      case wSET_DSBL_ANSWER:    key_SetDsblAnswer();    break;
      case wSET_MAX_REPEATS:    key_SetMaxRepeats();    break;
      case wSET_MAX_SHUTDOWN:   key_SetMaxShutdown();   break;
      case wSET_CONTROL_W:      key_SetControlW();      break;
      case wSET_ENBL_DIAGRAM:   key_SetEnblDiagram();   break;
      case wSET_SKIP_FAILURE_ENBL: key_SetSkipFailureEnbl(); break;
      case wSET_SKIP_FAILURE_REPEATS: key_SetSkipFailureRepeats(); break;
      case wSET_TIME_ZONE_34:   key_SetTimeZone34();    break;
      case wSET_MAX_TIMER_35:   key_SetMaxTimer35();    break;
      case wSET_IGNORE_STATUS_38: key_SetIgnoreStatus38(); break;
      case wSET_SHORT_PROFILE_B:key_SetShortProfileB(); break;
      case wSET_MODEM_DISCONNECT_BD:key_SetModemDisconnectBD(); break;

      case wSET_PROFILE_INTERVAL: key_SetProfileInterval(); break;
      case wSET_PROFILE_INTERVAL_DIRECT: key_SetProfileIntervalDirect(); break;
      case wSET_PROFILE_INTERVAL_MODEM: key_SetProfileIntervalModem(); break;

      case wSET_REVIEW_FLAG:    key_SetReviewFlag();    break;
      case wSET_REVIEW_CAN:     key_SetReviewCan();     break;
      case wSET_REVIEW_READ_ID: key_SetReviewReadId();  break;
      case wSET_REVIEW_REPEATS: key_SetReviewRepeats(); break;
      case wSET_REVIEW_BORDERS: key_SetReviewBorders(); break;
      case wSET_REVIEW_MARGINS: key_SetReviewMargins(); break;
      case wSET_REVIEW_WRN_PERCENT: key_SetReviewWrnPercent(); break;
      case wSET_REVIEW_WRN_TOP: key_SetReviewWrnTop(); break;

      case wSET_AUTO_FLOW_ENBL: key_SetAutoFlowEnbl();  break;
      case wSET_AUTO_FLOW_HOURS:key_SetAutoFlowHours(); break;

      case wSET_DSBL_ESC:       key_SetDsblEsc();       break;

      case wSET_RECORDS_DSBL:   key_SetRecordsDsbl();   break;

      case wSET_PLC_U_FLAG:     key_SetPlcUFlag();      break;
      case wSET_PLC_U_SIZE:     key_SetPlcUSize();      break;
      case wSET_PLC_U_SHUTDOWN: key_SetPlcUShutdown();  break;

      case bGET_DEVICE19_LONG:  key_GetDevice19Long();  break;
      case bGET_DEVICE19_DOUBLE:key_GetDevice19Double();break;

      case wSET_INPUT_MODE_RESET: key_SetInputModeReset(); break;
      case bSET_SLAVE_MODEM: key_SetSlaveModem(); break;

#ifdef ENABLE_BULK
      case wSET_BULK_ENBL: key_SetBulkEnable(); break;
      case wSET_BULK_SIZE: key_SetBulkSize(); break;
      case wSET_BULK_MAX_DELAY: key_SetBulkMaxDelay(); break;
#endif

      case wSET_STRICT_UNI:         key_SetStrictUni();        break;
      case wSET_ENBL_PASS_UNI:      key_SetEnblPassUni();      break;
      case wSET_MAX_DELAY_UNI:      key_SetMaxDelayUni();      break;
      case wSET_REPEAT_FLOW_UNI:    key_SetRepeatFlowUni();    break;

      case wSET_MNT_ESC_S:      key_SetMntEscS();       break;
      case wSET_CORRECT_LIMIT:  key_SetCorrectLimit();  break;

      case wSET_EXT0_FLAG:      key_SetExt0Flag();      break;
      case wSET_EXT0_COUNTER:   key_SetExt0Counter();   break;

      case bSET_EXT3_RESET:     key_SetExt3Reset();     break;
      case bSET_EXT3_FLAG:      key_SetExt3Flag();      break;
      case bSET_EXT3_EVENTS_A:  key_SetExt3A();         break;
      case bSET_EXT3_EVENTS_B:  key_SetExt3B();         break;

      case bSET_EXT4_FLAG:      key_SetExt4Flag();      break;
      case bSET_EXT4_MONTHS:    key_SetExt4Months();    break;
      case bSET_EXT4_ENBL_CAN:  key_SetExt4EnblCan();   break;

      case wSET_EXT4T_FLAG:         key_SetExt4TFlag();        break;
      case wSET_EXT4T_MONTHS:       key_SetExt4TMonths();      break;
      case wSET_EXT4T_RESET_FULL:   key_SetExt4TResetFull();   break;
      case wSET_EXT4T_RESET_CUSTOM: key_SetExt4TResetCustom(); break;

      case bSET_EXT5_FLAG:      key_SetExt5Flag();      break;

      case wSET_EXT6_FLAG:      key_SetExt6Flag();      break;

      case wGET_HEALTH:         key_GetHealth();        break;

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

      case bGET_CORRECT_TIME:   key_CorrectTime();      break;
      case bGET_CORRECTCURR:    key_GetCorrectCurr();   break;
      case bGET_CORRECTPREV:    key_GetCorrectPrev();   break;

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

      case bGET_PROGRAM18:      key_GetProgram18();     break;
      case bGET_PROGRAM19:      key_GetProgram19();     break;

      case bSET_PASSWORD:       key_GetPassword();      break;
      case bSET_LOGICAL:        key_SetLogical();       break;
      case bSET_PRIVATE:        key_SetPrivate();       break;

      case bSET_VERSION:
      case bGET_VERSION:        key_GetVersion();       break;

      case bSET_MAJOR_DELAYS:
      case bSET_MINOR_DELAYS:   key_SetDelays();        break;

      case bSET_PHONES20:       key_SetPhones20();      break;
      case bSET_PHONES21:       key_SetPhones21();      break;
      case bSET_PHONES22:       key_SetPhones22();      break;
      case bSET_PHONES23:       key_SetPhones23();      break;

      case bSET_CORRECT2_FLAG:  key_SetCorrect2Flag();  break;
      case bSET_CORRECT3_FLAG:  key_SetCorrect3Flag();  break;
      case bSET_CORRECT3_VALUE: key_SetCorrect3Value(); break;
      case bSET_CORRECT3_INFO:  key_SetCorrect3Info();  break;

      case bSET_DIGITALS:       key_SetDigitals();      break;
      case bSET_ENBL_HOURS:     key_SetEnblHours();     break;
      case bSET_CONTROL_HOURS:  key_SetCtrlHours();     break;
      case bSET_ENBL_CANALS:    key_SetEnblCanals();    break;

      case bSET_PARAMS_FLAG:    key_SetParamsFlag();    break;
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

      case bSET_GPS_CONFIG:     key_SetGpsConfig();     break;
      case bSET_GPS_GMT:        key_SetGpsGmt();        break;
      case bGET_GPS_DATA:       key_GetGpsData();       break;
      case bGET_GPS_CORRECT:    key_GetGpsCorrect();    break;
      case bSET_GPS_SCHEDULE:   key_SetGpsSchedule();   break;
      case bSET_GPS_SEASON:     key_SetGpsSeason();     break;

      case bSET_FLOW_PORT_TO:   key_FlowPortTo();       break;
      case bSET_MAX_FLOW_DELAY: key_SetMaxFlowDelay();  break;
      case bSET_FLOW_PORT_FROM: key_FlowPortFrom();     break;

      case bSET_ENBL_CURRENT:   key_SetEnblCurrent();   break;
      case bSET_ENBL_CURRENT2:  key_SetEnblCurrent2();  break;
      case bSET_ENBL_PROFILE:   key_SetEnblProfile();   break;
      case bSET_TIMEOUT_PROFILE:key_SetTimeoutProfile();break;
      case bSET_TIMEOUT_CURRENT:key_SetTimeoutCurrent();break;
      case bSET_CONTROL_TIME:   key_SetControlTime();   break;
      case bSET_MANAGE_TIME:    key_SetManageTime();    break;

      case bSET_MACHINES_ESC:   key_SetMachinesEsc();   break;
      case bSET_BLOCK_ESC:      key_SetBlockEsc();      break;

      case bSET_EXTENDED_ESC_S: key_SetExtendedEscS();  break;
      case bSET_EXTENDED_ESC_V: key_SetExtendedEscV();  break;
      case bSET_EXTENDED_ESC_U: key_SetExtendedEscU();  break;

      case bSET_ADDRESSES:      key_SetAddresses();     break;
      case bSET_ASCII_ADDRESSES:key_SetAsciiAddresses();break;
      case bSET_ENBL_KEYS:      key_SetEnblKeys();      break;
      case bSET_KEYS:           key_SetKeys();          break;
      case wSET_KEYS_LEVEL_B:   key_SetKeysLevelB();    break;
      case bSET_SERIALS_MANUAL: key_SetSerialsManual(); break;
      case bSET_SERIALS1:       key_SetSerials1();      break;
      case bSET_SERIALS2:       key_SetSerials2();      break;

      case bGET_MODEMS_QUALITY: key_GetModemsQuality(); break;
      case bSET_PHONES:         key_SetPhones();        break;
      case bSET_MAX_CONNECT:    key_SetMaxConnect();    break;
      case bSET_CUSTOM_MODEM:   key_SetCustomModem();   break;
      case bSET_MODEM_ATDP:     key_SetModemATDP();     break;

      case bSET_SHOW_MESSAGES:  key_SetShowMessages();  break;

      case bSET_SEPARATE_CAN:   key_SetSeparateCan();   break;
      case bSET_ENBL_WDT:       key_SetEnblWDT();       break;

      case bSET_RECALC_TIME:    key_SetRecalcTime();    break;
      case bSET_RECALC_ALWAYS:  key_SetRecalcAlways();  break;
      case wSET_RECALC_3:       key_SetRecalc3();       break;

      case bGET_CNTCURR_10:
      case bGET_CNTCURR_110:
      case bGET_READTIMEDATE1:
      case bGET_READTIMEDATE2:
      case bGET_IMPCANCURRMNT:  key_GetSingleCan();     break;

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

      case bGET_POWGRPCURRMNT:  key_GetSingleGrp();     break;

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
      case bGET_ENGGRPYEAR_A:   key_GetEngYear(); break;

      case bGET_CNTCANYEAR1:
      case bGET_CNTCANYEAR10:
      case bGET_CNTCANYEAR2:
      case bGET_CNTCANYEAR20:
      case wGET_CNTCANYEAR3:    key_GetCntYear(); break;

      case bRUN_PROFILE:        key_RunProfile();       break;

      case bGET_PROGRAM73:      key_GetOldProgram73();  break;
      case bGET_PROGRAM74:      key_GetOldProgram74();  break;

      case bSET_DECRET:         key_SetDecret();        break;
      case bSET_WINTER:
      case bSET_SUMMER:         key_SetSeason();        break;

      case bTEST_DIRECT:        key_TestDirect();       break;

      case bTEST_REQUEST:       key_TestRequest();      break;
      case bTEST_RESPONSE:      key_TestResponse();     break;
      case bTEST_FLOW:          key_TestFlow();         break;
      case bTEST_PORTS_IO:      key_TestPortsIO();      break;
      case bTEST_UNI:           key_TestUni();          break;

      case wSET_MONITOR_LOG_BASIC: key_MonitorLogBasic(); break;
      case wSET_MONITOR_LOG_HEX:   key_MonitorLogHex();   break;
      case wSET_MONITOR_LOG_CHAR7: key_MonitorLogChar7(); break;
      case wSET_MONITOR_LOG_CHAR8: key_MonitorLogChar8(); break;
      case wSET_MONITOR_OPEN:   key_MonitorOpen();      break;
      case wTEST_MONITOR:       key_TestMonitor();      break;

      case bTEST_IMPULSES:      key_TestImpulses();     break;
      case bTEST_KEYS:          key_TestKeys();         break;
      case bTEST_RTC:           key_TestRTC();          break;
      case bTEST_POWER_OFF:     key_TestPowerOff();     break;


      case wSET_OUTPUT_DELAY:   key_SetOutputDelay();   break;
      case wSET_TX_DELAY:       key_SetTxDelay();       break;
      case wSET_HIDE_MESSAGES:  key_SetHideMessages();  break;

      case wSET_GAPS_FLAG:      key_SetGapsFlag();      break;
      case wSET_GAPS:           key_GetGaps();          break;

      case wSET_CONTROL_Q:      key_SetControlQ();      break;
      case wSET_CONTROL_K:      key_SetControlK();      break;
      case wSET_SHORT_PROFILE_C:key_SetShortProfileC(); break;
      case wSET_DSBL_REFILL:    key_SetDsblRefill();    break;
      case wSET_DSBL_ANSWER:    key_SetDsblAnswer();    break;
      case wSET_MAX_REPEATS:    key_SetMaxRepeats();    break;
      case wSET_MAX_SHUTDOWN:   key_SetMaxShutdown();   break;
      case wSET_CONTROL_W:      key_SetControlW();      break;
      case wSET_ENBL_DIAGRAM:   key_SetEnblDiagram();   break;
      case wSET_SKIP_FAILURE_ENBL: key_SetSkipFailureEnbl(); break;
      case wSET_SKIP_FAILURE_REPEATS: key_SetSkipFailureRepeats(); break;
      case wSET_TIME_ZONE_34:   key_SetTimeZone34();    break;
      case wSET_MAX_TIMER_35:   key_SetMaxTimer35();    break;
      case wSET_IGNORE_STATUS_38: key_SetIgnoreStatus38(); break;
      case wSET_SHORT_PROFILE_B:key_SetShortProfileB(); break;
      case wSET_MODEM_DISCONNECT_BD:key_SetModemDisconnectBD(); break;

      case wSET_PROFILE_INTERVAL: key_SetProfileInterval(); break;
      case wSET_PROFILE_INTERVAL_DIRECT: key_SetProfileIntervalDirect(); break;
      case wSET_PROFILE_INTERVAL_MODEM: key_SetProfileIntervalModem(); break;

      case wSET_REVIEW_FLAG:    key_SetReviewFlag();    break;
      case wSET_REVIEW_CAN:     key_SetReviewCan();     break;
      case wSET_REVIEW_READ_ID: key_SetReviewReadId();  break;
      case wSET_REVIEW_REPEATS: key_SetReviewRepeats(); break;
      case wSET_REVIEW_BORDERS: key_SetReviewBorders(); break;
      case wSET_REVIEW_MARGINS: key_SetReviewMargins(); break;
      case wSET_REVIEW_WRN_PERCENT: key_SetReviewWrnPercent(); break;
      case wSET_REVIEW_WRN_TOP: key_SetReviewWrnTop(); break;

      case wSET_AUTO_FLOW_ENBL: key_SetAutoFlowEnbl();  break;
      case wSET_AUTO_FLOW_HOURS:key_SetAutoFlowHours(); break;

      case wSET_DSBL_ESC:       key_SetDsblEsc();       break;

      case wSET_RECORDS_DSBL:   key_SetRecordsDsbl();   break;

      case wSET_PLC_U_FLAG:     key_SetPlcUFlag();      break;
      case wSET_PLC_U_SIZE:     key_SetPlcUSize();      break;
      case wSET_PLC_U_SHUTDOWN: key_SetPlcUShutdown();  break;

      case bGET_DEVICE19_LONG:  key_GetDevice19Long();  break;
      case bGET_DEVICE19_DOUBLE:key_GetDevice19Double();break;

      case wSET_INPUT_MODE_RESET: key_SetInputModeReset(); break;
      case bSET_SLAVE_MODEM: key_SetSlaveModem(); break;

#ifdef ENABLE_BULK
      case wSET_BULK_ENBL: key_SetBulkEnable(); break;
      case wSET_BULK_SIZE: key_SetBulkSize(); break;
      case wSET_BULK_MAX_DELAY: key_SetBulkMaxDelay(); break;
#endif

      case wSET_STRICT_UNI:         key_SetStrictUni();        break;
      case wSET_ENBL_PASS_UNI:      key_SetEnblPassUni();      break;
      case wSET_MAX_DELAY_UNI:      key_SetMaxDelayUni();      break;
      case wSET_REPEAT_FLOW_UNI:    key_SetRepeatFlowUni();    break;

      case wSET_MNT_ESC_S:      key_SetMntEscS();       break;
      case wSET_CORRECT_LIMIT:  key_SetCorrectLimit();  break;

      case wSET_EXT0_FLAG:      key_SetExt0Flag();      break;
      case wSET_EXT0_COUNTER:   key_SetExt0Counter();   break;

      case bSET_EXT3_RESET:     key_SetExt3Reset();     break;
      case bSET_EXT3_FLAG:      key_SetExt3Flag();      break;
      case bSET_EXT3_EVENTS_A:  key_SetExt3A();         break;
      case bSET_EXT3_EVENTS_B:  key_SetExt3B();         break;

      case bSET_EXT4_FLAG:      key_SetExt4Flag();      break;
      case bSET_EXT4_MONTHS:    key_SetExt4Months();    break;
      case bSET_EXT4_ENBL_CAN:  key_SetExt4EnblCan();   break;

      case wSET_EXT4T_FLAG:     key_SetExt4TFlag();     break;
      case wSET_EXT4T_MONTHS:   key_SetExt4TMonths();   break;

      case bSET_EXT5_FLAG:      key_SetExt5Flag();      break;

      case wSET_EXT6_FLAG:      key_SetExt6Flag();      break;

      case wGET_HEALTH:         key_GetHealth();        break;

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

      case bSET_RESET_WDT:      key_ResetWatchdog();         break;

      case bSEARCH_BY_NUMBER:   key_SearchByNumber();   break;
      case bSEARCH_BY_SPEED:    key_SearchBySpeed();    break;

      case bSET_AUTOMATIC1:     key_Automatic1();       break;
      case bSET_AUTOMATIC2:     key_Automatic2();       break;

      case bSET_MAJOR_DELAYS:
      case bSET_MINOR_DELAYS:   key_SetDelays();        break;

      case bSET_PHONES20:       key_SetPhones20();      break;
      case bSET_PHONES21:       key_SetPhones21();      break;
      case bSET_PHONES22:       key_SetPhones22();      break;
      case bSET_PHONES23:       key_SetPhones23();      break;

      case bSET_CORRECT2_FLAG:  key_SetCorrect2Flag();  break;
      case bSET_CORRECT3_FLAG:  key_SetCorrect3Flag();  break;
      case bSET_CORRECT3_VALUE: key_SetCorrect3Value(); break;
      case bSET_CORRECT3_INFO:  key_SetCorrect3Info();  break;

      case bSET_DIGITALS:       key_SetDigitals();      break;
      case bSET_ENBL_HOURS:     key_SetEnblHours();     break;
      case bSET_CONTROL_HOURS:  key_SetCtrlHours();     break;
      case bSET_ENBL_CANALS:    key_SetEnblCanals();    break;

      case bSET_PARAMS_FLAG:    key_SetParamsFlag();    break;
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

      case bSET_GPS_CONFIG:     key_SetGpsConfig();     break;
      case bSET_GPS_GMT:        key_SetGpsGmt();        break;
      case bGET_GPS_DATA:       key_GetGpsData();       break;
      case bGET_GPS_CORRECT:    key_GetGpsCorrect();    break;
      case bSET_GPS_SCHEDULE:   key_SetGpsSchedule();   break;
      case bSET_GPS_SEASON:     key_SetGpsSeason();     break;

      case bSET_FLOW_PORT_TO:   key_FlowPortTo();       break;
      case bSET_MAX_FLOW_DELAY: key_SetMaxFlowDelay();  break;
      case bSET_FLOW_PORT_FROM: key_FlowPortFrom();     break;

      case bSET_ENBL_CURRENT:   key_SetEnblCurrent();   break;
      case bSET_ENBL_CURRENT2:  key_SetEnblCurrent2();  break;
      case bSET_ENBL_PROFILE:   key_SetEnblProfile();   break;
      case bSET_TIMEOUT_PROFILE:key_SetTimeoutProfile();break;
      case bSET_TIMEOUT_CURRENT:key_SetTimeoutCurrent();break;
      case bSET_CONTROL_TIME:   key_SetControlTime();   break;
      case bSET_MANAGE_TIME:    key_SetManageTime();    break;

      case bSET_MACHINES_ESC:   key_SetMachinesEsc();   break;
      case bSET_BLOCK_ESC:      key_SetBlockEsc();      break;

      case bSET_EXTENDED_ESC_S: key_SetExtendedEscS();  break;
      case bSET_EXTENDED_ESC_V: key_SetExtendedEscV();  break;
      case bSET_EXTENDED_ESC_U: key_SetExtendedEscU();  break;

      case bSET_ADDRESSES:      key_SetAddresses();     break;
      case bSET_ASCII_ADDRESSES:key_SetAsciiAddresses();break;
      case bSET_ENBL_KEYS:      key_SetEnblKeys();      break;
      case bSET_KEYS:           key_SetKeys();          break;
      case wSET_KEYS_LEVEL_B:   key_SetKeysLevelB();    break;
      case bSET_SERIALS_MANUAL: key_SetSerialsManual(); break;
      case bSET_SERIALS1:       key_SetSerials1();      break;
      case bSET_SERIALS2:       key_SetSerials2();      break;

      case bGET_MODEMS_QUALITY: key_GetModemsQuality(); break;
      case bSET_PHONES:         key_SetPhones();        break;
      case bSET_MAX_CONNECT:    key_SetMaxConnect();    break;
      case bSET_CUSTOM_MODEM:   key_SetCustomModem();   break;
      case bSET_MODEM_ATDP:     key_SetModemATDP();     break;

      case bSET_SHOW_MESSAGES:  key_SetShowMessages();  break;

      case bSET_SEPARATE_CAN:   key_SetSeparateCan();   break;
      case bSET_ENBL_WDT:       key_SetEnblWDT();       break;

      case bSET_RECALC_TIME:    key_SetRecalcTime();    break;
      case bSET_RECALC_ALWAYS:  key_SetRecalcAlways();  break;
      case wSET_RECALC_3:       key_SetRecalc3();       break;

      case bSET_RECALC_FULL:
      case bSET_RECALC_MAXPOW:
      case bSET_RECALC_ENG:     key_SetRecalc();        break;


      case bGET_CNTCURR_110:
      case bGET_READTIMEDATE1:
      case bGET_READTIMEDATE2:  key_GetSingleCan();     break;

      case bSET_DECRET:         key_SetDecret();        break;
      case bSET_WINTER:
      case bSET_SUMMER:         key_SetSeason();        break;

      case bTEST_DIRECT:        key_TestDirect();       break;

      case bTEST_UART:          key_TestUART();         break;
      case bTEST_REQUEST:       key_TestRequest();      break;
      case bTEST_RESPONSE:      key_TestResponse();     break;
      case bTEST_FLOW:          key_TestFlow();         break;
      case bTEST_PORTS_IO:      key_TestPortsIO();      break;
      case bTEST_UNI:           key_TestUni();          break;

      case wSET_MONITOR_LOG_BASIC: key_MonitorLogBasic(); break;
      case wSET_MONITOR_LOG_HEX:   key_MonitorLogHex();   break;
      case wSET_MONITOR_LOG_CHAR7: key_MonitorLogChar7(); break;
      case wSET_MONITOR_LOG_CHAR8: key_MonitorLogChar8(); break;
      case wSET_MONITOR_OPEN:   key_MonitorOpen();      break;
      case wTEST_MONITOR:       key_TestMonitor();      break;

      case bTEST_IMPULSES:      key_TestImpulses();     break;
      case bTEST_KEYS:          key_TestKeys();         break;
      case bTEST_RTC:           key_TestRTC();          break;
      case bTEST_POWER_OFF:     key_TestPowerOff();     break;


      case wSET_OUTPUT_DELAY:   key_SetOutputDelay();   break;
      case wSET_TX_DELAY:       key_SetTxDelay();       break;
      case wSET_HIDE_MESSAGES:  key_SetHideMessages();  break;

      case wSET_GAPS_FLAG:      key_SetGapsFlag();      break;
      case wSET_GAPS:           key_SetGaps();          break;

      case wSET_CONTROL_Q:      key_SetControlQ();      break;
      case wSET_CONTROL_K:      key_SetControlK();      break;
      case wSET_SHORT_PROFILE_C:key_SetShortProfileC(); break;
      case wSET_DSBL_REFILL:    key_SetDsblRefill();    break;
      case wSET_DSBL_ANSWER:    key_SetDsblAnswer();    break;
      case wSET_MAX_REPEATS:    key_SetMaxRepeats();    break;
      case wSET_MAX_SHUTDOWN:   key_SetMaxShutdown();   break;
      case wSET_CONTROL_W:      key_SetControlW();      break;
      case wSET_ENBL_DIAGRAM:   key_SetEnblDiagram();   break;
      case wSET_SKIP_FAILURE_ENBL: key_SetSkipFailureEnbl(); break;
      case wSET_SKIP_FAILURE_REPEATS: key_SetSkipFailureRepeats(); break;
      case wSET_TIME_ZONE_34:   key_SetTimeZone34();    break;
      case wSET_MAX_TIMER_35:   key_SetMaxTimer35();    break;
      case wSET_IGNORE_STATUS_38: key_SetIgnoreStatus38(); break;
      case wSET_SHORT_PROFILE_B:key_SetShortProfileB(); break;
      case wSET_MODEM_DISCONNECT_BD:key_SetModemDisconnectBD(); break;

      case wSET_PROFILE_INTERVAL: key_SetProfileInterval(); break;
      case wSET_PROFILE_INTERVAL_DIRECT: key_SetProfileIntervalDirect(); break;
      case wSET_PROFILE_INTERVAL_MODEM: key_SetProfileIntervalModem(); break;

      case wSET_REVIEW_FLAG:    key_SetReviewFlag();    break;
      case wSET_REVIEW_CAN:     key_SetReviewCan();     break;
      case wSET_REVIEW_READ_ID: key_SetReviewReadId();  break;
      case wSET_REVIEW_REPEATS: key_SetReviewRepeats(); break;
      case wSET_REVIEW_BORDERS: key_SetReviewBorders(); break;
      case wSET_REVIEW_MARGINS: key_SetReviewMargins(); break;
      case wSET_REVIEW_WRN_PERCENT: key_SetReviewWrnPercent(); break;
      case wSET_REVIEW_WRN_TOP: key_SetReviewWrnTop(); break;

      case wSET_AUTO_FLOW_ENBL: key_SetAutoFlowEnbl();  break;
      case wSET_AUTO_FLOW_HOURS:key_SetAutoFlowHours(); break;

      case wSET_DSBL_ESC:       key_SetDsblEsc();       break;

      case wSET_RECORDS_DSBL:   key_SetRecordsDsbl();   break;

      case wSET_PLC_U_FLAG:     key_SetPlcUFlag();      break;
      case wSET_PLC_U_SIZE:     key_SetPlcUSize();      break;
      case wSET_PLC_U_SHUTDOWN: key_SetPlcUShutdown();  break;

      case bGET_DEVICE19_LONG:  key_GetDevice19Long();  break;
      case bGET_DEVICE19_DOUBLE:key_GetDevice19Double();break;

      case wSET_INPUT_MODE_RESET: key_SetInputModeReset(); break;
      case bSET_SLAVE_MODEM: key_SetSlaveModem(); break;

#ifdef ENABLE_BULK
      case wSET_BULK_ENBL: key_SetBulkEnable(); break;
      case wSET_BULK_SIZE: key_SetBulkSize(); break;
      case wSET_BULK_MAX_DELAY: key_SetBulkMaxDelay(); break;
#endif

      case wSET_STRICT_UNI:         key_SetStrictUni();        break;
      case wSET_ENBL_PASS_UNI:      key_SetEnblPassUni();      break;
      case wSET_MAX_DELAY_UNI:      key_SetMaxDelayUni();      break;
      case wSET_REPEAT_FLOW_UNI:    key_SetRepeatFlowUni();    break;

      case wSET_MNT_ESC_S:      key_SetMntEscS();       break;
      case wSET_CORRECT_LIMIT:  key_SetCorrectLimit();  break;

      case wSET_EXT0_FLAG:      key_SetExt0Flag();      break;
      case wSET_EXT0_COUNTER:   key_SetExt0Counter();   break;

      case bSET_EXT3_RESET:     key_SetExt3Reset();     break;
      case bSET_EXT3_FLAG:      key_SetExt3Flag();      break;
      case bSET_EXT3_EVENTS_A:  key_SetExt3A();         break;
      case bSET_EXT3_EVENTS_B:  key_SetExt3B();         break;

      case bSET_EXT4_FLAG:      key_SetExt4Flag();      break;
      case bSET_EXT4_MONTHS:    key_SetExt4Months();    break;
      case bSET_EXT4_ENBL_CAN:  key_SetExt4EnblCan();   break;

      case wSET_EXT4T_FLAG:         key_SetExt4TFlag();        break;
      case wSET_EXT4T_MONTHS:       key_SetExt4TMonths();      break;
      case wSET_EXT4T_RESET_FULL:   key_SetExt4TResetFull();   break;
      case wSET_EXT4T_RESET_CUSTOM: key_SetExt4TResetCustom(); break;

      case bSET_EXT5_FLAG:      key_SetExt5Flag();      break;

      case wSET_EXT6_FLAG:      key_SetExt6Flag();      break;

      case bSET_CLEAR_CANALS:   key_ClearCanals();      break;
      case wSET_SET_PROFILES1:  key_SetProfiles1();     break;
      case wSET_SET_PROFILES2:  key_SetProfiles2();     break;

      case wGET_HEALTH:         key_GetHealth();        break;

      default:                  NoProgram();            break;
    }
  }
}
