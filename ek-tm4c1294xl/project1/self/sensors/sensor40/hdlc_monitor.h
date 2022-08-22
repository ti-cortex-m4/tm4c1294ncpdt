/*------------------------------------------------------------------------------
hdlc_monitor.h


------------------------------------------------------------------------------*/

void    MonitorOutputHDLC(void);
bool    ValidateInputHDLC(void);

uchar   ValidateFrameHDLC(uchar  bNS_client, uchar  bNR_client);

bool    LastSegmentDMLS(void);
bool    UseBlocksDMLS(void);
bool    LastBlockDMLS(void);
