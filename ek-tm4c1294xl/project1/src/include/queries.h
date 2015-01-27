/*------------------------------------------------------------------------------
QUERIES.H

 Запросы
------------------------------------------------------------------------------*/


#ifndef __INQUIRYS
#define __INQUIRYS


#define bINQ_GETCURRTIME               1

#define bINQ_GETGROUP                  9
#define bINQ_SETGROUP                  10

#define bINQ_GETPUBLIC                 14
#define bINQ_SETPUBLIC                 15
#define bINQ_GETOLDMODE                16
#define bINQ_SETOLDMODE                17

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

#define bINQ_SETDELAY                  243

#define bINQ_GETFLASHPAGE              249

#define bINQ_SETKEY                    246
#define bINQ_GETDISPLAY                247


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
