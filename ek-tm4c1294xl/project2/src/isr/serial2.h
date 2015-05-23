/*------------------------------------------------------------------------------
SERIAL2.H


------------------------------------------------------------------------------*/

void    DTROff2(void);
void    InputMode2(void);
void    OutputMode2(void);

void    InitSerial2(void);
void    InDelay2_Timer0(void);
void    Query2(uint  cwIn, uchar  cbOut, bool  fMinInDelay);
void    Answer2(uint  wSize, serial  seT);
