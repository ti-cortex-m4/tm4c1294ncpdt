/*------------------------------------------------------------------------------
RECALC.H


------------------------------------------------------------------------------*/

extern  cache const             chOpenCalc;



void    InitRecalc(void);



bool    Recalc(bool  fUseImp, bool  fUsePow);
bool    ClearCanals(bool  fStopCan, uchar  ibDigMin, uchar  ibDigMax, uint  wHhrMin, uint  wHhrMax);
