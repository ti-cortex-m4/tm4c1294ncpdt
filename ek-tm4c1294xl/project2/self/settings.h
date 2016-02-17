/*------------------------------------------------------------------------------
SETTINGS.H


------------------------------------------------------------------------------*/

#define MAX_CHAR 0xFF
#define MAX_INT 0xFFFF
#define MAX_LONG 0xFFFFFFFF

#define BAUD_RATE_COUNT      14

#define DEFAULT_CONNECTION_TIMEOUT 2 // 5
#define DEFAULT_ROUTING_MODE 0
#define DEFAULT_CONNECTION_MODE 1
#define DEFAULT_DESTINATION_IP 0x00000001
#define DEFAULT_DESTINATION_PORT 1001
#define DEFAULT_BAUD_RATE 6 // 9600


extern ulong                   dwIP;
extern ulong                   dwGateway;
extern ulong                   dwNetmask;

extern char                    szDeviceName[NAME_SIZE];
extern char                    szOwnerName[NAME_SIZE];

extern uchar                   mbConnectionTimeout[UART_COUNT];
extern uchar                   mbRoutingMode[UART_COUNT];
extern uint                    mwPort[UART_COUNT];
extern uchar                   mbConnectionMode[UART_COUNT];
extern ulong                   mdwDestinationIP[UART_COUNT];
extern uint                    mwDestinationPort[UART_COUNT];

extern uchar                   mibBaudRate[UART_COUNT];

extern bool                    fUdpDebugFlag;
extern ulong                   dwUdpDebugIP;
extern uint                    wUdpDebugPort;

extern uchar                   pbMAC[6];



uchar InitSettings(void);

uchar SaveSettings(void);

uchar SaveIP(void);
uchar SaveGateway(void);
uchar SaveNetmask(void);
uchar SavePort(void);

uchar SaveDeviceName(void);
uchar SaveOwnerName(void);

uchar SaveConnectionTimeout(void);
uchar SaveRoutingMode(void);
uchar SaveDestIP(void);
uchar SaveDestPort(void);

uchar SaveBaud(void);

uchar LoadSettings(void);

ulong GetBaud(uchar ibPort);
