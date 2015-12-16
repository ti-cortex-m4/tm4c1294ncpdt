/*------------------------------------------------------------------------------
SETTINGS.H


------------------------------------------------------------------------------*/


#define BAUDS_SIZE      14
#define DEFAULT_BAUD    6 // 9600



extern ulong                   dwIP;
extern ulong                   dwGateway;
extern ulong                   dwNetmask;

extern char                    szDeviceName[NAME_SIZE];
extern char                    szOwnerName[NAME_SIZE];

extern uint                    wPort;
extern uchar                   ibBaud;

extern uchar                   pbMAC[6];



uchar   InitSettings(void);

uchar   SaveSettings(void);

uchar SaveIP(void);
uchar SaveGateway(void);
uchar SaveNetmask(void);
uchar SaveDeviceName(void);
uchar SaveOwnerName(void);
uchar SavePort(void);
uchar SaveBaud(void);

uchar   LoadSettings(void);

ulong GetBaud(void);
