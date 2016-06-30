/*------------------------------------------------------------------------------
serial.h


------------------------------------------------------------------------------*/

#include "utils/ringbuf.h"



extern tRingBufObject g_sRxBuf[UART_COUNT];
extern tRingBufObject g_sTxBuf[UART_COUNT];

extern const uint32_t g_ulUARTBase[UART_COUNT];
extern const uint32_t g_ulIntUART[UART_COUNT];

extern volatile uint16_t mcwUARTTxOut[UART_COUNT];



void SerialInit(void);
