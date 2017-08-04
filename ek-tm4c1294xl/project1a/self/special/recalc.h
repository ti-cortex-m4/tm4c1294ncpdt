/*------------------------------------------------------------------------------
RECALC!H


------------------------------------------------------------------------------*/

extern  cache const             chOpenCalc;



void    InitRecalc(void);



bool    Recalc(bool  fUseImp, bool  fUsePow);
bool    ClearCanals(uchar  ibDigMin, uchar  ibDigMax, uint  wHhrMin, uint  wHhrMax, bool  fStopCan);
