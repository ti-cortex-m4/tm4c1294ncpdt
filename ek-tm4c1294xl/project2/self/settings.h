/*------------------------------------------------------------------------------
SETTINGS.H


------------------------------------------------------------------------------*/

extern ulong                   dwIP;
extern ulong                   dwGateway;
extern ulong                   dwNetmask;

extern uchar                   pbMAC[6];



uchar   InitSettings(void);
uchar   SaveSettings(void);
uchar   LoadSettings(void);

void    SetMAC(uchar *pb);
