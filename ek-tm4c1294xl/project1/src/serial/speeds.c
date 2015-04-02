/*------------------------------------------------------------------------------
SPEEDS.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "driverlib/rom.h"
#include        "driverlib/uart.h"
#include        "inc/hw_memmap.h"
#include        "../hardware/system_clock.h"
#include        "../memory/mem_ports.h"
#include        "../serial/ports.h"
#include        "../digitals/correct_limit.h"
#include        "speeds.h"
#include        "speeds_storage.h"



// массив скоростей обмена
ulong const             mpdwBauds[bBAUDS] =
{ 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400 };

// массив таймаутов на приём для портов RS-232 (время передачи 100 бит на данной скорости)
static uint const       mpwInDelaySlave[bBAUDS] =
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
static uint const       mpwInDelayMaster[bBAUDS] =
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



bool    IsMaster(uchar  ibPrt)
{
  return((mppoPorts[ibPrt].enStream == STR_MASTERDIRECT) || (mppoPorts[ibPrt].enStream == STR_MASTERMODEM));
}


bool    IsSlave(uchar  ibPrt)
{
  return( ~IsMaster(ibPrt) );
}



void    SetDefaultDelay(uchar  ibPrt)
{
uint    w;

  mpSerial[ibPrt] = SER_BEGIN;

  if ((mppoPorts[ibPrt].enStream == STR_MASTERDIRECT) || 
      (mppoPorts[ibPrt].enStream == STR_MASTERMODEM))
    w = mpwInDelayMaster[ mppoPorts[ibPrt].ibBaud ];
  else
    w = mpwInDelaySlave[ mppoPorts[ibPrt].ibBaud ];

  mpwMajorInDelay[ibPrt] = w;
  mpwMinorInDelay[ibPrt] = w;

  SaveMajorInDelay();
  SaveMinorInDelay();
}



void     MakeSpeed(uchar  ibPrt, ulong  dwBase)
{
  ulong dwBaud = mpdwBauds[ mppoPorts[ibPrt].ibBaud ];

  ulong dwParity;
  switch (mppoPorts[ibPrt].ibParity)
  {
    case 0:  dwParity = UART_CONFIG_PAR_NONE;  break;
    case 1:  dwParity = UART_CONFIG_PAR_EVEN;  break;
    case 2:  dwParity = UART_CONFIG_PAR_ODD;   break;
    case 3:  dwParity = UART_CONFIG_PAR_ONE;   break;
    case 4:  dwParity = UART_CONFIG_PAR_ZERO;  break;

    default: ASSERT(false); dwParity = UART_CONFIG_PAR_NONE;  break;
  }

  ROM_UARTConfigSetExpClk(dwBase, ui32SysClock, dwBaud, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | dwParity));
}


void    SetSpeed0(void)
{
  MakeSpeed(0, UART0_BASE);
}


void    SetSpeed1(void)
{
  MakeSpeed(1, UART2_BASE);
}


void    SetSpeed2(void)
{
  MakeSpeed(2, UART3_BASE);
}


void    SetSpeed3(void)
{
  MakeSpeed(3, UART4_BASE);
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
    default: ASSERT(false);
  }

  SavePorts();
}



void    InitSpeeds(void)
{
uchar   p;

  LoadPorts();
  LoadLocalDisable();
  LoadMajorInDelay();
  LoadMinorInDelay();

  for (p=0; p<bPORTS; p++)
  {
    if (mppoPorts[p].ibBaud >= bBAUDS)
    {
      mppoPorts[p].ibBaud = 0;
      SetDefaultDelay(p);
    }

    if (mppoPorts[p].ibParity >= bPARITYS)
      mppoPorts[p].ibParity = 0;

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
    mppoPorts[p].ibBaud  = 3;
    mppoPorts[p].ibParity = 0;

    SetDefaultDelay(p);
    mpboLocalDisable[p] = FALSE;
    SetCorrectLimit(p);
  }

  SavePorts();
  SaveLocalDisable();
  SaveMajorInDelay();
  SaveMinorInDelay();
}
