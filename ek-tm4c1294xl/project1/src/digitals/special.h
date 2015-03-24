/*------------------------------------------------------------------------------
SPECIAL.H


------------------------------------------------------------------------------*/

extern  bool                    fLoadHou, fLoadDay, fLoadMon,
                                fLoadMem, fSaveDay, fSaveMon;



bool    IsDefect(uchar    ibCan);

bool    IsOpenSpecial(void);
void    OpenSpecial(void);
void    MakeSpecial(void);
void    CloseSpecial(void);
