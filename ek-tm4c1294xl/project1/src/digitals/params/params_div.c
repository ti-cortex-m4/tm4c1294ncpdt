/*------------------------------------------------------------------------------
PARAMS_DIV,C


------------------------------------------------------------------------------*/

#include    "../../main.h"
#include    "../../flash/files.h"
#include    "params.h"
#include    "params_div.h"



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
      case PAR_I  : mpboEnblParams[iwPrm] = false; break;

      case PAR_I1 : 
      case PAR_I2 : 
      case PAR_I3 : fl = 1000; break;

      case PAR_U  : mpboEnblParams[iwPrm] = false; break;

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
      case PAR_F3 : mpboEnblParams[iwPrm] = false; break;

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

      case PAR_F  : mpboEnblParams[iwPrm] = false; break;

      default: fl = 1; break;
    }
  }
  else if (GetParamDevice(iwPrm) == 18)
  {
    if (GetParamLine(iwPrm) != PAR_P) 
      mpboEnblParams[iwPrm] = false;
    else
    {
      fl = 1;
      mpboEnblParams[iwPrm] = true;
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
      case PAR_F3 : mpboEnblParams[iwPrm] = false; break;

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
      case PAR_F3 : mpboEnblParams[iwPrm] = false; break;

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
      case PAR_F3 : mpboEnblParams[iwPrm] = false; break;

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
