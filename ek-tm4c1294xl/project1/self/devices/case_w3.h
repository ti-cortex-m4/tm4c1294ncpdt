
#ifndef SKIP_W

    case DEV_START_W3:
      ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryOpenW();
      SetCurr(DEV_OPENCANAL_W3);
      break;

    case DEV_OPENCANAL_W3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_W3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenW();
          SetCurr(DEV_OPENCANAL_W3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_W3:
      Clear(); ShowPercent(51);

      cbRepeat = GetMaxRepeats();
      QueryOptionW();
      SetCurr(DEV_OPTION_W3);
      break;

    case DEV_OPTION_W3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_W3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionW();
          SetCurr(DEV_OPTION_W3);
        }
      }
      break;

    case DEV_POSTOPTION_W3:
      ShowPercent(52);

      cbRepeat = GetMaxRepeats();
      QueryEngAbsW();
      SetCurr(DEV_ENERGY_W3);
      break;

    case DEV_ENERGY_W3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEngW();
        ReadCurrentW();
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbsW();
          SetCurr(DEV_ENERGY_W3);
        }
      }
      break;

#endif
