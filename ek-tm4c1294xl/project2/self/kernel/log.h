/*------------------------------------------------------------------------------
log.h


------------------------------------------------------------------------------*/

#ifndef __LOG_H__
#define __LOG_H__


#ifdef DEBUG
#define CONSOLE DebugPrintF
#define WARNING DebugPrintF("WARNING "); DebugPrintF
#define ERROR DebugPrintF("ERROR "); DebugPrintF
#else
#define CONSOLE
#define WARNING
#define ERROR
#endif


#endif


void DebugPrintF(const char *sz, ...);
void UDPPrintF(const char *sz, ...);
void UartPrintF(const char *sz, ...);
void UARTprintf(const char *sz, ...);

