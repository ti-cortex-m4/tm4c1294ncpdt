/*------------------------------------------------------------------------------
led.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "inc/hw_emac.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/emac.h"
#include "../kernel/settings.h"
#include "../kernel/entities.h"
#include "../kernel/log.h"
#include "delay.h"
#include "led.h"



void InitLEDs(void)
{
  GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_4 | GPIO_PIN_6);

  GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_4 | GPIO_PIN_4, 0);
  GPIOPadConfigSet(GPIO_PORTK_BASE, GPIO_PIN_4 | GPIO_PIN_6, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

  OnLED0();
  OnLED1();
  DelayMilliSecond(300);
  OffLED0();
  OffLED1();
}



void OffLED0(void)
{
  GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_4, GPIO_PIN_4);
}

void OnLED0(void)
{
  GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_4, 0);
}


void OffLED1(void)
{
  GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_6, GPIO_PIN_6);
}

void OnLED1(void)
{
  GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_6, 0);
}



static ulong GetLED0Mask(void)
{
  return EPHY_LEDCFG_LED0_LINK;
}

static ulong GetLED1Mask(void)
{
  switch(bLED1Mode)
  {
    case LED_MODE_LINK: return EPHY_LEDCFG_LED1_LINK;
    case LED_MODE_RXTX: return EPHY_LEDCFG_LED1_RXTX;
    case LED_MODE_TX: return EPHY_LEDCFG_LED1_TX;
    case LED_MODE_RX: return EPHY_LEDCFG_LED1_RX;
    case LED_MODE_COLLISION: return EPHY_LEDCFG_LED1_COL;
    case LED_MODE_100_BASE_TX: return EPHY_LEDCFG_LED1_100BT;
    case LED_MODE_10_BASE_TX: return EPHY_LEDCFG_LED1_10BT;
    case LED_MODE_FULL_DUPLEX: return EPHY_LEDCFG_LED1_FD;
    case LED_MODE_LINK_RXTX: return EPHY_LEDCFG_LED1_LINKTXRX;

    default: WARNING("ethernet LED1 mode %u", bLED1Mode);
             return EPHY_LEDCFG_LED1_RXTX;
  }
}


void InitEthernetLEDs(void)
{
  // Set Ethernet LED polarity to be active low
  HWREG(EMAC0_BASE + EMAC_O_CC) |= EMAC_CC_POL;


  GPIOPinConfigure(GPIO_PK4_EN0LED0);
  GPIOPinConfigure(GPIO_PK6_EN0LED1);

  GPIOPinTypeEthernetLED(GPIO_PORTK_BASE, GPIO_PIN_4 | GPIO_PIN_6);


  EMACPHYExtendedWrite(EMAC0_BASE, 0, EPHY_LEDCR,
    (EMACPHYExtendedRead(EMAC0_BASE, 0, EPHY_LEDCR) & ~EPHY_LEDCR_BLINKRATE_M) |
      EPHY_LEDCR_BLINKRATE_10HZ);

  EMACPHYExtendedWrite(EMAC0_BASE, 0, EPHY_LEDCFG,
    (EMACPHYExtendedRead(EMAC0_BASE, 0, EPHY_LEDCFG) & ~(EPHY_LEDCFG_LED0_M | EPHY_LEDCFG_LED1_M | EPHY_LEDCFG_LED2_M)) |
      GetLED0Mask() | GetLED1Mask());
}



void InitLEDs_After(void)
{
  InitLEDs();

  OnLED0();
  OnLED1();
  DelayMilliSecond(300);
  OffLED0();
  OffLED1();

  InitEthernetLEDs();
}


// http://e2e.ti.com/support/microcontrollers/tiva_arm/f/908/t/378413
// http://e2e.ti.com/support/microcontrollers/tiva_arm/f/908/p/377773/1333509
