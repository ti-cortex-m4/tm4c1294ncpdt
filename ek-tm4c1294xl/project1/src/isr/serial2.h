/*------------------------------------------------------------------------------
SERIAL2.H


------------------------------------------------------------------------------*/

void    InitSerial2(void);
void    InDelay2_Timer0(void);
void    Query2(uint  cwIn, uchar  cbOut, bool  fMinInDelay);
void    Answer2(uint  wSize, serial  seT);
