/*------------------------------------------------------------------------------
serial_flow.h


------------------------------------------------------------------------------*/

void    InitSerialFlow(void);

void    InSerialFlow(uchar  p, uchar  b);
void    StopSerialFlow(uchar  p);
void    InDelaySerialFlow_Timer0(void);

void    RunResponseSerialFlow_All(void);