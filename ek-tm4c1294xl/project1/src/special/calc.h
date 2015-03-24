/*------------------------------------------------------------------------------
CALC.H


------------------------------------------------------------------------------*/

extern  bool                    fLoadHou, fLoadDay, fLoadMon,
                                fLoadMem, fSaveDay, fSaveMon;



void    OpenCalc(void);

void    CalcTimeDate(bool  fUseImp, bool  fUsePow);
void    CalcDigCanals(void);
void    CalcAllCanals(bool  fUseImp);
void    CalcAllGroups(bool  fUsePow);

void    CloseCalc(bool  fUseImp, bool  fUsePow);
