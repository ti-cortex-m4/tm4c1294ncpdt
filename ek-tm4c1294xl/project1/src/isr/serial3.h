/*------------------------------------------------------------------------------
SERIAL3.H


------------------------------------------------------------------------------*/

void    InitSerial3(void);
void    InDelay3_Timer0(void);
void    Query3(uint  cwIn, uchar  cbOut, bool  fMinInDelay);
void    Answer3(uint  wSize, serial  seT);
