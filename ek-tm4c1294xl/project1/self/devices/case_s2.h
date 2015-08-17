
#ifndef SKIP_S

    case DEV_START_S2:                  
      cbRepeat = GetMaxRepeats();
      QueryVersionS();
      SetCurr(DEV_VERSION_S2);
      break;

    case DEV_VERSION_S2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadVersionS();

        if (boHideMessages == false)
          MakeLongPause(DEV_POSTVERSION_S2, 1);
        else
          MakePause(DEV_POSTVERSION_S2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryVersionS();
          SetCurr(DEV_VERSION_S2);
        }
      } 
      break;


    case DEV_POSTVERSION_S2:                     
      cbCorrects = 0;

      if (fCurrCtrlHou == 1)
        MakePause(DEV_POSTOPENCANAL_S2);
      else
        MakePause(DEV_POSTCORRECT_S2);  
      break;

    case DEV_POSTOPENCANAL_S2:                  
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1bu",cbCorrects+1); DelayInf();

      cbRepeat = GetMaxRepeats();
      QueryTimeS();                          
      SetCurr(DEV_TIME_S2);          
      break;

    case DEV_TIME_S2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltS();                  
        MakePause(DEV_POSTTIME_S2);
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTimeS();
          SetCurr(DEV_TIME_S2);
        }
      } 
      break;


    case DEV_POSTTIME_S2:
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

        if (dwBuffC < GetCorrectLimit())                                           // без коррекции
        { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_S2); }     
        else if (GetHouIndex() == (tiAlt.bHour*2 + tiAlt.bMinute/30))           // простая коррекция 
        { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_S2); } 
        else                                                                    
        { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
      }
      break;

    case DEV_CONTROL_S2: 
      if (++cbCorrects > bMINORREPEATS)          
        MakePause(DEV_POSTCORRECT_S2);
      else
      {
        cbRepeat = GetMaxRepeats();                         
        QueryControlS(tiCurr);
        SetCurr(DEV_POSTOPENCANAL_S2);
      }
      break;


    case DEV_POSTCORRECT_S2:
      Clear(); ShowPercent(25);

      cbRepeat = GetMaxRepeats();
      QueryConfigS();
      SetCurr(DEV_CONFIG_S2);
      break;

    case DEV_CONFIG_S2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadConfigS();
        MakePause(DEV_POSTCONFIG_S2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryConfigS();
          SetCurr(DEV_CONFIG_S2);
        }
      } 
      break;

    case DEV_POSTCONFIG_S2:
      ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryTimeS();                          
      SetCurr(DEV_VALUE_S2);
      break;

    case DEV_VALUE_S2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltS();                  
        tiValueC = tiAlt;  
        dwValueC = DateToHouIndex();
        MakePause(DEV_POSTVALUE_S2);
      }
      else                                    
      {
        if (cbRepeat == 0) 
          ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTimeS();
          SetCurr(DEV_VALUE_S2);
        }
      } 
      break;

    case DEV_POSTVALUE_S2:   
      ShowPercent(75);
      InitHeaderS();

      cbRepeat = GetMaxRepeats();
      QueryHeaderS();
      SetCurr(DEV_HEADER_S2);
      break;

    case DEV_HEADER_S2:                       
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_S2);         
      else
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderS();
          SetCurr(DEV_HEADER_S2);
        }
      } 
      break;

    case DEV_POSTHEADER_S2:
      if (ReadHeaderS() == 0)
        DoneProfile();  
      else 
        MakePause(DEV_DATA_S2);         
      break;

    case DEV_DATA_S2:                   
      cbRepeat = GetMaxRepeats();
      QueryHeaderS();
      SetCurr(DEV_HEADER_S2);
      break;

#endif
