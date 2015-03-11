/*------------------------------------------------------------------------------
SPEEDS.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../serial/ports.h"
#include        "speeds.h"
#include        "speeds_storage.h"



// массив таймаутов на приём для портов RS-232 (время передачи 100 бит на данной скорости)
static uint const       mpwInDelaySlave[bSPEEDS] =
{
  (uint)(wFREQUENCY_T0*0.0833),
  (uint)(wFREQUENCY_T0*0.0417),
  (uint)(wFREQUENCY_T0*0.0208),
  (uint)(wFREQUENCY_T0*0.0104),
  (uint)(wFREQUENCY_T0*0.0052),
  (uint)(wFREQUENCY_T0*0.0035),
  (uint)(wFREQUENCY_T0*0.0035),
  (uint)(wFREQUENCY_T0*0.0035),
  (uint)(wFREQUENCY_T0*0.0035)
};

// массив таймаутов на приём для порта RS-485 (300 миллисекунд плюс время передачи 1000 бит на данной скорости)
static uint const       mpwInDelayMaster[bSPEEDS] =
{
  (uint)(wFREQUENCY_T0*1.1333),
  (uint)(wFREQUENCY_T0*0.7167),
  (uint)(wFREQUENCY_T0*0.5083),
  (uint)(wFREQUENCY_T0*0.4042),
  (uint)(wFREQUENCY_T0*0.3521),
  (uint)(wFREQUENCY_T0*0.3260),
  (uint)(wFREQUENCY_T0*0.3174),
  (uint)(wFREQUENCY_T0*0.3087),
  (uint)(wFREQUENCY_T0*0.3044)
};



void    SetSpeed0(void)
{
}



void    SetSpeed1(void)
{
}



void    SetSpeed2(void)
{
}



void    SetSpeed3(void)
{
}



bool    IsMaster(uchar  ibPrt)
{
  return((mppoPorts[ibPrt].enStream == STR_MASTERDIRECT) || (mppoPorts[ibPrt].enStream == STR_MASTERMODEM));
}


bool    IsSlave(uchar  ibPrt)
{
  return( ~IsMaster(ibPrt) );
}



void    SetCorrectLimit(uchar  ibPrt)
{
//  mpbCorrectLimit[ibPrt] = (mppoPorts[ibPrt].enStream == STR_MASTERMODEM) ? bCORRECT_MODEM : bCORRECT_DIRECT;
}


void    CheckCorrectLimit(uchar  ibPrt)
{
//  if (mpbCorrectLimit[ibPrt] < bCORRECT_MINIMUM) SetCorrectLimit(ibPrt);
//  if (mpbCorrectLimit[ibPrt] > bCORRECT_MAXIMUM) mpbCorrectLimit[ibPrt] = bCORRECT_MAXIMUM;
}


void    MakeCorrectLimit(void)
{
//  if (diT.bDevice == 24) mpbCorrectLimit[diT.ibPort] = bCORRECT_DEVICE_S;
}



void    SetDefaultDelay(uchar  ibPrt)
{
uint    w;

  mpSerial[ibPrt] = SER_BEGIN;

  if ((mppoPorts[ibPrt].enStream == STR_MASTERDIRECT) || 
      (mppoPorts[ibPrt].enStream == STR_MASTERMODEM))
    w = mpwInDelayMaster[ mppoPorts[ibPrt].ibSpeed ];
  else
    w = mpwInDelaySlave[ mppoPorts[ibPrt].ibSpeed ];

  mpwMajorInDelay[ibPrt] = w;
  mpwMinorInDelay[ibPrt] = w;
}



void    SetSpeed(uchar  ibPrt)
{
  mpSerial[ibPrt] = SER_BEGIN;

  switch (ibPrt)
  {
    case 0:  SetSpeed0();  break;
    case 1:  SetSpeed1();  break;
    case 2:  SetSpeed2();  break;
    case 3:  SetSpeed3();  break;
  }
}



void    InitSpeeds(void)
{
uchar   p;

  LoadPorts();
  LoadMajorInDelay();
  LoadMinorInDelay();

  for (p=0; p<bPORTS; p++)
  {
    if (mppoPorts[p].ibSpeed >= bSPEEDS)
    {
      mppoPorts[p].ibSpeed = 0;
      SetDefaultDelay(p);
    }

    if (mppoPorts[p].enStream >= bSTREAMS)
      mppoPorts[p].enStream = STR_SLAVEESC;

    SetSpeed(p);
    CheckCorrectLimit(p);
  }
}



void    ResetSpeeds(void)
{  
uchar   p;

  mppoPorts[0].enStream = STR_SLAVEESC;
  mppoPorts[1].enStream = STR_SLAVEESC;
  mppoPorts[2].enStream = STR_MASTERDIRECT;
  mppoPorts[3].enStream = STR_MASTERDIRECT;

  for (p=0; p<bPORTS; p++)
  {
    mppoPorts[p].ibSpeed  = 3;
    mppoPorts[p].ibParity = 0;

    SetDefaultDelay(p);
    SetCorrectLimit(p);
  }

  SavePorts();
  SaveMajorInDelay();
  SaveMinorInDelay();
}
