/*------------------------------------------------------------------------------
_ANOTHER.C


------------------------------------------------------------------------------*/
/*
#include        <intrins.h>
#include        "main.h"
#include        "xdata.h"
#include        "beep.h"
#include        "timer0.h"
#include        "display.h"
#include        "keyboard.h"
#include        "programs.h"
#include        "nexttime.h"
#include        "engine.h"
#include        "timedate.h"
#include        "ports.h"
#include        "params.h"
#include        "devices_far.h"
#include        "general_far.h"



//                                         0123456789ABCDEF
message         code    szParamCurr    = "Значения        ",
                        szParamBuff    = "Значения: буфер ",
                        szParamFull    = "Значения: массив";




void    ShowParamCurr(void)
{
  if (GetParamDevice(iwA) == 0)
    ShowLo(szEmpty);
  else
  {
    boBeginParam = FALSE;

    LoadCurrParam(iwA);
    ibPort = diCurr.ibPort;

    if (mpboEnblPar[iwA] == FALSE)
      ShowLo(szBlocking); 
    else if (diCurr.ibPhone != 0)
      ShowLo(szEmpty);
    else if (ReadParam(iwA) == 1) 
      sprintf(szLo,"%12.3f", reBuffA);
    else
      Error();   
  }
}


void    ShowParamBuff(void)
{
  if (GetParamDevice(iwA) == 0)
    ShowLo(szEmpty);
  else
  {
    if (mpboEnblPar[iwA] == FALSE)
      ShowLo(szBlocking); 
    else
    {
      tiAlt = mptiParBuff[iwA];

      switch (ibY)
      {
        case 0:  reBuffA = mpreParBuff[ibSoftTim][iwA];
                 sprintf(szLo,"%12.3f", reBuffA); break;

        case 1:  ShowTime();  break;
        case 2:  ShowDate();  break;
      }
    }
  }
}


void    ShowParamFull(void)
{
  if (GetParamDevice(iwA) == 0)
    ShowLo(szEmpty);
  else
  {
    if (mpboEnblPar[iwA] == FALSE)
      ShowLo(szBlocking); 
    else
    {
       if (LoadParTim((wTIMES + iwHardTim - iwAmin) % wTIMES) == 1)
       {
         sprintf(szHi+12,"-%03u",iwAmin);

         reBuffA = mpreParBuff[ PrevSoftTim() ][ iwA ];

         if (_chkfloat_(reBuffA) < 2)
           sprintf(szLo,"%12.3f", reBuffA); 
         else
           ShowLo(szEmpty);
       }
       else Error();
    }
  }
}



void    ShowAnother(void)
{   
  switch (GetParamLine(iwA))
  {
    case PAR_P  : ShowHi(szRecP);  break;
    case PAR_P1 : ShowHi(szRecP1); break;
    case PAR_P2 : ShowHi(szRecP2); break;
    case PAR_P3 : ShowHi(szRecP3); break;

    case PAR_Q  : ShowHi(szRecQ);  break;
    case PAR_Q1 : ShowHi(szRecQ1); break;
    case PAR_Q2 : ShowHi(szRecQ2); break;
    case PAR_Q3 : ShowHi(szRecQ3); break;

    case PAR_S  : ShowHi(szRecS);  break;
    case PAR_S1 : ShowHi(szRecS1); break;
    case PAR_S2 : ShowHi(szRecS2); break;
    case PAR_S3 : ShowHi(szRecS3); break;

    case PAR_U  : ShowHi(szRecU);  break;
    case PAR_U1 : ShowHi(szRecU1); break;
    case PAR_U2 : ShowHi(szRecU2); break;
    case PAR_U3 : ShowHi(szRecU3); break;

    case PAR_I  : ShowHi(szRecI);  break;
    case PAR_I1 : ShowHi(szRecI1); break;
    case PAR_I2 : ShowHi(szRecI2); break;
    case PAR_I3 : ShowHi(szRecI3); break;

    case PAR_C  : ShowHi(szRecC);  break;
    case PAR_C1 : ShowHi(szRecC1); break;
    case PAR_C2 : ShowHi(szRecC2); break;
    case PAR_C3 : ShowHi(szRecC3); break;

    case PAR_F  : ShowHi(szRecF);  break;
    case PAR_F1 : ShowHi(szRecF1); break;
    case PAR_F2 : ShowHi(szRecF2); break;
    case PAR_F3 : ShowHi(szRecF3); break;

    default:      ShowHi(szRecNo); break;
  }

  switch (bProgram)
  { 
    case bGET_PARAMCURR: ShowParamCurr();  break;
    case bGET_PARAMBUFF: ShowParamBuff();  break;
    case bGET_PARAMFULL: ShowParamFull();  break;
  }

  sprintf(szLo+13,"%3u",iwA+1);
}



void    key_GetAnother(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Param();

      switch (bProgram)
      { 
        case bGET_PARAMCURR: ShowHi(szParamCurr); break;
        case bGET_PARAMBUFF: ShowHi(szParamBuff); break;
        case bGET_PARAMFULL: ShowHi(szParamFull); break;
      }
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      ibY = 0;
      iwAmin = 0;

      iwA = 0;
      ShowAnother();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((iwA = GetInt(10,12) - 1) < wPARAMS)
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        ShowAnother();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++iwA >= wPARAMS) iwA = 0;

      ibY = 0; 
      iwAmin = 0;

      ShowAnother();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if (iwA > 0) iwA--; else iwA = wPARAMS - 1;

      ibY = 0; 
      iwAmin = 0;

      ShowAnother();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {        
    if (++ibY >= 3) ibY = 0;
    if (++iwAmin >= wTIMES) iwAmin = 0;

    ShowAnother();
  }


  else if (bKey < 10)
  {        
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,12);
    }
    else Beep();
  }
  else Beep();
}
*/







