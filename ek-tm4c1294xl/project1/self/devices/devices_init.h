/*------------------------------------------------------------------------------
DEVICES_INIT.H


------------------------------------------------------------------------------*/

extern  cache const             chSeparateCan;
extern  cache const             chShowMessages;
extern  cache const             chHideMessages;
extern  cache const             chControlTime;
extern  cache const             chManageTime;

extern  cache const             chKeysLevelB;
extern  cache const             chShortProfileC;



void    InitDevices1(void);
void    InitDevices2(void);
void    ResetDevices(bool  fFull);
