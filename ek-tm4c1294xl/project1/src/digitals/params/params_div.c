/*------------------------------------------------------------------------------
PARAMS_DIV.C


------------------------------------------------------------------------------*/

#include    "../../main.h"
#include    "../../memory/mem_digitals.h"
#include    "../../memory/mem_realtime.h"
#include    "../../serial/ports.h"
#include    "../../serial/ports_devices.h"
#include    "../../digitals/digitals.h"
#include    "../../digitals/digitals_display.h"
#include    "../../digitals/digitals_messages.h"
#include    "../../devices/devices.h"
#include    "../../sensors/device_a.h"
#include    "../../sensors/device_b.h"
#include    "../../sensors/device_c.h"
#include    "../../time/delay.h"
#include    "../../console.h"
#include    "../../engine.h"
#include    "../../flash/files.h"
#include    "params.h"
#include    "params2.h"



void    MakeParamDiv(uint  iwPrm)
{
  float fl = 1;

  if (GetParamDevice(iwPrm) == 1)
  {
    switch (GetParamLine(iwPrm))
    {
      case PAR_P  :
      case PAR_P1 :
      case PAR_P2 :
      case PAR_P3 :

      case PAR_Q  :
      case PAR_Q1 :
      case PAR_Q2 :
      case PAR_Q3 :

      case PAR_S  :
      case PAR_S1 :
      case PAR_S2 :
      case PAR_S3 : fl = 1000; break;

      case PAR_I  : 
      case PAR_I1 : 
      case PAR_I2 : 
      case PAR_I3 : fl = 10; break;

      default: fl = 100; break;
    }
  }
  else if ((GetParamDevice(iwPrm) == 2) ||
           (GetParamDevice(iwPrm) == 8) ||
           (GetParamDevice(iwPrm) == 12))
  {
    switch (GetParamLine(iwPrm))
    {
      case PAR_I  : mpboEnblParams[iwPrm] = FALSE; break;

      case PAR_I1 : 
      case PAR_I2 : 
      case PAR_I3 : fl = 1000; break;

      case PAR_U  : mpboEnblParams[iwPrm] = FALSE; break;

      case PAR_C  :
      case PAR_C1 :
      case PAR_C2 :
      case PAR_C3 : fl = 1000; break;

      default: fl = 100; break;
    }
  }
  else if (GetParamDevice(iwPrm) == 3)
  {
    switch (GetParamLine(iwPrm))
    {
      case PAR_S  :
      case PAR_S1 :
      case PAR_S2 :
      case PAR_S3 : 

      case PAR_U  : 
      case PAR_I  : 
      case PAR_C  : 

      case PAR_F1 :
      case PAR_F2 :
      case PAR_F3 : mpboEnblParams[iwPrm] = FALSE; break;

      default: fl = 1; break;
    }
  }
  else if (GetParamDevice(iwPrm) == 9)
  {
    switch (GetParamLine(iwPrm))
    {
      case PAR_P  :
      case PAR_Q  :
      case PAR_S  :

      case PAR_U  : 
      case PAR_I  : 

      case PAR_C  : 

      case PAR_F  : mpboEnblParams[iwPrm] = FALSE; break;

      default: fl = 1; break;
    }
  }
  else if (GetParamDevice(iwPrm) == 18)
  {
    if (GetParamLine(iwPrm) != PAR_P) 
      mpboEnblParams[iwPrm] = FALSE;
    else
    {
      fl = 1;
      mpboEnblParams[iwPrm] = TRUE;
    }
  }
  else if (GetParamDevice(iwPrm) == 21)
  {
    switch (GetParamLine(iwPrm))
    {
      case PAR_U  : 

      case PAR_I  : 

      case PAR_C  : 
      case PAR_C1 : 
      case PAR_C2 : 
      case PAR_C3 : 

      case PAR_F1 : 
      case PAR_F2 : 
      case PAR_F3 : mpboEnblParams[iwPrm] = FALSE; break;

      default: fl = 1; break;
    }
  }
  else if (GetParamDevice(iwPrm) == 25)
  {
    switch (GetParamLine(iwPrm))
    {
      case PAR_S  : 
      case PAR_S1 : 
      case PAR_S2 : 
      case PAR_S3 : 

      case PAR_U  : 

      case PAR_I  : 

      case PAR_C  : 
      case PAR_C1 : 
      case PAR_C2 : 
      case PAR_C3 : 

      case PAR_F1 : 
      case PAR_F2 : 
      case PAR_F3 : mpboEnblParams[iwPrm] = FALSE; break;

      default: fl = 1; break;
    }
  }
  else if (GetParamDevice(iwPrm) == 26)
  {
    switch (GetParamLine(iwPrm))
    {
      case PAR_P  : 

      case PAR_Q  : 
      case PAR_Q1 : 
      case PAR_Q2 : 
      case PAR_Q3 : 

      case PAR_S  : 
      case PAR_S1 : 
      case PAR_S2 : 
      case PAR_S3 : 

      case PAR_U  : 

      case PAR_I  : 

      case PAR_C  : 
      case PAR_C1 : 
      case PAR_C2 : 
      case PAR_C3 : 

      case PAR_F1 : 
      case PAR_F2 : 
      case PAR_F3 : mpboEnblParams[iwPrm] = FALSE; break;

      default: fl = 1; break;
    }
  }

  mpreParamsDiv[iwPrm] = fl;
}


void    MakeParamsDiv(void)
{
  uint p;
  for (p=0; p<wPARAMS; p++)
  {
    MakeParamDiv(p);
  }

  SaveFile(&flParamsDiv);
}
