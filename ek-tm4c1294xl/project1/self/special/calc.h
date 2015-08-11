/*------------------------------------------------------------------------------
CALC.H


------------------------------------------------------------------------------*/

extern  bool                    fLoadHou, fLoadDay, fLoadMon,
                                fLoadMem, fSaveDay, fSaveMon;



void    OpenCalc(void);

void    CalcTimeDate(bool  fUseImp, bool  fUsePow, time  ti);
void    CalcDigCanals(time  ti);
void    CalcAllCanals(bool  fUseImp, time  ti);
void    CalcAllGroups(bool  fUsePow, time  ti);

void    CloseCalc(bool  fUseImp, bool  fUsePow);
