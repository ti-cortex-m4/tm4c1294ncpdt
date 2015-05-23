/*------------------------------------------------------------------------------
DEVICES_INIT.H


------------------------------------------------------------------------------*/

extern  file const              flSeparateCan;
extern  file const              flShowMessages;
extern  file const              flHideMessages;
extern  file const              flControlTime;
extern  file const              flManageTime;

extern  file const              flKeysLevelB;
extern  file const              flShortProfileC;



void    InitDevices1(void);
void    InitDevices2(void);
void    ResetDevices(bool  fFull);
