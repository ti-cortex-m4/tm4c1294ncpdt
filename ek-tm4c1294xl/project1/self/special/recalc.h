/*------------------------------------------------------------------------------
RECALC.H


------------------------------------------------------------------------------*/

extern  cache const             chOpenCalc;



void    InitRecalc(void);



bool    Recalc(bool  fUseImp, bool  fUsePow);
bool    ClearCanals(bool  fStopCan, uchar  ibXmin, uchar  ibXmax, uint  iwAmin, uint  iwAmax);
