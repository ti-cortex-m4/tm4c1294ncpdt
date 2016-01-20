#ifndef SKIP_N31

    case DEV_START_N31C:
      cbRepeat = GetMaxRepeats();
      QueryOpenN31();
      SetCurr(DEV_OPENCANAL_N31C);
      break;

    case DEV_OPENCANAL_N31C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadOpenN31() == false)
          ErrorCurrent();
        else
          MakePause(DEV_POSTOPENCANAL_N31C);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenN31();
          SetCurr(DEV_OPENCANAL_N31C);
        }
      }
      break;

    case DEV_POSTOPENCANAL_N31C:
      cbRepeat = GetMaxRepeats();
      QueryEngAbsN31();
      SetCurr(DEV_ENERGY_N31C);
      break;

    case DEV_ENERGY_N31C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentN31();
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbsN31();
          SetCurr(DEV_ENERGY_N31C);
        }
      }
      break;

#endif
