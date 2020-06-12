/*------------------------------------------------------------------------------
DIGITALS_PAUSE!H


------------------------------------------------------------------------------*/

#include "../main_devices.h"



extern  uint                    mpcwPause[bPORTS];



void    Pause(void);

void    MakePause(device  de);
void    MakeLongPause(device  de, uchar  bSecond);

void    NextPause(void);
