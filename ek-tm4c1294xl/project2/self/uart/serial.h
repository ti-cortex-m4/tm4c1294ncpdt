/*------------------------------------------------------------------------------
SERIAL.H


------------------------------------------------------------------------------*/

extern bool SerialSendFull(uint32_t ulPort);
extern void SerialSend(uint32_t ulPort, uint8_t ucChar);

extern long SerialReceive(uint32_t ulPort);
extern uint32_t SerialReceiveAvailable(uint32_t ulPort);

extern void SerialSetDefault(uint32_t ulPort);
//extern void SerialSetFactory(uint32_t ulPort);
//extern void SerialSetCurrent(uint32_t ulPort);
//extern void SerialInit(void);
