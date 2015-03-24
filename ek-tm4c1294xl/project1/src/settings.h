/*------------------------------------------------------------------------------
SETTINGS.H


------------------------------------------------------------------------------*/

extern  file const              flLogical;

extern  file const              flFirstReset;



void    InitSettings(void);
void    ResetSettings(bool  fFullReset);

boolean SavePrivate(void);
boolean LoadPrivate(void);

boolean SaveGlobal(void);
boolean LoadGlobal(void);
