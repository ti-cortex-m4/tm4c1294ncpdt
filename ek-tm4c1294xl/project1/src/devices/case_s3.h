
#ifndef SKIP_S

    case DEV_START_S3:
      ShowPercent(25);

      cbRepeat = bMINORREPEATS;
      QueryConfigS();
      SetCurr(DEV_CONFIG_S3);
      break;

    case DEV_CONFIG_S3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadConfigS();
        MakePause(DEV_POSTCONFIG_S3);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryConfigS();
          SetCurr(DEV_CONFIG_S3);
        }
      } 
      break;

    case DEV_POSTCONFIG_S3:
      ShowPercent(50);

      cbRepeat = bMINORREPEATS;
      QueryEngMonS(0);
      SetCurr(DEV_ENERGY_S3);
      break;

    case DEV_ENERGY_S3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentS();
      else 
      {
        if (cbRepeat == 0) ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryEngMonS(0);
          SetCurr(DEV_ENERGY_S3);
        }
      } 
      break;

#endif
