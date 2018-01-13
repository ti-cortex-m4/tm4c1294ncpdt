/*------------------------------------------------------------------------------
customer_settings_1.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/settings.h"
#include "../uart/io_mode.h"
#include "../uart/serial_send.h"
#include "customer_settings_1.h"



static volatile bool    mbFlags[UART_COUNT];



void InitCustomerSettings1(void)
{
  uchar u;
  for (u = 0; u < UART_COUNT; u++)
  {
    mbFlags[u] = false;
  }
}


void CustomerSettings1_TelnetReceive(uchar u) {
  ASSERT(u < UART_COUNT);
  if (mbCustomerSettings[u] == 1) {
    mbFlags[u] = true;
  }
}


void CustomerSettings1_SerialSend(uchar u) {
  ASSERT(u < UART_COUNT);
  if (mbCustomerSettings[u] == 1) {
    if (mbFlags[u] == true) {
      mbFlags[u] = false;

      OutMode(u);
      SerialSend(u, 0x99);
    }
  }
}
