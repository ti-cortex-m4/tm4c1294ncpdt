
#ifndef SKIP_P

    case DEV_START_P3:
      ShowPercent(50);

      cbRepeat = bMINORREPEATS;
      QueryOpenP();
      SetCurr(DEV_OPENCANAL_P3);
    break;

    case DEV_OPENCANAL_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTOPENCANAL_P3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenP();
          SetCurr(DEV_OPENCANAL_P3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_P3:
      ShowPercent(60);

      cbRepeat = bMINORREPEATS;
      QueryModeP();
      SetCurr(DEV_MODE_P3);
    break;

    case DEV_MODE_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTMODE_P3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryModeP();
          SetCurr(DEV_MODE_P3);
        }
      }
      break;

    case DEV_POSTMODE_P3:
      ShowPercent(70);

      cbRepeat = bMINORREPEATS;
      QueryPasswordP();
      SetCurr(DEV_PASSWORD_P3);
    break;

    case DEV_PASSWORD_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTPASSWORD_P3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordP();
          SetCurr(DEV_PASSWORD_P3);
        }
      }
      break;

    case DEV_POSTPASSWORD_P3:
      ShowPercent(80);

      cbRepeat = bMINORREPEATS;
      QueryRegisterP();
      SetCurr(DEV_REGISTER_P3);
      break;

    case DEV_REGISTER_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadRegisterP();
        MakePause(DEV_POSTREGISTER_P3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryRegisterP();
          SetCurr(DEV_REGISTER_P3);
        }
      }
      break;

    case DEV_POSTREGISTER_P3:
      ShowPercent(90);

      cbRepeat = bMINORREPEATS;
      QueryEngAbsP(0);
      SetCurr(DEV_ENERGY0_P3);
      break;

    case DEV_ENERGY0_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEngAbsP(0);

        cbRepeat = bMINORREPEATS;
        QueryEngAbsP(1);
        SetCurr(DEV_ENERGY1_P3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbsP(0);
          SetCurr(DEV_ENERGY0_P3);
        }
      }
      break;

    case DEV_ENERGY1_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEngAbsP(1);

        ReadCurrentP();
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbsP(1);
          SetCurr(DEV_ENERGY1_P3);
        }
      }
      break;

#endif
