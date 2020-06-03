/*------------------------------------------------------------------------------
profile38.h


------------------------------------------------------------------------------*/

extern  time                    tiValue38;
extern  ulong                   dwValue38;



void    InitHeader38(void);
void    QueryHeader38(void);
void    QueryProfile38(uint  iw30MinRelStart, uint  iw30MinRelEnd);
bool    ReadData38(void);

void    RunProfile38(void);
