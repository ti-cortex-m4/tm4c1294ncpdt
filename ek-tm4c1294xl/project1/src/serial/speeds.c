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
                        szOnlyDirect[]= "для прямой связи",
                        szOnlyModem[] = "   для модема   ";



// массив значений скоростей обмена
ulong                   mpdwSpeeds[bSPEEDS] =
{ 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400 };


// массив таймаутов на приём для портов RS-232 (время передачи 100 бит на данной скорости)
uchar                   mpwInDelaySlave[bSPEEDS] =
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
uint                    mpwInDelayMaster[bSPEEDS] =
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



bool    IsMaster(uchar  i)
{
  return((mppoPorts[i].enStream == STR_MASTERDIRECT) || (mppoPorts[i].enStream == STR_MASTERMODEM));
}


bool    IsSlave(uchar  i)
{
  return( ~IsMaster(i) );
}



void    SetCorrectLimit(uchar  i)
{
//  mpbCorrectLimit[i] = (mppoPorts[i].enStream == STR_MASTERMODEM) ? bCORRECT_MODEM : bCORRECT_DIRECT;
}


void    CheckCorrectLimit(uchar  i)
{
//  if (mpbCorrectLimit[i] < bCORRECT_MINIMUM) SetCorrectLimit(i);
//  if (mpbCorrectLimit[i] > bCORRECT_MAXIMUM) mpbCorrectLimit[i] = bCORRECT_MAXIMUM;
}


void    MakeCorrectLimit(void)
{
//  if (diT.bDevice == 24) mpbCorrectLimit[diT.ibPort] = bCORRECT_DEVICE_S;
}



void    SetDelay(uchar  i)    
{
uint    j;

  mpSerial[i] = SER_BEGIN;

  if ((mppoPorts[i].enStream == STR_MASTERDIRECT) || 
      (mppoPorts[i].enStream == STR_MASTERMODEM))
    j = mpwInDelayMaster[ mppoPorts[i].ibSpeed ];
  else
    j = mpwInDelaySlave[ mppoPorts[i].ibSpeed ];

  mpwMajInDelay[i] = j;
  mpwMinInDelay[i] = j;
}


/*
void    ResetAllSerial(void)
{
uchar   i;

  // ожидаем окончания передачи
  DelayInf(); 

  // сбрасываем состояния для возможности переключения в ведомый режим
  for (i=0; i<bPORTS; i++) mpSerial[i] = SER_BEGIN;
}
*/


void    ResetSpeeds(void)
{  
uchar   i;

  mppoPorts[0].enStream = STR_SLAVEESC;
  mppoPorts[1].enStream = STR_SLAVEESC;
  mppoPorts[2].enStream = STR_MASTERDIRECT;
  mppoPorts[3].enStream = STR_MASTERDIRECT;

  for (i=0; i<bPORTS; i++)
  {
    mppoPorts[i].ibSpeed  = 3;
    mppoPorts[i].ibParity = 0;

    mpibActives[i] = 0;

    SetDelay(i);
    SetCorrectLimit(i);
  }
}



void    SetSpeeds(uchar  i)
{
  mpSerial[i] = SER_BEGIN;

  switch (i)
  {
    case 0:  SetSpeed0();  break;
    case 1:  SetSpeed1();  break;
    case 2:  SetSpeed2();  break;
    case 3:  SetSpeed3();  break;
  }

  ResetSendAT();
}



void    InitSpeeds(void)
{
uchar   i;

  for (i=0; i<bPORTS; i++)
  {
    if (mppoPorts[i].ibSpeed >= bSPEEDS)
    {
      mppoPorts[i].ibSpeed = 0;
      SetDelay(i);
    }

    if (mppoPorts[i].enStream >= bSTREAMS)
      mppoPorts[i].enStream = STR_SLAVEESC;

    SetSpeeds(i);               
    CheckCorrectLimit(i);
  }
}



void    ShowSpeeds(uchar  i, bool fShow)
{
  ClearLo();
  sprintf(szLo+1,"%-6lu",mpdwSpeeds[ mppoPorts[i].ibSpeed ]);
  sprintf(szLo+15,"%u",i+1);

  if (mppoPorts[i].ibParity < bPARITYS)
    szLo[8] = szParitys[ mppoPorts[i].ibParity ];
  else
    szLo[8] = '?';

  if (mppoPorts[i].enStream < bSTREAMS)
    ShowHi(msgStreams[ mppoPorts[i].enStream ]);
  else 
    ShowHi(szError);

  if (fShow)
  {
    if (IsMaster(i))
      (mpboLocalDisable[i] == TRUE) ? (szLo[13] = '-') : (szLo[13] = '+');
    else
      szLo[13] = ' ';
  }

  if (enGlobal != GLB_WORK) 
    szLo[0] = '.';
}



bool    StreamPort(uchar  i)
{
  if ((mppoPorts[i].enStream == STR_MASTERDIRECT) ||
      (mppoPorts[i].enStream == STR_MASTERMODEM)) return(1);
  else
  {
    SaveDisplay();

    ClearLo();
    sprintf(szHi,"Порт %u: нужны",i+1);
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


bool    StreamPortDirect(uchar  i)
{
  if (mppoPorts[i].enStream == STR_MASTERDIRECT) return(1);
  else
  {
    ShowStreamPort(szOnlyDirect);
    return(0);
  }
}


bool    StreamPortModem(uchar  i)
{
  if (mppoPorts[i].enStream == STR_MASTERMODEM) return(1);
  else
  {
    ShowStreamPort(szOnlyModem);
    return(0);
  }
}



void    ShowStreamPortCan(char const  *szT, uchar  i, uchar  ibCanal)
{
  SaveDisplay();

  ShowHi(szWarning);
  sprintf(szLo,"    канала %bu    ",ibCanal+1);
  DelayMsg();

  sprintf(szHi,"Порт %bu: нужны   ",i+1);
  ShowLo(szT);
  DelayMsg();

  BlockPrograms(bSET_SPEED,bSET_DIGITALS);
  DelayMsg();

  LoadDisplay();
}



bool    StreamPortCan(uchar  i, uchar  ibCanal)
{
  if ((mppoPorts[i].enStream == STR_MASTERDIRECT) ||
      (mppoPorts[i].enStream == STR_MASTERMODEM)) return(1);
  else
  {
    ShowStreamPortCan(szMasters,i,ibCanal);
    return(0);
  }
}



bool    StreamPortPhoneCan(uchar  i, uchar  ibPhone, uchar  ibCanal)
{
  if ((mppoPorts[i].enStream == STR_MASTERDIRECT) && (ibPhone != 0)) 
  {
    ShowStreamPortCan(szDirectYes,i,ibCanal);
    return(0);
  }
  else
  if ((mppoPorts[i].enStream == STR_MASTERMODEM) && (ibPhone == 0)) 
  {
    ShowStreamPortCan(szDirectNo,i,ibCanal);
    return(0);
  }
  else return(1);
}
