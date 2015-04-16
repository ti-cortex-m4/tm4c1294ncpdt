
#ifndef SKIP_F

    case DEV_START_F2:
      cbCorrects = 0;

      QueryBreakF();
      MakePause(DEV_OPENCANAL_F2);
      break;
 
    case DEV_OPENCANAL_F2:                     
      if (fCurrCtrlHou == 1)
        MakePause(DEV_POSTOPENCANAL_F2);
      else 
        MakePause(DEV_POSTCORRECT_F2);  
      break;

    case DEV_POSTOPENCANAL_F2:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1bu",cbCorrects+1); DelayInf();

      cbRepeat = GetMaxRepeats();
      QueryTimeF();                          
      SetCurr(DEV_TIME_F2);          
      break;

    case DEV_TIME_F2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltF();                  
        MakePause(DEV_POSTTIME_F2);
      }
      else                                    
      {
        if (cbRepeat == 0) 
          ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTimeF();
          SetCurr(DEV_TIME_F2);
        }
      } 
      break;


    case DEV_POSTTIME_F2:
      wBuffD  = GetDayIndex();              // ���������� ���� � ������ ���� �������� ��������
      dwBuffC = GetSecondIndex();           // ���������� ������ �������� ��������

      tiAlt = tiCurr;                       // ������� �����/���� ���������

      if (wBuffD != GetDayIndex())          
      { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ���������� 
      else 
      {
        if (dwBuffC > GetSecondIndex())                                         // ���������� ��������� ������� �������� �������� �����
          ShowDeltaNeg();
        else
          ShowDeltaPos();

        if (dwBuffC < bMINORCORRECT_F)                                          // ��� ���������
        { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_F2); }     
        else if (GetHouIndex() == (tiAlt.bHour*2 + tiAlt.bMinute/30))           // ������� ��������� 
        { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_F2);  } 
        else                                                                    
        { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
      }
      break;

    case DEV_CONTROL_F2: 
      if (++cbCorrects > bMINORREPEATS)          
        MakePause(DEV_POSTCORRECT_F2);
      else
      {
        cbRepeat = GetMaxRepeats();                         
        QueryControlF();                          
        SetCurr(DEV_POSTCONTROL_F2);
      }
      break;

    case DEV_POSTCONTROL_F2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultF() == 1))
        MakePause(DEV_POSTOPENCANAL_F2);
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryControlF();
          SetCurr(DEV_POSTCONTROL_F2);
        }
      } 
      break;


    case DEV_POSTCORRECT_F2:    
      cbRepeat2 = 0;              
      InitEnergyF();

      cbRepeat = GetMaxRepeats();
      QueryEnergyF();                          
      SetCurr(DEV_ENERGY_F2);
      break;

    case DEV_ENERGY_F2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTENERGY_F2);
      else                                    
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR_F2);
/*
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryEnergyF();
          SetCurr(DEV_ENERGY_F2);
        }*/
      } 
      break;

    case DEV_ERROR_F2: 
      mpcwOutput1[ibDig]++; Beep();

      if (++cbRepeat2 > bMINORREPEATS) ErrorProfile();
      else 
      {
        cbRepeat = GetMaxRepeats();
        QueryIdF();
        SetCurr(DEV_POSTERROR_F2);
      }
      break;

    case DEV_POSTERROR_F2: 
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdF() == 1)
        {
          QueryEnergyF();
          SetCurr(DEV_ENERGY_F2);
        }
        else
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR_F2);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdF();
          SetCurr(DEV_POSTERROR_F2);
        }
      } 
      break;

    case DEV_POSTENERGY_F2:              
      cbRepeat2 = 0;
      for (i=0; i<bBLOCKS_F; i++)
      {
        if (ReadEnergyF(i) == 0) break;
        if (++iwMajor >= wHOURS) break;
      }

      if (i == bBLOCKS_F)
      {
        cbRepeat = GetMaxRepeats();
        QueryEnergyF();                          
        SetCurr(DEV_ENERGY_F2);
      }
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderF();                          
        SetCurr(DEV_HEADER_F2);
      }
      break;

    case DEV_HEADER_F2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadHeaderF();
        DoneProfile_Stop();
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryHeaderF();
          SetCurr(DEV_HEADER_F2);
        }
      } 
      break;

#endif
