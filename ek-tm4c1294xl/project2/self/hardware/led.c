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
#include "delay.h"
#include "led.h"



void InitLEDs(void)
{
  GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_4 | GPIO_PIN_6);

  GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_4 | GPIO_PIN_4, 0);
  GPIOPadConfigSet(GPIO_PORTK_BASE, GPIO_PIN_4 | GPIO_PIN_6, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

  OnLED0();
  OnLED1();
  DelayMilliSecond(200);
  OffLED0();
  OnLED1();
  DelayMilliSecond(200);
  OnLED0();
  OffLED1();
  DelayMilliSecond(200);
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
      EPHY_LEDCFG_LED0_LINK | EPHY_LEDCFG_LED1_RXTX);
}



// http://e2e.ti.com/support/microcontrollers/tiva_arm/f/908/t/378413
// http://e2e.ti.com/support/microcontrollers/tiva_arm/f/908/p/377773/1333509
