/*------------------------------------------------------------------------------
LABEL.H


------------------------------------------------------------------------------*/

extern  uchar                   mpbLabelGlobal[0x20];

extern  cache const             chLabelGlobal;



void    SetLabelGlobal(void);
bool    GetLabelGlobal(void);
void    BreakLabelGlobal(void);
