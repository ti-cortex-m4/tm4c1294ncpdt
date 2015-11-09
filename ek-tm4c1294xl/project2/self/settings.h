/*------------------------------------------------------------------------------
SETTINGS.H


------------------------------------------------------------------------------*/

extern ulong                   dwIP;
extern ulong                   dwGateway;
extern ulong                   dwNetmask;



void    InitSettings(void);
ulong   SaveSettings(void);
ulong   LoadSettings(void);
