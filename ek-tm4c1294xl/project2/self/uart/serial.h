/*------------------------------------------------------------------------------
serial.h


------------------------------------------------------------------------------*/

bool SerialSendFull(uint32_t ulPort);
void SerialSend(uint32_t ulPort, uint8_t ucChar);

long SerialReceive(uint32_t ulPort);
uint32_t SerialReceiveAvailable(uint32_t ulPort);

#if false
void SerialSetBaudRate(uint32_t ulPort, uint32_t ulBaudRate);
uint32_t SerialGetBaudRate(uint32_t ulPort);
void SerialSetDataSize(uint32_t ulPort, uint8_t ucDataSize);
uint8_t SerialGetDataSize(uint32_t ulPort);
void SerialSetParity(uint32_t ulPort, uint8_t ucParity);
uint8_t SerialGetParity(uint32_t ulPort);
void SerialSetStopBits(uint32_t ulPort, uint8_t ucStopBits);
uint8_t SerialGetStopBits(uint32_t ulPort);
void SerialSetFlowControl(uint32_t ulPort, uint8_t ucFlowControl);
uint8_t SerialGetFlowControl(uint32_t ulPort);
void SerialSetFlowOut(uint32_t ulPort, uint8_t ucFlowValue);
uint8_t SerialGetFlowOut(uint32_t ulPort);
#endif

void SerialPurgeData(uint32_t ulPort, uint8_t ucPurgeCommand);
void SerialSetDefault(uint32_t ulPort);
void SerialSetFactory(uint32_t ulPort);
void SerialSetCurrent(uint32_t ulPort);
void SerialInit(void);
