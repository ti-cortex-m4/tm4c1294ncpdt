
#ifndef SKIP_E

    case DEV_START_E2:         
      Log(LOG_BEG_DEVICE_E);

      ShowLo(szOpen);
      SetPause(DEV_OPENCANAL_E2);

      InitWaitAnswer();
      QueryBreakE();

      cbRepeat = GetMaxRepeats();
      QueryOpenE();
      SetCurr(DEV_OPENCANAL_E2);
      break;

    case DEV_OPENCANAL_E2:                     
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadOpenE() == 1))
      {                          
        ShowLo(szOpenOK); DelayInf();  
        if (fCurrCtrlHou == 1)
          MakePause(DEV_POSTOPENCANAL_E2);
        else
          MakePause(DEV_POSTCORRECT3_E2);
      }
      else                                      
      { 
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ShowRepeat();
          cbRepeat--;
          
          ShowLo(szOpen); 
          SetPause(DEV_OPENCANAL_E2);

          InitWaitAnswer();
          QueryBreakE();      

          QueryOpenE();
          SetCurr(DEV_OPENCANAL_E2);
        }
      }  
      break;


    case DEV_POSTOPENCANAL_E2:                  
      Log(LOG_BEG_CORRECT_E);

      cbRepeat = GetMaxRepeats();
      QueryTimeE();                          
      SetCurr(DEV_TIME0_E2);                // первичное чтение времени
      break;

    case DEV_TIME0_E2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltE();                  
        MakePause(DEV_POSTTIME0_E2);
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTimeE();
          SetCurr(DEV_TIME0_E2);
        }
      } 
      break;

    case DEV_POSTTIME0_E2:
      wBuffD  = GetDayIndex();              // количество дней с начала года ведомого СЭМ-2
      dwBuffC = GetSecondIndex();           // количество секунд ведомого СЭМ-2

      tiAlt.bSecond = tiCurr.bSecond;
      tiAlt.bMinute = tiCurr.bMinute;
      tiAlt.bHour   = tiCurr.bHour;
      tiAlt.bDay    = tiCurr.bDay;
      tiAlt.bMonth  = tiCurr.bMonth;
      tiAlt.bYear   = tiCurr.bYear;

      if (wBuffD != GetDayIndex())          // даты не совпадают, коррекция невозможна 
      {
        ShowLo(szBadDates); DelayMsg(); 
        ErrorProfile();                     
      }
      else if (dwBuffC > GetSecondIndex())  // необходима коррекция времени ведомого СЭМ-2 назад
      {
        ShowDeltaNeg();

        if (dwBuffC < 30-bMINORCORRECT_E)   // без изменений
        {
          ShowLo(szCorrectNo); DelayInf();  
          MakePause(DEV_POSTCORRECT3_E2);
        }
        else if (dwBuffC < bMINORCORRECT_E) // простая коррекция назад
        {
          ShowLo(szCorrectYes); DelayInf();  
          MakePause(DEV_TIME1LO_E2);
        }
        else if (dwBuffC < wMAJORCORRECT_E)
        {
          cbRepeat = GetMaxRepeats();         
          QueryTimeE();                          
          SetCurr(DEV_TIME2LO_E2);
        }
        else                                // разница времени слишком велика, коррекция невозможна 
        {
          ShowLo(szCorrectBig); DelayMsg(); 
          ErrorProfile();                     
        }
      }
      else                                  // необходима коррекция времени ведомого СЭМ-2 вперёд
      {
        ShowDeltaPos();

        if (dwBuffC < 30-bMINORCORRECT_E)   // без изменений
        {
          ShowLo(szCorrectNo); DelayInf();  
          MakePause(DEV_POSTCORRECT3_E2);
        }
        else if (dwBuffC < bMINORCORRECT_E) // простая коррекция вперёд
        {
          ShowLo(szCorrectYes); DelayInf();  
          MakePause(DEV_TIME1HI_E2);
        }
        else if (dwBuffC < wMAJORCORRECT_E)
        {
          cbRepeat = GetMaxRepeats();         
          QueryTimeE();                          
          SetCurr(DEV_TIME2HI_E2);
        }
        else                                // разница времени слишком велика, коррекция невозможна 
        {
          ShowLo(szCorrectBig); DelayMsg(); 
          ErrorProfile();                     
        }
      }
      break;


    case DEV_TIME1LO_E2:                  
      if (tiCurr.bSecond < 30-bMINORCORRECT_E)
      {
        Beep();

        cbRepeat = GetMaxRepeats();
        QueryCorrectE();                          
        SetCurr(DEV_CORRECT3_E2);           // исполняем простую коррекцию
      }
      else 
      {
        ShowTimeOneE();
        MakePause(DEV_TIME1LO_E2);          // ожидаем время ведущего СЭМ-2 
      }
      break;


    case DEV_TIME2LO_E2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltE();  
        MakePause(DEV_POSTTIME2LO_E2);
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTimeE();
          SetCurr(DEV_TIME2LO_E2);
        }
      } 
      break;

    case DEV_POSTTIME2LO_E2:                  
      if ((tiAlt.bSecond > bMINORCORRECT_E) && (tiAlt.bSecond < 30))
      {
        Beep();

        cbRepeat = GetMaxRepeats();
        QueryCorrectE();                          
        SetCurr(DEV_CORRECT2LO_E2);
      }
      else 
      {
        ShowTimeTwoE();

        cbRepeat = GetMaxRepeats();         
        QueryTimeE();                          
        SetCurr(DEV_TIME2LO_E2);
      }
      break;


    case DEV_CORRECT2LO_E2:
      if ((mpSerial[ibPort] == SER_GOODCHECK)  && (ReadCorrectE() == 1))
        MakePause(DEV_POSTCORRECT2LO_E2);
      else                                    
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT3_E2);  // да !
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryCorrectE();
          SetCurr(DEV_CORRECT2LO_E2);
        }
      } 
      break;

    case DEV_POSTCORRECT2LO_E2:                  
      cbRepeat = GetMaxRepeats();
      QueryTimeE();                          
      SetCurr(DEV_TIME0_E2);
      break;


    case DEV_TIME1HI_E2:                  
      if (tiCurr.bSecond < 30-bMINORCORRECT_E)
      {
        Beep();

        cbRepeat = GetMaxRepeats();
        QueryCorrectE();                          
        SetCurr(DEV_CORRECT3_E2);
      }
      else
      {                      
        ShowTimeOneE();
        MakePause(DEV_TIME1HI_E2);          // ожидаем время ведущего СЭМ-2 
      }
      break;


    case DEV_TIME2HI_E2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltE();  
        MakePause(DEV_POSTTIME2HI_E2);
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTimeE();
          SetCurr(DEV_TIME2HI_E2);
        }
      } 
      break;

    case DEV_POSTTIME2HI_E2:                  
      if ((tiAlt.bSecond > 30) && (tiAlt.bSecond < 60-bMINORCORRECT_E))
      {
        Beep();

        cbRepeat = GetMaxRepeats();
        QueryCorrectE();                          
        SetCurr(DEV_CORRECT2HI_E2);
      }
      else 
      {
        ShowTimeTwoE();

        cbRepeat = GetMaxRepeats();         
        QueryTimeE();                          
        SetCurr(DEV_TIME2HI_E2);
      }
      break;


    case DEV_CORRECT2HI_E2:
      if ((mpSerial[ibPort] == SER_GOODCHECK)  && (ReadCorrectE() == 1))
        MakePause(DEV_POSTCORRECT2HI_E2);
      else                                    
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT3_E2);  // да !
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryCorrectE();
          SetCurr(DEV_CORRECT2HI_E2);
        }
      } 
      break;

    case DEV_POSTCORRECT2HI_E2:                  
      cbRepeat = GetMaxRepeats();
      QueryTimeE();                          
      SetCurr(DEV_TIME0_E2);
      break;


    case DEV_CORRECT3_E2:
      if ((mpSerial[ibPort] == SER_GOODCHECK)  && (ReadCorrectE() == 1))
        MakePause(DEV_POSTCORRECT3_E2);
      else                                    
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT3_E2);  // да !
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryCorrectE();
          SetCurr(DEV_CORRECT3_E2);
        }
      } 
      break;

    case DEV_POSTCORRECT3_E2:                  
      Log(LOG_END_CORRECT_E);
      Log(LOG_BEG_TIMEDATE_E);

      ShowDigitalHi();
      ShowLo(szStamp); DelayInf();

      ibMinor = 0;

      cbRepeat = GetMaxRepeats();
      QueryTimeE();                          
      SetCurr(DEV_TIME3_E2);
      break;


    case DEV_TIME3_E2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeDigE();  
        MakePause(DEV_POSTTIME3_E2);
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTimeE();
          SetCurr(DEV_TIME3_E2);
        }
      } 
      break;

    case DEV_POSTTIME3_E2:                  
      Log(LOG_END_TIMEDATE_E);

      ShowLo(szStampOK); DelayInf();

      if (TestIndexE() == 0)
      {
        DoneProfile();
        Log(LOG_END_DEVICE_E);
      }
      else 
      {
        Log(LOG_BEG_ALLINDEXES_E);
        fAlt = ReadAllIndexesE('l',ibMinor);
        Log(LOG_END_ALLINDEXES_E);

        if (fAlt == 1)                         
        {
          if ((ibMinor == 0) || (ReadIndexE('l',ibMinor) == 1))
          {
            Log(LOG_BEG_ENERGY_E);

            InitWaitAnswer();

            ShowLo(szDelay); 
            SetPause(DEV_ENERGY_E2);

            cbRepeat = GetMaxRepeats();
            QueryEnergyE();                          
            SetCurr(DEV_ENERGY_E2);
          }
          else if (ReadIndexE('l',0) == 1)
          {
            DoneProfile(); 
            Log(LOG_END_DEVICE_E);
          }
          else ErrorProfile();
        }
        else ErrorProfile();
      }
      break;

    case DEV_ENERGY_E2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEnergyE();  
        Log(LOG_END_ENERGY_E);

        DefaultDefectE();
        if (boPoweredEsc == true)
          MakePause(DEV_POSTENERGY_E2);
        else
          MakePause(DEV_POSTDEFECT_E2);
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          InitWaitAnswer();

          ShowLo(szDelay); 
          SetPause(DEV_ENERGY_E2);

          QueryEnergyE();
          SetCurr(DEV_ENERGY_E2);
        }
      } 
      break;

    case DEV_POSTENERGY_E2:              
      Log(LOG_BEG_DEFECT_E);
      ShowLo(szDefect); DelayInf();

      cbRepeat = GetMaxRepeats();
      QueryDefectE();     
      SetCurr(DEV_DEFECT_E2); 
      break;

    case DEV_DEFECT_E2:                      
      if ((mpSerial[ibPort] == SER_GOODCHECK))
      {
        ReadDefectE();
        Log(LOG_END_DEFECT_E);

        MakePause(DEV_POSTDEFECT_E2);
      }
      else                                    
      {
        if (cbRepeat == 0) MakePause(DEV_POSTDEFECT_E2);    // да !       
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryDefectE();
          SetCurr(DEV_DEFECT_E2);
        }
      } 
      break;

    case DEV_POSTDEFECT_E2:              
      Log(LOG_BEG_INDEX_E);
      ShowLo(szIndex); DelayInf();

      cbRepeat = GetMaxRepeats();
      QueryIndexE();     
      SetCurr(DEV_INDEX_E2); 
      break;

    case DEV_INDEX_E2:                      
      if ((mpSerial[ibPort] == SER_GOODCHECK))
        MakePause(DEV_POSTINDEX_E2);
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryIndexE();
          SetCurr(DEV_INDEX_E2);
        }
      } 
      break;

    case DEV_POSTINDEX_E2:              
      Log(LOG_END_INDEX_E);

      ShowLo(szIndexOK); DelayInf();

      if (ReadIndexE('l',ibMinor+1) == 1)
      {
        Log(LOG_BEG_MAKEENERGY_E);
        fAlt = MakeEnergyE();
        Log(LOG_END_MAKEENERGY_E);

        if (fAlt == 0)
        {
          DoneProfile(); 
          Log(LOG_END_DEVICE_E);
        }
        else
        {
          Log(LOG_BEG_TIMEDATE_E);
          ShowLo(szStamp); DelayInf();

          ibMinor++;

          cbRepeat = GetMaxRepeats();
          QueryTimeE();
          SetCurr(DEV_TIME3_E2);
        }
      }
      else if (ReadIndexE('l',0) == 1)
      {
        Log(LOG_BEG_MAKEENERGY_E);
        MakeEnergyE();
        Log(LOG_END_MAKEENERGY_E);

        DoneProfile(); 
        Log(LOG_END_DEVICE_E);
      }
      else ErrorProfile();
      break;

#endif
