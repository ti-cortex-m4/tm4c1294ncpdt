/*------------------------------------------------------------------------------
KEY_TEST_DIRECT.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_realtime.h"
#include        "../../memory/mem_digitals.h"
//#include        "../../memory/mem_energy.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
//#include        "../../realtime/realtime.h"
#include        "../../digitals/digitals.h"
#include        "../../digitals/digitals_messages.h"
#include        "../../serial/ports.h"
#include        "../../serial/modems.h"
//#include        "../../engine.h"
//#include        "../../energy.h"
//#include        "../../energy2.h"
//#include        "../../energy4.h"
//#include        "../../impulses/max_power.h"
#include        "../../devices/automatic2.h"
//#include        "../../time/timedate.h"
//#include        "../../time/timedate_display.h"



//                                         0123456789ABCDEF
static char const       szTestDirect[]  = "Тест связи      ",
                        szNoDirect[]    = "      нет       ";



static uchar            ibYmin, ibYmax;



static void ShowTestDirect(void)
{
  Clear(); sprintf(szHi+14,"%2u",ibX+1);

  if (GetDigitalDevice(ibX) == 0)
    ShowLo(szNoDirect);
  else
  {
    LoadCurrDigital(ibX);
    ibPort = diCurr.ibPort;

    if (LoadConnect(ibX) == 0) return;
    Clear();

    if (mpboEnblCan[ibX] == FALSE)
      ShowLo(szBlocking); 
    else 
    {
      ibYmin = 0;
      ibY    = 0;
      ibYmax = 0;

      for (ibZ=0; ibZ<100; ibZ++)
      {
        Clear();
 
        ShowHi(szDirectEscU); DelayInf();
        if (ReadTimeCan(ibX) == 1) ibYmax++;
        if (fKey == 1) break;

        ShowHi(szDirectEscV); DelayInf();
        if (ReadCntMonCan(tiCurr.bMonth-1, ibX) == 1) ibYmin++;
        if (fKey == 1) break;

        ShowHi(szDirectEscS); DelayInf();
        if (ReadCntCurrCan(ibX) == 1) ibY++;
        if (fKey == 1) break;

        ShowHi(szTestDirect); sprintf(szHi+14,"%2u",ibX+1);

        Clear();
        sprintf(szLo,"%02u   %02u-%02u-%02u",ibZ+1,ibYmin,ibY,ibYmax);

        Delay(1000); 
      }
    }

    SaveConnect();
  }
}



void    key_TestDirect(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Canal();

      ShowHi(szTestDirect);

      InitConnectKey();
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      ibX = 0;
      ShowTestDirect();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,12) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        ShowTestDirect();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS) ibX = 0;

      ShowTestDirect();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibX > 0) ibX--; else ibX = bCANALS-1;

      ShowTestDirect();
    }
    else Beep();
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

