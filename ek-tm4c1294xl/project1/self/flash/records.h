/*------------------------------------------------------------------------------
RECORDS,H


------------------------------------------------------------------------------*/

void    InitRecords(void);
void    ResetRecords(void);

void    RecordToBuff(uchar*  pBuff);
void    BuffToRecord(uchar*  pBuff);

bool    AddKeyRecord(event  ev);
bool    AddSysRecord(event  ev);
bool    AddSysRecordReprogram(event  ev);
bool    AddDigRecord(event  ev);
bool    AddImpRecord(event  ev);
bool    AddModRecord(event  ev);
bool    AddPh2Record(event  ev);
