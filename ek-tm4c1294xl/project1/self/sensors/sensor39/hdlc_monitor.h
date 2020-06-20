/*------------------------------------------------------------------------------
hdlc_monitor.h


------------------------------------------------------------------------------*/

void    MonitorOutputHDLC(void);
bool    ValidateInputHDLC(void);

bool    ValidateIframe(uchar  bNS_client, uchar  bNR_client);
bool    ValidateSframe(uchar  bNR_client);
void    ShowSframe(uchar  bNR_client);
void    ValidateFrame(uchar  bNS_client, uchar  bNR_client);

bool    LastSegmentDMLS(void);
bool    UseBlocksDMLS(void);
bool    LastBlockDMLS(void);
