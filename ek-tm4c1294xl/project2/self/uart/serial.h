/*------------------------------------------------------------------------------
SERIAL.H


------------------------------------------------------------------------------*/

extern void SerialSend(uint32_t ulPort, uint8_t ucChar);

extern long SerialReceive(uint32_t ulPort);
extern uint32_t SerialReceiveAvailable(uint32_t ulPort);
