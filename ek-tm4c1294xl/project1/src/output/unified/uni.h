/*------------------------------------------------------------------------------
UNI.H


------------------------------------------------------------------------------*/

extern  file const              flObjectName;
extern  file const              flCanalsName;
extern  file const              flGroupsName;

extern  cache const             chStrictUni;
extern  cache const             chMaxDelayUni;
extern  cache const             chRepeatFlowUni;
extern  cache const             chEnblPasswUni;



void    InitUni(void);
void    ResetUni(void);

void    DelayUni_1Hz(void);
