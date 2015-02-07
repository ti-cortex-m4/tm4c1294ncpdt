/*------------------------------------------------------------------------------
MEM_TARIFFS.H


------------------------------------------------------------------------------*/

extern  relax                  mpreRelaxs;

extern  time                    tiRelax;

extern  boolean                 boRelaxsFlag;

extern  uchar                   ibRelaxsTariff;



extern  zone                   mpzoPowMonthMode[12][bMODES],
                                mpzoEngMonthMode[12][bMODES];

extern  uchar                   mpibPowCurrTariff[48],
                                mpibEngCurrTariff[48];

extern  uchar                   mpibPowPrevTariff[48],
                                mpibEngPrevTariff[48];

extern  boolean                 fPublicTariffsCurr,
                                fPublicTariffsPrev;

extern  period                  mpeTariffPow[12],
                                mpeTariffEng[12];

extern  uchar                   bTariffsMode;



extern  zone                   zoAlt,zoKey;

extern  breaks                  brAlt,brKey;



extern  boolean                 boGapsFlag;

extern  gap                    mpgaGaps;

extern  time                    tiGap;

extern  uchar                   mpbGaps[365];
