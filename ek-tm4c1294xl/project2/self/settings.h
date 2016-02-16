/*------------------------------------------------------------------------------
SETTINGS.H


------------------------------------------------------------------------------*/


#define MAX_CHAR 0xFF
#define MAX_INT 0xFFFF
#define MAX_LONG 0xFFFFFFFF

#define BAUDS_SIZE      14

#define DEFAULT_CONNECTION_TIMEOUT 0
#define DEFAULT_ROUTING_MODE 0
#define DEFAULT_DEST_IP 0xC0A80165 // inet_addr("101.1.168.192")
#define DEFAULT_DEST_PORT 101
#define DEFAULT_BAUD 6 // 9600


extern ulong                   dwIP;
extern ulong                   dwGateway;
extern ulong                   dwNetmask;
extern uint                    wPort;

extern char                    szDeviceName[NAME_SIZE];
extern char                    szOwnerName[NAME_SIZE];

extern uchar                   bConnectionTimeout;
extern uchar                   bRoutingMode;
extern ulong                   dwDestIP;
extern uint                    wDestPort;

extern uchar                   mibBaud[UART_COUNT];

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
