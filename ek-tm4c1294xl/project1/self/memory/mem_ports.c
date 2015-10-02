/*------------------------------------------------------------------------------
MEM_PORTS!C


------------------------------------------------------------------------------*/

#include "../main.h"



// массив портов
port                    mppoPorts[bPORTS];

// текущие счётчики таймаута на приём
uint                    mpwInDelay[bPORTS];

// начальные счётчики таймаута на приём (нормальные и расширенные)
uint                    mpwMinorInDelay[bPORTS], mpwMajorInDelay[bPORTS];

// массив временной смены режима портов
bool                    mpboLocal[bPORTS];

// флаги запрещения временной смены режима
bool                    mpboLocalDisable[bPORTS];

// задержки на переключение сигнала прием-передача
uint                    mpwOutputDelay[bPORTS];

// минимальные лимиты коррекции времени
uchar                   mpbCorrectLimit[bPORTS];

// переменные
uchar                   bInBuff0,
                        bInBuff1,
                        bInBuff2,
                        bInBuff3,
                        bInBuff4,
                        bInBuff5,
                        bInBuff6,
                        bInBuff7,
                        bInBuff8,
                        bInBuff9,
                        bInBuffA,
                        bInBuffB,
                        bInBuffC,
                        bInBuffD,
                        bInBuffE,
                        bInBuffF;

// текущий запрос
uchar                   bQuery;

// анализируемый порт
uchar                   ibPortActive;



// индекс для доступа к буферу в режиме стека
uint                    iwPopSave;

// индекс по буферу
uint                    iwInBuffSave;

// счётчик по буферу
uint                    cwInBuffSave;

// промежуточный буфер
uchar                   mpbInBuffSave[wINBUFF_SIZE];

// промежуточный буфер
uchar                   mpbOutBuffZ[1024];



// счётчик служебных символов
uchar                   cbHeaderBcc;

// счётчик принятых байт
uint                    cwInBuffBcc;



// правило выключения режима на прием для ведомых портов 3,4
uchar                   bInputModeReset;

// время последнего выключения
time                    tiInputModeReset;

// количество выключений
ulong                   dwInputModeReset;



// флаг управления модемом
bool                    fSlaveModem;

// признак выдачи команды на программирование модема
bool                    fSendAT;

// массив текущих значений таймаутов
uchar                   mpcbSendAT[bPORTS];

// массив состояний
send_at                 mpstSendAT[bPORTS];



// флаг включения пакетного режима
bool                    fBulkEnbl;

// размеры пакета
uchar                   bBulkSize, cbBulk[bPORTS];

// счетчики таймаута
uint                    wBulkMaxDelay, cwBulkDelay[bPORTS];

// буфера
serial                  mpSerial_Bulk[bPORTS];
