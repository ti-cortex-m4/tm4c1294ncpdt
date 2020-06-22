/*------------------------------------------------------------------------------
time39.h


------------------------------------------------------------------------------*/

void    QueryTime39(uchar  bNS, uchar  bNR, uchar  bInvokeId);
time    ReadTime39(void);

void    QueryCorrectTime39(uchar  bNS, uchar  bNR, uchar  bInvokeId, sint  wSeconds);
