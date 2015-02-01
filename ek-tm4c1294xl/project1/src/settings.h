/*------------------------------------------------------------------------------
SETTINGS.H


------------------------------------------------------------------------------*/

void    InitSettings(void);
void    ResetSettings(bool  fFullReset);

bool    SavePrivate(void);
bool    LoadPrivate(void);

bool    SaveGlobal(void);
bool    LoadGlobal(void);

bool    SaveLogical(void);
bool    LoadLogical(void);
