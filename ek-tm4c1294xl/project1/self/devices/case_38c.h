
#ifndef SKIP_38

    case DEV_START_38C:
      cbRepeat = MaxRepeats();
      Query38_DISC();
      SetCurr(DEV_DISC_38C);
      break;

    case DEV_DISC_38C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_POSTDISC_38C);
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          Query38_DISC();
          SetCurr(DEV_DISC_38C);
        }
      }
      break;


    case DEV_POSTDISC_38C:
      cbRepeat = MaxRepeats();
      Query38_SNRM();
      SetCurr(DEV_SNRM_38C);
      break;

    case DEV_SNRM_38C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_POSTSNRM_38C);
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          Query38_SNRM();
          SetCurr(DEV_SNRM_38C);
        }
      }
      break;


    case DEV_POSTSNRM_38C:
      cbRepeat = MaxRepeats();
      Query38_Open2_Current();
      SetCurr(DEV_OPEN2_38C);
      break;

    case DEV_OPEN2_38C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateIframe_Current())
          ErrorCurrent();
        else
          MakePause(DEV_POSTOPEN2_38C);
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          Query38_Open2_Current();
          SetCurr(DEV_OPEN2_38C);
        }
      }
      break;


    case DEV_POSTOPEN2_38C:
      cbRepeat = MaxRepeats();
      Query38_RR_Current();
      SetCurr(DEV_RR1_38C);
      break;

    case DEV_RR1_38C:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateSframe_Current())
          ErrorCurrent();
        else
          MakePause(DEV_POSTRR1_38C);
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          Query38_RR_Current();
          SetCurr(DEV_RR1_38C);
        }
      }
      break;


    case DEV_POSTRR1_38C:
      cbRepeat = MaxRepeats();
      QueryEngAbs38_Current();
      SetCurr(DEV_ENGABS_38C);
      break;

    case DEV_ENGABS_38C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (!ValidateIframe_Current())
          ErrorCurrent();
        else {
          SaveCurrent38();
          MakePause(DEV_POSTENGABS_38C);
        }
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          QueryEngAbs38_Current();
          SetCurr(DEV_ENGABS_38C);
        }
      }
      break;


    case DEV_POSTENGABS_38C:
      cbRepeat = MaxRepeats();
      Query38_RR_Current();
      SetCurr(DEV_RR2_38C);
      break;

    case DEV_RR2_38C:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (!ValidateSframe_Current())
          ErrorCurrent();
        else {
          ReadCurrent38();
        }
      }
      else {
        if (cbRepeat == 0) ErrorCurrent();
        else {
          ErrorLink();
          cbRepeat--;

          Query38_RR_Current();
          SetCurr(DEV_RR2_38C);
        }
      }
      break;

#endif
