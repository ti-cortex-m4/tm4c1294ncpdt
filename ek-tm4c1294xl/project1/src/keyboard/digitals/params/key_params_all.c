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
#include "../../../engine.h"



//                                         0123456789ABCDEF
static char const       szParamCurr[]  = "Значения        ",
                        szParamBuff[]  = "Значения: буфер ",
                        szParamFull[]  = "Значения: массив";


static uint             iwPrm, iwTime;



static void ShowParamCurr(void)
{
  if (GetParamDevice(iwPrm) == 0)
    ShowLo(szEmpty);
  else
  {
    boBeginParam = FALSE;

    LoadCurrParam(iwPrm);
    ibPort = diCurr.ibPort;

    if (mpboEnblPar[iwPrm] == FALSE)
      ShowLo(szBlocking); 
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
    if (mpboEnblPar[iwPrm] == FALSE)
      ShowLo(szBlocking); 
    else
    {
      switch (ibY)
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
    if (mpboEnblPar[iwPrm] == FALSE)
      ShowLo(szBlocking); 
    else
    {
       if (LoadPrmTim((wTIMES + iwHardTim - iwTime) % wTIMES) == TRUE)
       {
         sprintf(szHi+12,"-%03u",iwTime);

         combo32 co;
         co.reBuff = mpreParBuff[ PrevSoftTim() ][ iwPrm ];

         if (co.dwBuff != 0xFFFFFFFF)
           sprintf(szLo,"%12.3f", co.reBuff);
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

      ibY = 0;
      iwTime = 0;

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

      ibY = 0; 
      iwTime = 0;

      ShowParams();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if (iwPrm > 0) iwPrm--; else iwPrm = wPARAMS - 1;

      ibY = 0; 
      iwTime = 0;

      ShowParams();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {        
    if (++ibY >= 3) ibY = 0;
    if (++iwTime >= wTIMES) iwTime = 0;

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
