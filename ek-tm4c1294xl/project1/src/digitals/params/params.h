/*------------------------------------------------------------------------------
PARAMS.C


------------------------------------------------------------------------------*/

#include    "../../memory/mem_params.h"



extern  file const              flEnblAllParams;
extern  file const              flMntParams;

extern  file const              flParams;
extern  file const              flParamsDiv;
extern  file const              flEnblParams;

extern  file const              flFixParamsBugs;



void    InitParams(void);
void    ResetParams(void);


/*
#include        "main.h"



extern  param           code    mppaParamMap[bPARAM_BLOCK];



void    ResetParams(void);
*/
void    LoadCurrParam(uint  iwPrm);

bool    TrueParam(void);
bool    TrueParamLine(uchar  ibLine);

void    SetParam(uint  iwPrm, digital  *pdi);

uchar   GetParamPort(uint  iwPrm);
uchar   GetParamPhone(uint  iwPrm);
uchar   GetParamDevice(uint  iwPrm);
uchar   GetParamAddress(uint  iwPrm);
uchar   GetParamLine(uint  iwPrm);

void    ShowParam(uint  iwPrm);
