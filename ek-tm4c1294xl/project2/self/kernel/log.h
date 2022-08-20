/*------------------------------------------------------------------------------
log.h


------------------------------------------------------------------------------*/

#ifndef __LOG_H__
#define __LOG_H__


#ifdef DEBUG
#define CONSOLE DebugPrintF
#define WARNING DebugPrintF_Warning
#define ERROR DebugPrintF_Error
#else
#define CONSOLE
#define WARNING
#define ERROR
#endif


#endif


void DebugPrintF(const char *pcsz, ...);
void DebugPrintF_Warning(const char *pcsz, ...);
void DebugPrintF_Error(const char *pcsz, ...);

void UDPPrintF(const char *pcsz, ...);
void UARTPrintF(const char *pcsz, ...);
void UARTprintf(const char *pcsz, ...);

