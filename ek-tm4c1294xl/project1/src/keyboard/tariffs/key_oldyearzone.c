/*------------------------------------------------------------------------------
KEY_OLDYEARZONE.С

 Задание и просмотр тарифных графиков за год (старый вариант)
------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_tariffs.h"
#include        "../../memory/mem_program.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../access.h"
#include        "../../tariffs/zones.h"
#include        "../../tariffs/tariffs.h"
#include        "../../tariffs/oldtariffs.h"



//                                         0123456789ABCDEF
static char const       szOnMonths[]    = "   по месяцам   ",
                        szOnQuarters[]  = "  по кварталам  ",
                        szMaskZones[]   = "01            12";

static char const      *pszPubPrg10[]   = { szZones, szOnMonths,   "" },
                       *pszPubPrg17[]   = { szZones, szOnQuarters, "" },
                       *pszPowPrg10[]   = { szZones, szOnMonths,   szForPower,  "" },
                       *pszPowPrg17[]   = { szZones, szOnQuarters, szForPower,  "" },
                       *pszEngPrg20[]   = { szZones, szOnMonths,   szForEnergy, "" },
                       *pszEngPrg27[]   = { szZones, szOnQuarters, szForEnergy, "" };

static uchar            ibX, ibXmax, ibYmin, ibYmax;

static period           pe;



void    ShowOldZones(void)
{
uchar   i;

  ShowLo(szMaskZones);

  switch (wProgram)
  {
    case bSET_PROGRAM10:  
    case bSET_PROGRAM17:
      for (i=0; i<12; i++)
        szLo[i+2] = mpeTariffPow[i];
      break; 

    case bSET_PROGRAM20:  
    case bSET_PROGRAM27:  
      for (i=0; i<12; i++)
        szLo[i+2] = mpeTariffEng[i];
      break;
  }
}



void    key_SetOldYearZone(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (GetZoneKeySize() == 0) 
      {
        NeedProgram(bSET_DAY_ZONE);
        return;
      }      

      if (fPublicTariffs == true)
      {
        switch (wProgram)
        {
          case bSET_PROGRAM10:  LoadSlide(pszPubPrg10); 
                                ibXmax = 12;
                                ShowOldZones();  break;
          case bSET_PROGRAM17:  LoadSlide(pszPubPrg17); 
                                ibXmax = 4;   
                                ShowOldZones();  break; 

          case bSET_PROGRAM20: 
          case bSET_PROGRAM27:  NeedProgram(bSET_PUBLIC_TARIFFS);
                                return;
        }
      }
      else
      {
        switch (wProgram)
        {
          case bSET_PROGRAM10:  LoadSlide(pszPowPrg10);
                                ibXmax = 12;  
                                ShowOldZones();  break;
          case bSET_PROGRAM17:  LoadSlide(pszPowPrg17);
                                ibXmax = 4;      
                                ShowOldZones();  break; 
          case bSET_PROGRAM20:  LoadSlide(pszEngPrg20); 
                                ibXmax = 12;  
                                ShowOldZones();  break;
          case bSET_PROGRAM27:  LoadSlide(pszEngPrg27); 
                                ibXmax = 4;   
                                ShowOldZones();  break; 
        }        
      }

      enKeyboard = KBD_INPUT1;
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,11)) == 0)
      {
        enKeyboard = KBD_POSTENTER;

        ibYmin = 0; 
        ibYmax = 11;

        pe = YEAR;
      }
      else if ((ibXmax == 4) && (ibX <= ibXmax))
      {
        enKeyboard = KBD_POSTENTER;

        switch (ibX) 
        {
          case 1:  ibYmin = 0; ibYmax =  2;  break;
          case 2:  ibYmin = 3; ibYmax =  5;  break;
          case 3:  ibYmin = 6; ibYmax =  8;  break;
          case 4:  ibYmin = 9; ibYmax = 11;  break;
        }

        pe = QUARTER;
      }
      else if ((ibXmax == 12) && (ibX <= ibXmax))
      {
        enKeyboard = KBD_POSTENTER;

        ibYmin = ibX-1;
        ibYmax = ibX-1;

        pe = MONTH;
      }
      else Beep();
    }


    if (enKeyboard == KBD_POSTENTER)
    {
      if (fPublicTariffs == true)
      {
        switch (wProgram)
        {
          case bSET_PROGRAM10: 
          case bSET_PROGRAM17:  
            SetPeriodTariffsPow(ibYmin,ibYmax,&zoKey,pe);
            SetPeriodTariffsEng(ibYmin,ibYmax,&zoKey,pe);
            ShowOldZones();  break;
        }
      }
      else
      {
        switch (wProgram)
        {
          case bSET_PROGRAM10: 
          case bSET_PROGRAM17: 
            SetPeriodTariffsPow(ibYmin,ibYmax,&zoKey,pe);
            ShowOldZones();  break;

          case bSET_PROGRAM20: 
          case bSET_PROGRAM27: 
            SetPeriodTariffsEng(ibYmin,ibYmax,&zoKey,pe);
            ShowOldZones();  break;
        }        
      }
    }
  }


  else if (bKey < 10)
  {
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;

      switch (wProgram)
      {
        case bSET_PROGRAM10:  
        case bSET_PROGRAM20:  Month();    break;
        case bSET_PROGRAM17:  
        case bSET_PROGRAM27:  Quarter();  break;
      }
    }


    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else Beep();
  }
  else Beep();
}
