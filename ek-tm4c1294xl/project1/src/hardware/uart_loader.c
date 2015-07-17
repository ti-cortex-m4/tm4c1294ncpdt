/*------------------------------------------------------------------------------
UART_LOADER.C


------------------------------------------------------------------------------*/

#include "../main.h"
//#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "inc/hw_flash.h"
//#include "driverlib/systick.h"
#include "uart_loader.h"



// bNumPort - номер порта (0-A, 1-B, 2-C, 3-D, 4-E, 5-F, 6-G, 7-H)
// bNumPin - номер пина (0-Pin0, 1-Pin1, 2-Pin2, 3-Pin3, 4-Pin4, 5-Pin5, 6-Pin6, 7-Pin7)
// bPolarity - пол€рность сигнала на пине порта (0-”ровень0, 1-”ровень1)
// bEnableNegative - активаци€ запуска загрузчика при старте (0-загрузчик активен)
void    BOOTCFG_Write(uchar bNumPort, uchar bNumPin, uchar bPolarity, uchar bEnableNegative)
{
  // проверка правильности значений
  if((bNumPort > 7) || (bNumPin > 7) || (bPolarity > 1) || (bEnableNegative > 1) ) return;

  // данные
  HWREG(FLASH_FMD) = 0xFFFF00FE + (bNumPort << 13) + (bNumPin << 10) + (bPolarity << 9 ) + (bEnableNegative << 8 );

  // адрес BOOTCFG дл€ записи
  HWREG(FLASH_FMA) = 0x75100000;

  // делаем запись с ключом 0xA442
  HWREG(FLASH_FMC) = FLASH_FMC_WRKEY + FLASH_FMC_WRITE + FLASH_FMC_COMT;

  // ожидаем окончани€ записи (бит 0 должен очиститьс€)
  while(HWREG(FLASH_FMC) & (FLASH_FMC_WRITE + FLASH_FMC_COMT));
}


void    InitUartLoader(void)
{
  if(HWREG(FLASH_BOOTCFG) == 0xFFFFFFFE)
  {
    BOOTCFG_Write(2, 4, 0, 0);
  }
}
