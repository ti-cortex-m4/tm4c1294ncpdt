+   #define bINQ_GETGLOBAL                 0

#define bINQ_GETCURRTIME               1
#define bINQ_SETCURRTIME               2
#define bINQ_GETLOGICAL                3
#define bINQ_SETLOGICAL                4
#define bINQ_GETPRIVATE                5
#define bINQ_SETPRIVATE                6
#define bINQ_GETPASSWORD               7
#define bINQ_SETPASSWORD               8
+   #define bINQ_GETGROUP                  9
+   #define bINQ_SETGROUP                  10
#define bINQ_CORRECT1                  11
#define bINQ_CORRECT2                  12
#define bINQ_CORRECT3                  13
#define bINQ_CORRECT4                  238
+   #define bINQ_GETPUBLIC                 14
+   #define bINQ_SETPUBLIC                 15
#define bINQ_GETOLDMODE                16
#define bINQ_SETOLDMODE                17

+   #define bINQ_GETOLDPOWTARIFFS          18
+   #define bINQ_SETOLDPOWTARIFFS          19
+   #define bINQ_GETOLDENGTARIFFS          20
+   #define bINQ_SETOLDENGTARIFFS          21
+   #define bINQ_GETOLDPUBTARIFFS          22
+   #define bINQ_SETOLDPUBTARIFFS          23

+   #define bINQ_GETNEWPOWTARIFFS          24
+   #define bINQ_SETNEWPOWTARIFFS          25
+   #define bINQ_GETNEWENGTARIFFS          26
+   #define bINQ_SETNEWENGTARIFFS          27
+   #define bINQ_GETNEWPUBTARIFFS          28
+   #define bINQ_SETNEWPUBTARIFFS          29

+   #define bINQ_GETTRANS_ENG              30
+   #define bINQ_SETTRANS_ENG              31
+   #define bINQ_GETTRANS_CNT              32
+   #define bINQ_SETTRANS_CNT              33
+   #define bINQ_GETPULSE_HOU              34
+   #define bINQ_SETPULSE_HOU              35
+   #define bINQ_GETPULSE_MNT              234
+   #define bINQ_SETPULSE_MNT              235
+   #define bINQ_GETVALUE_ENGHOU           36
+   #define bINQ_GETVALUE_CNTHOU           37
+   #define bINQ_GETVALUE_ENGMNT           236
+   #define bINQ_GETVALUE_CNTMNT           237
+   #define bINQ_GETCOUNT                  38
+   #define bINQ_SETCOUNT                  39
+   #define bINQ_GETLOSSE                  40
+   #define bINQ_SETLOSSE                  41
+   #define bINQ_GETLEVEL                  180
+   #define bINQ_SETLEVEL                  181

+   #define bINQ_GETDIGITAL                42
+   #define bINQ_SETDIGITAL                43

#define bINQ_GETPARAM_100              53
+   #define bINQ_GETPARAM                  44
+   #define bINQ_SETPARAM                  45
+   #define bINQ_GETDIVIDER                46
+   #define bINQ_SETDIVIDER                47
#define bINQ_GETPARAMCURR              48
#define bINQ_GETPARAMBUFF              49
#define bINQ_GETPARAMFULL              50
+   #define bINQ_RESETDIVIDERS             51
#define bINQ_GETPARAMDIG               52

#define bINQ_GETBLOCKING1              60
#define bINQ_SETBLOCKING2              61
#define bINQ_SETBLOCKING3              62

#define bINQ_GETCONTACT_MODE           63
#define bINQ_SETCONTACT_MODE           64
#define bINQ_GETCONTACT_PASS           65
#define bINQ_SETCONTACT_PASS1          66
#define bINQ_SETCONTACT_PASS2          67

#define bINQ_GETKOEFF                  233

#define bINQ_GETIMPCANMNT              100
#define bINQ_GETIMPCANHOU              101
#define bINQ_GETIMPCANDAY              102
#define bINQ_GETIMPCANMON              103
#define bINQ_GETIMPCANABS              104

#define bINQ_GETIMPCANMNT_ALL          200
#define bINQ_GETIMPCANHOU_ALL          201
+   #define bINQ_GETIMPCANDAY_ALL          202 x2
+   #define bINQ_GETIMPCANMON_ALL          203 x2
#define bINQ_GETIMPCANABS_ALL          204

#define bINQ_GETCNTCANMON              140
#define bINQ_GETCNTCANMONPREV          141
#define bINQ_GETCNTCANMONCURR          142

#define bINQ_GETCNTCANMON_ALL          240
#define bINQ_GETCNTCANMONPREV_ALL      241   
#define bINQ_GETCNTCANMONCURR_ALL      242

#define bINQ_GETCNTCANNEW              107
#define bINQ_GETCNTCANOLD              108
//#define bINQ_GETCNTCAN                 231

#define bINQ_GETCNTCANNEW_ALL          207
#define bINQ_GETCNTCANOLD_ALL          208
//#define bINQ_GETCNTCAN_ALL             232

#define bINQ_GETIMPCANMNTCURR          109
#define bINQ_GETIMPCANMNTCURR_ALL      209


#define bINQ_GETPOWGRPMNTPREV          110
#define bINQ_GETPOWGRPMNT              111

#define bINQ_GETENGGRPMNTPREV_ALL      160
#define bINQ_GETENGGRPMNT_ALL          161

#define bINQ_GETPOWGRPMNTPREV_ALL      210
#define bINQ_GETPOWGRPMNT_ALL          211
#define bINQ_GETPOWCANMNT_ALL          206


#define bINQ_GETPOWGRPHOUPREV          112
#define bINQ_GETPOWGRPHOUCURR          113
#define bINQ_GETPOWGRPHOU              114

#define bINQ_GETENGGRPHOUPREV_ALL      162
#define bINQ_GETENGGRPHOUCURR_ALL      163
#define bINQ_GETENGGRPHOU_ALL          164

#define bINQ_GETPOWGRPHOUPREV_ALL      212
#define bINQ_GETPOWGRPHOUCURR_ALL      213
#define bINQ_GETPOWGRPHOU_ALL          214


#define bINQ_GETENGGRPDAYCURR          115
#define bINQ_GETENGGRPDAYPREV          116
#define bINQ_GETENGGRPDAY              117
#define bINQ_GETENGGRPMONCURR          118
#define bINQ_GETENGGRPMONPREV          119
#define bINQ_GETENGGRPMON              120

#define bINQ_GETENGGRPDAYCURR_ALLSUM   165
#define bINQ_GETENGGRPDAYPREV_ALLSUM   166
+   #define bINQ_GETENGGRPDAY_ALLSUM       167
#define bINQ_GETENGGRPMONCURR_ALLSUM   168
#define bINQ_GETENGGRPMONPREV_ALLSUM   169
+   #define bINQ_GETENGGRPMON_ALLSUM       170

#define bINQ_GETENGGRPDAYCURR_ALL      215
#define bINQ_GETENGGRPDAYPREV_ALL      216
+   #define bINQ_GETENGGRPDAY_ALL          217
#define bINQ_GETENGGRPMONCURR_ALL      218
#define bINQ_GETENGGRPMONPREV_ALL      219
+   #define bINQ_GETENGGRPMON_ALL          220


#define bINQ_GETMAXPOWGRPDAYCURR       121
#define bINQ_GETMAXPOWGRPDAYPREV       122
#define bINQ_GETMAXPOWGRPDAY           123
#define bINQ_GETMAXPOWGRPMONCURR       124
#define bINQ_GETMAXPOWGRPMONPREV       125
#define bINQ_GETMAXPOWGRPMON           126

#define bINQ_GETMAXPOWGRPDAYCURR_ALL   221
#define bINQ_GETMAXPOWGRPDAYPREV_ALL   222
#define bINQ_GETMAXPOWGRPDAY_ALL       223
#define bINQ_GETMAXPOWGRPMONCURR_ALL   224
#define bINQ_GETMAXPOWGRPMONPREV_ALL   225
#define bINQ_GETMAXPOWGRPMON_ALL       226

#define bINQ_GETTRATIMEDATE            227
#define bINQ_GETTRACNTCURRCAN          228
#define bINQ_GETTRACNTMONCAN           229

#define bINQ_GETTARIFFSDAY             150

#define bINQ_GETDEFHOU                 151
#define bINQ_GETDEFDAY                 152
#define bINQ_GETDEFMON                 153

#define bINQ_GETDEFHOU_INDEX           154
#define bINQ_GETDEFDAY_INDEX           155
#define bINQ_GETDEFMON_INDEX           156

#define bINQ_GETPOWGRPHOU_DAY          157
#define bINQ_GETIMPCANHOU_DAY          158
#define bINQ_GETPOWCANHOU_DAY          159
#define bINQ_GETDEFCANHOU_DAY          179

//#define bINQ_TRANSIT_INIT              171
#define bINQ_TRANSIT_EXECUTE           172
#define bINQ_TRANSIT_EXECUTE2          173
#define bINQ_TRANSIT_EXECUTE3          174
//#define bINQ_TRANSIT_DONE              173

#define bINQ_GETDEFIMPCANHOU           239

+   #define bINQ_SETKEY                    246
+   #define bINQ_GETDISPLAY                247

+   #define bINQ_GETCONFIG                 248
#define bINQ_GETFLASHPAGE              249

+   #define bINQ_QUICKMNT                  250
+   #define bINQ_QUICKMIN15                230
+   #define bINQ_QUICKHOU                  251
+   #define bINQ_QUICKDAY                  252
+   #define bINQ_QUICKMON                  253
+   #define bINQ_QUICKYEA                  254

#define bINQ_INFO                      244
#define bINQ_FLOW                      245

#define bINQ_ANSWER_ENABLE             231


-   #define bINQ_EXTENDED                  255

+   #define bEXT_GETPHONE                  1
+   #define bEXT_SETPHONE                  2

+   #define bEXT_GETSIMPLE_ESC_U           3
+   #define bEXT_GETSIMPLE_ESC_S           4

+   #define bEXT_GETTIME_ESC_S             5
+   #define bEXT_GETTIME_ESC_V             6

+   #define bEXT_GETGROUPS                 7
+   #define bEXT_GETDIGITALS               8
+   #define bEXT_GETPHONES                 9

+   #define bEXT_CORRECT1                  10
+   #define bEXT_CORRECT2                  11

+   #define bEXT_GETSTOPCAN                12
+   #define bEXT_GETENBLCAN                13
+   #define bEXT_GETCTRLHOU                14
+   #define bEXT_GETENBLPORTHOU            15

+   #define bEXT_GETIMPCANHOU              16
+   #define bEXT_GETADDRESSES              17
+   #define bEXT_GETIMPCANMNT              18
+   #define bEXT_GETPOWCANMNT              27

+   #define bEXT_GETRECORD                 19
+   #define bEXT_GETRECORDSBLOCK           20

//#define bEXT_BLOCKING1                 21
//#define bEXT_BLOCKING2                 22

#define bEXT_DOOR                      23

+   #define bEXT_GETENG3MIN_DATA           24
+   #define bEXT_GETENG3MIN_TIME           25

+   #define bEXT_GETENGGRPHOU_ALL          26
 
+   #define bEXT_GETADDRESS                28
+   #define bEXT_SETADDRESS                29

#define bEXT_GETCORRECT_1              31
#define bEXT_GETCORRECT_2              51

#define bEXT_GETMAXPOWGRPDAY_CUST1     33
+   #define bEXT_GETCURRENT                35
#define bEXT_GETMAXPOWGRPDAY_CUST2     36
#define bEXT_GETCNTCANMON              37

#define bEXT_GETCONTACT3               39

#define bEXT_GETRECALC                 41

+   #define bEXT_GETEXTENDED40             42
+   #define bEXT_GETEXTENDED41             43
+   #define bEXT_GETEXTENDED42             44

+   #define bEXT_GETRELAXS                 45
+   #define bEXT_SETRELAXS                 46

#define bEXT_GETEXTENDED30             47
#define bEXT_GETEXTENDED31             48

+   #define bEXT_GETEXTENDED50             49
+   #define bEXT_GETEXTENDED51             50

+   #define bEXT_GETSTARTCAN               52
+   #define bEXT_GETVERSION                53

#define bEXT_GETPHONES2                54
+   #define bEXT_GETPORTS                  55

+   #define bEXT_CORRECT20                 56
+   #define bEXT_CORRECT21                 57
#define bEXT_GETACE                    58
+   #define bEXT_CORRECT3                  59

+   #define bEXT_GETEXTENDED401            60
+   #define bEXT_GETEXTENDED43             61
+   #define bEXT_GETEXTENDED6              62

+   #define bEXT_GETENGCANDAY              65
+   #define bEXT_GETENGCANMON              66
+   #define bEXT_GETSTOPCAN2               67

+   #define bEXT_GETOUTPUTDELAY            68
+   #define bEXT_GETCORRECTLIMIT           69
+   #define bEXT_GETLINKERRORS             70
#define bEXT_GETHOUCHECK               71

+   #define bEXT_SETCTRLHOU                72
+   #define bEXT_SETENBLPORTHOU            73
+   #define bEXT_SETRECALC1                74
+   #define bEXT_SETRECALC2                75

+   #define bEXT_GETHOUCANDEF              76
+   #define bEXT_GETHOUGRPDEF              91
+   #define bEXT_GETDAYCANDEF_ALL          77
+   #define bEXT_GETMONCANDEF_ALL          78
+   #define bEXT_GETDAYGRPDEF_ALL          79
+   #define bEXT_GETMONGRPDEF_ALL          80
+   #define bEXT_GETDAYCANDEF              81
+   #define bEXT_GETMONCANDEF              82
+   #define bEXT_GETDAYGRPDEF              83
+   #define bEXT_GETMONGRPDEF              84

+   #define bINQ_GETENGGRPDAY_DEF          85
+   #define bINQ_GETENGGRPMON_DEF          86
+   #define bINQ_GETMAXPOWGRPDAY_DEF       87
+   #define bINQ_GETMAXPOWGRPMON_DEF       88
+   #define bINQ_GETENGGRPHOUPREV_DEF      89
+   #define bINQ_GETPOWGRPHOUPREV_DEF      90

#define bINQ_GETDIAGRAM                95
+   #define bINQ_GETGAPS1                  96
+   #define bINQ_GETGAPS2                  97

#define bINQ_FAILURE2                  98

+   #define bEXT_GETRECORDSBLOCK2          99
+   #define bEXT_GETEXTENDED7              100
#define bEXT_ANSWER_DISABLE            101
#define bEXT_CONTROL_R                 102
+   #define bEXT_OVERFLOW_HOU              103

+   #define bEXT_GETSTOPAUXCAN             104
+   #define bEXT_GETDECRET                 105
+   #define bEXT_GETSTART                  106
#define bEXT_GETBULK                   107
#define bEXT_GETMNTCURRENT2            108
+   #define bEXT_RECORD_DISABLE            109
+   #define bEXT_GETENGFRACDIGCAN          110

+   #define bEXT_GETOBJECTNAME             111
+   #define bEXT_SETOBJECTNAME             112
+   #define bEXT_GETCANALNAME              113
+   #define bEXT_SETCANALNAME              114
+   #define bEXT_GETGROUPNAME              115
+   #define bEXT_SETGROUPNAME              116

+   #define bEXT_GETEXTENDED40_T           119

#define bEXT_CHECKUP                   120
#define bEXT_CHECKUP_EVENT_DAY         121
#define bEXT_GET_CHECKUP_HOU           122
#define bEXT_SET_CHECKUP_HOU           123
#define bEXT_CHECKUP_DEFECT_DAY        124
#define bEXT_CHECKUP_DEFECT_MON        125
#define bEXT_CHECKUP_EVENT_MON         126
#define bEXT_CHECKUP_DAYS              127

+   #define bEXT_FLASH_CONTROL             250
