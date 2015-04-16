
#ifndef SKIP_U

    case DEV_START_U3:                     
      Clear(); ShowPercent(50);

      cbRepeat = bMINORREPEATS;
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_U3);
      break;

    case DEV_OPENCANAL_U3:                     
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_U3);
      else                                      
      {
        if (cbRepeat == 0) ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryOpenK();
          SetCurr(DEV_OPENCANAL_U3);
        }
      }  
      break;

    case DEV_POSTOPENCANAL_U3:                     
      Clear(); ShowPercent(51);

      cbRepeat = bMINORREPEATS;
      QueryOptionU();
      SetCurr(DEV_OPTION_U3);
      break;

    case DEV_OPTION_U3:                     
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_U3);
      else                                      
      {
        if (cbRepeat == 0) ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryOptionK();
          SetCurr(DEV_OPTION_U3);
        }
      }  
      break;

    case DEV_POSTOPTION_U3:                     
      Clear(); ShowPercent(52);

      ibMinor = 0;
      if (SkipLine(ibDig, ibMinor) == 1)
      {
        ReadEnergyU_SkipLine(ibMinor);
        ibMinor++;
      }

      cbRepeat = bMINORREPEATS;
      QueryEnergySpecU(ibMinor); 
      SetCurr(DEV_ENERGY_U3);
      break; 

    case DEV_ENERGY_U3: 
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEnergyU(ibMinor);

        if (SkipLine(ibDig, ibMinor+1) == 1)
        {
          ReadEnergyU_SkipLine(ibMinor+1);
          ibMinor++;
        }

        if (++ibMinor < 2) 
        {
          Clear(); ShowPercent(53);
          QueryEnergySpecU(ibMinor); 
          SetCurr(DEV_ENERGY_U3);
        }
        else
          ReadCurrentU();
      }
      else                                      
      {
        if (cbRepeat == 0) ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryEnergySpecU(ibMinor); 
          SetCurr(DEV_ENERGY_U3);
        }
      }  
      break;

#endif
