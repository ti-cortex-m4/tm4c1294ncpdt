/*------------------------------------------------------------------------------
SETTINGS,H


------------------------------------------------------------------------------*/

extern  file const              flPrivate;
extern  cache const             chLogical;

extern  cache const             chFirstReset;
extern  cache const             chEnblWDT;

extern  cache const             chSetTime;
extern  cache const             chSetDate;
extern  cache const             chSetGroups;
extern  cache const             chSetPassword;

extern  cache const             chStart;
extern  cache const             chPowerOff;
extern  cache const             chPowerOn;
extern  cache const             chSwitchOn;



void    InitSettings(void);
void    ResetSettings(bool  fFullReset);
