/*------------------------------------------------------------------------------
SERIAL1.H


------------------------------------------------------------------------------*/

void    InitSerial1(void);
void    InDelay1_Timer0(void);
void    Query1(uint  cwIn, uchar  cbOut, bool  fMinInDelay);
void    Answer1(uint  wSize, serial  seT);
