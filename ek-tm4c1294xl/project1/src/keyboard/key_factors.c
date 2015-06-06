/*------------------------------------------------------------------------------
KEY_FACTORS,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy.h"
#include "../memory/mem_current.h"
#include "../energy.h"
#include "../impulses/factors.h"
#include "../digitals/digitals.h"
#include "key_factors.h"



//                                         0123456789ABCDEF
static char const       szTransEng[]    = "К трансформации ",
                        szPulseHou[]    = "К преобразования",
                        szLosse[]       = "К потерь, %     ",
                        szLevel[]       = "К отношения     ",
                        szCount[]       = "Счетчики        ",
                        szSpecial[]     = " (специальный)  ",
                        szMask[]        = "_________ ___";
                      
static char const      *pszTransCnt[]   = { szTransEng, szSpecial, "" },
                       *pszPulseMnt[]   = { szPulseHou, szSpecial, "" };



static void Show(void)
{
  if (enGlobal != GLB_WORK)
  {
    switch (wProgram)
    {
      case bSET_TRANS_ENG:  ShowFloat( mpreTransEng[ibX] );  break;
      case bSET_TRANS_CNT:  ShowFloat( mpreTransCnt[ibX] );  break;
      case bSET_PULSE_HOU:  ShowFloat( mprePulseHou[ibX] );  break;
      case bSET_PULSE_MNT:  ShowFloat( mprePulseMnt[ibX] );  break;

      case bSET_COUNT:      ShowFloat( GetCntCurrImp(ibX) ); break;
      case bSET_LOSSE:      ShowFloat( mpreLosse[ibX]*100 ); break;
      case bSET_LEVEL:      ShowFloat( mpreLevel[ibX] );     break;
    }
  }
  else
  {
    switch (wProgram)
    {
      case bGET_TRANS_ENG:  ShowFloat( mpreTransEng[ibX] );  break;
      case bGET_TRANS_CNT:  ShowFloat( mpreTransCnt[ibX] );  break;
      case bGET_PULSE_HOU:  ShowFloat( mprePulseHou[ibX] );  break;
      case bGET_PULSE_MNT:  ShowFloat( mprePulseMnt[ibX] );  break;

      case bGET_LOSSE:      ShowFloat( mpreLosse[ibX]*100 ); break;
      case bSET_LEVEL:      ShowFloat( mpreLevel[ibX] );     break;
    }
  }

  sprintf(szLo+14,"%2u",ibX+1);
}



void    key_SetFactors(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Canal();

      switch (wProgram)
      {
        case bSET_TRANS_ENG:  ShowHi(szTransEng);      break;
        case bSET_TRANS_CNT:  LoadSlide(pszTransCnt);  break;
        case bSET_PULSE_HOU:  ShowHi(szPulseHou);      break;
        case bSET_PULSE_MNT:  LoadSlide(pszPulseMnt);  break;
        case bSET_LOSSE:      ShowHi(szLosse);         break;
        case bSET_LEVEL:      ShowHi(szLevel);         break;
        case bSET_COUNT:      ShowHi(szCount);         break;
      }      
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        Show();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS) ibX = 0;

      Show();
    }
    else if ((enKeyboard == KBD_POSTINPUT2) || (enKeyboard == KBD_POSTINPUT3))
    {      
      float fl = GetRealLo(0,8) + GetRealLo(10,12)/1000;

      switch (wProgram)
      {
        case bSET_TRANS_ENG:   
          if (fl > 0)
          {
            enKeyboard = KBD_POSTENTER;

            mpreTransEng[ibX] = fl;
            SaveFile(&flTransEng);

            mpreTransCnt[ibX] = 1;
            SaveFile(&flTransCnt);
          }
          else Beep();
          break;

        case bSET_TRANS_CNT:   
          if (fl > 0)
          {
            enKeyboard = KBD_POSTENTER;

            mpreTransCnt[ibX] = fl;
            SaveFile(&flTransCnt);
          }
          else Beep();
          break;

        case bSET_PULSE_HOU:  
          if (fl > 0)
          {
            enKeyboard = KBD_POSTENTER;

            mprePulseHou[ibX] = fl;
            SaveFile(&flPulseHou);

            mprePulseMnt[ibX] = fl;
            SaveFile(&flPulseMnt);
          }
          else Beep();
          break;

        case bSET_PULSE_MNT:  
          if (fl > 0)
          {
            enKeyboard = KBD_POSTENTER;

            mprePulseMnt[ibX] = fl;
            SaveFile(&flPulseMnt);
          }
          else Beep();
          break;

        case bSET_COUNT:    
          if (fl >= 0)
          {
            enKeyboard = KBD_POSTENTER;

            if (GetDigitalDevice(ibX) == 19)
            {
              fl -= mpdwBase[ibX] * mpdbValueCntHou[ibX];
            }
            else
            {
              fl -= mpwImpMntCan[ibSoftMnt][ibX] * mpdbValueCntMnt[ibX];
              fl -= *PGetCanImpAll(mpimAbsCan,ibX) * mpdbValueCntHou[ibX];
            }

            mpreCount[ibX] = fl;
            SaveFile(&flCount);
          }
          else Beep();
          break;

        case bSET_LOSSE:   
          if (fl < 100)
          {
            enKeyboard = KBD_POSTENTER;

            mpreLosse[ibX] = fl/100;
            SaveFile(&flLosse);
          }   
          else Beep();
          break;

        case bSET_LEVEL:  
          if (fl > 0)
          {
            enKeyboard = KBD_POSTENTER;

            mpreLevel[ibX] = fl;
            SaveFile(&flLevel);
          }
          else Beep();
          break;
      }

      if (enKeyboard == KBD_POSTENTER)
      {
        if (++ibX >= bCANALS) ibX = 0;

        Show();
      }
      else 
      {
        enKeyboard = KBD_INPUT2;
        LongBeep();

        ShowLo(szMask);
      }
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT3;
      szLo[9] = '.';
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT2;
      ShowLo(szMask);
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else 
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(0,8);
    }
    else 
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(10,12);
    }
  }
  else Beep();
}



void    key_GetFactors(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Canal();

      switch (wProgram)
      {
        case bGET_TRANS_ENG:  ShowHi(szTransEng);      break;
        case bGET_TRANS_CNT:  LoadSlide(pszTransCnt);  break;
        case bGET_PULSE_HOU:  ShowHi(szPulseHou);      break;
        case bGET_PULSE_MNT:  LoadSlide(pszPulseMnt);  break;
        case bGET_LOSSE:      ShowHi(szLosse);         break;
        case bSET_LEVEL:      ShowHi(szLevel);         break;
      }
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        Show();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS) ibX = 0;

      Show();
    }
  }


  else if (bKey < 10)
  {        
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
  }
  else Beep();
}
