/*------------------------------------------------------------------------------
RTC1!H


------------------------------------------------------------------------------*/

#include "rtc.h"

#ifndef NATIVE_RTC

//Биты управления SPI
#define SPI_BIT_SCK   0x0008 //PP3
#define SPI_BIT_SI    0x0010 //PP4
#define SPI_BIT_SO    0x0020 //PP5
#define SPI_BIT_CS    0x0004 //PP2 //выборка часов при PP2=1 !!!

//Адреса пинов управления SPI
#define GPIO_DATABIT_SCK (GPIO_PORTP_BASE + GPIO_O_DATA + 0x0020)//PP3
#define GPIO_DATABIT_SI  (GPIO_PORTP_BASE + GPIO_O_DATA + 0x0040)//PP4
#define GPIO_DATABIT_SO  (GPIO_PORTP_BASE + GPIO_O_DATA + 0x0080)//PP5
#define GPIO_DATABIT_CS  (GPIO_PORTP_BASE + GPIO_O_DATA + 0x0010)//PP2

#endif
