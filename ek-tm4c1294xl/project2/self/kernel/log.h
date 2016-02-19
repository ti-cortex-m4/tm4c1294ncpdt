/*------------------------------------------------------------------------------
log.h


------------------------------------------------------------------------------*/

#ifndef __ENTITIES_H__
#define __ENTITIES_H__


#ifdef DEBUG
#define CONSOLE DebugPrintF
#define CONSOLE_UART UartPrintF
#define ERROR_UART UARTprintf
#else
#define CONSOLE
#define CONSOLE_UART
#define ERROR_UART
#endif



void DebugPrintF(const char *sz, ...);
void UdpPrintF(const char *sz, ...);
void UartPrintF(const char *sz, ...);
void UARTprintf(const char *sz, ...);


#endif

