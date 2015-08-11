/*------------------------------------------------------------------------------
MEM_TARIFFS.H


------------------------------------------------------------------------------*/

extern  bool                    boRelaxsFlag;

extern  uchar                   ibRelaxsTariff;

extern  relaxs                  reRelaxs;

extern  time                    tiRelax;



extern  zone                    mpzoPowMonthMode[12][bMODES],
                                mpzoEngMonthMode[12][bMODES];

extern  uchar                   mpibPowCurrTariff[48],
                                mpibEngCurrTariff[48];

extern  uchar                   mpibPowPrevTariff[48],
                                mpibEngPrevTariff[48];

extern  bool                 fPublicTrf, fPublicTrfPrevMon;

extern  period                  mpePeriodTrfPow[12],
                                mpePeriodTrfEng[12];

extern  uchar                   bOldTrfMode;



extern  zone                    zoAlt, zoKey;

extern  br3ak                   brAlt, brKey;



extern  bool                    boGapsFlag;

extern  gaps                    gaGaps;

extern  time                    tiGap;

extern  uchar                   mpbGaps[365];
