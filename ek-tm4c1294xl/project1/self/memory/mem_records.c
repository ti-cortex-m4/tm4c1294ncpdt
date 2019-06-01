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
uchar                   mpfRecordDsbl[256];

// глобальная переменная - время
time                    tiRecordTime, tiRecordTime2;

// глобальная переменная - канал
uchar                   ibRecordCan;

// глобальная переменная
uchar                   bRecord;

// глобальная переменная
uint                    wRecord;

// глобальная переменная
ulong                   dwRecord;
