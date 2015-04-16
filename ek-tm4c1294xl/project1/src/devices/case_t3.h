
#ifndef SKIP_T

    case DEV_START_T3:
      InitCurrentT();
      iwMajor = 0;

      cbRepeat = GetMaxRepeats();
      QueryEnergyAbsT(iwMajor);
      SetCurr(DEV_ENERGY_T3);
      break;

    case DEV_ENERGY_T3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        AddCurrentT();
        if (++iwMajor < 4)
        {
          cbRepeat = GetMaxRepeats();
          QueryEnergyAbsT(iwMajor);
          SetCurr(DEV_ENERGY_T3);
        }
        else ReadCurrentT();
      }
      else 
      {
        if (cbRepeat == 0)
          ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryEnergyAbsT(iwMajor);
          SetCurr(DEV_ENERGY_T3);
        }
      } 
      break;

#endif
