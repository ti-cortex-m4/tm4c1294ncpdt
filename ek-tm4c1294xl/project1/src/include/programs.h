/*------------------------------------------------------------------------------
PROGRAMS.H

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
#define bSET_STARTHOU               16

#define bSET_RESETCUSTOM            80
#define bSET_RESETFULL              81
#define bSET_RESETWATCHDOG          82
#define bSET_DEBUG                  83

#define bSEARCH_BY_NUMBER           88
#define bSEARCH_BY_SPEED            89

#define bSET_MAJOR_DELAYS           97
#define bSET_MINOR_DELAYS           98


// режим: функционирование

#define bGET_SPEED                  14

#define bGET_CURRTIME               1
#define bGET_CURRDATE               3

#define bGET_GROUPS                 4

#define bGET_PUBLIC_TARIFFS         126
#define bGET_TARIFFS_MODE           38

#define bGET_PROGRAM5               5
#define bGET_PROGRAM84              84
#define bGET_PROGRAM85              85

#define bGET_VERSION                15

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


// все режимы

#define bSET_DIGITALS               90
#define bSET_ENBL_HOURS             182
#define bSET_CONTROL_HOURS          183
#define bSET_ENBL_CANALS            185

#define bSET_ENBL_CURRENT           192
#define bSET_ENBL_PROFILE           193
#define bSET_TIMEOUT_PROFILE        194
#define bSET_TIMEOUT_CURRENT        195

#define bSET_RELAXS_FLAG            117
#define bSET_RELAXS_TARIFF          118
#define bSET_RELAXS                 119

#define bSET_DECRET                 123
#define bSET_SUMMER                 124
#define bSET_WINTER                 125

#define bSET_ADDRESSES              100
#define bSET_ENBL_KEYS              170
#define bSET_KEYS                   171

#define bSET_PHONES                 180
#define bSET_MAX_CONNECT            181
#define bSET_CUSTOM_MODEM           203

#define bGET_STREAM                 216

#define bTEST_RESPONSE              220
#define bTEST_IMPULSES              227
#define bTEST_KEYS                  228
#define bTEST_RTC                   229


#endif
