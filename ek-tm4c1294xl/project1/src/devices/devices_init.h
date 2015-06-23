/*------------------------------------------------------------------------------
DEVICES_INIT.H


------------------------------------------------------------------------------*/

extern  cache const             chSeparateCan;
extern  cache const             chShowMessages;
extern  cache const             chHideMessages;
extern  cache const             chControlTime;
extern  cache const             chManageTime;

extern  file const              flKeysLevelB;
extern  file const              flShortProfileC;



void    InitDevices1(void);
void    InitDevices2(void);
void    ResetDevices(bool  fFull);
