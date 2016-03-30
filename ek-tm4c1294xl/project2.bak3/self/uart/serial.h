/*------------------------------------------------------------------------------
serial,h


------------------------------------------------------------------------------*/

#include "utils/ringbuf.h"



extern tRingBufObject g_sRxBuf[UART_COUNT];
extern tRingBufObject g_sTxBuf[UART_COUNT];

extern const uint32_t g_ulUARTBase[UART_COUNT];
extern const uint32_t g_ulIntUART[UART_COUNT];

//void SerialPurgeData(uint32_t ulPort, uint8_t ucPurgeCommand);
//void SerialSetDefault(uint32_t ulPort);
//void SerialSetFactory(uint32_t ulPort);
//void SerialSetCurrent(uint32_t ulPort);
void SerialInit(void);
