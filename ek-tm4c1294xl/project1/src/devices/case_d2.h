
#ifndef SKIP_D

    case DEV_START_D2:
      cbRepeat = bMAJORREPEATS;            

      QueryOpenD();
      SetCurr(DEV_OPENCANAL_D2);
      break;

    case DEV_OPENCANAL_D2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_D2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ShowPercent(bMAJORREPEATS - cbRepeat);   
          cbRepeat--;
          
          QueryOpenD();
          SetCurr(DEV_OPENCANAL_D2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_D2:
      ShowPercent(96);

      cbRepeat = bMINORREPEATS;
      QueryPasswordD();
      SetCurr(DEV_PASSWORD_D2);
      break;

    case DEV_PASSWORD_D2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultD() == 1))
      {
        if (fCurrCtrlHou == 1)
          MakePause(DEV_POSTPASSWORD_D2);
        else
          MakePause(DEV_POSTCORRECT_D2);
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryPasswordD();
          SetCurr(DEV_PASSWORD_D2);
        }
      } 
      break;

    case DEV_POSTPASSWORD_D2:
      ShowPercent(97);

      cbRepeat = bMINORREPEATS;
      QueryCorrectD();
      SetCurr(DEV_CORRECT_D2);
      break;

    case DEV_CORRECT_D2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_D2);
      else                                    
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_D2);   // да !
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryCorrectD();
          SetCurr(DEV_CORRECT_D2);
        }
      } 
      break;

    case DEV_POSTCORRECT_D2:
      ShowPercent(98);

      cbRepeat = bMINORREPEATS;
      QueryProfileD();
      SetCurr(DEV_PROFILE_D2);
      break;

    case DEV_PROFILE_D2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadProfileD();
        MakePause(DEV_POSTPROFILE_D2);
      }
      else 
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryProfileD();
          SetCurr(DEV_PROFILE_D2);
        }
      } 
      break;

    case DEV_POSTPROFILE_D2:
      ShowPercent(99);

      cbRepeat = bMINORREPEATS;
      QueryPacketSizeD();
      SetCurr(DEV_PACKETSIZE_D2);
      break;

    case DEV_PACKETSIZE_D2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        memset(&tiDigPrev, 0, sizeof(time));
        MakePause(DEV_POSTPACKETSIZE_D2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryPacketSizeD();
          SetCurr(DEV_PACKETSIZE_D2);
        }
      } 
      break;

    case DEV_POSTPACKETSIZE_D2:
      ibMinor = 0;

      cbRepeat = bMINORREPEATS;
      QueryDataD(5+6 + (uint)48*2*cbChannels + 2);
      SetCurr(DEV_DATA1_D2);
      break;

    case DEV_DATA1_D2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadDataD() == 1)
          MakePause(DEV_POSTDATA1_D2);
        else
          DoneProfile();
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryDataD(5+6 + (uint)48*2*cbChannels + 2);
          SetCurr(DEV_DATA1_D2);
        }
      } 
      break;

    case DEV_POSTDATA1_D2:
    case DEV_POSTDATA2_D2:
      ibMinor++;

      cbRepeat = bMINORREPEATS;
      QueryDataD(5 + (uint)64*ibMinorMax + 2);
      SetCurr(DEV_DATA2_D2);
      break;

    case DEV_DATA2_D2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadDataD() == 1)
        {
          if (ibMinor < cbDigDay)
            MakePause(DEV_POSTDATA2_D2);  
          else
            DoneProfile();  
        }
        else DoneProfile();
      }
      else 
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryDataD(5 + (uint)64*ibMinorMax + 2);
          SetCurr(DEV_DATA2_D2);
        }
      } 
      break;

#endif
