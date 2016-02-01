/*------------------------------------------------------------------------------
MONITOR_SETTINGS.H


-----------------------------------------------------------------------------*/

extern bool                    fMonitorLogBasic;
extern bool                    fMonitorLogHex;
extern bool                    fMonitorLogChar7;
extern bool                    fMonitorLogChar8;

extern cache const             chMonitorLogBasic;
extern cache const             chMonitorLogHex;
extern cache const             chMonitorLogChar7;
extern cache const             chMonitorLogChar8;



void    InitMonitorSettings(void);
void    ResetMonitorSettings(void);
