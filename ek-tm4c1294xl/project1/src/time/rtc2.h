/*------------------------------------------------------------------------------
RTC1.H


------------------------------------------------------------------------------*/

#include "rtc.h"

#ifdef NATIVE_RTC

//Биты управления SPI
#define SPI_BIT_SCK   0x0008 //F3
#define SPI_BIT_SI    0x0002 //F1
#define SPI_BIT_SO    0x0001 //F0
#define SPI_BIT_CS    0x0004 //F2

//Адреса пинов управления SPI
#define GPIO_DATABIT_SCK (GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0020)//F3
#define GPIO_DATABIT_SI  (GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0008)//F1
#define GPIO_DATABIT_SO  (GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0004)//F0
#define GPIO_DATABIT_CS  (GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x0010)//F2

#endif
