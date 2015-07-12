/*------------------------------------------------------------------------------
FLASH1.C


------------------------------------------------------------------------------*/

#include "at45.h"



#ifndef NATIVE_FLASH

//Биты управления SPI
#define SPI_bTT2_SCK   0x0020 //PB5
#define SPI_bTT2_SI    0x0010 //PE4
#define SPI_bTT2_SO    0x0020 //PE5
#define SPI_bTT2_CS    0x0010 //PB4

//Адреса пинов управления SPI
#define GPIO_DATAbTT2_SCK (GPIO_PORTB_AHB_BASE + GPIO_O_DATA + 0x0080)//PB5
#define GPIO_DATAbTT2_SI  (GPIO_PORTE_AHB_BASE + GPIO_O_DATA + 0x0040)//PE4
#define GPIO_DATAbTT2_SO  (GPIO_PORTE_AHB_BASE + GPIO_O_DATA + 0x0080)//PE5
#define GPIO_DATAbTT2_CS  (GPIO_PORTB_AHB_BASE + GPIO_O_DATA + 0x0040)//PB4

#endif
