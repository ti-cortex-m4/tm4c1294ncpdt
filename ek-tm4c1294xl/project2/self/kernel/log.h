/*------------------------------------------------------------------------------
log.h


------------------------------------------------------------------------------*/

#ifndef __LOG_H__
#define __LOG_H__


#ifdef DEBUG
#define CONSOLE DebugPrintF
#define CONSOLE_UART DebugPrintF
#else
#define CONSOLE
#define CONSOLE_UART
#endif


#endif


void DebugPrintF(const char *sz, ...);
void UdpPrintF(const char *sz, ...);
void UartPrintF(const char *sz, ...);
void UARTprintf(const char *sz, ...);

