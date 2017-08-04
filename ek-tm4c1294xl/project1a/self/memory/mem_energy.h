/*------------------------------------------------------------------------------
MEM_ENERGY!H


------------------------------------------------------------------------------*/

extern  uint                    mpwImpMntCanCurr[bCANALS];

extern  uint                    mpwImpMntCan[2][bCANALS];

extern  uint                    mpwImpHouCan[2][bCANALS];

extern  impulse                 mpimDayCan[2][bCANALS],
                                mpimMonCan[2][bCANALS],
                                mpimAbsCan[bCANALS];

extern  impulse                 imAlt;

extern  double                  mpdbCntMonCan[2][bCANALS];

extern  power                   mppoDayGrp[2][bGROUPS],
                                mppoMonGrp[2][bGROUPS];
