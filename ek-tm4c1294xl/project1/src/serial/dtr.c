/*------------------------------------------------------------------------------
DTR.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../digitals/wait_query.h"




void    DTROff0(void);
void    DTROff1(void);
void    DTROff2(void);
void    DTROff3(void);



void    DTROff_All(void)
{
  DTROff0();
  DTROff1();
  DTROff2();
  DTROff3();
}



void    RunDTR(void)
{
//  if (boDTREnable != TRUE) return;
//  if (mpboDTRResetHou[ GetCurrHouIndex() ] != TRUE) return;

  if (cbWaitQuery == 0) DTROff_All();
}



void    ResetDTR(void)
{
//  if (boDTREnable != TRUE) return;
//  if (SuperUser() == 0) return;
//  if (enGlobal == GLB_WORK) return;
//
//  if ((bProgram != bGET_READTIMEDATE1) &&
//      (bProgram != bGET_READTIMEDATE2) &&
//      (bProgram != bGET_COUNTOLD)) return;
//
//  DTROff_All();
}
