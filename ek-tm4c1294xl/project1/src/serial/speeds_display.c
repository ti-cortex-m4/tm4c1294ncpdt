/*------------------------------------------------------------------------------
SPEEDS_DISPLAY.C


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



// массив четностей
static char const       szParitys[]     = "neoms";



void    ShowSpeeds(uchar  ibPrt, bool  fShowLocalDisable)
{
  Clear();
  sprintf(szLo+1,"%-6lu",mpdwBauds[ mppoPorts[ibPrt].ibBaud ]);
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

    ShowHi(szClear);
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

  ShowHi(szClear);
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
