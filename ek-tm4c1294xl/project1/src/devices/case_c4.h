
#ifndef SKIP_C

    case DEV_START_C4:
      SetupCheckup();

      cbRepeat = bMINORREPEATS;
      QueryOpenC();
      SetCurr(DEV_OPENCANAL_C4);             
      break;

    case DEV_OPENCANAL_C4:
      if ((mpSerial[ibPort] == SER_GOODCHECK)/* && (ReadResultC() == 1)*/)
        MakePause(DEV_CHECKUP_DAY_C4);
      else
      {
        if (cbRepeat == 0) ErrorCheckup();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenC();
          SetCurr(DEV_OPENCANAL_C4);
        }
      }
      break;


    case DEV_CHECKUP_DAY_C4:
      if (mpbCheckupLimitD[ibDig] == 0)
      {
        //x_str("\n days checkup disabled");
        ShowLo(szBlocking);
        MakePause(DEV_CHECKUP_MON_C4);
      }
      else 
      {
        ibCheckupDay = 1;
        CheckupShowDay(ibCheckupDay);

        cbRepeat2 = 0;

        cbRepeat = bMINORREPEATS;
        QueryEnergyDayC(-ibCheckupDay);                          
        SetCurr(DEV_ENERGY_DAY_C4);          
      }
      break;

    case DEV_ENERGY_DAY_C4:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTENERGY_DAY_C4);
      else                                    
      {
        if ((IndexInBuff() == 6) && (InBuff(1) == 0x83) && (InBuff(2) == 0x02) && (InBuff(3) == 0x03))
        {
          //x_str("\n day error");
          MakePause(DEV_CHECKUP_MON_C4);
        }        
        else
        {
          ShowLo(szFailure1);
          MakePause(DEV_ERROR1_6_C4);
        }
      } 
      break;

    case DEV_ERROR1_6_C4: 
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbRepeat2 > bMINORREPEATS) ErrorCheckup();
      else 
      {
        cbRepeat = bMINORREPEATS;
        QueryIdC();
        SetCurr(DEV_POSTERROR1_6_C4);
      }
      break;

    case DEV_POSTERROR1_6_C4: 
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdC() == 1)
        {
          QueryEnergyDayC(-ibCheckupDay);                          
          SetCurr(DEV_ENERGY_DAY_C4);          
        }
        else         
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR1_6_C4);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorCheckup(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdC();
          SetCurr(DEV_POSTERROR1_6_C4);
        }
      } 
      break;


    case DEV_POSTENERGY_DAY_C4:
      ReadEnergyC(); 
      CheckupDayEnergy(ibCheckupDay);

      if (++ibCheckupDay <= mpbCheckupLimitD[ibDig]) 
      {
        CheckupShowDay(ibCheckupDay);

        cbRepeat2 = 0;

        cbRepeat = bMINORREPEATS;
        QueryEnergyDayC(-ibCheckupDay);                          
        SetCurr(DEV_ENERGY_DAY_C4);          
      }
      else
      {
        //x_str("\n days checkup finished");
        MakePause(DEV_CHECKUP_MON_C4);
      }
      break;


    case DEV_CHECKUP_MON_C4:
      if (mpbCheckupLimitM[ibDig] == 0)
      {
        //x_str("\n months checkup disabled");
        ShowLo(szBlocking);
        MakePause(DEV_PREVCORRECT_C4);
      }
      else 
      {
        ibCheckupMon = 1;
        CheckupShowMon(ibCheckupMon);

        cbRepeat2 = 0;

        cbRepeat = bMINORREPEATS;
        QueryEnergyMonC(-ibCheckupMon);
        SetCurr(DEV_ENERGY_MON_C4);          
      }
      break;

    case DEV_ENERGY_MON_C4:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTENERGY_MON_C4);
      else                                    
      {
        if ((IndexInBuff() == 6) && (InBuff(1) == 0x83) && (InBuff(2) == 0x03) && (InBuff(3) == 0x03))
        {
          //x_str("\n month error");
          MakePause(DEV_PREVCORRECT_C4);
        }        
        else
        {
          ShowLo(szFailure1);
          MakePause(DEV_ERROR3_6_C4);
        }
      } 
      break;

    case DEV_ERROR3_6_C4: 
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbRepeat2 > bMINORREPEATS) ErrorCheckup();
      else 
      {
        cbRepeat = bMINORREPEATS;
        QueryIdC();
        SetCurr(DEV_POSTERROR3_6_C4);
      }
      break;

    case DEV_POSTERROR3_6_C4: 
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdC() == 1)
        {
          QueryEnergyMonC(-ibCheckupMon);
          SetCurr(DEV_ENERGY_MON_C4);          
        }
        else         
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR3_6_C4);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorCheckup(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdC();
          SetCurr(DEV_POSTERROR3_6_C4);
        }
      } 
      break;


    case DEV_POSTENERGY_MON_C4:
      ReadEnergyC(); 
      CheckupMonEnergy(ibCheckupMon);

      if (++ibCheckupMon <= mpbCheckupLimitM[ibDig]) 
      {
        CheckupShowMon(ibCheckupMon);

        cbRepeat2 = 0;

        cbRepeat = bMINORREPEATS;
        QueryEnergyMonC(-ibCheckupMon);                          
        SetCurr(DEV_ENERGY_MON_C4);          
      }
      else
      {
        //x_str("\n months checkup finished");
        MakePause(DEV_PREVCORRECT_C4);
      }
      break;


    case DEV_PREVCORRECT_C4:
      CheckupRecordInfo();
      if (cbCheckupDays == 0)
      {
        //x_str("\n no bad days, done checkup");
        ShowLo("   нет брака    ");
        DelayInf();
        DoneCheckup();
      }
      else
      { 
        Clear();
        sprintf(szLo+4, "брак: %bu", cbCheckupDays);

        if (boCheckupReadonly == boTrue)
        {
          DelayInf();
          DoneCheckup();
        }
        else
        {
          ibCheckupDay = 0;
          MakeLongPause(DEV_PREVHEADER_6_C4,1);
        }
      }
      break;

    case DEV_PREVHEADER_6_C4:
      InitHeaderC_6_Checkup(); 
      //x_str("\n query day "); x_time(&tiDigPrev);

      cbRepeat2 = 0;

      cbRepeat = bMINORREPEATS;     
      QueryHeaderC_6();
      SetCurr(DEV_HEADER_6_C4);
      break;

    case DEV_HEADER_6_C4:                       
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_6_C4);         
      else
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR2_6_C4);
      } 
      break;

    case DEV_ERROR2_6_C4: 
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbRepeat2 > bMINORREPEATS) ErrorCheckup();
      else 
      {
        cbRepeat = bMINORREPEATS;
        QueryIdC();
        SetCurr(DEV_POSTERROR2_6_C4);
      }
      break;

    case DEV_POSTERROR2_6_C4: 
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdC() == 1)
        {
          QueryHeaderC_6();
          SetCurr(DEV_HEADER_6_C4);
        }
        else         
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR2_6_C4);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorCheckup(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdC();
          SetCurr(DEV_POSTERROR2_6_C4);
        }
      } 
      break;


    case DEV_POSTHEADER_6_C4:                   
      if (ReadHeaderC_6_Checkup() == 0)
      { 
        //x_str(" day completed ");
        if (++ibCheckupDay < cbCheckupDays)
        { 
          //x_str(" next day");
          MakePause(DEV_PREVHEADER_6_C4);
        }
        else
        { 
          //x_str("\n all days completed, done checkup");
          DoneCheckup();
        }
      }
      else
      {
        MakePause(DEV_DATA_6_C4);         
      }
      break;

    case DEV_DATA_6_C4: 
      cbRepeat2 = 0;

      cbRepeat = bMINORREPEATS;
      QueryHeaderC_6();
      SetCurr(DEV_HEADER_6_C4);
      break;

#endif
