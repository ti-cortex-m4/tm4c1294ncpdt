/*------------------------------------------------------------------------------
KEY_TEST_DIRECT.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_digitals.h"
#include "../keyboard.h"
#include "../../display/display.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_messages.h"
#include "../../serial/ports.h"
#include "../../serial/modems.h"
#include "../../sensors/automatic2.h"



//                                         0123456789ABCDEF
static char const       szTestDirect[]  = "Тест связи      ",
                        szNoDirect[]    = "      нет       ";



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

    if (mpboEnblCan[ibX] == false)
      ShowLo(szBlocked); 
    else 
    {
      uchar bA = 0;
      uchar bB = 0;
      uchar bC = 0;

      for (ibZ=0; ibZ<100; ibZ++)
      {
        Clear();
 
        ShowHi(szDirectEscU); DelayInf();
        time2 ti2 = ReadTimeCan(ibX)
        if (ti2.fValid) bC++;
        if (fKey == true) break;

        ShowHi(szDirectEscV); DelayInf();
        double2 db2 = ReadCntMonCan(tiCurr.bMonth-1, ibX);
        if (db2.fValid) bA++;
        if (fKey == true) break;

        ShowHi(szDirectEscS); DelayInf();
        db2 = ReadCntCurrCan(ibX);
        if (db2.fValid) bB++;
        if (fKey == true) break;

        ShowHi(szTestDirect); sprintf(szHi+14,"%2u",ibX+1);

        Clear();
        sprintf(szLo,"%02u   %02u-%02u-%02u",ibZ+1,bA,bB,bC);

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

