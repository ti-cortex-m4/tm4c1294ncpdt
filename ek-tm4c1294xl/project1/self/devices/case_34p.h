#ifndef SKIP_34

    case DEV_START_34P:
      MakePause(DEV_PREVOPEN_34P);
      break;

    case DEV_PREVOPEN_34P:
      InitProfileOpen34();

      cbRepeat = MaxRepeats();
      QueryProfileOpen34();
      MakePause(DEV_OPEN_34P);
      break;

    case DEV_OPEN_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_PREVREAD_34P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryProfileOpen34();
          SetCurr(DEV_OPEN_34P);
        }
      }
      break;

    case DEV_PREVREAD_34P:
      InitProfileRead34();

      cbRepeat = MaxRepeats();
      QueryProfileRead34();
      MakePause(DEV_READ_34P);
      break;

    case DEV_READ_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        if (ReadProfileRead34()) {
          cbRepeat = MaxRepeats();
          QueryProfileRead34();
          MakePause(DEV_READ_34P);
        } else {
          MakePause(DEV_PREVCLOSE_34P);
        }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryProfileRead34();
          SetCurr(DEV_READ_34P);
        }
      }
      break;

    case DEV_PREVCLOSE_34P:
      cbRepeat = MaxRepeats();
      QueryProfileClose34();
      MakePause(DEV_CLOSE_34P);
      break;

    case DEV_CLOSE_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        if (ReadProfileClose34()) {
          cbRepeat = MaxRepeats();
          QueryProfileRead34();
          MakePause(DEV_READ_34P);
        } else {
          DoneProfile();
        }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryProfileClose34();
          SetCurr(DEV_CLOSE_34P);
        }
      }
      break;

#endif
