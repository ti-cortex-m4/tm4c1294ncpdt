/*------------------------------------------------------------------------------
KEY_SINGLE.C

 Просмотр канальных и групповых величин (старый вариант)
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../keyboard.h"
#include        "../display/display.h"



//                                         0123456789ABCDEF
static char const       szFree[]        = "      нет    ";
                        
static char const      *pszEngCurrMin[]     = { szPower, szMiddle, szCurrMnt,  "" },
                       *pszCountersB[]      = { szCounters, szForDigital, "" },

                       *pszPowPrevHou[]     = { szPower, szMiddle, szPrevHou, "" },
                       *pszPowCurrHou[]     = { szPower, szMiddle, szCurrHou, "" },

                       *pszPowDayPrevABCD[] = { szPower, szMaximum, szDayPrev, szFull,    "" },
                       *pszPowDayPrevC[]    = { szPower, szMaximum, szDayPrev, szMorning, "" },
                       *pszPowDayPrevD[]    = { szPower, szMaximum, szDayPrev, szEvening, "" },

                       *pszPowDayCurrABCD[] = { szPower, szMaximum, szDayCurr, szFull,    "" },
                       *pszPowDayCurrC[]    = { szPower, szMaximum, szDayCurr, szMorning, "" },
                       *pszPowDayCurrD[]    = { szPower, szMaximum, szDayCurr, szEvening, "" },

                       *pszPowMonPrevABCD[] = { szPower, szMaximum, szMonPrev, szFull,    "" },
                       *pszPowMonPrevC[]    = { szPower, szMaximum, szMonPrev, szMorning, "" },
                       *pszPowMonPrevD[]    = { szPower, szMaximum, szMonPrev, szEvening, "" },

                       *pszPowMonCurrABCD[] = { szPower, szMaximum, szMonCurr, szFull,    "" },
                       *pszPowMonCurrC[]    = { szPower, szMaximum, szMonCurr, szMorning, "" },
                       *pszPowMonCurrD[]    = { szPower, szMaximum, szMonCurr, szEvening, "" },

                       *pszEngDayPrevABCD[] = { szEnergy, szDayPrev, szFull,   "" },
                       *pszEngDayPrevCD[]   = { szEnergy, szDayPrev, szTops,   "" },
                       *pszEngDayPrevB[]    = { szEnergy, szDayPrev, szMid,    "" },
                       *pszEngDayPrevA[]    = { szEnergy, szDayPrev, szBottom, "" },

                       *pszEngDayCurrABCD[] = { szEnergy, szDayCurr, szFull,   "" },
                       *pszEngDayCurrCD[]   = { szEnergy, szDayCurr, szTops,   "" },
                       *pszEngDayCurrB[]    = { szEnergy, szDayCurr, szMid,    "" },
                       *pszEngDayCurrA[]    = { szEnergy, szDayCurr, szBottom, "" },

                       *pszEngMonPrevSpec[] = { szEnergy, szMonPrev, szFull,   szDeviceD, "" },

                       *pszEngMonPrevABCD[] = { szEnergy, szMonPrev, szFull,   "" },
                       *pszEngMonPrevCD[]   = { szEnergy, szMonPrev, szTops,   "" },
                       *pszEngMonPrevB[]    = { szEnergy, szMonPrev, szMid,    "" },
                       *pszEngMonPrevA[]    = { szEnergy, szMonPrev, szBottom, "" },

                       *pszEngMonCurrABCD[] = { szEnergy, szMonCurr, szFull,   "" },
                       *pszEngMonCurrCD[]   = { szEnergy, szMonCurr, szTops,   "" },
                       *pszEngMonCurrB[]    = { szEnergy, szMonCurr, szMid,    "" },
                       *pszEngMonCurrA[]    = { szEnergy, szMonCurr, szBottom, "" };




void    ShowGrpDayMaxPow(void)
{
  tiAlt = *PGetGrpMaxPowTime(mppoDayGrp[ PrevSoftDay() ],ibX,ibZ);

  switch (ibY)
  {
    case 0:  ShowReal(PGetGrpMaxPowReal(mppoDayGrp[ PrevSoftDay() ],ibX,ibZ));  break;
    case 1:  ShowTime();  break;
    case 2:  ShowDate();  break;
  }
}


void    ShowGrpMonMaxPow(void)
{
  tiAlt = *PGetGrpMaxPowTime(mppoMonGrp[ PrevSoftMon() ],ibX,ibZ);

  switch (ibY)
  {
    case 0:  ShowReal(PGetGrpMaxPowReal(mppoMonGrp[ PrevSoftMon() ],ibX,ibZ));  break;
    case 1:  ShowTime();  break;
    case 2:  ShowDate();  break;
  }
}



void    ShowGrpDayPrevEng(uchar  bMask)
{
  LoadImpDay( PrevHardDay() );
  ShowReal(PGetGrpImp2RealEng(mpimDayCan[ PrevSoftDay() ],ibX,bMask));
}


void    ShowGrpDayCurrEng(uchar  bMask)
{
  LoadImpDay( ibHardDay );
  ShowReal(PGetGrpImp2RealEng(mpimDayCan[ PrevSoftDay() ],ibX,bMask));
}


void    ShowGrpMonPrevEng(uchar  bMask)
{
  LoadImpMon( PrevHardMon() );
  ShowReal(PGetGrpImp2RealEng(mpimMonCan[ PrevSoftMon() ],ibX,bMask));
}


void    ShowGrpMonPrevEngSpec(void)
{
  ShowReal(PGetGrpImp2RealEng(mpimMonCanSpec,ibX,0x0F));
}


void    ShowGrpMonCurrEng(uchar  bMask)
{
  LoadImpMon( ibHardMon );
  ShowReal(PGetGrpImp2RealEng(mpimMonCan[ PrevSoftMon() ],ibX,bMask));
}


void    ShowModemReadSensors(void)
{
  if (GetDigitalDevice(ibX) == 0)
    ShowReal(PGetCounterOld(ibX));
  else
  {
    LoadCurrDigital(ibX);
    ibPort = diCurr.ibPort;

    if (LoadConnect(ibX) == 0) return;
    Clear();

    if (mpboEnblCan[ibX] == boFalse)
      ShowLo(szBlocking); 
    else 
      (ReadSensors(ibX) == 1) ? ShowReal(&reBuffA) : Error();   

    SaveConnect();
  }
}


void    ShowModemReadTimeDate(bit  fShow)
{
  ShowHi(szTimeDate); 

  if (GetDigitalDevice(ibX) == 0)
    ShowLo(szFree); 
  else
  {
    LoadCurrDigital(ibX);
    ibPort = diCurr.ibPort;

    if (LoadConnect(ibX) == 0) return;
    Clear();

    if (mpboEnblCan[ibX] == boFalse)
    { 
      sprintf(szHi+14,"%2bu",ibX+1);
      ShowLo(szBlocking); 
    }
    else if (ReadTimeDate(ibX) == 1)
    {
      sprintf(szHi+14,"%2bu",ibX+1);  
      Clear(); 
      (fShow == 1) ? ShowTimeDate() : ShowDeltaTime();
    }
    else Error();   

    SaveConnect();
  }
}



void    ShowSingle(void)
{
  switch (bProgram)
  {
    case bGET_COUNTNEW: 
      ShowModemReadSensors(); 
      break;

    case bGET_COUNTOLD: 
      ShowModemReadSensors(); 
      break;

    case bGET_POWGRPCURRMNT:
      ShowReal(PGetGrpMntInt2Real(mpwImpMntCan[ PrevSoftMnt() ],ibX,20));
      break;

    case bGET_IMPCANCURRMNT:
      ShowInt(*PGetCanInt(mpwImpMntCan[ ibSoftMnt ],ibX));  
      break;

    case bGET_POWGRPPREVHOU:      
      LoadImpHou( PrevHardHou() );
      ShowReal(PGetGrpHouInt2Real(mpwImpHouCan[ PrevSoftHou() ],ibX,2));
      break;

    case bGET_POWGRPCURRHOU:            // прогнозируемая получасовая средняя мощность                 
      PGetPowGrpHouCurr(ibX,2);
      ShowReal(&reBuffA);
      break;

    case bGET_POWGRPDAYPREV_ABCD:  
      LoadPowDay( PrevHardDay() );
      ibZ = GetGrpMaxPowIndex(mppoDayGrp[ PrevSoftDay() ],ibX);
      ShowGrpDayMaxPow();
      break;

    case bGET_POWGRPDAYPREV_C:     
      LoadPowDay( PrevHardDay() );   
      ibZ = 2;        
      ShowGrpDayMaxPow();
      break;

    case bGET_POWGRPDAYPREV_D:     
      LoadPowDay( PrevHardDay() );
      ibZ = 3;  
      ShowGrpDayMaxPow();
      break;

    case bGET_POWGRPDAYCURR_ABCD:
      LoadPowDay(ibHardDay);
      ibZ = GetGrpMaxPowIndex(mppoDayGrp[ PrevSoftDay() ],ibX);
      ShowGrpDayMaxPow();
      break;

    case bGET_POWGRPDAYCURR_C:     
      LoadPowDay(ibHardDay);
      ibZ = 2;
      ShowGrpDayMaxPow();
      break;

    case bGET_POWGRPDAYCURR_D:     
      LoadPowDay(ibHardDay);
      ibZ = 3;
      ShowGrpDayMaxPow();
      break;

    case bGET_POWGRPMONPREV_ABCD: 
      LoadPowMon( PrevHardMon() ); 
      ibZ = GetGrpMaxPowIndex(mppoMonGrp[ PrevSoftMon() ],ibX);  
      ShowGrpMonMaxPow();
      break;

    case bGET_POWGRPMONPREV_C:     
      LoadPowMon( PrevHardMon() ); 
      ibZ = 2;
      ShowGrpMonMaxPow();
      break;

    case bGET_POWGRPMONPREV_D:     
      LoadPowMon( PrevHardMon() ); 
      ibZ = 3;
      ShowGrpMonMaxPow();
      break;

    case bGET_POWGRPMONCURR_ABCD: 
      LoadPowMon(ibHardMon);  
      ibZ = GetGrpMaxPowIndex(mppoMonGrp[ PrevSoftMon() ],ibX);  
      ShowGrpMonMaxPow();
      break;

    case bGET_POWGRPMONCURR_C:   
      LoadPowMon(ibHardMon);
      ibZ = 2;
      ShowGrpMonMaxPow();
      break;

    case bGET_POWGRPMONCURR_D: 
      LoadPowMon(ibHardMon);
      ibZ = 3;
      ShowGrpMonMaxPow();
      break;

    case bGET_ENGGRPDAYPREV_ABCD:  ShowGrpDayPrevEng(0x0F);  break;
    case bGET_ENGGRPDAYPREV_CD:    ShowGrpDayPrevEng(0x0C);  break;
    case bGET_ENGGRPDAYPREV_B:     ShowGrpDayPrevEng(0x02);  break;
    case bGET_ENGGRPDAYPREV_A:     ShowGrpDayPrevEng(0x01);  break;

    case bGET_ENGGRPDAYCURR_ABCD:  ShowGrpDayCurrEng(0x0F);  break;
    case bGET_ENGGRPDAYCURR_CD:    ShowGrpDayCurrEng(0x0C);  break;
    case bGET_ENGGRPDAYCURR_B:     ShowGrpDayCurrEng(0x02);  break;
    case bGET_ENGGRPDAYCURR_A:     ShowGrpDayCurrEng(0x01);  break;

    case bGET_ENGGRPMONPREV_SPEC:  ShowGrpMonPrevEngSpec();  break;

    case bGET_ENGGRPMONPREV_ABCD:  ShowGrpMonPrevEng(0x0F);  break;
    case bGET_ENGGRPMONPREV_CD:    ShowGrpMonPrevEng(0x0C);  break;
    case bGET_ENGGRPMONPREV_B:     ShowGrpMonPrevEng(0x02);  break;
    case bGET_ENGGRPMONPREV_A:     ShowGrpMonPrevEng(0x01);  break;

    case bGET_ENGGRPMONCURR_ABCD:  ShowGrpMonCurrEng(0x0F);  break;
    case bGET_ENGGRPMONCURR_CD:    ShowGrpMonCurrEng(0x0C);  break;
    case bGET_ENGGRPMONCURR_B:     ShowGrpMonCurrEng(0x02);  break;
    case bGET_ENGGRPMONCURR_A:     ShowGrpMonCurrEng(0x01);  break; 
  }      

  sprintf(szLo+14,"%2bu",ibX+1);

  switch (bProgram)
  {
    case bGET_READTIMEDATE1:  ShowModemReadTimeDate(1);  break;
    case bGET_READTIMEDATE2:  ShowModemReadTimeDate(0);  break;
  }
}



void    key_GetSingle(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      ShowLogin();

      InitConnectKey();

      switch (bProgram)
      {
        case bGET_IMPCANCURRMNT:       ShowHi(szImpulseA);            break;
        case bGET_POWGRPCURRMNT:       LoadSlide(pszEngCurrMin);      break;

        case bGET_COUNTNEW:            ShowHi(szCounters);            break;
        case bGET_COUNTOLD:            LoadSlide(pszCountersB);       break;

        case bGET_READTIMEDATE1:     
        case bGET_READTIMEDATE2:       ShowHi(szTimeDate);            break;

        case bGET_POWGRPPREVHOU:       LoadSlide(pszPowPrevHou);      break;
        case bGET_POWGRPCURRHOU:       LoadSlide(pszPowCurrHou);      break;

        case bGET_POWGRPDAYPREV_ABCD:  LoadSlide(pszPowDayPrevABCD);  break;
        case bGET_POWGRPDAYPREV_C:     LoadSlide(pszPowDayPrevC);     break;
        case bGET_POWGRPDAYPREV_D:     LoadSlide(pszPowDayPrevD);     break;

        case bGET_POWGRPDAYCURR_ABCD:  LoadSlide(pszPowDayCurrABCD);  break;
        case bGET_POWGRPDAYCURR_C:     LoadSlide(pszPowDayCurrC);     break;
        case bGET_POWGRPDAYCURR_D:     LoadSlide(pszPowDayCurrD);     break;

        case bGET_POWGRPMONPREV_ABCD:  LoadSlide(pszPowMonPrevABCD);  break;
        case bGET_POWGRPMONPREV_C:     LoadSlide(pszPowMonPrevC);     break;
        case bGET_POWGRPMONPREV_D:     LoadSlide(pszPowMonPrevD);     break;
   
        case bGET_POWGRPMONCURR_ABCD:  LoadSlide(pszPowMonCurrABCD);  break;
        case bGET_POWGRPMONCURR_C:     LoadSlide(pszPowMonCurrC);     break;
        case bGET_POWGRPMONCURR_D:     LoadSlide(pszPowMonCurrD);     break;

        case bGET_ENGGRPDAYPREV_ABCD:  LoadSlide(pszEngDayPrevABCD);  break;
        case bGET_ENGGRPDAYPREV_CD:    LoadSlide(pszEngDayPrevCD);    break;
        case bGET_ENGGRPDAYPREV_B:     LoadSlide(pszEngDayPrevB);     break;
        case bGET_ENGGRPDAYPREV_A:     LoadSlide(pszEngDayPrevA);     break;

        case bGET_ENGGRPDAYCURR_ABCD:  LoadSlide(pszEngDayCurrABCD);  break;
        case bGET_ENGGRPDAYCURR_CD:    LoadSlide(pszEngDayCurrCD);    break;
        case bGET_ENGGRPDAYCURR_B:     LoadSlide(pszEngDayCurrB);     break;
        case bGET_ENGGRPDAYCURR_A:     LoadSlide(pszEngDayCurrA);     break;

        case bGET_ENGGRPMONPREV_SPEC:  LoadSlide(pszEngMonPrevSpec);  
                                       SaveDisplay();
                                       MakeMonPrevEngSpec(); 
                                       LoadDisplay();                 break;

        case bGET_ENGGRPMONPREV_ABCD:  LoadSlide(pszEngMonPrevABCD);  break;
        case bGET_ENGGRPMONPREV_CD:    LoadSlide(pszEngMonPrevCD);    break;
        case bGET_ENGGRPMONPREV_B:     LoadSlide(pszEngMonPrevB);     break;
        case bGET_ENGGRPMONPREV_A:     LoadSlide(pszEngMonPrevA);     break;

        case bGET_ENGGRPMONCURR_ABCD:  LoadSlide(pszEngMonCurrABCD);  break;
        case bGET_ENGGRPMONCURR_CD:    LoadSlide(pszEngMonCurrCD);    break;
        case bGET_ENGGRPMONCURR_B:     LoadSlide(pszEngMonCurrB);     break;
        case bGET_ENGGRPMONCURR_A:     LoadSlide(pszEngMonCurrA);     break; 
      }      
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      ibX = 0;
      ibY = 0;
      ShowSingle();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetChar(10,11) - 1) < GetMaximum())
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        ibY = 0;
        ShowSingle();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= GetMaximum()) 
        ibX = 0;

      ibY = 0;
      ShowSingle();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {        
    ResetDTR();
    if ((reReview == REV_GROUPS) && (enKeyboard == KBD_POSTENTER))
    {
      if (++ibY >= 3) 
        ibY = 0;

      ShowSingle();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibX > 0) 
        ibX--;
      else         
        ibX = GetMaximum() - 1;

      ibY = 0;
      ShowSingle();
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else Beep();
  }
  else Beep();
}



void    auto_GetSingle(void)
{
  if (enKeyboard == KBD_POSTENTER)
    ShowSingle();
}
