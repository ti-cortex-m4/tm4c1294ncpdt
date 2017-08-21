#ifndef SKIP_31

    case DEV_START_31C:
      cbRepeat = MaxRepeats();
      QueryOpen31();
      SetCurr(DEV_OPENCANAL_31C);
      break;

    case DEV_OPENCANAL_31C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadOpen31() == false)
          ErrorCurrent();
        else
          MakePause(DEV_POSTOPENCANAL_31C);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpen31();
          SetCurr(DEV_OPENCANAL_31C);
        }
      }
      break;

    case DEV_POSTOPENCANAL_31C:
      cbRepeat = MaxRepeats();
      QueryEngAbs31();
      SetCurr(DEV_ENERGY_31C);
      break;

    case DEV_ENERGY_31C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrent31();
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbs31();
          SetCurr(DEV_ENERGY_31C);
        }
      }
      break;

#endif
