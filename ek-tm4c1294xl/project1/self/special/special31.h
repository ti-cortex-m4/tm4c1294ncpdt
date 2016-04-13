/*------------------------------------------------------------------------------
SPECIAL31!H


------------------------------------------------------------------------------*/

extern  double                  mpdbChannelsPrev31[bCHANNELS],
                                mpdbChannelsCurr31[bCHANNELS];



void    MonitorChannelsCurr(uchar  i);
void    MonitorChannelsPrev(uchar  i);

void    ClearChannels31(void);

bool    MakeSpecial31(time  ti, uchar  bMaxLine);
