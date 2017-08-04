/*------------------------------------------------------------------------------
SERIAL0!H


------------------------------------------------------------------------------*/

void    DTROff0(void);
void    InputMode0(void);
void    OutputMode0(void);

void    InitSerial0(void);
void    InDelay0_Timer0(void);
void    Query0(uint  cwIn, uchar  cbOut, bool  fMinInDelay);
void    Answer0(uint  wSize, serial  seT);
