/*------------------------------------------------------------------------------
SERIAL,H


------------------------------------------------------------------------------*/

extern bool SerialSendFull(uint32_t ulPort);
extern void SerialSend(uint32_t ulPort, uint8_t ucChar);

extern long SerialReceive(uint32_t ulPort);
extern uint32_t SerialReceiveAvailable(uint32_t ulPort);

extern void SerialSetBaudRate(uint32_t ulPort, uint32_t ulBaudRate);
extern uint32_t SerialGetBaudRate(uint32_t ulPort);
extern void SerialSetDataSize(uint32_t ulPort, uint8_t ucDataSize);
extern uint8_t SerialGetDataSize(uint32_t ulPort);
extern void SerialSetParity(uint32_t ulPort, uint8_t ucParity);
extern uint8_t SerialGetParity(uint32_t ulPort);
extern void SerialSetStopBits(uint32_t ulPort, uint8_t ucStopBits);
extern uint8_t SerialGetStopBits(uint32_t ulPort);
extern void SerialSetFlowControl(uint32_t ulPort, uint8_t ucFlowControl);
extern uint8_t SerialGetFlowControl(uint32_t ulPort);
extern void SerialSetFlowOut(uint32_t ulPort, uint8_t ucFlowValue);
extern uint8_t SerialGetFlowOut(uint32_t ulPort);

extern void SerialPurgeData(uint32_t ulPort, uint8_t ucPurgeCommand);
extern void SerialSetDefault(uint32_t ulPort);
extern void SerialSetFactory(uint32_t ulPort);
extern void SerialSetCurrent(uint32_t ulPort);
extern void SerialInit(void);
