/*------------------------------------------------------------------------------
PARAMS,H


------------------------------------------------------------------------------*/

#include    "../../memory/mem_params.h"



extern  param const             mppaParamsLines[bPARAM_BLOCK];



extern  cache const             chParamsFlag;
extern  cache const             chMntParams;

extern  cache const             flParams;
extern  cache const             flParamsDiv;
extern  cache const             flEnblParams;

extern  cache const             chFixParamsBugs;
extern  cache const             chUseParamsDiv;



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
