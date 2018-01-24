/*------------------------------------------------------------------------------
customer_settings_1.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/settings.h"
#include "../hardware/delay.h"
#include "../uart/io_mode.h"
#include "../uart/serial.h"
#include "../uart/serial_send.h"
#include "customer_settings_1.h"



static volatile bool    mbFlags[UART_COUNT];
static volatile uchar   mbTimeout[UART_COUNT];



void InitCustomerSettings1(void) {
  uchar u;
  for (u = 0; u < UART_COUNT; u++) {
    mbFlags[u] = false;
    mbTimeout[u] = 0;
  }
}


void CustomerSettings1_1000Hz(void) {
  uchar u;
  for (u = 0; u < UART_COUNT; u++) {
    if (mbCustomerSettings[u] == 1) {
      if (mbTimeout[u] > 0) {
        mbTimeout[u]--;
      }
    }
  }
}


void CustomerSettings1_TelnetReceive(uchar u) {
  ASSERT(u < UART_COUNT);
  if (mbCustomerSettings[u] == 1) {
    if (mbTimeout[u] == 0) {
      mbFlags[u] = true;
      mbTimeout[u] = mbCustomerSetting1_Delay[u] + mwCustomerSetting1_Timeout[u];
    }
  }
}


void CustomerSettings1_TelnetProcessCharacter(uchar u) {
  ASSERT(u < UART_COUNT);
  if (mbCustomerSettings[u] == 1) {
    if (mbFlags[u] == true) {
      mbFlags[u] = false;

      OutMode(u);
      SerialSend(u, 0x99);

      mcwUARTTxOut[u]++;
    }
  }
}


void CustomerSettings1_SerialProcessCharacter(uchar u, uchar b) {
  ASSERT(u < UART_COUNT);
  if (mbCustomerSettings[u] == 1) {
    if (b == 0x99) {
      DelayMilliSecond(mbCustomerSetting1_Delay[u]);
    }
  }
}
