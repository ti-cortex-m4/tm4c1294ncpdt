/*------------------------------------------------------------------------------
AUTOMATIC_U.C


------------------------------------------------------------------------------*/

#include        "../main.h"
//#include        "xdata.h"
//#include        "timer0.h"
//#include        "display.h"
//#include        "engine.h"
//#include        "sensors.h"
//#include        "timedate.h"
//#include        "ports.h"
//#include        "delay.h"
//#include        "device_u.h"



#ifndef SKIP_U

bit     ReadTimeDateK(void);



bit     ReadTimeDateU(void)
{
  return ReadTimeDateK();
}


bit     ReadSensorU(void)
{
uchar   i;

  Clear();

  for (ibZmin=0; ibZmin<2; ibZmin++)
  {
    if (SkipLine(ibDig, ibZmin) == 1) { mpreChannelsB[ibZmin] = 0; continue; }

    for (i=0; i<bMINORREPEATS; i++)
    {
      ShowPercent(50 + ibZmin);
      QueryCloseU();
      QueryEnergyAbsU(ibZmin);

      if (BccInput() == SER_GOODCHECK) break;
      if (fKey == 1) return(0);
    }

    if (i == bMINORREPEATS) return(0);
    ReadEnergyU(ibZmin);
  }

  QueryCloseU();


  reBuffB = mpreTransCnt[ibDig];

  for (i=0; i<2; i++) 
  {
    reBuffA = mpreChannelsB[i] * reBuffB;
    mpreChannelsB[i] = reBuffA;
    mpboChannelsA[i] = boTrue;     
  }

  reBuffA = mpreChannelsB[diCurr.ibLine];

  return(1);
}



bit     ReadCntMonCanU(uchar  ibMonth)
{
uchar   i;

  if (ReadTimeDateK() == 0) return(0);

  if (tiAlt.bMonth == ibMonth+1)
  {
    if (tiAlt.bDay > 1)
      tiAlt.bDay--;
    else
    {
      if (tiAlt.bMonth > 1)
        tiAlt.bMonth--;
      else
      {
        tiAlt.bMonth = 12;  
        tiAlt.bYear--; 
      }

      tiAlt.bDay = DaysInMonth();             
    } 

    for (ibZmin=0; ibZmin<2; ibZmin++)
    {
      if (SkipLine(ibDig, ibZmin) == 1) { mpreChannelsB[ibZmin] = 0; continue; }

      for (i=0; i<bMINORREPEATS; i++)
      {
        ShowPercent(50 + ibZmin);
        QueryCloseU();
        QueryEnergyDayU(ibZmin);

        if (BccInput() == SER_GOODCHECK) break;
        if (IndexInBuff() == 10) 
        { 
          sprintf(szLo, "сутки %02bu.%02bu.%02bu ?",tiAlt.bDay,tiAlt.bMonth,tiAlt.bYear); 
          Delay(1000); 
          return(0); 
        }
        if (fKey == 1) return(0);
      }

      if (i == bMINORREPEATS) return(0);
      ReadEnergyU(ibZmin);
    }

    QueryCloseU();
  }
  else
  {
    tiAlt.bYear = (ibMonth+1 > tiAlt.bMonth) ? tiAlt.bYear-1 : tiAlt.bYear;
    tiAlt.bMonth = ibMonth+1;

    for (ibZmin=0; ibZmin<2; ibZmin++)
    {
      if (SkipLine(ibDig, ibZmin) == 1) { mpreChannelsB[ibZmin] = 0; continue; }

      for (i=0; i<bMINORREPEATS; i++)
      {
        ShowPercent(50 + ibZmin);
        QueryCloseU();
        QueryEnergyMonU(ibZmin);

        if (BccInput() == SER_GOODCHECK) break;
        if (IndexInBuff() == 10) 
        { 
          sprintf(szLo, " мес€ц %02bu.%02bu ?  ",tiAlt.bMonth,tiAlt.bYear); 
          Delay(1000); 
          return(0); 
        }
        if (fKey == 1) return(0);
      }

      if (i == bMINORREPEATS) return(0);
      ReadEnergyU(ibZmin);
    }

    QueryCloseU();
  }


  reBuffB = mpreTransCnt[ibDig];

  for (i=0; i<2; i++) 
  {
    reBuffA = mpreChannelsB[i] * reBuffB;
    mpreChannelsB[i] = reBuffA;
    mpboChannelsA[i] = boTrue;     
  }

  reBuffA = mpreChannelsB[diCurr.ibLine];

  return(1);
}

#endif

