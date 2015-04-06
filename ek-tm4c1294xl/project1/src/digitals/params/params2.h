/*------------------------------------------------------------------------------
PARAMS2.H


------------------------------------------------------------------------------*/

extern  char const              szRecP[],
                                szRecP1[],
                                szRecP2[],
                                szRecP3[],
                                szRecQ[],
                                szRecQ1[],
                                szRecQ2[],
                                szRecQ3[],
                                szRecS[],
                                szRecS1[],
                                szRecS2[],
                                szRecS3[],
                                szRecU[],
                                szRecU1[],
                                szRecU2[],
                                szRecU3[],
                                szRecI[],
                                szRecI1[],
                                szRecI2[],
                                szRecI3[],
                                szRecC[],
                                szRecC1[],
                                szRecC2[],
                                szRecC3[],
                                szRecF[],
                                szRecF1[],
                                szRecF2[],
                                szRecF3[],
                                szRecNo[];


extern  boolean                 boBeginParam;



bool    ReadParam(uint  iwPrm);

void    MakeExtended2(void);

void    MakeParamDiv(uint  iwPrm);
//void    MakeAllDividers(void);
//
uint    GetParamIndex(digital  di);
