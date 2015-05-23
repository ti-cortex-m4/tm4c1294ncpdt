/*------------------------------------------------------------------------------
FLASH1.C


------------------------------------------------------------------------------*/

#include "at45.h"



#ifndef NATIVE_FLASH

//Биты управления SPI
#define SPI_bTT_SCK   0x0001 //PQ0
#define SPI_bTT_SI    0x0004 //PQ2
#define SPI_bTT_SO    0x0008 //PQ3
#define SPI_bTT_CS    0x0001 //PH0

//Адреса пинов управления SPI
#define GPIO_DATAbTT_SCK (GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0004)//PQ0
#define GPIO_DATAbTT_SI  (GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0010)//PQ2
#define GPIO_DATAbTT_SO  (GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0020)//PQ3
#define GPIO_DATAbTT_CS  (GPIO_PORTH_AHB_BASE + GPIO_O_DATA + 0x0004)//PH0

#endif
