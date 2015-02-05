/*------------------------------------------------------------------------------
KEY_FACTORS.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_factors.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy.h"
#include        "../memory/mem_graph3.h"
#include        "../keyboard.h"
#include        "../display/display.h"
#include        "../engine.h"
#include        "../energy.h"
#include        "../sensors.h"



//                                         0123456789ABCDEF
static char const       szTransEng[]    = "� ������������� ",
                        szPulseHou[]    = "� ��������������",
                        szLosse[]       = "� ������, %     ",
                        szLevel[]       = "� ���������     ",
                        szCount[]       = "��������        ",
                        szSpecial[]     = " (�����������)  ",
                        szMaskFactors[]  = "_________ ___";
                      
static char const      *pszTransCnt[]   = { szTransEng, szSpecial, "" },
                       *pszPulseMnt[]   = { szPulseHou, szSpecial, "" };



void    ShowFactors(void)
{
  if (enGlobal != GLB_WORK)
  {
    switch (bProgram)
    {
      case bSET_TRANS_ENG:     ShowReal( PGetCanReal(mpreTransEng,    ibX) );  break;
      case bSET_TRANS_CNT:     ShowReal( PGetCanReal(mpreTransCnt,    ibX) );  break;
      case bSET_PULSE_HOU:     ShowReal( PGetCanReal(mprePulseHou,    ibX) );  break;
      case bSET_PULSE_MNT:     ShowReal( PGetCanReal(mprePulseMnt,    ibX) );  break;

      case bSET_COUNT:         ShowReal( PGetCounterOld(ibX) );                break;

      case bSET_LOSSE:         reBuffA = *PGetCanReal(mpreLosse, ibX)*100;
                               ShowReal( &reBuffA );                           break;

      case bSET_LEVEL:         ShowReal( PGetCanReal(mpreLevelDiv,    ibX) );  break;
    }
  }
  else
  {
    switch (bProgram)
    {
      case bGET_TRANS_ENG:     ShowReal( PGetCanReal(mpreTransEng,    ibX) );  break;
      case bGET_TRANS_CNT:     ShowReal( PGetCanReal(mpreTransCnt,    ibX) );  break;
      case bGET_PULSE_HOU:     ShowReal( PGetCanReal(mprePulseHou,    ibX) );  break;
      case bGET_PULSE_MNT:     ShowReal( PGetCanReal(mprePulseMnt,    ibX) );  break;

      case bGET_LOSSE:         reBuffA = *PGetCanReal(mpreLosse, ibX)*100;
                               ShowReal( &reBuffA );                           break;

      case bSET_LEVEL:         ShowReal( PGetCanReal(mpreLevelDiv,    ibX) );  break;
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

      switch (bProgram)
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
      ShowFactors();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetChar(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowFactors();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS)
        ibX = 0;

      ShowFactors();
    }
    else if ((enKeyboard == KBD_POSTINPUT2) || (enKeyboard == KBD_POSTINPUT3))
    {      
      reBuffA = *PGetReal(0,8) + *PGetReal(10,12)/1000;

      switch (bProgram)
      {
        case bSET_TRANS_ENG:   
          if (reBuffA > 0)
          {
            enKeyboard = KBD_POSTENTER;
            SetCanReal(mpreTransEng,ibX);
            reBuffA = 1;
            SetCanReal(mpreTransCnt,ibX);
          }
          break;

        case bSET_TRANS_CNT:   
          if (reBuffA > 0)
          {
            enKeyboard = KBD_POSTENTER;
            SetCanReal(mpreTransCnt,ibX);
          }
          break;

        case bSET_PULSE_HOU:  
          if (reBuffA > 0)
          {
            enKeyboard = KBD_POSTENTER;
            SetCanReal(mprePulseHou,ibX);
            SetCanReal(mprePulseMnt,ibX);
          }
          break;

        case bSET_PULSE_MNT:  
          if (reBuffA > 0)
          {
            enKeyboard = KBD_POSTENTER;
            SetCanReal(mprePulseMnt,ibX);
          }
          break;

        case bSET_COUNT:    
          if (reBuffA >= 0)
          {
            enKeyboard = KBD_POSTENTER;

            if (GetDigitalDevice(ibX) == 19)
            {
              reBuffA -= mpdwBase[ibX] * *PGetCanReal(mpreValueCntHou,ibX);
            }
            else
            {
              reBuffA -= *PGetCanInt(mpwImpMntCan[ibSoftMnt],ibX) * *PGetCanReal(mpreValueCntMnt,ibX);
              reBuffA -= *PGetCanImpAll(mpimAbsCan,ibX)           * *PGetCanReal(mpreValueCntHou,ibX); 
            }

            SetCanReal(mpreCount,ibX);
          }
          break;

        case bSET_LOSSE:   
          if (reBuffA < 100)
          {
            enKeyboard = KBD_POSTENTER;
            reBuffA /= 100;
            SetCanReal(mpreLosse,ibX);
          }   
          break;

        case bSET_LEVEL:  
          if (reBuffA > 0)
          {
            enKeyboard = KBD_POSTENTER;
            SetCanReal(mpreLevelDiv,ibX);
          }
          break;
      }

      if (enKeyboard == KBD_POSTENTER)
      {
        if (++ibX >= bCANALS)
          ibX = 0;

        ShowFactors();
      }
      else 
      {
        enKeyboard = KBD_INPUT2;
        LongBeep();

        ShowLo(szMaskFactors);
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
      ShowLo(szMaskFactors);
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

      switch (bProgram)
      {
        case bGET_TRANS_ENG:     ShowHi(szTransEng);         break;
        case bGET_TRANS_CNT:     LoadSlide(pszTransCnt);     break;
        case bGET_PULSE_HOU:     ShowHi(szPulseHou);         break;
        case bGET_PULSE_MNT:     LoadSlide(pszPulseMnt);     break;
        case bGET_LOSSE:         ShowHi(szLosse);            break;
        case bSET_LEVEL:         ShowHi(szLevel);            break;
      }
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      ShowFactors();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetChar(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowFactors();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS)
        ibX = 0;

      ShowFactors();
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
