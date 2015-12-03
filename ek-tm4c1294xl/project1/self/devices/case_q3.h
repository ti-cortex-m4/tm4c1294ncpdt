
#ifndef SKIP_Q

    case DEV_START_Q3:
      ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_Q3);
      break;

    case DEV_OPENCANAL_Q3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_Q3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_Q3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_Q3:
      Clear(); ShowPercent(51);

      cbRepeat = GetMaxRepeats();
      QueryOptionQ();
      SetCurr(DEV_OPTION_Q3);
      break;

    case DEV_OPTION_Q3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_Q3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionK();
          SetCurr(DEV_OPTION_Q3);
        }
      }
      break;

    case DEV_POSTOPTION_Q3:
      ShowPercent(52);

      cbRepeat = GetMaxRepeats();
      QueryEnergySpecQ();
      SetCurr(DEV_ENERGY_Q3);
      break;

    case DEV_ENERGY_Q3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEnergyQ();
        ReadCurrentQ();
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEnergySpecQ();
          SetCurr(DEV_ENERGY_Q3);
        }
      }
      break;

#endif
