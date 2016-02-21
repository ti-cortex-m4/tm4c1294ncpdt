/*------------------------------------------------------------------------------
SETTINGS,H


------------------------------------------------------------------------------*/

#include "kernel/entities.h"


#define BAUD_RATE_COUNT      14

#define DEFAULT_CONNECTION_TIMEOUT 1 // 5
#define DEFAULT_ROUTING_MODE 0
#define DEFAULT_CONNECTION_MODE 1
#define DEFAULT_DESTINATION_IP 0x00000001
#define DEFAULT_DESTINATION_PORT 1001
#define DEFAULT_BAUD_RATE 6 // 9600



extern uchar                   pbMAC[6];

extern ulong                   dwIP;
extern ulong                   dwGateway;
extern ulong                   dwNetmask;

extern char                    szOwnerName[NAME_SIZE];
extern char                    szDeviceName[NAME_SIZE];

extern uchar                   mbConnectionTimeout[UART_COUNT];
extern uchar                   mbRoutingMode[UART_COUNT];
extern uint                    mwPort[UART_COUNT];
extern uchar                   mbConnectionMode[UART_COUNT];
extern ulong                   mdwDestinationIP[UART_COUNT];
extern uint                    mwDestinationPort[UART_COUNT];

extern uchar                   mibBaudRate[UART_COUNT];

extern uint                    wSerialNumber;

extern bool                    ibDebugMode;

extern ulong                   dwUdpDebugIP;
extern uint                    wUdpDebugPort;

extern bool                    fLwIpDebugFlag;
extern uint                    wLwIpDebugTimeout;

extern uint                    cwErrStorageInit;
extern uint                    cwErrEntitySave;



void InitSettings(void);
void ResetSettings(void);

ulong GetBaud(uchar ibPort);
ulong getTelnetTimeout(uchar u);

