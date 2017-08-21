
#ifndef SKIP_T

    case DEV_START_T2:                     
      cbRepeat = MaxRepeats();
      QueryVersionT();
      SetCurr(DEV_VERSION_T2);
      break;

    case DEV_VERSION_T2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadVersionT();                  
        MakeLongPause(DEV_POSTVERSION_T2,1);
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryVersionT();
          SetCurr(DEV_VERSION_T2);
        }
      } 
      break;

    case DEV_POSTVERSION_T2:
      cbCorrects = 0;

      if (fCurrCtrlHou == 1)
        MakePause(DEV_POSTOPENCANAL_T2);
      else
        MakePause(DEV_POSTCORRECT_T2);  
      break;


    case DEV_POSTOPENCANAL_T2:                  
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = MaxRepeats();
      QueryTimeT();                          
      SetCurr(DEV_TIME_T2);          
      break;

    case DEV_TIME_T2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltT();                  
        MakePause(DEV_POSTTIME_T2);
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTimeT();
          SetCurr(DEV_TIME_T2);
        }
      } 
      break;


    case DEV_POSTTIME_T2:
      wBuffD  = GetDayIndex();              // количество дней с начала года ведомого счётчика
      dwBuffC = GetSecondIndex();           // количество секунд ведомого счётчика

      tiAlt = tiCurr;                       // текущие время/дата сумматора

      if (wBuffD != GetDayIndex())          
      { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна 
      else 
      {
        if (dwBuffC > GetSecondIndex())                                         // необходима коррекция времени ведомого счётчика назад
          ShowDeltaNeg();
        else
          ShowDeltaPos();

        if (dwBuffC < bMINORCORRECT_I)                                          // без коррекции
        { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_T2); }     
        else if (GetHouIndex() == (tiAlt.bHour*2 + tiAlt.bMinute/30))           // простая коррекция 
        { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_T2); } 
        else                                                                    
        { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
      }
      break;

    case DEV_CONTROL_T2: 
      if (++cbCorrects > bCORRECTS)          
        MakePause(DEV_POSTCORRECT_T2);
      else
      {
        cbRepeat = MaxRepeats();                         
        QueryControlT();                          
        SetCurr(DEV_POSTCONTROL_T2);
      }
      break;

    case DEV_POSTCONTROL_T2:
      MakePause(DEV_POSTOPENCANAL_T2);
      break;

    case DEV_POSTCORRECT_T2:                  
      Clear();

      cbRepeat = MaxRepeats();
      QueryTimeT();                          
      SetCurr(DEV_PREVHEADER_T2);          
      break;

    case DEV_PREVHEADER_T2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltT();
        InitHeaderT();
   
        cbRepeat = MaxRepeats();
        QueryHeaderT();                         
        SetCurr(DEV_HEADER_T2);
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTimeT();
          SetCurr(DEV_PREVHEADER_T2);
        }
      } 
      break;

    case DEV_HEADER_T2:                    
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_T2);
      else                                  
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderT();
          SetCurr(DEV_HEADER_T2);
        }
      } 
      break;

    case DEV_POSTHEADER_T2:                   
      if (ReadHeaderT() == 0)
        DoneProfile();  
      else
      { 
        cbRepeat = MaxRepeats();
        QueryHeaderT();
        SetCurr(DEV_HEADER_T2);
      }
      break;

#endif
