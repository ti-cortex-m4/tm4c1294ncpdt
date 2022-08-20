/*------------------------------------------------------------------------------
hdlc_monitor.h


------------------------------------------------------------------------------*/

void    MonitorOutputHDLC(void);
bool    ValidateInputHDLC(void);

uchar   ValidateFrame(uchar  bNS_client, uchar  bNR_client);

bool    LastSegmentDMLS(void);
bool    UseBlocksDMLS(void);
bool    LastBlockDMLS(void);
