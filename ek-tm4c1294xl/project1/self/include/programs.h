/*------------------------------------------------------------------------------
PROGRAMS!H

 Номера программ
------------------------------------------------------------------------------*/


#ifndef __PROGRAMS
#define __PROGRAMS


// режим: программирование

#define bSET_SPEED                  1
#define bSET_CURRDATE               8
#define bSET_CURRTIME               9

#define bSET_GROUPS                 2

#define bSET_TRANS_ENG              4
#define bSET_TRANS_CNT              244
#define bSET_PULSE_HOU              5
#define bSET_PULSE_MNT              245
#define bSET_COUNT                  6
#define bSET_LOSSE                  3
#define bSET_LEVEL                  108

#define bSET_DAY_ZONE               7
#define bSET_PUBLIC_TARIFFS         26
#define bSET_TARIFFS_MODE           18

#define bSET_PROGRAM10              10
#define bSET_PROGRAM17              17
#define bSET_PROGRAM20              20
#define bSET_PROGRAM27              27

#define bSET_PASSWORD               11
#define bSET_LOGICAL                13
#define bSET_PRIVATE                99
#define bSET_VERSION                115

#define bSET_START                  15
#define bSET_START_MINUTES30        16

#define bSET_RESETCUSTOM            80
#define bSET_RESETFULL              81
#define bSET_RESET_WDT              82
#define bSET_DEBUG                  83

#define bSEARCH_BY_NUMBER           88
#define bSEARCH_BY_SPEED            89

#define bSET_AUTOMATIC1             94
#define bSET_AUTOMATIC2             149

#define bSET_MAJOR_DELAYS           97
#define bSET_MINOR_DELAYS           98


// режим: функционирование

#define bGET_SPEED                  14

#define bGET_CURRTIME               1
#define bGET_CURRDATE               3

#define bGET_CORRECT_TIME           2
#define bGET_CORRECTCURR            12
#define bGET_CORRECTPREV            212

#define bGET_GROUPS                 4

#define bGET_PUBLIC_TARIFFS         126
#define bGET_TARIFFS_MODE           38

#define bGET_PROGRAM5               5
#define bGET_PROGRAM84              84
#define bGET_PROGRAM85              85

#define bGET_VERSION                15

#define bGET_PROGRAM18              18
#define bGET_PROGRAM19              19

#define bGET_TRANS_ENG              6
#define bGET_TRANS_CNT              246
#define bGET_PULSE_HOU              7
#define bGET_PULSE_MNT              247
#define bGET_LOSSE                  37

#define bGET_CNTCURR_10             10
#define bGET_CNTCURR_110            110
#define bGET_READTIMEDATE1          111
#define bGET_READTIMEDATE2          112

#define bGET_IMPCANCURRMNT          9
#define bGET_POWGRPCURRMNT          20

#define bGET_POWGRPPREVHOU          21
#define bGET_POWGRPCURRHOU          22 // прогнозируемая получасовая средняя мощность

#define bGET_POWGRPDAYPREV_ABCD     23
#define bGET_POWGRPDAYPREV_C        24
#define bGET_POWGRPDAYPREV_D        25

#define bGET_POWGRPDAYCURR_ABCD     26
#define bGET_POWGRPDAYCURR_C        27
#define bGET_POWGRPDAYCURR_D        28

#define bGET_POWGRPMONPREV_ABCD     29
#define bGET_POWGRPMONPREV_C        30
#define bGET_POWGRPMONPREV_D        31

#define bGET_POWGRPMONCURR_ABCD     32
#define bGET_POWGRPMONCURR_C        33
#define bGET_POWGRPMONCURR_D        34

#define bGET_ENGGRPDAYPREV_ABCD     50
#define bGET_ENGGRPDAYPREV_CD       51
#define bGET_ENGGRPDAYPREV_B        52
#define bGET_ENGGRPDAYPREV_A        53

#define bGET_ENGGRPDAYCURR_ABCD     54
#define bGET_ENGGRPDAYCURR_CD       55
#define bGET_ENGGRPDAYCURR_B        56
#define bGET_ENGGRPDAYCURR_A        57

#define bGET_ENGGRPMONPREV_ABCD     58
#define bGET_ENGGRPMONPREV_CD       59
#define bGET_ENGGRPMONPREV_B        60
#define bGET_ENGGRPMONPREV_A        61

#define bGET_ENGGRPMONCURR_ABCD     62
#define bGET_ENGGRPMONCURR_CD       63
#define bGET_ENGGRPMONCURR_B        64
#define bGET_ENGGRPMONCURR_A        65

#define bGET_ENGGRPYEAR_ABCD        80
#define bGET_ENGGRPYEAR_CD          81
#define bGET_ENGGRPYEAR_B           82
#define bGET_ENGGRPYEAR_A           83

#define bGET_PROGRAM73              73
#define bGET_PROGRAM74              74
#define bGET_CNTCANYEAR1            79
#define bGET_CNTCANYEAR10           49
#define bGET_CNTCANYEAR2            78
#define bGET_CNTCANYEAR20           48
#define wGET_CNTCANYEAR3            279

#define bGET_POWCANCURRMNT          120

#define bGET_POWCANPREVHOU          121
#define bGET_POWCANCURRHOU          122

#define bGET_ENGCANDAYPREV_ABCD     150
#define bGET_ENGCANDAYPREV_CD       151
#define bGET_ENGCANDAYPREV_B        152
#define bGET_ENGCANDAYPREV_A        153

#define bGET_ENGCANDAYCURR_ABCD     154
#define bGET_ENGCANDAYCURR_CD       155
#define bGET_ENGCANDAYCURR_B        156
#define bGET_ENGCANDAYCURR_A        157

#define bGET_ENGCANMONPREV_ABCD     158
#define bGET_ENGCANMONPREV_CD       159
#define bGET_ENGCANMONPREV_B        160
#define bGET_ENGCANMONPREV_A        161

#define bGET_ENGCANMONCURR_ABCD     162
#define bGET_ENGCANMONCURR_CD       163
#define bGET_ENGCANMONCURR_B        164
#define bGET_ENGCANMONCURR_A        165

#define bGET_ENGCANYEAR_ABCD        166
#define bGET_ENGCANYEAR_CD          167
#define bGET_ENGCANYEAR_B           168
#define bGET_ENGCANYEAR_A           169

#define bRUN_PROFILE                190


// все режимы

#define bSET_PHONES20               66
#define bSET_PHONES21               67
#define bSET_PHONES22               68
#define bSET_PHONES23               69

#define bSET_CORRECT2_FLAG          75
#define bSET_CORRECT3_FLAG          76
#define bSET_CORRECT3_VALUE         77
#define bSET_CORRECT3_INFO          86

#define bSET_DIGITALS               90
#define bSET_ENBL_HOURS             182
#define bSET_CONTROL_HOURS          183
#define bSET_ENBL_CANALS            185

#define bSET_PARAMS_FLAG            101
#define bSET_MNT_PARAMS             102
#define bSET_PARAMS                 103
#define bSET_PARAMS_DIV             104
#define bGET_PARAMS_CURR            105
#define bGET_PARAMS_BUFF            106
#define bGET_PARAMS_FULL            107
#define wSET_FIX_PARAMS_BUGS        303
#define wSET_USE_PARAMS_DIV         304

#define bSET_LIMITS                 184
#define bSET_LIMITS2                148
#define bSET_LIMITS30               143
#define bSET_LIMITS31               146
#define bSET_LIMITS32               147
#define bSET_LIMITS33               142

#define bSET_GPS_CONFIG             174
#define bSET_GPS_GMT                175
#define bGET_GPS_DATA               176
#define bGET_GPS_CORRECT            177
#define bSET_GPS_SCHEDULE           178
#define bSET_GPS_SEASON             186

#define bSET_FLOW_PORT_TO           187
#define bSET_MAX_FLOW_DELAY         188
#define bSET_FLOW_PORT_FROM         189

#define bSET_ENBL_CURRENT           192
#define bSET_ENBL_CURRENT2          414
#define bSET_ENBL_PROFILE           193
#define bSET_TIMEOUT_PROFILE        194
#define bSET_TIMEOUT_CURRENT        195
#define bSET_CONTROL_TIME           196
#define bSET_MANAGE_TIME            197

#define bSET_MACHINES_ESC           113
#define bSET_BLOCK_ESC              206

#define bSET_EXTENDED_ESC_S         200
#define bSET_EXTENDED_ESC_V         201
#define bSET_EXTENDED_ESC_U         202

#define bSET_RELAXS_FLAG            117
#define bSET_RELAXS_TARIFF          118
#define bSET_RELAXS                 119

#define bSET_DECRET                 123
#define bSET_SUMMER                 124
#define bSET_WINTER                 125

#define bSET_ADDRESSES              100
#define bSET_ENBL_KEYS              170
#define bSET_KEYS                   171
#define wSET_KEYS_LEVEL_B           271
#define bSET_SERIALS_MANUAL         430
#define bSET_SERIALS1               431
#define bSET_SERIALS2               432

#define bGET_MODEMS_QUALITY         222
#define bSET_PHONES                 180
#define bSET_MAX_CONNECT            181
#define bSET_CUSTOM_MODEM           203
#define bSET_MODEM_ATDP             204

#define bSET_SHOW_MESSAGES          199

#define bSET_SEPARATE_CAN           218
#define bSET_ENBL_WDT               219

#define bSET_RECALC_TIME            230
#define bSET_RECALC_ALWAYS          231
#define wSET_RECALC_3               340

#define bSET_RECALC_FULL            240
#define bSET_RECALC_MAXPOW          241
#define bSET_RECALC_ENG             242

#define bTEST_DIRECT                216

#define bTEST_UART                  85
#define bTEST_REQUEST               239
#define bTEST_RESPONSE              220
#define bTEST_FLOW                  221
#define bTEST_PORTS_IO              237
#define bTEST_UNI                   238

#define bTEST_IMPULSES              800
#define bTEST_KEYS                  801
#define bTEST_RTC                   802
#define bTEST_POWER_OFF             803
#define wSET_MONITOR_LOG_BASIC      812
#define wSET_MONITOR_LOG_HEX        813
#define wSET_MONITOR_LOG_CHAR7      814
#define wSET_MONITOR_LOG_CHAR8      815
#define wSET_MONITOR_OPEN           816
#define wTEST_MONITOR               817


#define wSET_OUTPUT_DELAY           298
#define wSET_TX_DELAY               297
#define wSET_HIDE_MESSAGES          299

#define wSET_GAPS_FLAG              300
#define wSET_GAPS                   301

#define wGET_READTRANS              354
#define wGET_READPULSE              355

#define wSET_CONTROL_Q              402
#define wSET_CONTROL_K              403
#define wSET_SHORT_PROFILE_C        404
#define wSET_DSBL_REFILL            405
#define wSET_DSBL_ANSWER            406
#define wSET_MAX_REPEATS            409
#define wSET_MAX_SHUTDOWN           423
#define wSET_CONTROL_W              424
#define wSET_ENBL_DIAGRAM           425
#define wSET_SKIP_FAILURE_ENBL      426
#define wSET_SKIP_FAILURE_REPEATS   427
#define wSET_TIME_ZONE_34           428
#define wSET_MAX_TIMER_35           429
#define wSET_IGNORE_STATUS_38       433
#define wSET_SHORT_PROFILE_B        434
#define wSET_MODEM_DISCONNECT_BD    435

#define wSET_REVIEW_FLAG            440
#define wSET_REVIEW_CAN             441
#define wSET_REVIEW_READ_ID         442
#define wSET_REVIEW_REPEATS         443
#define wSET_REVIEW_BORDERS         444
#define wSET_REVIEW_MARGINS         445
#define wSET_REVIEW_WRN_TREND       446
#define wSET_REVIEW_WRN_TOP         447

#define wSET_AUTO_FLOW_ENBL         448
#define wSET_AUTO_FLOW_HOURS        449

#define wSET_DSBL_ESC               410

#define wSET_RECORDS_DSBL           415

#define wSET_PLC_U_FLAG             419
#define wSET_PLC_U_SIZE             420
#define wSET_PLC_U_SHUTDOWN         421

#define bGET_DEVICE19_LONG          144
#define bGET_DEVICE19_DOUBLE        145

#define wSET_INPUT_MODE_RESET       416
#define bSET_SLAVE_MODEM            198

#define wSET_BULK_ENBL              411
#define wSET_BULK_SIZE              412
#define wSET_BULK_MAX_DELAY         413

#define wSET_STRICT_UNI             417
#define wSET_ENBL_PASS_UNI          418
#define wSET_MAX_DELAY_UNI          422
#define wSET_REPEAT_FLOW_UNI        288

#define wSET_MNT_ESC_S              500
#define wSET_CORRECT_LIMIT          501

#define bSET_EXT3_RESET             136
#define bSET_EXT3_FLAG              137
#define bSET_EXT3_EVENTS_A          138
#define bSET_EXT3_EVENTS_B          139

#define bSET_EXT4_FLAG              249
#define bSET_EXT4_MONTHS            250
#define bSET_EXT4_ENBL_CAN          252
#define bSET_EXT4_RESET             253
#define bSET_EXT6_RESET             254

#define bSET_EXT5_FLAG              251

#define wSET_EXT4T_FLAG             516
#define wSET_EXT4T_MONTHS           517
#define wSET_EXT4T_RESET_FULL       518
#define wSET_EXT4T_RESET_CUSTOM     519

#define wSET_EXT0_FLAG              520
#define wSET_EXT0_COUNTER           521

#define wSET_EXT6_FLAG              400

#define bSET_CLEAR_CANALS           87
#define wSET_SET_PROFILES1          990
#define wSET_SET_PROFILES2          991

#define wGET_HEALTH                 999


#endif
