/*------------------------------------------------------------------------------
profile39_caller.c


------------------------------------------------------------------------------*/

#include "../../main.h"
// #include "../../memory/mem_digitals.h"
// #include "../../memory/mem_Profile.h"
// #include "../../memory/mem_factors.h"
// #include "../../serial/ports.h"
// #include "../../devices/devices.h"
// #include "../../digitals/digitals.h"
#include "io39.h"
#include "device39.h"
#include "profile39_caller.h"



static uchar            bNS;
static uchar            bNR;
static uchar            bInvokeId;



void    InitRunner39_Profile(void)
{

}



void    Query39_DISC_Profile(void)
{
  bNS = 0;
  bNR = 0;
  bInvokeId = 0;

  Query39_DISC();
}


void    Query39_AARQ_Profile(void)
{
  Query39_AARQ(bNS, bNR);
}


void    Query39_RR_Profile(void)
{
  bNR++;
  Query39_RR(bNR);
}


void    QueryEngAbs39_Profile(void)
{
  bNS++;
  bInvokeId++;
  QueryEngAbs39(bNS, bNR, bInvokeId);
}



bool    ValidateSframe_Profile(void)
{
  return ValidateSframe(bNR);
}


bool    ValidateIframe_Profile(void)
{
  return ValidateIframe(bNS, bNR);
};



void    SaveProfile39(void)
{
  dwProfile = ReadEngAbs39() % 0x100000000;
}


void    ReadProfile39(void)
{
  mpdwBaseDig[0] = dwProfile * mpdbPulseMnt[ibDig];

  MakeProfile();
}
