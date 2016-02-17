/*------------------------------------------------------------------------------
TELNET.H


------------------------------------------------------------------------------*/

#include "telnet_include.h"



tTelnetSession *getTelnetSession(uchar ibUart);

extern void TelnetInit(void);

extern void TelnetOpen(uint32_t ulIPAddr, uint16_t usTelnetRemotePort,/* uint16_t usTelnetLocalPort,*/ uint32_t ulSerialPort);
extern void TelnetListen(uint16_t usTelnetPort, uint32_t ulSerialPort);
extern void TelnetClose(uint32_t ulSerialPort);

extern void TelnetHandler(void);

#if false
extern uint16_t TelnetGetLocalPort(uint32_t ulSerialPort);
extern uint16_t TelnetGetRemotePort(uint32_t ulSerialPort);
#endif
