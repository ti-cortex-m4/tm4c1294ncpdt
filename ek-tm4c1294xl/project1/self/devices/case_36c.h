
#ifndef SKIP_36

    case DEV_RUN_WAIT_36:
      MonitorString("\t run: wait");

      Query36Internal(3000, 0, NNCL2_DATA_GET);
      SetCurr(DEV_RUN_DATA_GET_36);
      break;

    case DEV_RUN_BREAK_36:
      MonitorString("\t run: break");

      if (exExtended == EXT_CURRENT_3MIN)
        ErrorCurrent();
      else
        ErrorProfile();
      break;

    case DEV_RUN_DATA_GET_36:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MonitorString("\t run: good data");

        SetSerial35(SER_GOODCHECK);
        MakePause(GetCurr35Internal());
      }
      else
      {
        MonitorString("\t run: bad data");

        SetSerial35(SER_BADCHECK);
        MakePause(GetCurr35Internal());
      }
      break;



    case DEV_START_36C:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryOpen36();
      SetCurr35(DEV_OPENCANAL_36C);
      break;

    case DEV_OPENCANAL_36C:
      if (IsSerial35())
        MakePause(DEV_POSTOPENCANAL_36C);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpen36();
          SetCurr35(DEV_OPENCANAL_36C);
        }
      }
      break;

    case DEV_POSTOPENCANAL_36C:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      QueryOption36();
      SetCurr35(DEV_OPTION_36C);
      break;

    case DEV_OPTION_36C:
      if (IsSerial35())
        MakePause(DEV_POSTOPTION_36C);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOption36();
          SetCurr35(DEV_OPTION_36C);
        }
      }
      break;

    case DEV_POSTOPTION_36C:
      Clear(); ShowPercent(52);

      ibLineU = 0;
      if (SkipLine(ibDig, ibLineU) == true)
      {
        ReadEng36_SkipLine(ibLineU);
        ibLineU++;
      }

      cbRepeat = MaxRepeats();
      QueryEngCurrent36(ibLineU);
      SetCurr35(DEV_ENERGY_36C);
      break;

    case DEV_ENERGY_36C:
      if (IsSerial35())
      {
        ReadEng36(ibLineU);

        if (SkipLine(ibDig, ibLineU+1) == true)
        {
          ReadEng36_SkipLine(ibLineU+1);
          ibLineU++;
        }

        uchar bMaxLine = GetMaxLine36(ibDig);
        if (++ibLineU < bMaxLine)
        {
          Clear(); ShowPercent(52+ibLineU);
          QueryEngCurrent36(ibLineU);
          SetCurr35(DEV_ENERGY_36C);
        }
        else
          ReadCurrent36(bMaxLine);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngCurrent36(ibLineU);
          SetCurr35(DEV_ENERGY_36C);
        }
      }
      break;

#endif
