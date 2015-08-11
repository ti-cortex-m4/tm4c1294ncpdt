
#ifndef SKIP_C

    case DEV_START_C2:
      cbCorrects = 0;

      cbRepeat = GetMaxRepeats();
      QueryOpenC();
      SetCurr(DEV_OPENCANAL_C2);
      break;
 
    case DEV_OPENCANAL_C2:                     
      if ((mpSerial[ibPort] == SER_GOODCHECK)/* && (ReadResultC() == 1)*/)
      {
        if (fCurrCtrl == 1)
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
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = GetMaxRepeats();
      QueryTimeC();                          
      SetCurr(DEV_TIME_C2);          
      break;

    case DEV_TIME_C2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueC = ReadTimeC();
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
    {
      uint iwDay1 = GetDayIndexMD(tiValueC.bMonth, tiValueC.bDay);              // количество дней с начала года ведомого счётчика
      ulong dwSecond1 = GetSecondIndex(tiValueC);                               // количество секунд ведомого счётчика

      uint iwDay2 = GetDayIndexMD(tiCurr.bMonth, tiCurr.bDay);                  // количество дней с начала года сумматора
      ulong dwSecond2 = GetSecondIndex(tiCurr);                                 // количество секунд сумматора

      if (iwDay1 != iwDay2)
      { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
      else
      {
        ulong dwDelta;
        if (dwSecond1 > dwSecond2)
        {
          dwDelta = dwSecond1 - dwSecond2;
          ShowDeltaTimeNegative(ibDig, dwDelta);
        }
        else
        {
          dwDelta = dwSecond2 - dwSecond1;
          ShowDeltaTimePositive(ibDig, dwDelta);
        }

        if (dwDelta < GetCorrectLimit())                                           // без коррекции
        { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_C2); }     
        else if (GetCurrHouIndex() == (tiValueC.bHour*2 + tiValueC.bMinute/30)) // простая коррекция
        { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_C2);  } 
        else                                                                    
        { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
      }
    }
      break;

    case DEV_CONTROL_C2: 
      if (++cbCorrects > 3)          
        MakePause(DEV_POSTCORRECT_C2);
      else
      {
        cbRepeat = GetMaxRepeats();                         
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
      cbRepeat = GetMaxRepeats();
      QueryVersionC();
      SetCurr(DEV_VERSION_C2);
      break;

    case DEV_VERSION_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadVersionC();

        if (boHideMessages == false)
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
      cbRepeat = GetMaxRepeats();
      QueryTimeC();                          
      SetCurr(DEV_VALUE_C2);          
      break;

    case DEV_VALUE_C2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueC = ReadTimeC();
        dwValueC = DateToHouIndex(tiValueC);
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
      if (boShortProfileC == false)
      {             
        InitHeaderC_6();

        cbRepeat = GetMaxRepeats();
        QueryHeaderC_6();
        SetCurr(DEV_HEADER_6_C2);
      }
      else
      {
        InitHeaderC_1();

        cbRepeat = GetMaxRepeats();
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
        cbRepeat = GetMaxRepeats();
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
      cbRepeat = GetMaxRepeats();
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
        cbRepeat = GetMaxRepeats();
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
        cbRepeat = GetMaxRepeats();
        QueryHeaderC_1();
        SetCurr(DEV_HEADER_1_C2);
      }
      break;

#endif
