/*------------------------------------------------------------------------------
DIGITALS_PAUSE.H


------------------------------------------------------------------------------*/

extern  uint                    mpcwPause[bPORTS];



void    Pause(void);

void    MakePause(uint  w);
void    MakeLongPause(uint  w, uchar  bSecond);

void    NextPause(void);
