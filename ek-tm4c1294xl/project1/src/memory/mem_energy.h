/*------------------------------------------------------------------------------
MEM_ENERGY.H


------------------------------------------------------------------------------*/

extern  uint                    mpwImpMntCan[bMINUTES][bCANALS],
                                mpwImpHouCan[2][bCANALS];

extern  impulse                 mpimDayCan[2][bCANALS],
                                mpimMonCan[2][bCANALS],
                                mpimAbsCan[bCANALS];

extern  impulse                 imAlt;

extern  real                    mpreCntMonCan[2][bCANALS];

extern  power                   mppoDayGrp[2][bGROUPS],
                                mppoMonGrp[2][bGROUPS];

extern  maximum                 maAlt;
