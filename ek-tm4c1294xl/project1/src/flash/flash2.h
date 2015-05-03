/*------------------------------------------------------------------------------
FLASH2.C


------------------------------------------------------------------------------*/

#include "at45.h"



#ifdef NATIVE_FLASH

//Биты управления SPI
#define SPI_bTT_SCK   0x0008 //PD3
#define SPI_bTT_SI    0x0002 //PD1
#define SPI_bTT_SO    0x0001 //PD0
#define SPI_bTT_CS    0x0004 //PD2

//Адреса пинов управления SPI
#define GPIO_DATAbTT_SCK (GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0020) //PD3
#define GPIO_DATAbTT_SI  (GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0008) //PD1
#define GPIO_DATAbTT_SO  (GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0004) //PD0
#define GPIO_DATAbTT_CS  (GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0010) //PD2

#endif
