/*------------------------------------------------------------------------------
FLASH2.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include 				"inc/hw_gpio.h"
#include 				"inc/hw_memmap.h"
#include 				"inc/hw_sysctl.h"
#include "../time/delay.h"
#include        "at45.h"
#include        "flash1.h"



#ifdef NATIVE_FLASH


#define HWREG(x) (*((volatile uint32_t *)(x)))



void Init_SPIhandAT45DB321(void)
{
	 //Включение периферии
	 HWREG(SYSCTL_RCGCGPIO) |= 0x4080;//Запуск генераторов портов "H" и "Q"

	 RunClocking();

	 //Для порта "Q" (SPI)
	 HWREG(GPIO_PORTQ_BASE + GPIO_O_DIR)   |= 0x0005;//пины на передачу (PQ3 на прием)
	 HWREG(GPIO_PORTQ_BASE + GPIO_O_DEN)   |= 0x000D;//цифровой сигнал

	 //Для порта "H" (CE)
	 HWREG(GPIO_PORTH_AHB_BASE + GPIO_O_DIR) |= 0x0001;//пин на передачу
	 HWREG(GPIO_PORTH_AHB_BASE + GPIO_O_DEN) |= 0x0001;//цифровой сигнал
}

#endif
