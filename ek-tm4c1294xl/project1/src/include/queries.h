/*------------------------------------------------------------------------------
QUERIES.H

 Запросы
------------------------------------------------------------------------------*/


#ifndef __INQUIRYS
#define __INQUIRYS


#define bINQ_GETCURRTIME               1

#define bINQ_GETGROUP                  9
#define bINQ_SETGROUP                  10

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

#define bINQ_GETDIGITAL                42
#define bINQ_SETDIGITAL                43

#define bINQ_GETTARIFFSDAY             150

#define bINQ_SETDELAY                  243

#define bINQ_GETFLASHPAGE              249

#define bINQ_SETKEY                    246
#define bINQ_GETDISPLAY                247

#define bINQ_RESPONSE2                 255


// TODO
#define bESC_OK                        'O'
#define bESC_BADCOMMAND                'C'
#define bESC_BADADDRESS                'A'
#define bESC_BADDATA                   'D'
#define bESC_BADSIZE                   'S'
#define bESC_BADMODE                   'M'
#define bESC_BADFLASH                  'F'
#define bESC_BADDIGITAL                'D'


// TODO
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
