/*------------------------------------------------------------------------------
CHECKUP.C 


------------------------------------------------------------------------------*/

#include        "../../main.h"



void    ClearCheckup(void)
{
//  boCheckupRecalc = FALSE;
//
//  cbCheckupDays = 0;
//  memset(&mpCheckupDays, 0, sizeof(mpCheckupDays));
//
//  cbCheckupErrorDay = 0;
//  cbCheckupErrorMon = 0;
}

/*
void    ResetCheckupCustom(void)
{
  boCheckupRecalc = FALSE;

  cbCheckupEventDay = 0;
  memset(&mpCheckupEventDay, 0, sizeof(mpCheckupEventDay));

  cbCheckupEventMon = 0;
  memset(&mpCheckupEventMon, 0, sizeof(mpCheckupEventMon));

  cbCheckupDefectDay = 0;
  memset(&mpCheckupDefectDay, 0, sizeof(mpCheckupDefectDay));

  cbCheckupDefectMon = 0;
  memset(&mpCheckupDefectMon, 0, sizeof(mpCheckupDefectMon));

  cbCheckupDays = 0;
  memset(&mpCheckupDays, 0, sizeof(mpCheckupDays));

  cbCheckupRun = 0;

  cbCheckupErrorDay = 0;
  cbCheckupErrorMon = 0;
}


void    ResetCheckupFull(void)
{
uchar   i;

  ResetCheckupCustom();

  boCheckupEnable = FALSE;

  for (i=0; i<bCANALS; i++)
  {
    mpbCheckupLimitD[i] = 0;
    mpbCheckupLimitM[i] = 0;
  }

  for (i=0; i<48; i++) mpboCheckupHou[i] = FALSE;
  mpboCheckupHou[2] = TRUE;
  mpboCheckupHou[3] = TRUE;
  mpboCheckupHou[4] = TRUE;
  mpboCheckupHou[5] = TRUE;
}


void    SetupCheckup(void)
{
  cbCheckupDays = 0;
  memset(&mpCheckupDays, 0, sizeof(mpCheckupDays));

  cbCheckupErrorDay = 0;
  cbCheckupErrorMon = 0;

  //x_init();
  //x_str("\n\n start checkup");
}



void    CheckupShow(void)
{
  // запрещаем запуск получасового опроса во время длительных операций без опроса счетчиков
  cbWaitQuery = bWAITQUERY;
}


void    CheckupShowDay(uchar  ibDay)
{
  //x_str("\n day "); x_bytedec(ibDay);

  Clear();
  sprintf(szLo+2, "сутки: %bu-%bu", ibDay, mpbCheckupLimitD[ibDig]);

  CheckupShow();
}


void    CheckupShowMon(uchar  ibMon)
{
  //x_str("\n month "); x_bytedec(ibMon);

  Clear();
  sprintf(szLo+2, "месяц: %bu-%bu", ibMon, mpbCheckupLimitM[ibDig]);

  CheckupShow();
}



uchar    GetCheckupDefectDayAdded(void)
{
uchar   i;

  if (cbCheckupDefectDay == 0)
    return bCHECKUP2;
  else
  {
    for (i=0; i<bCHECKUP2; i++)
    {
      cBuff2 = mpCheckupDefectDay[i];
      if ((cBuff2.daSelf.bDay   == daAlt.bDay)   &&
          (cBuff2.daSelf.bMonth == daAlt.bMonth) &&
          (cBuff2.daSelf.bYear  == daAlt.bYear)  &&
          (cBuff2.ibCanal == ibDig))
        return i;
    }

    return bCHECKUP2;
  }
}

uchar    GetCheckupDefectMonAdded(void)
{
uchar   i;

  if (cbCheckupDefectMon == 0)
    return bCHECKUP2;
  else
  {
    for (i=0; i<bCHECKUP2; i++)
    {
      cBuff2 = mpCheckupDefectMon[i];
      if ((cBuff2.daSelf.bDay   == daAlt.bDay)   &&
          (cBuff2.daSelf.bMonth == daAlt.bMonth) &&
          (cBuff2.daSelf.bYear  == daAlt.bYear)  &&
          (cBuff2.ibCanal == ibDig))
        return i;
    }

    return bCHECKUP2;
  }
}



void    AddCheckupDefectDay(void)
{
  cBuff2.ibCanal   = ibDig;
  cBuff2.cbRepeats = 1;
  cBuff2.daSelf    = daAlt;
  mpCheckupDefectDay[cbCheckupDefectDay++ % bCHECKUP2] = cBuff2;
}


void    AddCheckupDefectMon(void)
{
  cBuff2.ibCanal   = ibDig;
  cBuff2.cbRepeats = 1;
  cBuff2.daSelf    = daAlt;
  mpCheckupDefectMon[cbCheckupDefectMon++ % bCHECKUP2] = cBuff2;
}



bit     IsCheckupDayAdded(void)
{
uchar   i;

  //x_str("\n check day "); x_date(&daAlt);

  if (cbCheckupDays == 0)
  {
    //x_str(" day not added, empty list "); 
    return 0;
  }
  else
  {
    for (i=0; i<cbCheckupDays; i++)
    {
      daDig = mpCheckupDays[i];
      if ((daDig.bDay   == daAlt.bDay)   &&
          (daDig.bMonth == daAlt.bMonth) &&
          (daDig.bYear  == daAlt.bYear))
      {
        //x_str(" day already added "); 
        return 1;
      }
    }

    //x_str(" day not added "); 
    return 0;
  }
}


bit     IsCheckupMonAdded(void)
{
uchar   i,j;

  //x_str("\n check month "); x_date(&daAlt);

  j = DaysInMonthSpec(daAlt.bYear,daAlt.bMonth);
  for (i=1; i<=j; i++)
  {
    daAlt.bDay = i;
    if (IsCheckupDayAdded() == 0) 
    {
      //x_str("\n month not added "); 
      return 0;
    } 
  }

  //x_str("\n month already added "); 
  return 1;
}



void    AddCheckupDay(void)
{
  cBuff1.ibCanal = ibDig;
  cBuff1.tiSelf  = tiCurr;
  cBuff1.daSelf  = daAlt;
  mpCheckupEventDay[cbCheckupEventDay++ % bCHECKUP1] = cBuff1;

  // проверка на переполнение
  // сортировка
  //x_str("\n add day "); x_date(&daAlt);
  mpCheckupDays[cbCheckupDays++ % bCHECKUP_DAYS] = daAlt; 

  AddDigRecord(EVE_CHECKUP_DAY);
}


void    AddCheckupMon(void)
{
uchar   i,j;

  cBuff1.ibCanal = ibDig;
  cBuff1.tiSelf  = tiCurr;
  cBuff1.daSelf  = daAlt;
  mpCheckupEventMon[cbCheckupEventMon++ % bCHECKUP1] = cBuff1;

  //x_str("\n add month "); x_date(&daAlt);
  j = DaysInMonthSpec(daAlt.bYear,daAlt.bMonth);
  for (i=1; i<=j; i++)
  {
    daAlt.bDay = i;
    if (IsCheckupDayAdded() == 0)
    {
      mpCheckupDays[cbCheckupDays++ % bCHECKUP_DAYS] = daAlt; 
      //x_str(" add day from month ");
    }
  }

  AddDigRecord(EVE_CHECKUP_MON);
}



void       CheckupDayEnergy(uchar  ibDay)
{    
uchar   i;

  memset(&mpdwCheckupImpCan, 0, sizeof(mpdwCheckupImpCan));

  if (ibDay < bDAYS)
  {
    LoadImpDay((bDAYS+ibHardDay-ibDay) % bDAYS);

    for (ibCan=0; ibCan<bCANALS; ibCan++)
      for (i=0; i<bTARIFFS; i++)
        mpdwCheckupImpCan[ibCan] += mpimDayCan[ PrevSoftDay() ][ibCan].mpdwImp[i];  
  }
  else
  {
    iwHou = PrevDayIndex(ibDay);
    for (i=0; i<48; i++)
    {
      LoadImpHouFree(iwHou);

      for (ibCan=0; ibCan<bCANALS; ibCan++)
      {
        wBuffD = mpwImpHouCan[ PrevSoftHou() ][ ibCan ];
        if (wBuffD == 0xFFFF) wBuffD = 0;
        mpdwCheckupImpCan[ibCan] += wBuffD;
      }

      if (++iwHou >= wHOURS) iwHou = 0;
    }
  }

  LoadCurrDigital(ibDig);      
  for (ibCan=0; ibCan<bCANALS; ibCan++)                           
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1)
    {
      dwBuffC = mpdwCheckupImpCan[ibCan];

      //x_str("\n canal "); x_bytedec(ibCan+1); //x_str("  int"); x_longdec(dwBuffC); //x_str(" ext"); x_longdec(mpdwChannelsA[diPrev.ibLine]);          
      if (dwBuffC != mpdwChannelsA[diPrev.ibLine]) 
      {
        //x_str("\n not equals");
        AddDigRecord(EVE_CHECKUP_CANAL);
        AddDigRecord(EVE_CHECKUP_VALUE);

        tiAlt = *PGetCurrTimeDate();
        dwBuffC = DateToDayIndex();       
        dwBuffC -= ibDay;        
        DayIndexToDate(dwBuffC);
                 
        daAlt.bDay   = tiAlt.bDay;
        daAlt.bMonth = tiAlt.bMonth;
        daAlt.bYear  = tiAlt.bYear;

        cbCheckupErrorDay++;
        if (boCheckupReadonly == TRUE)
        {
          AddDigRecord(EVE_CHECKUP_DAY);
        }
        else
        {
          //x_str("\n bad day "); x_date(&daAlt);
          if (IsCheckupDayAdded() == 0)
          {
            i = GetCheckupDefectDayAdded();
            if (i == bCHECKUP2)
            { 
              //x_str("\n the day not in in defects, add");
              AddCheckupDefectDay();
              AddCheckupDay();
            }
            else
            { 
              //x_str("\n the day already in in defects");
              cBuff2 = mpCheckupDefectDay[i];
              if (cBuff2.cbRepeats >= bMAX_CHECKUP)
              {
                //x_str("\n too many defects, skip");
                AddDigRecord(EVE_CHECKUP_DAY_FAIL);
              }
              else
              { 
                //x_str("\n try another time");
                ibGrp = mpCheckupDefectDay[i].cbRepeats++;
                AddCheckupDay();
                AddDigRecord(EVE_CHECKUP_DAY_NEXT);
              }
            }
          }
          else
          {
            AddDigRecord(EVE_CHECKUP_DAY_SKIP);
          }
        }
      }
    } 
  } 
}


void       CheckupMonEnergy(uchar  ibMon)
{
uchar   i;

  memset(&mpdwCheckupImpCan, 0, sizeof(mpdwCheckupImpCan));

  LoadImpMon((bMONTHS+ibHardMon-ibMon) % bMONTHS);

  for (ibCan=0; ibCan<bCANALS; ibCan++)
    for (i=0; i<bTARIFFS; i++)
      mpdwCheckupImpCan[ibCan] += mpimMonCan[ PrevSoftMon() ][ibCan].mpdwImp[i];  

  LoadCurrDigital(ibDig);      
  for (ibCan=0; ibCan<bCANALS; ibCan++)                           
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1)
    {
      dwBuffC = mpdwCheckupImpCan[ibCan];

      //x_str("\n canal "); x_bytedec(ibCan+1); //x_str("  int"); x_longdec(dwBuffC); //x_str(" ext"); x_longdec(mpdwChannelsA[diPrev.ibLine]);          
      if (dwBuffC != mpdwChannelsA[diPrev.ibLine]) 
      {
        //x_str("\n not equals");
        AddDigRecord(EVE_CHECKUP_CANAL);
        AddDigRecord(EVE_CHECKUP_VALUE);

        tiAlt = *PGetCurrTimeDate();
        dwBuffC = DateToMonIndex();       
        dwBuffC -= ibMon;        
        MonIndexToDate(dwBuffC);
                 
        daAlt.bDay   = tiAlt.bDay;
        daAlt.bMonth = tiAlt.bMonth;
        daAlt.bYear  = tiAlt.bYear;

        cbCheckupErrorMon++;
        if (boCheckupReadonly == TRUE)
        {
          AddDigRecord(EVE_CHECKUP_MON);
        }
        else
        {
          //x_str("\n bad month "); x_date(&daAlt);
          if (IsCheckupMonAdded() == 0)
          {
            i = GetCheckupDefectMonAdded();
            if (i == bCHECKUP2)
            { 
              //x_str("\n the month not in in defects, add");
              AddCheckupDefectMon();
              AddCheckupMon();
            }
            else
            { 
              //x_str("\n the month already in defects");
              cBuff2 = mpCheckupDefectMon[i];
              if (cBuff2.cbRepeats >= bMAX_CHECKUP)
              {
                //x_str("\n too many defects, skip");
                AddDigRecord(EVE_CHECKUP_MON_FAIL);
              }
              else
              { 
                //x_str("\n try another time");
                ibGrp = mpCheckupDefectMon[i].cbRepeats++;
                AddCheckupMon();
                AddDigRecord(EVE_CHECKUP_MON_NEXT);
              }
            }
          }
          else
          {
            AddDigRecord(EVE_CHECKUP_MON_SKIP);
          }
        }
      }
    } 
  } 
}



void    CheckupRecordInfo(void)
{
  AddDigRecord(EVE_CHECKUP_INFO);
}



void    CheckupClearCanals(void)
{
uchar   i;

  boCheckupRecalc = TRUE;
  memset(&mpboReadyCheckup, 0, sizeof(mpboReadyCheckup));

  for (i=ibXmin; i<=ibXmax; i++)
  { 
    LoadCurrDigital(i);                             
    for (ibCan=0; ibCan<bCANALS; ibCan++) 
    {
      LoadPrevDigital(ibCan);

      if (CompareCurrPrevLines() == 1)
        mpboReadyCheckup[ibCan] = TRUE;
    } 
  }


  fLoadHou = 0;

  bHouInc = 0;
  for (iwHou=0; iwHou<wHOURS; iwHou++) 
  {
    if ((iwHou % 0x10) == 0) NexttimeMnt();

    iwA = (wHOURS + iwHardHou - iwHou - bHouInc) % wHOURS;

    if (iwA == iwAmax) fLoadHou = 1;

    if (fLoadHou == 1)
    {
      LoadImpHouSpec(iwA,1);                   // обработка по получасам
    
      for (ibCan=0; ibCan<bCANALS; ibCan++)         // обработка по каналам
      {
        if (mpboReadyCheckup[ibCan] == TRUE) 
        { 
          SetCanInt(mpwImpHouCanSpec, ibCan, 0xFFFF); 
        }
      }

      SaveImpHouSpec(1,iwA);
    }

    if (iwA == iwAmin) fLoadHou = 0;
  }
}



void    OutCheckup(void)
{
  InitPushCRC();
  PushChar(boCheckupEnable);
  Push(&mpbCheckupLimitD, sizeof(mpbCheckupLimitD));
  Push(&mpbCheckupLimitM, sizeof(mpbCheckupLimitM));
  Output(1+sizeof(mpbCheckupLimitD)+sizeof(mpbCheckupLimitD));
}


void    OutCheckupEventDay(void)
{
  InitPushCRC();
  PushChar(cbCheckupEventDay);
  Push(&mpCheckupEventDay, sizeof(mpCheckupEventDay));
  Output(1+sizeof(mpCheckupEventDay));
}


void    OutCheckupEventMon(void)
{
  InitPushCRC();
  PushChar(cbCheckupEventMon);
  Push(&mpCheckupEventMon, sizeof(mpCheckupEventMon));
  Output(1+sizeof(mpCheckupEventMon));
}


void    OutGetCheckupHou(void)
{
  InitPushCRC();
  Push(&mpboCheckupHou, sizeof(mpboCheckupHou));
  Output(48);
}


void    OutSetCheckupHou(void)
{
uchar   i;

  InitPop(6);
  for (i=0; i<48; i++) mpboCheckupHou[i] = PopChar();
  Result(bRES_OK);
}


void    OutCheckupDefectDay(void)
{
  InitPushCRC();
  PushChar(cbCheckupDefectDay);
  Push(&mpCheckupDefectDay, sizeof(mpCheckupDefectDay));
  Output(1+sizeof(mpCheckupDefectDay));
}


void    OutCheckupDefectMon(void)
{
  InitPushCRC();
  PushChar(cbCheckupDefectMon);
  Push(&mpCheckupDefectMon, sizeof(mpCheckupDefectMon));
  Output(1+sizeof(mpCheckupDefectMon));
}



void    OutCheckupDays(void)
{
  InitPushCRC();
  PushChar(cbCheckupDays);
  Push(&mpCheckupDays, sizeof(mpCheckupDays));
  Output(1+sizeof(mpCheckupDays));
}
*/
