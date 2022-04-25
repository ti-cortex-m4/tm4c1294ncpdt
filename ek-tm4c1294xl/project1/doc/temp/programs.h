
// режим: программирование
#define bSET_CURRTIME               9
#define bSET_CURRDATE               8
#define bSET_SPEED                  1

#define bSET_GROUPS                 2
//#define bSET_NODES                  102

+   #define bSET_TRANS_ENG              4
+   #define bSET_TRANS_CNT              244
+   #define bSET_PULSE_HOU              5
+   #define bSET_PULSE_MNT              245
+   #define bSET_COUNT                  6
+   #define bSET_LOSSE                  3
+   #define bSET_LEVEL                  108

#define bSET_DAYZONE                7
#define bSET_PUBLIC                 26

#define bSET_PROGRAM10              10
#define bSET_PROGRAM17              17
#define bSET_PROGRAM20              20
#define bSET_PROGRAM27              27

#define bSET_PROGRAM18              18
+   #define bSET_RELAXS_FLAG            117
#define bSET_RELAXS_TARIFF          118
#define bSET_RELAXS                 119
/*
#define bSET_PUBMODE1               130
#define bSET_PUBMODE2               131
#define bSET_PUBMODE3               132
#define bSET_POWMODE1               133
#define bSET_POWMODE2               134
#define bSET_POWMODE3               135
#define bSET_ENGMODE1               136
#define bSET_ENGMODE2               137
#define bSET_ENGMODE3               138

#define bSET_RESETZONES             140
#define bSET_RESETGROUPS            141
#define bSET_RESETRELAXS            142
#define bSET_RESETENGINE            143
*/
#ifdef  DS80C400
+   #define bSET_DECRET                 123
+   #define bSET_SUMMER                 124
+   #define bSET_WINTER                 125
#endif

#define bSET_PASSWORD               11
+   #define bSET_LOGICAL                13
+   #define bSET_MACHINES               113
#define bSET_START                  15
#define bSET_STARTHOU               16
+   #define bSET_PRIVATE                99
+   #define bSET_VERSION                115

#define bSET_PROGRAM79              79
#define bSET_RESETCUSTOM            80
#define bSET_RESETFULL              81
#define bSET_RESETWATCHDOG          82
#define bSET_DEBUG                  83
#define bSET_PROGRAM85              85

- //#define bSET_CLEARCANALS_1          86
+   #define bSET_CLEARCANALS_2          87
#define bSET_FINDDEVICENUMBER       88
#define bSET_FINDDEVICESPEED        89
+   #define bSET_DIGITALS               90
#define bSET_AUTOMATIC              94
#define bSET_AUTOMATIC2             149
#define bSET_MAJORDELAYS            97
#define bSET_MINORDELAYS            98
#define bSET_ADDRESSES              100
+   #define bSET_ENABLE_KEYS            170
+   #define bSET_KEYS                   171
#define bSET_ENABLE_LINES           172
#define bSET_LINES                  173

+   #define bSET_GPS_CONFIG             174
+   #define bSET_GPS_GMT                175
+   #define bGET_GPS_DATA               176
+   #define bGET_GPS_CORRECT            177
+   #define bSET_GPS_RUN                178
+   #define bSET_GPS_SEASON             186

#define bSET_SMK_CONFIG             213
#define bGET_SMK_DATA               214
#define bGET_SMK_CORRECT            215
#define bSET_SMK_RUN                228
#define bSET_SMK_DELAY              229

#define bSET_SETRECALC              230
#define bSET_RECALC_ALWAYS          231

+   #define bGET_DEVICESINT             144
+   #define bGET_DEVICESREAL            145

+   #define bSET_ENABLE_PARAM           101
+   #define bSET_QUICK_PARAM            102
+   #define bSET_PARAMS                 103
+   #define bSET_DIVIDER                104
#define bGET_PARAMCURR              105
#define bGET_PARAMBUFF              106
#define bGET_PARAMFULL              107

#define bSET_CONTACTS               109
#define bSET_CONTACTS2              208
#define bSET_RELAYS                 209
#define bSET_CONTACTS3              211
#define bSET_CONTACTS4              223
#define bSET_CONTACTS5              224
#define bSET_CONTACTS6              225
#define bSET_CONTACTS7              226
#define bSET_CONTACTS8              227

#define bSET_EXT3_RESET             136
#define bSET_EXT3_FLAG              137
#define bSET_EXT3_EVENTS_A          138
#define bSET_EXT3_EVENTS_B          139

#define bSET_OLD_VERSION_D          141

+   #define bSET_EXT4_FLAG              249
+   #define bSET_EXT4_MONTHS            250
#define bSET_EXT4_CANALS            252
#define bSET_EXT4_RESET             253
#define bSET_EXT6_RESET             254

+   #define bSET_EXT5_FLAG              251

#ifdef  DS80C400
#define bGET_MODEMS                 179
#endif

#define bGET_MODEMS_QUALITY         222
+   #define bSET_PHONES                 180
#define bSET_CONNECTTIME            181

#define bSET_PHONES20               66
#define bSET_PHONES21               67
#define bSET_PHONES22               68
#define bSET_PHONES23               69

+   #define bSET_CORRECT2               75
+   #define bSET_CORRECT30              76
+   #define bSET_CORRECT31              77
+   #define bSET_CORRECT32              86

#ifdef  DS80C400
#define bSET_ENBLHOURS              182
#endif

#define bSET_CONTROL                183
#define bSET_LIMITS                 184
#define bSET_LIMITS30               143
#define bSET_LIMITS31               146
#define bSET_LIMITS32               147
#define bSET_LIMITS33               142
#define bSET_LIMITS2                148

#ifdef  DS80C400
+   #define bSET_ENBLSENSORS            185
#endif

#define bSET_RECALCFULL             240
#define bSET_RECALCMAXPOW           241
#define bSET_RECALCENG              242



// режим: функционирование
#define bGET_CURRTIME               1
#define bGET_CORRECTNOW             2
+   #define bGET_CORRECTCURR            12
+   #define bGET_CORRECTPREV            212
#define bGET_CURRDATE               3
#define bGET_SPEED                  14

#define bGET_GROUPS                 4
+   #define bGET_VERSION                15

+   #define bGET_PROGRAM18              18
+   #define bGET_PROGRAM19              19

#define bGET_PROGRAM5               5
#define bGET_PROGRAM84              84
#define bGET_PROGRAM85              85

+   #define bGET_TRANS_ENG              6
+   #define bGET_TRANS_CNT              246
+   #define bGET_PULSE_HOU              7
+   #define bGET_PULSE_MNT              247
#define bGET_COUNTNEW               10
#define bGET_COUNTOLD               110
#define bGET_READTIMEDATE1          111
#define bGET_READTIMEDATE2          112
#define bGET_READQUADRANTS          210
//#define bGET_READTRANS              254
//#define bGET_READPULSE              255
//#define bGET_READSENSORS            113
+   #define bGET_LOSSE                  37
/*
#define bGET_VALUE_ENGHOU           201
#define bGET_VALUE_CNTHOU           202
#define bGET_VALUE_ENGMNT           203
#define bGET_VALUE_CNTMNT           204
*/
#define bGET_PUBLIC                 126
#define bGET_PROGRAM38              38

#define bGET_IMPCANCURRMNT          9
#define bGET_POWGRPCURRMNT          20

#define bGET_POWGRPPREVHOU          21
#define bGET_POWGRPCURRHOU          22

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

#define bGET_ENGGRPMONPREV_SPEC     158

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

#define bGET_MAXPOWMONCAN           71
#define bGET_MAXPOWDAYCAN           72
#define bGET_PROGRAM73              73
#define bGET_PROGRAM74              74
#define bGET_CNTCANYEAR1            79
#define bGET_CNTCANYEAR10           49
#define bGET_CNTCANYEAR2            78
#define bGET_CNTCANYEAR20           48

#define bSET_RECALC2                128
#define bSET_RECALC_ENABLE          129

#define bGET_POWGRPMONPREV_C2       130
#define bGET_POWGRPMONPREV_D2       131

#define bGET_POWGRPMONCURR_C2       133
#define bGET_POWGRPMONCURR_D2       134

#ifdef  POWER
#define bGET_TRUE                   91
#define bGET_FALSE                  92
#define bGET_REPEAT                 93
#define bGET_MORE                   94
#define bGET_LESS                   95
#define bGET_BASE                   191
#endif
/*
#define bGET_IMPCANMNT              140
#define bGET_IMPCANHOU              141
#define bGET_POWGRPMNT              142
#define bGET_POWGRPHOU              143

#define bGET_IMPCANDAY              154
#define bGET_IMPCANMON              155
#define bGET_IMPCANABS              156
#define bGET_ENGGRPDAY              157
#define bGET_ENGGRPMON              158

#define bGET_DEFECTHOU              160
#define bGET_DEFECTDAY              161
#define bGET_DEFECTMON              162
*/

#ifdef  FLOW
#define bSET_PORTTO                 187
#define bSET_MAXFLOWDELAY           188
#define bSET_PORTFROM               189
#endif

#define bGET_RUNDIGITALS            190

+   #define bSET_ENABLELOADMNT          192
+   #define bSET_ENABLELOADHOU          193
#define bSET_TIMEOUT_HOU            194
#define bSET_TIMEOUT_MNT            195
#define bSET_CONTROLTIME            196
#define bSET_MANAGETIME             197
#define bSET_SLAVEMODEM             198
+   #define bSET_SHOWMESSAGES           199
+   #define bSET_EXTENDED_ESC_S         200
+   #define bSET_EXTENDED_ESC_V         201
+   #define bSET_EXTENDED_ESC_U         202
#define bSET_CUSTOMMODEM            203
#define bSET_POWERED_ESC            204
#define bSET_BLOCKING_CRC           205
+   #define bSET_BLOCKING_ESC           206
#define bGET_DOOR                   207

#define bGET_STREAM                 216
#define bGET_STATIC                 217
#define bSET_SEPARATECAN            218
#define bSET_ENABLEWATCHDOG         219

+   #define bGET_ANALYSIS1              220

#ifdef  FLOW
#define bGET_ANALYSIS2              221
#endif

#define bGET_ANALYSIS3              237
+   #define bGET_ANALYSIS4              238

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

