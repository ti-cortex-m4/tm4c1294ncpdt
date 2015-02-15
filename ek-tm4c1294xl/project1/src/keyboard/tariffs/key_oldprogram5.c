/*------------------------------------------------------------------------------
KEY_OLDPROGRAM5.C

 Просмотр тарифных графиков за год (старый вариант)
------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_tariffs.h"
#include        "../../memory/mem_realtime.h"
#include        "../../keyboard.h"
#include        "../../display/display.h"
#include        "../../access.h"
#include        "../../timedate.h"
#include        "../../tariffs/zones.h"
#include        "../../tariffs/tariffs.h"
#include        "../../tariffs/oldtariffs.h"



static char const      *pszPubPrg5[]    = { szZones, szBeta, "" },
                       *pszPubPrg85[]   = { szZones, szBeta, "" },
                       *pszEngPrg84[]   = { szZones, szBeta, szForEnergy, "" },
                       *pszPowPrg85[]   = { szZones, szBeta, szForPower,  "" };



void    key_GetOldProgram5(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (fPublicTariffsCurr == false) 
      {
        NeedPrograms(bGET_PROGRAM84, bGET_PROGRAM85); 
        return;
      }      

      enKeyboard = KBD_POSTENTER;

      LoadSlide(pszPubPrg5);
      Clear();

      ibY = tiCurr.bMonth - 1;
      LoadBetaMonth(ibY);

      zoAlt = *PGetZonePowMonthMode(ibY, 0);

      ibX = 0;                         
      ShowZoneAltBreak(ibX);
    }
    else if (enKeyboard == KBD_POSTENTER)
    {                                
      if (++ibX >= GetZoneAltSize()) 
        ibX = 0;

      ShowZoneAltBreak(ibX);
    } 
  }
  else Beep();
}



void    key_GetOldProgram84(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    { 
      if (fPublicTariffsCurr == true)
      {
        switch (bProgram)
        {
          case bGET_PROGRAM84: 
            BlockProgram(bGET_PUBLIC_TARIFFS);
            return;

          case bGET_PROGRAM85:  
            LoadSlide(pszPubPrg85);  
            break;
        }
      }
      else
      {
        switch (bProgram)
        {
          case bGET_PROGRAM84:  LoadSlide(pszEngPrg84);  break;
          case bGET_PROGRAM85:  LoadSlide(pszPowPrg85);  break;
        }
      }

      enKeyboard = KBD_INPUT1;
      strcpy(szBeta,szOn12Months); 

      Month();
    }
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_SHOW;

      ibY = ibHardMon;
      LoadBetaMonth(ibY);

      ShowSlide(szBeta);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibY = GetCharLo(10,11) - 1) < 12)
      {
        enKeyboard = KBD_SHOW;

        LoadBetaMonth(ibY);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= GetZoneAltSize()) 
        ibX = 0;

      ShowZoneAltBreak(ibX);
    } 
  }


  if (enKeyboard == KBD_SHOW)
  {
    enKeyboard = KBD_POSTENTER;

    switch (bProgram)
    {
      case bGET_PROGRAM84: 
        zoAlt = *PGetZoneEngMonthMode(ibY, 0);
        break;

      case bGET_PROGRAM85:  
        zoAlt = *PGetZonePowMonthMode(ibY, 0);
        break;
    }

    ibX = 0;                         
    ShowZoneAltBreak(ibX);
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
