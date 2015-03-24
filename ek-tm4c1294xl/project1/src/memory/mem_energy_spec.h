/*------------------------------------------------------------------------------
MEM_ENERGY_SPEC.H


------------------------------------------------------------------------------*/

extern  uint                    iwDigHou;

extern  uint                    mpwImpHouCanSpec[bCANALS];

extern  impulse                 mpimDayCanSpec[bCANALS],
                                mpimMonCanSpec[bCANALS];

extern  power                   mppoDayGrpSpec[bGROUPS],
                                mppoMonGrpSpec[bGROUPS];



extern  time                    tiOldDay, tiOldMon;

extern  uchar                   ibOldDay, ibOldMon;



extern  uchar                   mpbWinterCan[bCANALS];



extern  uchar                   cbChannels;

extern  uint                    mpwChannels[bCHANNELS];



extern  uchar                   boOpenCalc;



extern  impulse                 mpdeDayCan[bCANALS],
                                mpdeMonCan[bCANALS];

extern  uint                    mpwImpHouCanDef[bCANALS];
