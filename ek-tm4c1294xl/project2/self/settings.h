/*------------------------------------------------------------------------------
SETTINGS.H


------------------------------------------------------------------------------*/


#define BAUDS_SIZE      14
#define DEFAULT_BAUD    6 // 9600



extern ulong                   dwIP;
extern ulong                   dwGateway;
extern ulong                   dwNetmask;
extern uint                    wPort;

extern char                    szDeviceName[NAME_SIZE];
extern char                    szOwnerName[NAME_SIZE];

extern uchar                   bConnectionTimeout;
extern uchar                   ibRoutingMode;
extern ulong                   dwDestIP;
extern uint                    wDestPort;

extern uchar                   ibBaud;

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

ulong GetBaud(void);
