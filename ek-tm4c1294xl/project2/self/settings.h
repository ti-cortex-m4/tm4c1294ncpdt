/*------------------------------------------------------------------------------
SETTINGS.H


------------------------------------------------------------------------------*/

extern ulong                   dwIP;
extern ulong                   dwGateway;
extern ulong                   dwNetmask;

extern char                    szDeviceName[NAME_SIZE];
extern char                    szOwnerName[NAME_SIZE];

extern uint                    wPort;

extern uchar                   pbMAC[6];



uchar   InitSettings(void);
uchar   SaveSettings(void);
uchar   LoadSettings(void);
