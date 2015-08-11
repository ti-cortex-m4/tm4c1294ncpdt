/*------------------------------------------------------------------------------
RTC1.H


------------------------------------------------------------------------------*/

#include "rtc.h"

#ifdef NATIVE_RTC

//Биты управления SPI
#define SPI_BIT_SCK   0x0008 //B3
#define SPI_BIT_SI    0x0002 //B1
#define SPI_BIT_SO    0x0001 //B0
#define SPI_BIT_CS    0x0004 //B2

//Адреса пинов управления SPI
#define GPIO_DATABIT_SCK (GPIO_PORTB_AHB_BASE + GPIO_O_DATA + 0x0020)//B3
#define GPIO_DATABIT_SI  (GPIO_PORTB_AHB_BASE + GPIO_O_DATA + 0x0008)//B1
#define GPIO_DATABIT_SO  (GPIO_PORTB_AHB_BASE + GPIO_O_DATA + 0x0004)//B0
#define GPIO_DATABIT_CS  (GPIO_PORTB_AHB_BASE + GPIO_O_DATA + 0x0010)//B2

#endif
