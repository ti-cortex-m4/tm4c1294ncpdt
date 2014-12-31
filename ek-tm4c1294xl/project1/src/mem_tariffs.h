/*------------------------------------------------------------------------------
MEM_TARIFFS.H


------------------------------------------------------------------------------*/

extern  boolean                 boOldTariffs;



extern  relaxs                  mpreRelaxs;

extern  time                    tiRelax;

extern  boolean                 boRelaxsFlag;

extern  uchar                   ibRelaxsTariff;



extern  zones                   mpzoPowMonthMode[12+4+1][bMODES],
                                mpzoEngMonthMode[12+4+1][bMODES];

extern  boolean                 mpboPowMonthMode[12+4+1][bMODES],
                                mpboEngMonthMode[12+4+1][bMODES];

extern  uchar                   mpibPowCurrTariff[48],
                                mpibEngCurrTariff[48];

extern  uchar                   mpibPowPrevTariff[48],
                                mpibEngPrevTariff[48];

extern  boolean                 boPublicCurr,
                                boPublicPrev;


extern  uchar                   mpchPowMonth[12],
                                mpchEngMonth[12];

extern  uchar                   bOldMode;

extern  uchar                   chOldMode;

extern  uchar                   ibAltMode;



extern  zones                   zoAlt,zoKey;

extern  breaks                  brAlt,brKey;

extern  boolean                 boAlt;



extern  boolean                 boGapsFlag;

extern  gaps                    mpgaGaps;

extern  time                    tiGap;

extern  uchar                   mpbGaps[365];
