#ifndef SKIP_34

    case DEV_START_34P:
      MakePause(DEV_PREVOPEN_PROFILE_34P);
      break;

    case DEV_PREVOPEN_PROFILE_34P:
      cbRepeat = MaxRepeats();
      InitProfileOpen34();
      QueryProfileOpen34();
      MakePause(DEV_OPEN_PROFILE_34P);
      break;

    case DEV_OPEN_PROFILE_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadProfileOpen34();
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryProfileOpen34();
          SetCurr(DEV_OPEN_PROFILE_34P);
        }
      }
      break;

#endif
