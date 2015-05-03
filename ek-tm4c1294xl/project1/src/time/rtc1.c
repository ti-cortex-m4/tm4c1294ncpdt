/*------------------------------------------------------------------------------
RTC.C
              
 DS3234EN
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../time/timedate.h"
#include "../display/lines.h"
#include 		"inc/hw_sysctl.h"
#include 		"inc/hw_gpio.h"
#include 		"inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "../time/delay.h"
#include "rtc.h"
#include "rtc1.h"



#ifndef NATIVE_RTC

void    InitGPIO_RTC(void) {
  //��������� ���������
  HWREG(SYSCTL_RCGCGPIO) |= 0x2000;//������ ���������� ����� "P"

  RunClocking();

  //��� ����� "P" (SPI+CE)
  HWREG(GPIO_PORTP_BASE + GPIO_O_DIR)   |= 0x001C;//���� �� �������� (PP5 �� �����)
  HWREG(GPIO_PORTP_BASE + GPIO_O_DEN)   |= 0x003C;//�������� ������
}

#endif
