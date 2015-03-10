/*------------------------------------------------------------------------------
SPEEDS.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../keyboard/keyboard.h"
#include        "../display/display.h"
#include        "../serial/ports.h"
#include        "../include/programs.h"
#include        "speeds.h"



//                                       0123456789ABCDEF        
message                 msgStreams[bSTREAMS] =
                                      { "Ведомый,Esc+CRC ",
#ifndef MODBUS
                                        "Ведомый,CRC     ",
#else
                                        "Ведомый,Modbus  ",
#endif
                                        "Ведущий,прямой  ",
                                        "Ведущий,модемный",
                                        "Ведомый,УПИО    "};

static char const       szMasters[]   = " ведущие режимы ",
                        szDirectYes[] = "прямая связь: 0 ",
                        szDirectNo[]  = "телефонный номер",
                        szFunction[]  = "Данная функция: ",
                        szDirectOnly[]= "для прямой связи",
                        szModemOnly[] = "   для модема   ";



// массив значений скоростей обмена
static ulong const      mpdwSpeeds[bSPEEDS] =
{ 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400 };

// массив таймаутов на приём для портов RS-232 (время передачи 100 бит на данной скорости)
static uint const       mpwInDelaySlave[bSPEEDS] =
{
  (uint)(wFREQUENCY_T0*0.0833),
  (uint)(wFREQUENCY_T0*0.0417),
  (uint)(wFREQUENCY_T0*0.0208),
  (uint)(wFREQUENCY_T0*0.0104),
  (uint)(wFREQUENCY_T0*0.0052),
  (uint)(wFREQUENCY_T0*0.0035),
  (uint)(wFREQUENCY_T0*0.0035),
  (uint)(wFREQUENCY_T0*0.0035),
  (uint)(wFREQUENCY_T0*0.0035)
};

// массив таймаутов на приём для порта RS-485 (300 миллисекунд плюс время передачи 1000 бит на данной скорости)
static uint const       mpwInDelayMaster[bSPEEDS] =
{
  (uint)(wFREQUENCY_T0*1.1333),
  (uint)(wFREQUENCY_T0*0.7167),
  (uint)(wFREQUENCY_T0*0.5083),
  (uint)(wFREQUENCY_T0*0.4042),
  (uint)(wFREQUENCY_T0*0.3521),
  (uint)(wFREQUENCY_T0*0.3260),
  (uint)(wFREQUENCY_T0*0.3174),
  (uint)(wFREQUENCY_T0*0.3087),
  (uint)(wFREQUENCY_T0*0.3044)
};

// четности
static char const       szParitys[]     = "neoms";



void    SetSpeed0(void)
{
}



void    SetSpeed1(void)
{
}



void    SetSpeed2(void)
{
}



void    SetSpeed3(void)
{
}



bool    IsMaster(uchar  ibPrt)
{
  return((mppoPorts[ibPrt].enStream == STR_MASTERDIRECT) || (mppoPorts[ibPrt].enStream == STR_MASTERMODEM));
}


bool    IsSlave(uchar  ibPrt)
{
  return( ~IsMaster(ibPrt) );
}



void    SetCorrectLimit(uchar  ibPrt)
{
//  mpbCorrectLimit[ibPrt] = (mppoPorts[ibPrt].enStream == STR_MASTERMODEM) ? bCORRECT_MODEM : bCORRECT_DIRECT;
}


void    CheckCorrectLimit(uchar  ibPrt)
{
//  if (mpbCorrectLimit[ibPrt] < bCORRECT_MINIMUM) SetCorrectLimit(ibPrt);
//  if (mpbCorrectLimit[ibPrt] > bCORRECT_MAXIMUM) mpbCorrectLimit[ibPrt] = bCORRECT_MAXIMUM;
}


void    MakeCorrectLimit(void)
{
//  if (diT.bDevice == 24) mpbCorrectLimit[diT.ibPort] = bCORRECT_DEVICE_S;
}



void    SetDelay(uchar  ibPrt)    
{
uint    w;

  mpSerial[ibPrt] = SER_BEGIN;

  if ((mppoPorts[ibPrt].enStream == STR_MASTERDIRECT) || 
      (mppoPorts[ibPrt].enStream == STR_MASTERMODEM))
    w = mpwInDelayMaster[ mppoPorts[ibPrt].ibSpeed ];
  else
    w = mpwInDelaySlave[ mppoPorts[ibPrt].ibSpeed ];

  mpwMajInDelay[ibPrt] = w;
  mpwMinInDelay[ibPrt] = w;
}



void    ResetSpeeds(void)
{  
uchar   i;

  mppoPorts[0].enStream = STR_SLAVEESC;
  mppoPorts[1].enStream = STR_SLAVEESC;
  mppoPorts[2].enStream = STR_MASTERDIRECT;
  mppoPorts[3].enStream = STR_MASTERDIRECT;

  for (i=0; p<bPORTS; p++)
  {
    mppoPorts[p].ibSpeed  = 3;
    mppoPorts[p].ibParity = 0;

    SetDelay(p);
    SetCorrectLimit(p);
  }
}



void    SetSpeeds(uchar  ibPrt)
{
  mpSerial[ibPrt] = SER_BEGIN;

  switch (ibPrt)
  {
    case 0:  SetSpeed0();  break;
    case 1:  SetSpeed1();  break;
    case 2:  SetSpeed2();  break;
    case 3:  SetSpeed3();  break;
  }
}



void    InitSpeeds(void)
{
uchar   p;

  for (p=0; p<bPORTS; p++)
  {
    if (mppoPorts[p].ibSpeed >= bSPEEDS)
    {
      mppoPorts[p].ibSpeed = 0;
      SetDelay(p);
    }

    if (mppoPorts[p].enStream >= bSTREAMS)
      mppoPorts[p].enStream = STR_SLAVEESC;

    SetSpeeds(p);               
    CheckCorrectLimit(p);
  }
}



void    ShowSpeeds(uchar  ibPrt, bool  fShowLocalDisable)
{
  Clear();
  sprintf(szLo+1,"%-6lu",mpdwSpeeds[ mppoPorts[ibPrt].ibSpeed ]);
  sprintf(szLo+15,"%u",ibPrt+1);

  if (mppoPorts[ibPrt].ibParity < bPARITYS)
    szLo[8] = szParitys[ mppoPorts[ibPrt].ibParity ];
  else
    szLo[8] = '?';

  if (mppoPorts[ibPrt].enStream < bSTREAMS)
    ShowHi(msgStreams[ mppoPorts[ibPrt].enStream ]);
  else 
    ShowHi(szError);

  if (fShowLocalDisable)
  {
    if (IsMaster(ibPrt))
      (mpboLocalDisable[ibPrt] == TRUE) ? (szLo[13] = '-') : (szLo[13] = '+');
    else
      szLo[13] = ' ';
  }

  if (enGlobal != GLB_WORK) 
    szLo[0] = '.';
}



bool    StreamPort(uchar  ibPrt)
{
  if ((mppoPorts[ibPrt].enStream == STR_MASTERDIRECT) ||
      (mppoPorts[ibPrt].enStream == STR_MASTERMODEM)) return(1);
  else
  {
    SaveDisplay();

    Clear();
    sprintf(szHi,"Порт %u: нужны",ibPrt+1);
    ShowLo(szMasters);
    DelayMsg();

    BlockProgram(bSET_SPEED);
    DelayMsg();

    LoadDisplay();
    return(0);
  }
}



void    ShowStreamPort(char const  *szT)
{
  SaveDisplay();

  ShowHi(szFunction);
  ShowLo(szT);
  DelayMsg();

  BlockProgram(bSET_SPEED);
  DelayMsg();

  LoadDisplay();
}


bool    StreamPortDirect(uchar  ibPrt)
{
  if (mppoPorts[ibPrt].enStream == STR_MASTERDIRECT) return(1);
  else
  {
    ShowStreamPort(szDirectOnly);
    return(0);
  }
}


bool    StreamPortModem(uchar  ibPrt)
{
  if (mppoPorts[ibPrt].enStream == STR_MASTERMODEM) return(1);
  else
  {
    ShowStreamPort(szModemOnly);
    return(0);
  }
}



void    ShowStreamPortCan(char const  *szT, uchar  ibPrt, uchar  ibCan)
{
  SaveDisplay();

  ShowHi(szWarning);
  Clear();
  sprintf(szLo+4,"канала %u",ibCan+1);
  DelayMsg();

  Clear();
  sprintf(szHi,"Порт %u: нужны",ibPrt+1);
  ShowLo(szT);
  DelayMsg();

  BlockPrograms(bSET_SPEED,bSET_DIGITALS);
  DelayMsg();

  LoadDisplay();
}



bool    StreamPortCan(uchar  ibPrt, uchar  ibCan)
{
  if ((mppoPorts[ibPrt].enStream == STR_MASTERDIRECT) ||
      (mppoPorts[ibPrt].enStream == STR_MASTERMODEM)) return(1);
  else
  {
    ShowStreamPortCan(szMasters,ibPrt,ibCan);
    return(0);
  }
}



bool    StreamPortPhoneCan(uchar  ibPrt, uchar  ibPhn, uchar  ibCan)
{
  if ((mppoPorts[ibPrt].enStream == STR_MASTERDIRECT) && (ibPhn != 0)) 
  {
    ShowStreamPortCan(szDirectYes,ibPrt,ibCan);
    return(0);
  }
  else
  if ((mppoPorts[ibPrt].enStream == STR_MASTERMODEM) && (ibPhn == 0)) 
  {
    ShowStreamPortCan(szDirectNo,ibPrt,ibCan);
    return(0);
  }
  else return(1);
}
