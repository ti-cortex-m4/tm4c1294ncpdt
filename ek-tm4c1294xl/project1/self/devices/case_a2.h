
#ifndef SKIP_A

    case DEV_START_A2:                     
      cbCorrects = 0;

      cbRepeat = GetMaxRepeats();
      QueryOpenA();
      SetCurr(DEV_OPENCANAL_A2);
      break;

    case DEV_OPENCANAL_A2:                     
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultA() == 1))
      {
        if (fCurrCtrl == true)
          MakePause(DEV_POSTOPENCANAL_A2);
        else
          MakePause(DEV_POSTCORRECT_A2);  
      }
      else                                      
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryOpenA();
          SetCurr(DEV_OPENCANAL_A2);
        }
      }  
      break;

    case DEV_POSTOPENCANAL_A2:                  
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = GetMaxRepeats();
      QueryTimeA();                          
      SetCurr(DEV_TIME_A2);          
      break;

    case DEV_TIME_A2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueA = ReadTimeA();
        MakePause(DEV_POSTTIME_A2);
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTimeA();
          SetCurr(DEV_TIME_A2);
        }
      } 
      break;


    case DEV_POSTTIME_A2:
      {
        uint iwDay1 = GetDayIndexMD(tiValueA.bMonth, tiValueA.bDay);
        ulong dwSecond1 = GetSecondIndex(tiValueA);

        uint iwDay2 = GetDayIndexMD(tiCurr.bMonth, tiCurr.bDay);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (iwDay1 != iwDay2)
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // даты не совпадают, коррекция невозможна
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);
          ulong dwDelta = AbsLong(dwSecond1 - dwSecond2);

          if (dwDelta < GetCorrectLimit())                                        // без коррекции
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_A2); }
          else if (dwDelta < bMAJORCORRECT_A)                                     // простая коррекция
          {
            if (cbCorrects == 0)
            { ShowLo(szCorrectYes); DelayInf();  MakePause(DEV_CONTROL_A2); }
            else
            {
              if (boManageTime == true)
              { ShowLo(szManageYes); DelayInf();  MakePause(DEV_MANAGE_A2); }
              else
              { ShowLo(szManageNo); DelayMsg();  ErrorProfile(); }
            }
          }
          else if (dwDelta < wLIMITCORRECT_A)                                     // сложная коррекция
          {
            if (boManageTime == true)
            { ShowLo(szManageYes); DelayInf();  MakePause(DEV_MANAGE_A2); }
            else
            { ShowLo(szManageNo); DelayMsg();  ErrorProfile(); }
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // разница времени слишком велика, коррекция невозможна
        }
      }
      break;


    case DEV_CONTROL_A2: 
      if (++cbCorrects > bMINORREPEATS)          
        MakePause(DEV_POSTCORRECT_A2);
      else
      {
        cbRepeat = GetMaxRepeats();                         
        QueryControlA();                          
        SetCurr(DEV_POSTCONTROL_A2);
      }
      break;

    case DEV_POSTCONTROL_A2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultA() == 1))
        MakePause(DEV_POSTOPENCANAL_A2);
      else                                    
      {
        if (cbRepeat == 0) MakePause(DEV_POSTOPENCANAL_A2);   // да !
        else
        {
          DelayOff(); // ErrorLink();
          cbRepeat--;
          
          QueryControlA();
          SetCurr(DEV_POSTCONTROL_A2);
        }
      } 
      break;

    case DEV_MANAGE_A2:                  
      if (++cbCorrects > bMINORREPEATS)          
        MakePause(DEV_POSTCORRECT_A2);
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryManageA();                          
        SetCurr(DEV_POSTMANAGE_A2);
      }
      break;

    case DEV_POSTMANAGE_A2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultA() == 1))
        MakePause(DEV_POSTOPENCANAL_A2);
      else                                    
      {
        if (cbRepeat == 0) MakePause(DEV_POSTOPENCANAL_A2);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryManageA();
          SetCurr(DEV_POSTMANAGE_A2);
        }
      } 
      break;


    case DEV_POSTCORRECT_A2:                  
      Clear();

      cbRepeat = GetMaxRepeats();
      QueryTopA();                         
      SetCurr(DEV_TOP_A2);
      break;

    case DEV_TOP_A2:                    
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTopA();
        MakePause(DEV_POSTTOP_A2);
      }
      else                                  
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTopA();
          SetCurr(DEV_TOP_A2);
        }
      } 
      break;

    case DEV_POSTTOP_A2:                 
      cbRepeat2 = 0;
      if (diCurr.bDevice == 1)
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderA();
        SetCurr(DEV_HEADER_A2);
      }
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderA_Plus(bBLOCKS_A);
        SetCurr(DEV_HEADER_A2PLUS);
      }
      break;

    case DEV_HEADER_A2:                       
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadHeaderA();
        MakePause(DEV_POSTHEADER_A2);         
      }
      else                                    
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR1_A2);
/*
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderA();
          SetCurr(DEV_HEADER_A2);
        }*/
      } 
      break;

    case DEV_ERROR1_A2: 
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbRepeat2 > bMINORREPEATS) ErrorProfile();
      else 
      {
        cbRepeat = GetMaxRepeats();
        QueryIdA();
        SetCurr(DEV_POSTERROR1_A2);
      }
      break;

    case DEV_POSTERROR1_A2: 
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdA() == 1)
        {
          QueryHeaderA();
          SetCurr(DEV_HEADER_A2);
        }
        else
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR1_A2);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdA();
          SetCurr(DEV_POSTERROR1_A2);
        }
      } 
      break;

    case DEV_POSTHEADER_A2:                   
      cbRepeat2 = 0;
      cbRepeat = GetMaxRepeats();
      QueryDataA();                          
      SetCurr(DEV_DATA_A2);
      break;

    case DEV_DATA_A2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTDATA_A2);
      else                                   
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR2_A2);
/*
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDataA();
          SetCurr(DEV_DATA_A2);
        }*/
      } 
      break;

    case DEV_ERROR2_A2: 
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbRepeat2 > bMINORREPEATS) ErrorProfile();
      else 
      {
        cbRepeat = GetMaxRepeats();
        QueryIdA();
        SetCurr(DEV_POSTERROR2_A2);
      }
      break;

    case DEV_POSTERROR2_A2: 
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdA() == 1)
        {
          QueryDataA();
          SetCurr(DEV_DATA_A2);
        }
        else
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR2_A2);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdA();
          SetCurr(DEV_POSTERROR2_A2);
        }
      } 
      break;

    case DEV_POSTDATA_A2:                           
      cbRepeat2 = 0;
      NewBoundsAbs16(iwMajor);
      if (ReadDataA() == 0)
        DoneProfile();  
      else 
      {
        (iwMajor == 0) ? (iwMajor = 8192/3 - 1) : (iwMajor--);

        cbRepeat = GetMaxRepeats();
        QueryHeaderA();               
        SetCurr(DEV_HEADER_A2);
      }
      break;

    case DEV_HEADER_A2PLUS:                       
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_DATA_A2PLUS);         
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderA_Plus(bBLOCKS_A);
          SetCurr(DEV_HEADER_A2PLUS);
        }
      } 
      break;

    case DEV_DATA_A2PLUS:
    {
      uchar i;
      for (i=0; i<bBLOCKS_A; i++)
        if (TestDataA_Plus(i) == 0) break;

      if (i != bBLOCKS_A)
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderA_Plus(bBLOCKS_A);
          SetCurr(DEV_HEADER_A2PLUS);
        }
      }
      else
      {
        NewBoundsAbs16(iwMajor);
        for (i=0; i<bBLOCKS_A; i++)
        { 
          if (ReadDataA_Plus(i) == 0) break;
          (iwMajor == 0) ? (iwMajor = 8192/3 - 1) : (iwMajor--);
        }

        if (i != bBLOCKS_A)
          DoneProfile();
        else
        {
          cbRepeat = GetMaxRepeats();
          QueryHeaderA_Plus(bBLOCKS_A);
          SetCurr(DEV_HEADER_A2PLUS);
        }
      }
    }
      break;

#endif
