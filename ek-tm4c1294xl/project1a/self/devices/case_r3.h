
#ifndef SKIP_R

    case DEV_START_R3:
      ibMinor = 0;
      bOuterR = 0;
      bInnerR = 0;

      QueryDataR();
      SetCurr(DEV_DATA_R3);
      break;

    case DEV_DATA_R3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadDataR() == 1)
        {
          MakePause(DEV_POSTDATA_R3);
        }
        else
        {
          mpcwErrorsR1[ibDig]++;
          if (++bOuterR > bOuterMaxR) ErrorCurrent(); 
          else MakePause(DEV_ERROR_R3);
        }
      }
      else
      {
        mpcwErrorsR2[ibDig]++;
        if (++bOuterR > bOuterMaxR) ErrorCurrent(); 
        else MakePause(DEV_ERROR_R3);
      } 
      break;

    case DEV_ERROR_R3:
      BadDataR();

      QueryDataR();
      SetCurr(DEV_DATA_R3);
      break;

    case DEV_POSTDATA_R3:
      if (++ibMinor >= 8)
      {
        if (ReadCurrentR() == 0)
        {
          mpcwErrorsR3[ibDig]++;
          if (++bOuterR > bOuterMaxR) ErrorCurrent(); 
          else
          {
            QueryDataR();
            SetCurr(DEV_DATA_R3);
          }
        }
      }
      else 
      {
        QueryDataR();
        SetCurr(DEV_DATA_R3);
      }
      break;

#endif
