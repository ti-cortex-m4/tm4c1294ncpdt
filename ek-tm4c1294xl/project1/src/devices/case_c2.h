
#ifndef SKIP_C

    case DEV_START_C2:
      cbCorrects = 0;

      cbRepeat = bMINORREPEATS;
      QueryOpenC();
      SetCurr(DEV_OPENCANAL_C2);
      break;
 
    case DEV_OPENCANAL_C2:                     
      if ((mpSerial[ibPort] == SER_GOODCHECK)/* && (ReadResultC() == 1)*/)
      {
        if (fCurrCtrlHou == 1)
          MakePause(DEV_POSTOPENCANAL_C2);
        else 
          MakePause(DEV_POSTCORRECT_C2);  
      }
      else                                      
      {
        if (cbRepeat == 0) 
          ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryOpenC();
          SetCurr(DEV_OPENCANAL_C2);
        }
      }  
      break;

    case DEV_POSTOPENCANAL_C2:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1bu",cbCorrects+1); DelayInf();

      cbRepeat = bMINORREPEATS;
      QueryTimeC();                          
      SetCurr(DEV_TIME_C2);          
      break;

    case DEV_TIME_C2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltC();                  
        MakePause(DEV_POSTTIME_C2);
      }
      else                                    
      {
        if (cbRepeat == 0) 
          ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTimeC();
          SetCurr(DEV_TIME_C2);
        }
      } 
      break;


    case DEV_POSTTIME_C2:
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

        if (dwBuffC < MinorCorrect())                                           // без коррекции
        { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_C2); }     
        else if (GetHouIndex() == (tiAlt.bHour*2 + tiAlt.bMinute/30))           // простая коррекция 
        { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_C2);  } 
        else                                                                    
        { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
      }
      break;

    case DEV_CONTROL_C2: 
      if (++cbCorrects > 3)          
        MakePause(DEV_POSTCORRECT_C2);
      else
      {
        cbRepeat = bMINORREPEATS;                         
        QueryControlC();                          
        SetCurr(DEV_POSTCONTROL_C2);
      }
      break;

    case DEV_POSTCONTROL_C2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultC() == 1))
        MakePause(DEV_POSTOPENCANAL_C2);
      else                                    
      {
        if (cbRepeat == 0) 
          MakePause(DEV_POSTOPENCANAL_C2);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryControlC();
          SetCurr(DEV_POSTCONTROL_C2);
        }
      } 
      break;


    case DEV_POSTCORRECT_C2:                  
      cbRepeat = bMINORREPEATS;
      QueryVersionC();
      SetCurr(DEV_VERSION_C2);
      break;

    case DEV_VERSION_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadVersionC();

        if (boHideMessages == boFalse)
          MakeLongPause(DEV_POSTVERSION_C2, 1);
        else
          MakePause(DEV_POSTVERSION_C2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryVersionC();
          SetCurr(DEV_VERSION_C2);
        }
      } 
      break;

    case DEV_POSTVERSION_C2:
      cbRepeat = bMINORREPEATS;
      QueryTimeC();                          
      SetCurr(DEV_VALUE_C2);          
      break;

    case DEV_VALUE_C2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltC();                  
        tiValueC = tiAlt;  
        dwValueC = DateToHouIndex();
        MakePause(DEV_POSTVALUE_C2);
      }
      else                                    
      {
        if (cbRepeat == 0) 
          ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTimeC();
          SetCurr(DEV_VALUE_C2);
        }
      } 
      break;

    case DEV_POSTVALUE_C2:   
      /*if (mpbHouCheck[ibDig] != 0)
      {
        Clear(); sprintf(szLo+2,"проверки: %bu",mpbHouCheck[ibDig]);
        MakeLongPause(DEV_INIT_61_C2, 1);
      }
      else*/ 
      cbRepeat2 = 0;
      if (boShortProfileC == boFalse)
      {             
        InitHeaderC_6();

        cbRepeat = bMINORREPEATS;
        QueryHeaderC_6();
        SetCurr(DEV_HEADER_6_C2);
      }
      else
      {
        InitHeaderC_1();

        cbRepeat = bMINORREPEATS;
        QueryHeaderC_1();
        SetCurr(DEV_HEADER_1_C2);
      }
      break;

    case DEV_HEADER_6_C2:                       
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_6_C2);         
      else
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR_6_C2);
/*
        if (cbRepeat == 0)
          ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderC_6();
          SetCurr(DEV_HEADER_6_C2);
        }*/
      } 
      break;

    case DEV_ERROR_6_C2: 
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbRepeat2 > bMINORREPEATS) ErrorProfile();
      else 
      {
        cbRepeat = bMINORREPEATS;
        QueryIdC();
        SetCurr(DEV_POSTERROR_6_C2);
      }
      break;

    case DEV_POSTERROR_6_C2: 
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdC() == 1)
        {
          QueryHeaderC_6();
          SetCurr(DEV_HEADER_6_C2);
        }
        else         
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR_6_C2);
        }
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdC();
          SetCurr(DEV_POSTERROR_6_C2);
        }
      } 
      break;

    case DEV_POSTHEADER_6_C2:                   
      cbRepeat2 = 0;
      if (ReadHeaderC_6() == 0)
        DoneProfile();  
      else 
        MakePause(DEV_DATA_6_C2);         
      break;

    case DEV_DATA_6_C2:                   
      cbRepeat = bMINORREPEATS;
      QueryHeaderC_6();
      SetCurr(DEV_HEADER_6_C2);
      break;

    case DEV_HEADER_1_C2:                       
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        cbRepeat2 = 0;
        if ((IndexInBuff() == 6) && (InBuff(1) == 0x83) && (InBuff(2) == 0x24) && (InBuff(3) == 0x05))      // если нет требуемой записи
        {
          if (++iwMajor > 480)                             // если питание было выключено слишком долго
            DoneProfile();
          else
          {
            sprintf(szLo," выключено: %-4u   ",iwMajor);   // показываем процесс

            iwDigHou = (wHOURS+iwHardHou-wBaseCurr)%wHOURS;
            ShowProgressDigHou();

            if (MakeStopHou(0) == 0)  
              DoneProfile();
            else
              MakePause(DEV_DATA_1_C2);
          }
        }
        else
        {
          iwMajor = 0;                                      // если есть требуемая запись
          MakePause(DEV_POSTHEADER_1_C2);         
        }
      }
      else
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR_1_C2);
/*
        if (cbRepeat == 0)
          ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderC_1();
          SetCurr(DEV_HEADER_1_C2);
        }*/
      } 
      break;

    case DEV_ERROR_1_C2: 
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbRepeat2 > bMINORREPEATS) ErrorProfile();
      else 
      {
        cbRepeat = bMINORREPEATS;
        QueryIdC();
        SetCurr(DEV_POSTERROR_1_C2);
      }
      break;

    case DEV_POSTERROR_1_C2: 
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdC() == 1)
        {
          QueryHeaderC_1();
          SetCurr(DEV_HEADER_1_C2);
        }
        else         
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR_1_C2);
        }
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdC();
          SetCurr(DEV_POSTERROR_1_C2);
        }
      } 
      break;

    case DEV_POSTHEADER_1_C2:                   
      if (ReadHeaderC_1() == 0)
        DoneProfile();  
      else 
        MakePause(DEV_DATA_1_C2);         
      break;

    case DEV_DATA_1_C2:                   
      if (++wBaseCurr > wHOURS) 
        DoneProfile();
      else
      {
        cbRepeat = bMINORREPEATS;
        QueryHeaderC_1();
        SetCurr(DEV_HEADER_1_C2);
      }
      break;

#endif
