
#ifndef SKIP_A

    case DEV_START_A3:
      cbRepeat = MaxRepeats();

      QueryOpenA();
      SetCurr(DEV_OPENCANAL_A3);             
      break;

    case DEV_OPENCANAL_A3:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultA() == 1))
        MakePause(DEV_POSTOPENCANAL_A3);
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenA();
          SetCurr(DEV_OPENCANAL_A3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_A3:
      cbRepeat = MaxRepeats();
      QueryEnergyA(0);
      SetCurr(DEV_ENERGY_A3);
      break;

    case DEV_ENERGY_A3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentA();
      else 
      {
        if (cbRepeat == 0)
          ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryEnergyA(0);
          SetCurr(DEV_ENERGY_A3);
        }
      } 
      break;

#endif
