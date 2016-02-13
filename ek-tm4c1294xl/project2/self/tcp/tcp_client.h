/*------------------------------------------------------------------------------
TCP_CLIENT.H


------------------------------------------------------------------------------*/

extern void TelnetInit(void);

extern void TelnetOpen(uint32_t ulIPAddr, uint16_t usTelnetRemotePort, uint16_t usTelnetLocalPort, uint32_t ulSerialPort);
extern void TelnetClose(uint32_t ulSerialPort);

#if false
extern uint16_t TelnetGetLocalPort(uint32_t ulSerialPort);
extern uint16_t TelnetGetRemotePort(uint32_t ulSerialPort);
#endif
