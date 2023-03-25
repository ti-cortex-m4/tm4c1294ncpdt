/*------------------------------------------------------------------------------
profile41.h


------------------------------------------------------------------------------*/

extern  time                    tiValue41;
extern  ulong                   dwValue41;

extern  uint                    cwShutdown41;



void    InitHeader41(void);
void    QueryHeader41(void);
uchar   PushIndex41(uint  iw30MinRel);
void    QueryProfile41(uint  iw30MinRelStart, uint  iw30MinRelEnd);
bool    ReadData41(void);

void    RunProfile41(void);
