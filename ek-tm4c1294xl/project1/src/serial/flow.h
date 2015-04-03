/*------------------------------------------------------------------------------
FLOW.H


------------------------------------------------------------------------------*/

void    InitFlow(void);
void    ResetFlow(void);

void    RepeatFlow(void);

void    RunFlow0(void);
void    RunFlow1(void);

bool    IsFlow0(void);
bool    IsFlow1(void);
bool    IsFlow2(void);
bool    IsFlow3(void);

void    CloseFlow(void);

void    DelayFlow_1Hz(void);

void    RunResponseFlow_All(void);
