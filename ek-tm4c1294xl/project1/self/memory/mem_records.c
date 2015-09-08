/*------------------------------------------------------------------------------
MEM_RECORDS,C


------------------------------------------------------------------------------*/

#include "../main.h"



// текуща€ запись
record                  reCurr;

// счЄтчики записей
ulong                   cdwKeyRecord,
                        cdwSysRecord,
                        cdwDigRecord,
                        cdwImpRecord,
                        cdwModRecord,
                        cdwPh2Record,
                        cdwAuxRecord;

// флаги разрешени€ событий
uchar                   mpfRecordDsbl[256];

// глобальна€ переменна€ - врем€
time                    tiRecordTime;

// глобальна€ переменна€ - канал
uchar                   ibRecordCan;

// глобальна€ переменна€
uchar                   bRecord;
