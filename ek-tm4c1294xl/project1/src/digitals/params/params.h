/*------------------------------------------------------------------------------
PARAMS,H


------------------------------------------------------------------------------*/

#include    "../../memory/mem_params.h"



extern  param const             mppaParamMap[bPARAM_BLOCK];



extern  file const              flParamsFlag;
extern  file const              flMntParams;

extern  file const              flParams;
extern  file const              flParamsDiv;
extern  file const              flEnblParams;

extern  file const              flFixParamsBugs;
extern  file const              flUseParamsDiv;



void    InitParams(void);
void    ResetParams(void);

void    LoadCurrParam(uint  iwPrm);

bool    ValidParam(digital  *pdi);
bool    ValidParamLine(uchar  ibLine);

void    SetParam(uint  iwPrm, digital  *pdi);

uchar   GetParamPort(uint  iwPrm);
uchar   GetParamPhone(uint  iwPrm);
uchar   GetParamDevice(uint  iwPrm);
uchar   GetParamAddress(uint  iwPrm);
uchar   GetParamLine(uint  iwPrm);

void    ShowParam(uint  iwPrm);
