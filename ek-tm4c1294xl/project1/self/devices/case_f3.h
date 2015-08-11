
#ifndef SKIP_F

    case DEV_START_F3:
      cbRepeat = GetMaxRepeats();

      QueryBreakF();
      MakePause(DEV_POSTOPENCANAL_F3);
      break;

    case DEV_POSTOPENCANAL_F3:
      cbRepeat = GetMaxRepeats();
      QueryCurrentF();
      SetCurr(DEV_CURRENT_F3);
      break;

    case DEV_CURRENT_F3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentF();
      else 
      {
        if (cbRepeat == 0)
          ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryCurrentF();
          SetCurr(DEV_CURRENT_F3);
        }
      } 
      break;

#endif
