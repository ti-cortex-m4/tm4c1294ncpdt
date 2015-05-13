/*------------------------------------------------------------------------------
KEY_PARAMS_ALL.C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../console.h"
#include "../../../digitals/params/params.h"
#include "../../../digitals/params/params2.h"
#include "../../../digitals/params/params_storage.h"
#include "../../../digitals/digitals_messages.h"
#include "../../../realtime/realtime.h"
#include "../../../time/timedate_display.h"
#include "../../../serial/ports.h"
#include "../../../flash/files.h"
#include "../../../kernel/float.h"
#include "../../../engine.h"



//                                         0123456789ABCDEF
static char const       szParamCurr[]  = "Значения        ",
                        szParamBuff[]  = "Значения: буфер ",
                        szParamFull[]  = "Значения: массив";


static uint             iwPrm, iwTim, ibVal;



static void ShowParamCurr(void)
{
  if (GetParamDevice(iwPrm) == 0)
    ShowLo(szEmpty);
  else
  {
    boBeginParam = FALSE;

    LoadCurrParam(iwPrm);
    ibPort = diCurr.ibPort;

    if (mpboEnblParams[iwPrm] == FALSE)
      ShowLo(szBlocked); 
    else if (diCurr.ibPhone != 0)
      ShowLo(szEmpty);
    else if (ReadParam(iwPrm) == 1)
      sprintf(szLo,"%12.3f", reBuffA);
    else
      Error();   
  }
}


static void ShowParamBuff(void)
{
  if (GetParamDevice(iwPrm) == 0)
    ShowLo(szEmpty);
  else
  {
    if (mpboEnblParams[iwPrm] == FALSE)
      ShowLo(szBlocked); 
    else
    {
      switch (ibVal)
      {
        case 0:  sprintf(szLo,"%12.3f", mpreParBuff[ibSoftTim][iwPrm]); break;
        case 1:  ShowTime(mptiParBuff[iwPrm]);  break;
        case 2:  ShowDate(mptiParBuff[iwPrm]);  break;
      }
    }
  }
}


static void ShowParamFull(void)
{
  if (GetParamDevice(iwPrm) == 0)
    ShowLo(szEmpty);
  else
  {
    if (mpboEnblParams[iwPrm] == FALSE)
      ShowLo(szBlocked); 
    else
    {
       if (LoadPrmTim((wTIMES + iwHardTim - iwTim) % wTIMES) == TRUE)
       {
         sprintf(szHi+12,"-%03u",iwTim);

         float fl = mpreParBuff[ PrevSoftTim() ][ iwPrm ];

         if (ValidFloat(fl))
           sprintf(szLo,"%12.3f", fl);
         else
           ShowLo(szEmpty);
       }
       else Error();
    }
  }
}



static void ShowParams(void)
{   
  switch (GetParamLine(iwPrm))
  {
    case PAR_P  : ShowHi(szParamP);  break;
    case PAR_P1 : ShowHi(szParamP1); break;
    case PAR_P2 : ShowHi(szParamP2); break;
    case PAR_P3 : ShowHi(szParamP3); break;

    case PAR_Q  : ShowHi(szParamQ);  break;
    case PAR_Q1 : ShowHi(szParamQ1); break;
    case PAR_Q2 : ShowHi(szParamQ2); break;
    case PAR_Q3 : ShowHi(szParamQ3); break;

    case PAR_S  : ShowHi(szParamS);  break;
    case PAR_S1 : ShowHi(szParamS1); break;
    case PAR_S2 : ShowHi(szParamS2); break;
    case PAR_S3 : ShowHi(szParamS3); break;

    case PAR_U  : ShowHi(szParamU);  break;
    case PAR_U1 : ShowHi(szParamU1); break;
    case PAR_U2 : ShowHi(szParamU2); break;
    case PAR_U3 : ShowHi(szParamU3); break;

    case PAR_I  : ShowHi(szParamI);  break;
    case PAR_I1 : ShowHi(szParamI1); break;
    case PAR_I2 : ShowHi(szParamI2); break;
    case PAR_I3 : ShowHi(szParamI3); break;

    case PAR_C  : ShowHi(szParamC);  break;
    case PAR_C1 : ShowHi(szParamC1); break;
    case PAR_C2 : ShowHi(szParamC2); break;
    case PAR_C3 : ShowHi(szParamC3); break;

    case PAR_F  : ShowHi(szParamF);  break;
    case PAR_F1 : ShowHi(szParamF1); break;
    case PAR_F2 : ShowHi(szParamF2); break;
    case PAR_F3 : ShowHi(szParamF3); break;

    default:      ShowHi(szNoParam); break;
  }

  switch (wProgram)
  { 
    case bGET_PARAMS_CURR: ShowParamCurr();  break;
    case bGET_PARAMS_BUFF: ShowParamBuff();  break;
    case bGET_PARAMS_FULL: ShowParamFull();  break;
  }

  sprintf(szLo+13,"%3u",iwPrm+1);
}



void    key_GetParamsAll(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Param();

      switch (wProgram)
      { 
        case bGET_PARAMS_CURR: ShowHi(szParamCurr); break;
        case bGET_PARAMS_BUFF: ShowHi(szParamBuff); break;
        case bGET_PARAMS_FULL: ShowHi(szParamFull); break;
      }
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      ibVal = 0;

      iwTim = 0;
      iwPrm = 0;

      ShowParams();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((iwPrm = GetIntLo(10,12) - 1) < wPARAMS)
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        ShowParams();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++iwPrm >= wPARAMS) iwPrm = 0;

      ibVal = 0; 
      iwTim = 0;

      ShowParams();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if (iwPrm > 0) iwPrm--; else iwPrm = wPARAMS - 1;

      ibVal = 0; 
      iwTim = 0;

      ShowParams();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {        
    if (++ibVal >= 3) ibVal = 0;
    if (++iwTim >= wTIMES) iwTim = 0;

    ShowParams();
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
