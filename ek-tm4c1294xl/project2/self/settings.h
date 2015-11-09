/*------------------------------------------------------------------------------
SETTINGS.H


------------------------------------------------------------------------------*/

extern ulong                   dwIP;
extern ulong                   dwGateway;
extern ulong                   dwNetmask;



uchar   InitSettings(void);
uchar   SaveSettings(void);
uchar   LoadSettings(void);
