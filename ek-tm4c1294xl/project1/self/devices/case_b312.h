
#ifndef SKIP_B

    case DEV_START_B312:
      cbRepeat = MaxRepeats();
      QueryOpenB();
      SetCurr(DEV_OPENCANAL_B312);             
      break;

    case DEV_OPENCANAL_B312:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
        MakePause(DEV_POSTOPENCANAL_B312);
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenB();
          SetCurr(DEV_OPENCANAL_B312);
        }
      }
      break;

    case DEV_POSTOPENCANAL_B312:
      cbRepeat = MaxRepeats();
      QueryEnergyB(0);
      SetCurr(DEV_ENERGY_B312);
      break;

    case DEV_ENERGY_B312:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentB12();
      else 
      {
        if (cbRepeat == 0)
          ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryEnergyB(0);
          SetCurr(DEV_ENERGY_B312);
        }
      } 
      break;

#endif
