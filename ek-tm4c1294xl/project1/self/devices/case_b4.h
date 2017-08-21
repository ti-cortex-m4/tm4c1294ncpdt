
#ifndef SKIP_B

    case DEV_START_B4:
      SetupCheckup();

      cbRepeat = MaxRepeats();
      QueryOpenB();
      SetCurr(DEV_OPENCANAL_B4);             
      break;

    case DEV_OPENCANAL_B4:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
        if (TestVersionB710()) 
          DoneCheckup();
        else if (mpbCheckupLimitD[ibDig] == 1)
          MakePause(DEV_CHECKUP_DAY_B4);
        else
          MakePause(DEV_PREVTOP1_B4);
      else
      {
        if (cbRepeat == 0) ErrorCheckup();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenB();
          SetCurr(DEV_OPENCANAL_B4);
        }
      }
      break;


    case DEV_PREVTOP1_B4:
      cbRepeat = MaxRepeats();
      QueryTopB();                          
      SetCurr(DEV_TOP1_B4);
      break;

    case DEV_TOP1_B4:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTopBOld_Checkup();
        MakePause(DEV_POSTTOP1_B4);
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorCheckup(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTopB();
          SetCurr(DEV_TOP1_B4);
        }
      } 
      break;

    case DEV_POSTTOP1_B4:
      InitHeaderB_Checkup1();

      MakeLongPause(DEV_PREVHEADER1_B4,1);
      break;

    case DEV_PREVHEADER1_B4:
      cbIteration = 0;

      cbRepeat = MaxRepeats();     
      QueryHeaderB();
      SetCurr(DEV_HEADER1_B4);
      break;

    case DEV_HEADER1_B4:                       
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER1_B4);         
      else
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR4_B4);
      } 
      break;

    case DEV_ERROR4_B4: 
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbIteration > bMINORREPEATS) ErrorCheckup();
      else 
      {
        cbRepeat = MaxRepeats();
        QueryIdB();
        SetCurr(DEV_POSTERROR4_B4);
      }
      break;

    case DEV_POSTERROR4_B4: 
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdB() == 1)
        {
          QueryHeaderB();
          SetCurr(DEV_HEADER1_B4);
        }
        else         
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR4_B4);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorCheckup(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdB();
          SetCurr(DEV_POSTERROR4_B4);
        }
      } 
      break;

    case DEV_POSTHEADER1_B4:                   
        if (ReadHeaderB_Checkup1() == 0)
        {
          //x_str("\n days prealoding completed");
          MakePause(DEV_CHECKUP_DAY_B4);  
        }
        else
        {
          DecPtrB_Checkup(1);

          MakePause(DEV_PREVHEADER1_B4);
        }
      break;


    case DEV_CHECKUP_DAY_B4:
      if (mpbCheckupLimitD[ibDig] == 0)
      {
        //x_str("\n days checkup disabled");
        ShowLo(szBlocking);
        MakePause(DEV_CHECKUP_MON_B4);
      }
      else 
      {
        ibCheckupDay = 1;
        CheckupShowDay(ibCheckupDay);

        cbIteration = 0;

        cbRepeat = MaxRepeats();
        QueryEnergyPrevDayB();                          
        SetCurr(DEV_ENERGY_DAY_B4);          
      }
      break;

    case DEV_ENERGY_DAY_B4:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTENERGY_DAY_B4);
      else                                    
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR1_B4);
      } 
      break;

    case DEV_ERROR1_B4: 
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbIteration > bMINORREPEATS) ErrorCheckup();
      else 
      {
        cbRepeat = MaxRepeats();
        QueryIdB();
        SetCurr(DEV_POSTERROR1_B4);
      }
      break;

    case DEV_POSTERROR1_B4: 
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdB() == 1)
        {
          QueryEnergyPrevDayB();                          
          SetCurr(DEV_ENERGY_DAY_B4);          
        }
        else         
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR1_B4);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorCheckup(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdB();
          SetCurr(DEV_POSTERROR1_B4);
        }
      } 
      break;


    case DEV_POSTENERGY_DAY_B4:
      if (ibCheckupDay == 1) ReadEnergyB(); 
      CheckupDayEnergy(ibCheckupDay);
      
      if (++ibCheckupDay <= mpbCheckupLimitD[ibDig]) 
      {
        CheckupShowDay(ibCheckupDay);

        ReadEnergyPrevDayB(ibCheckupDay);
        MakePause(DEV_POSTENERGY_DAY_B4);          
      }
      else
      {
        //x_str("\n days checkup finished");
        MakePause(DEV_CHECKUP_MON_B4);
      }
      break;


    case DEV_CHECKUP_MON_B4:
      if (mpbCheckupLimitM[ibDig] == 0)
      {
        //x_str("\n months checkup disabled");
        ShowLo(szBlocking);
        MakePause(DEV_PREVCORRECT_B4);
      }
      else 
      {
        ibCheckupMon = 1;
        CheckupShowMon(ibCheckupMon);

        cbIteration = 0;

        cbRepeat = MaxRepeats();
        QueryEnergyPrevMonB(ibCheckupMon);
        SetCurr(DEV_ENERGY_MON_B4);          
      }
      break;

    case DEV_ENERGY_MON_B4:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTENERGY_MON_B4);
      else                                    
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR3_B4);
      } 
      break;

    case DEV_ERROR3_B4: 
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbIteration > bMINORREPEATS) ErrorCheckup();
      else 
      {
        cbRepeat = MaxRepeats();
        QueryIdB();
        SetCurr(DEV_POSTERROR3_B4);
      }
      break;

    case DEV_POSTERROR3_B4: 
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdB() == 1)
        {
          QueryEnergyPrevMonB(ibCheckupMon);
          SetCurr(DEV_ENERGY_MON_B4);          
        }
        else         
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR3_B4);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorCheckup(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdB();
          SetCurr(DEV_POSTERROR3_B4);
        }
      } 
      break;


    case DEV_POSTENERGY_MON_B4:
      ReadEnergyB(); 
      CheckupMonEnergy(ibCheckupMon);
      /*
      if (++ibCheckupMon <= mpbCheckupLimitM[ibDig]) 
      {
        CheckupShowMon(ibCheckupMon);

        cbIteration = 0;

        cbRepeat = MaxRepeats();
        QueryEnergyPrevMonB(ibCheckupMon);
        SetCurr(DEV_ENERGY_MON_B4);          
      }
      else
      */
      {
        //x_str("\n months checkup finished");
        MakePause(DEV_PREVCORRECT_B4);
      }
      break;


    case DEV_PREVCORRECT_B4:
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

        if (boCheckupReadonly == true)
        {
          DelayInf();
          DoneCheckup();
        }
        else
        {
          ibCheckupDay = 0;
          MakeLongPause(DEV_PREVTOP2_B4,1);
        }
      }
      break;


    case DEV_PREVTOP2_B4:
      cbRepeat = MaxRepeats();
      QueryTopB();                          
      SetCurr(DEV_TOP2_B4);
      break;

    case DEV_TOP2_B4:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTopBOld_Checkup();
        MakePause(DEV_POSTTOP2_B4);
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorCheckup(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTopB();
          SetCurr(DEV_TOP2_B4);
        }
      } 
      break;

    case DEV_POSTTOP2_B4:
      InitHeaderB_Checkup2();

      MakeLongPause(DEV_PREVHEADER2_B4,1);
      break;


    case DEV_PREVHEADER2_B4:
      cbIteration = 0;

      cbRepeat = MaxRepeats();     
      QueryHeaderB();
      SetCurr(DEV_HEADER2_B4);
      break;

    case DEV_HEADER2_B4:                       
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER2_B4);         
      else
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR2_B4);
      } 
      break;

    case DEV_ERROR2_B4: 
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbIteration > bMINORREPEATS) ErrorCheckup();
      else 
      {
        cbRepeat = MaxRepeats();
        QueryIdB();
        SetCurr(DEV_POSTERROR2_B4);
      }
      break;

    case DEV_POSTERROR2_B4: 
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdB() == 1)
        {
          QueryHeaderB();
          SetCurr(DEV_HEADER2_B4);
        }
        else         
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR2_B4);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorCheckup(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdB();
          SetCurr(DEV_POSTERROR2_B4);
        }
      } 
      break;

    case DEV_POSTHEADER2_B4:                   
        if (ReadHeaderB_Checkup2() == 0)
        {
          //x_str("\n all days completed, done checkup");
          DoneCheckup();  
        }
        else
        {
          DecPtrB_Checkup(1);

          MakePause(DEV_PREVHEADER2_B4);
        }
      break;

#endif
