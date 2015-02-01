/*------------------------------------------------------------------------------
SETTINGS.H


------------------------------------------------------------------------------*/

extern  file const              flLogical;



void    InitSettings(void);
void    ResetSettings(bool  fFullReset);

bool    SavePrivate(void);
bool    LoadPrivate(void);

bool    SaveGlobal(void);
bool    LoadGlobal(void);
