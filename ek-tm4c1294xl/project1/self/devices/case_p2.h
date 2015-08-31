
#ifndef SKIP_P

    case DEV_START_P2:
      ShowPercent(50);

      cbRepeat = bMINORREPEATS;
      QueryOpenP();
      SetCurr(DEV_OPENCANAL_P2);
    break;

    case DEV_OPENCANAL_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTOPENCANAL_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenP();
          SetCurr(DEV_OPENCANAL_P2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_P2:
      ShowPercent(60);

      cbRepeat = bMINORREPEATS;
      QueryModeP();
      SetCurr(DEV_MODE_P2);
    break;

    case DEV_MODE_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTMODE_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryModeP();
          SetCurr(DEV_MODE_P2);
        }
      }
      break;

    case DEV_POSTMODE_P2:
      ShowPercent(70);

      cbRepeat = bMINORREPEATS;
      QueryPasswordP();
      SetCurr(DEV_PASSWORD_P2);
    break;

    case DEV_PASSWORD_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTPASSWORD_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordP();
          SetCurr(DEV_PASSWORD_P2);
        }
      }
      break;

    case DEV_POSTPASSWORD_P2:
      ShowPercent(80);

      cbRepeat = bMINORREPEATS;
      QueryTimeP();
      SetCurr(DEV_TIME_P2);
      break;

    case DEV_TIME_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeP();

        if (boControlTime == true)
          MakePause(DEV_POSTTIME_P2);
        else
          MakePause(DEV_POSTCORRECT_P2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeP();
          SetCurr(DEV_TIME_P2);
        }
      }
      break;

    case DEV_POSTTIME_P2:
      {
        ulong dwSecond1 = GetSecondIndex(tiDig);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (dwSecond1 == dwSecond2)
        {
          MakePause(DEV_POSTCORRECT_P2);
        }
        else if (dwSecond1 > dwSecond2)
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          ulong dw = dwSecond1 - dwSecond2;
          if (dw > 5) dw = 5;
          iwMajor = dw % 0x10000;

          Clear(); sprintf(szLo+1,"коррекция: -%u с", iwMajor); DelayInf();
          iwMajor |= 0x8000;

          cbRepeat = bMINORREPEATS;
          QueryCorrectP();
          SetCurr(DEV_CORRECT_P2);
        }
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          ulong dw = dwSecond2 - dwSecond1;
          if (dw > 5) dw = 5;
          iwMajor = dw % 0x10000;

          Clear(); sprintf(szLo+1,"коррекция: +%u с", iwMajor); DelayInf();

          cbRepeat = bMINORREPEATS;
          QueryCorrectP();
          SetCurr(DEV_CORRECT_P2);
        }
      }
      break;

    case DEV_CORRECT_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        Clear();
        MakePause(DEV_POSTCORRECT_P2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryCorrectP();
          SetCurr(DEV_CORRECT_P2);
        }
      }
      break;

    case DEV_POSTCORRECT_P2:
      ShowPercent(90);

      cbRepeat = bMINORREPEATS;
      QueryRegisterP();
      SetCurr(DEV_REGISTER_P2);
      break;

    case DEV_REGISTER_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadRegisterP();
        if (ibMinorMax == 0)
          ErrorProfile();
        else
          MakePause(DEV_POSTREGISTER_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryRegisterP();
          SetCurr(DEV_REGISTER_P2);
        }
      }
      break;

    case DEV_POSTREGISTER_P2:
      Setup1P();

      cbRepeat = bMINORREPEATS;
      QuerySetValueP(); // возвращает (ERR5), если прошло более 6 минут после команды Р2
      SetCurr(DEV_SETVALUE_P2);
      break;

    case DEV_SETVALUE_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTSETVALUE_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QuerySetValueP();
          SetCurr(DEV_SETVALUE_P2);
        }
      }
      break;

    case DEV_POSTSETVALUE_P2:
      cbRepeat = bMINORREPEATS;
      QueryGetValueP();
      SetCurr(DEV_GETVALUE_P2);
      break;

    case DEV_GETVALUE_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadGetValueP();
        MakePause(DEV_POSTGETVALUE_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryGetValueP();
          SetCurr(DEV_GETVALUE_P2);
        }
      }
      break;

    case DEV_POSTGETVALUE_P2:
      cbRepeat = bMINORREPEATS;
      QueryProfileP();
      SetCurr(DEV_PROFILE_P2);
      break;

    case DEV_PROFILE_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTPROFILE_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryProfileP();
          SetCurr(DEV_PROFILE_P2);
        }
      }
      break;

    case DEV_POSTPROFILE_P2:
      ReadProfileP(tiDig);
      if ((++wBaseCurr > wBaseLast) || (bBreakEls == 1))
      {
        Setup2P();
        if (((MakeStopHou(0) == 0) || (iwMajor > 10)) && (iwDigHou != 0xFFFF))
        {
          DoneProfile();
        }
        else
        {
          if (BreakP())
          {
            DoneProfile();
          }
          else
          {
            NewBoundsAbs16(ibMinor++);

            if (cwSecondLockoutP > 60)
            {
              cbRepeat = bMINORREPEATS;
              QueryRepasswordP();
              SetCurr(DEV_REPASSWORD_P2);
            }
            else
            {
              cbRepeat = bMINORREPEATS;
              QuerySetValueP();
              SetCurr(DEV_SETVALUE_P2);
            }
          }
        }
      }
      else
      {
        cbRepeat = bMINORREPEATS;
        QueryProfileP();
        SetCurr(DEV_PROFILE_P2);
      }
      break;

    case DEV_REPASSWORD_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
          QuerySetValueP();
          SetCurr(DEV_SETVALUE_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryRepasswordP();
          SetCurr(DEV_REPASSWORD_P2);
        }
      }
      break;

#endif
