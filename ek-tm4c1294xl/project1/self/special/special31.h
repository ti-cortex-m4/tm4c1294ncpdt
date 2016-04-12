/*------------------------------------------------------------------------------
SPECIAL31!H


------------------------------------------------------------------------------*/

extern  double                  mpdbChannelsPrev31[bCHANNELS],
                                mpdbChannelsCurr31[bCHANNELS];



void    MonitorChannelsCurr(uchar  ibCan);
void    MonitorChannelsPrev(uchar  ibCan);

bool    MakeSpecial31(time  ti, uchar  bMaxLine);
