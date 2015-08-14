/*------------------------------------------------------------------------------
AUTOMATIC_U.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_factors.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"
#include "../time/delay.h"
#include "../time/timedate.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../devices/devices.h"
//#include "../digitals/digitals_messages.h"
#include "automatic1.h"
#include "device_u.h"
#include "automatic_u.h"



#ifndef SKIP_U

bool    ReadTimeDateK(void);



bool    ReadTimeDateU(void)
{
  return ReadTimeDateK();
}


bool    ReadSensorU(void)
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


  for (i=0; i<2; i++) 
  {
    mpreChannelsB[i] = mpreChannelsB[i] * mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;     
  }

  reBuffA = mpreChannelsB[diCurr.ibLine];

  return(1);
}



bool    ReadCntMonCanU(uchar  ibMonth)
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
          sprintf(szLo, "����� %02bu.%02bu.%02bu ?",tiAlt.bDay,tiAlt.bMonth,tiAlt.bYear); 
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
          sprintf(szLo, " ����� %02bu.%02bu ?  ",tiAlt.bMonth,tiAlt.bYear); 
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


  reBuffB = mpdbTransCnt[ibDig];

  for (i=0; i<2; i++) 
  {
    reBuffA = mpreChannelsB[i] * reBuffB;
    mpreChannelsB[i] = reBuffA;
    mpboChannelsA[i] = true;     
  }

  reBuffA = mpreChannelsB[diCurr.ibLine];

  return(1);
}

#endif

