/*------------------------------------------------------------------------------
SETTINGS.H


------------------------------------------------------------------------------*/

extern  file const              flLogical;



void    InitSettings(void);
void    ResetSettings(bool  fFullReset);

boolean SavePrivate(void);
boolean LoadPrivate(void);

boolean SaveGlobal(void);
boolean LoadGlobal(void);
