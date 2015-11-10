/*------------------------------------------------------------------------------
SETTINGS.H


------------------------------------------------------------------------------*/

extern ulong                   dwIP;
extern ulong                   dwGateway;
extern ulong                   dwNetmask;

extern ulong                   dwPort;

extern uchar                   pbMAC[6];



uchar   InitSettings(void);
uchar   SaveSettings(void);
uchar   LoadSettings(void);

uint    GetPort(void);
