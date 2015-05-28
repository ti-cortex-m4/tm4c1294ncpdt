/*------------------------------------------------------------------------------
SETTINGS.H


------------------------------------------------------------------------------*/

extern  file const              flLogical;

extern  file const              flFirstReset;

extern  file const              flSetTime;
extern  file const              flSetDate;
extern  file const              flSetGroups;
extern  file const              flSetPassword;



void    InitSettings(void);
void    ResetSettings(bool  fFullReset);

bool SavePrivate(void);
bool LoadPrivate(void);

bool SaveGlobal(void);
bool LoadGlobal(void);
