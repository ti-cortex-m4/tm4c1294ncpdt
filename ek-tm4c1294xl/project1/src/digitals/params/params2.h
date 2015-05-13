/*------------------------------------------------------------------------------
PARAMS2.H


------------------------------------------------------------------------------*/

extern  char const              szParamP[],
                                szParamP1[],
                                szParamP2[],
                                szParamP3[],
                                szParamQ[],
                                szParamQ1[],
                                szParamQ2[],
                                szParamQ3[],
                                szParamS[],
                                szParamS1[],
                                szParamS2[],
                                szParamS3[],
                                szParamU[],
                                szParamU1[],
                                szParamU2[],
                                szParamU3[],
                                szParamI[],
                                szParamI1[],
                                szParamI2[],
                                szParamI3[],
                                szParamC[],
                                szParamC1[],
                                szParamC2[],
                                szParamC3[],
                                szParamF[],
                                szParamF1[],
                                szParamF2[],
                                szParamF3[],
                                szNoParam[];


extern  boolean                 boBeginParam;



bool    ReadParam(uint  iwPrm);

void    MakeExtended2(void);

void    MakeParamDiv(uint  iwPrm);
void    MakeParamDivAll(void);

uint    GetParamIndex(digital  di);
