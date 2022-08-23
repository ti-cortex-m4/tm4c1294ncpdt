/*------------------------------------------------------------------------------
QUERIES!H

 «апросы
------------------------------------------------------------------------------*/


#ifndef __INQUIRYS
#define __INQUIRYS

#define bINQ_GETGLOBAL                 0
#define bINQ_GETCURRTIME               1
#define bINQ_GETLOGICAL                3
#define bINQ_GETPRIVATE                5

#define bINQ_GETGROUP                  9
#define bINQ_SETGROUP                  10

#define bINQ_GETOLDMODE                16

#define bINQ_CORRECT1                  11
#define bINQ_CORRECT2                  12
#define bINQ_CORRECT3                  13
#define bINQ_CORRECT4                  238

#define bINQ_GETPUBLIC_TARIFFS         14
#define bINQ_SETPUBLIC_TARIFFS         15

#define bINQ_GETOLDPOWTARIFFS          18
#define bINQ_SETOLDPOWTARIFFS          19
#define bINQ_GETOLDENGTARIFFS          20
#define bINQ_SETOLDENGTARIFFS          21
#define bINQ_GETOLDPUBTARIFFS          22
#define bINQ_SETOLDPUBTARIFFS          23

#define bINQ_GETNEWPOWTARIFFS          24
#define bINQ_SETNEWPOWTARIFFS          25
#define bINQ_GETNEWENGTARIFFS          26
#define bINQ_SETNEWENGTARIFFS          27
#define bINQ_GETNEWPUBTARIFFS          28
#define bINQ_SETNEWPUBTARIFFS          29

#define bINQ_GETTRANS_ENG              30
#define bINQ_SETTRANS_ENG              31
#define bINQ_GETTRANS_CNT              32
#define bINQ_SETTRANS_CNT              33
#define bINQ_GETPULSE_HOU              34
#define bINQ_SETPULSE_HOU              35
#define bINQ_GETPULSE_MNT              234
#define bINQ_SETPULSE_MNT              235
#define bINQ_GETVALUE_ENGHOU           36
#define bINQ_GETVALUE_CNTHOU           37
#define bINQ_GETVALUE_ENGMNT           236
#define bINQ_GETVALUE_CNTMNT           237
#define bINQ_GETCOUNT                  38
#define bINQ_SETCOUNT                  39
#define bINQ_GETLOSSE                  40
#define bINQ_SETLOSSE                  41
#define bINQ_GETLEVEL                  180
#define bINQ_SETLEVEL                  181
#define bINQ_GETKOEFF                  233

#define bINQ_GETDIGITAL                42
#define bINQ_SETDIGITAL                43

#define bINQ_GETPARAMS_100             53
#define bINQ_GETPARAM                  44
#define bINQ_SETPARAM                  45
#define bINQ_GETPARAM_DIV              46
#define bINQ_SETPARAM_DIV              47
#define bINQ_GETPARAM_CURR             48
#define bINQ_GETPARAM_BUFF             49
#define bINQ_GETPARAM_FULL             50
#define bINQ_RESETDIVIDERS             51
#define bINQ_GETPARAMS_ALL             52

#define bINQ_GETIMPCANMNT              100
#define bINQ_GETIMPCANHOU              101
#define bINQ_GETIMPCANDAY              102
#define bINQ_GETIMPCANMON              103
#define bINQ_GETIMPCANABS              104

#define bINQ_GETIMPCANMNT_ALL          200
#define bINQ_GETIMPCANHOU_ALL          201
#define bINQ_GETIMPCANDAY_ALL          202
#define bINQ_GETIMPCANMON_ALL          203
#define bINQ_GETIMPCANABS_ALL          204

#define bINQ_GETCNTCANNEW              107
#define bINQ_GETCNTCANOLD              108

#define bINQ_GETCNTCANNEW_ALL          207
#define bINQ_GETCNTCANOLD_ALL          208

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
#define bINQ_GETPOWGRPHOUCURR          113 // прогнозируема€ получасова€ средн€€ мощность
#define bINQ_GETPOWGRPHOU              114

#define bINQ_GETENGGRPHOUPREV_ALL      162
#define bINQ_GETENGGRPHOUCURR_ALL      163 // прогнозируема€ получасова€ средн€€ энерги€
#define bINQ_GETENGGRPHOU_ALL          164

#define bINQ_GETPOWGRPHOUPREV_ALL      212
#define bINQ_GETPOWGRPHOUCURR_ALL      213 // прогнозируема€ получасова€ средн€€ мощность
#define bINQ_GETPOWGRPHOU_ALL          214

#define bINQ_GETENGGRPDAYCURR          115
#define bINQ_GETENGGRPDAYPREV          116
#define bINQ_GETENGGRPDAY              117
#define bINQ_GETENGGRPMONCURR          118
#define bINQ_GETENGGRPMONPREV          119
#define bINQ_GETENGGRPMON              120

#define bINQ_GETENGGRPDAYCURR_ALLSUM   165
#define bINQ_GETENGGRPDAYPREV_ALLSUM   166
#define bINQ_GETENGGRPDAY_ALLSUM       167
#define bINQ_GETENGGRPMONCURR_ALLSUM   168
#define bINQ_GETENGGRPMONPREV_ALLSUM   169
#define bINQ_GETENGGRPMON_ALLSUM       170

#define bINQ_GETENGGRPDAYCURR_ALL      215
#define bINQ_GETENGGRPDAYPREV_ALL      216
#define bINQ_GETENGGRPDAY_ALL          217
#define bINQ_GETENGGRPMONCURR_ALL      218
#define bINQ_GETENGGRPMONPREV_ALL      219
#define bINQ_GETENGGRPMON_ALL          220

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

#define bINQ_GETTARIFFSDAY             150

#define bINQ_GETPOWGRPHOU_DAY          157
#define bINQ_GETIMPCANHOU_DAY          158
#define bINQ_GETPOWCANHOU_DAY          159
#define bINQ_GETDEFCANHOU_DAY          179

#define bINQ_TRANSIT_EXECUTE1          172
#define bINQ_TRANSIT_EXECUTE2          173
#define bINQ_TRANSIT_EXECUTE3          174
#define bINQ_TRANSIT_EXECUTE4          175
#define bINQ_TRANSIT_W                 176
#define bINQ_TRANSIT_DEVICE40          177

#define bINQ_ENBL_ANSWER               231

#define bINQ_FLOW                      245

#define bINQ_SETKEY                    246
#define bINQ_GETDISPLAY                247

#define bINQ_GETCONFIG                 248

#define bINQ_GETFLASHPAGE              249

#define bINQ_RESPONSE_252              252
#define bINQ_RESPONSE_253              253
#define bINQ_RESPONSE_254              254
#define bINQ_RESPONSE_255              255


// результаты обработки Esc-запросов
#define bESC_OK                        'O'
#define bESC_BADCOMMAND                'C'
#define bESC_BADADDRESS                'A'
#define bESC_BADDATA                   'D'
#define bESC_BADSIZE                   'S'
#define bESC_BADMODE                   'M'
#define bESC_BADFLASH                  'F'
#define bESC_BADDIGITAL                'D'


// результаты обработки CRC-запросов
#define bRES_OK                        0
#define bRES_BADCOMMAND                1
#define bRES_BADADDRESS                2
#define bRES_BADDATA                   3
#define bRES_BADSIZE                   4
#define bRES_BADMODE                   5
#define bRES_BADFLASH                  6
#define bRES_BADDIGITAL                7
#define bRES_BADPORT                   8
#define bRES_BADACCESS                 9
#define bRES_BADCORRECTION             10
#define bRES_BUSY                      11
#define bRES_OUTOVERFLOW               99
#define bRES_NEEDPROGRAM               100
#define bRES_NEEDWORK                  101
#define bRES_NEEDREPROGRAM             102


#endif
