/*------------------------------------------------------------------------------
RTC!C

 DS3234EN
------------------------------------------------------------------------------*/

#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "../main.h"
#include "../time/timedate.h"
#include "../display/lines.h"
#include "../time/delay.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "rtc_define.h"
#include "rtc.h"



static void OutChar(uchar  b)
{
  uchar i;
  for(i=0; i<8; i++)
  {
    if (b & (0x80 >> i)) HWREG(GPIO_RTC_SI) = MASK_RTC_SI;
    else HWREG(GPIO_RTC_SI) = ~MASK_RTC_SI;

    HWREG(GPIO_RTC_SCK) =  MASK_RTC_SCK;
    HWREG(GPIO_RTC_SCK) = ~MASK_RTC_SCK;
  }
}


static uchar InChar(void)
{
  uchar b = 0;

  uchar i;
  for(i=0; i<8; i++)
  {
    HWREG(GPIO_RTC_SCK) =  MASK_RTC_SCK;
    HWREG(GPIO_RTC_SCK) = ~MASK_RTC_SCK;

    if(HWREG(GPIO_RTC_SO)) b |= 0x80 >> i;
  }

  return b;
}



static void Enable(void)
{
  HWREG(GPIO_RTC_SCK) = ~MASK_RTC_SCK;
  HWREG(GPIO_RTC_CS) = MASK_RTC_CS;

  HWREG(GPIO_RTC_SCK) = ~MASK_RTC_SCK;
  HWREG(GPIO_RTC_CS) = ~MASK_RTC_CS;
}


static void Disable(void)
{
  HWREG(GPIO_RTC_SCK) = ~MASK_RTC_SCK;
  HWREG(GPIO_RTC_CS) = MASK_RTC_CS;
}



time    *GetCurrTimeDate(void)
{
static time ti;

  Enable();
  OutChar(0x00);

  ti.bSecond = FromBCD(InChar());
  ti.bMinute = FromBCD(InChar());
  ti.bHour   = FromBCD(InChar());
                       InChar(); // день недели
  ti.bDay    = FromBCD(InChar());
  ti.bMonth  = FromBCD(InChar());
  ti.bYear   = FromBCD(InChar());

  Disable();

  return &ti;
}


void    SetCurrTimeDate(time  ti)
{
  Enable();
  OutChar(0x80);

  OutChar( ToBCD(ti.bSecond) );
  OutChar( ToBCD(ti.bMinute) );
  OutChar( ToBCD(ti.bHour)   );
  OutChar( 0 ); // день недели
  OutChar( ToBCD(ti.bDay)    );
  OutChar( ToBCD(ti.bMonth)  );
  OutChar( ToBCD(ti.bYear)   );

  Disable();
}


void    SetCurrTime(time  ti)
{
  Enable();
  OutChar(0x80);

  OutChar( ToBCD(ti.bSecond) );
  OutChar( ToBCD(ti.bMinute) );
  OutChar( ToBCD(ti.bHour)   );

  Disable();
}


void    SetCurrDate(time  ti)
{
  Enable();
  OutChar(0x84);

  OutChar( ToBCD(ti.bDay)   );
  OutChar( ToBCD(ti.bMonth) );
  OutChar( ToBCD(ti.bYear)  );

  Disable();
}



void    SetLabelRTC(void)
{
  Enable();

  OutChar(0x98);
  OutChar(0x00);

  Disable();


  Enable();
  OutChar(0x99);

  uchar i;
  for (i=0; i<8; i++)
  {
    OutChar(i);
  }

  Disable();
}


bool    GetLabelRTC(void)
{
  Enable();

  OutChar(0x98);
  OutChar(0x00);

  Disable();


  Enable();

  OutChar(0x19);

  bool f = true;

  uchar i;
  for (i=0; i<8; i++)
  {
    if (InChar() != i)
    {
      f = false;
      break;
    }
  }

  Disable();

  return f;
}



bool    ValidTimeDateRTC(time  ti)
{
  if (ti.bSecond == FromBCD(0xFF)) return(0);
  if (ti.bMinute == FromBCD(0xFF)) return(0);
  if (ti.bHour   == FromBCD(0xFF)) return(0);
  if (ti.bDay    == FromBCD(0xFF)) return(0);
  if (ti.bMonth  == FromBCD(0xFF)) return(0);
  if (ti.bYear   == FromBCD(0xFF)) return(0);

  if (ti.bSecond > 59) return(0);
  if (ti.bMinute > 59) return(0);
  if (ti.bHour   > 23) return(0);

  if ((ti.bDay == 0) ||
      (ti.bDay > 31)) return(0);

  if ((ti.bMonth == 0) ||
      (ti.bMonth > 12 )) return(0);

  if ((ti.bYear < bMINYEAR) ||
      (ti.bYear > bMAXYEAR)) return(0);

  return(1);
}



static void InitGPIO()
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R1;

  DelayGPIO();

  HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DIR) |= 0x000E;
  HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DIR) &= 0xFFFE;

  HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DEN) |= 0x000F;
}


void    InitRTC(void)
{
  InitGPIO();

  SetLabelRTC();

  Disable();
}
