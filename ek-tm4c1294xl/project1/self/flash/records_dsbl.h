/*------------------------------------------------------------------------------
RECORDS_DSBL!H


------------------------------------------------------------------------------*/

extern  cache const             chRecordDsbl;



void    InitRecordsDsbl(void);
void    ResetRecordsDsbl(void);

bool    IsRecordDisabled(uchar  ibCode);
void    OutRecordsDsbl(void);
