/*------------------------------------------------------------------------------
MEM_RECORDS,C


------------------------------------------------------------------------------*/

#include "../main.h"



// текущая запись
record                  reCurr;

// счётчики записей
ulong                   cdwKeyRecord,
                        cdwSysRecord,
                        cdwDigRecord,
                        cdwImpRecord,
                        cdwModRecord,
                        cdwPh2Record,
                        cdwAuxRecord;

// флаги разрешения событий
uchar                   mpboRecordDsbl[256];

// глобальная переменная - время
time                    tiRecordSetCurrTime;

// глобальная переменная - канал
uchar                   ibRecordCan;
