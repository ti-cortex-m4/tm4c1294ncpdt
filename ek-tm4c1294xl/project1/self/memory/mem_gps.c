/*------------------------------------------------------------------------------
MEM_GPS.C


------------------------------------------------------------------------------*/

#include "../main.h"



// номер порта часов GPS
uchar                   bPortGps;

// глобальные переменные
uchar                   bStatusGps;

// глобальные переменные
uchar                   bVersionMaxGps, bVersionMinGps;

// глобальная переменная
time                    tiGps;

// часовой пояс
uchar                   bGmtGps;

// график коррекции времени
bool                    mpboScheduleGps[48];

// счётчики событий
uint                    mpcwGpsStatus20[20];

// значения времени до/после последней коррекции
time                    tiPrevCorrect, tiPostCorrect;

// признак использования сезонного времени при расчете местного времени
bool                    boSeasonGps;

// буфер значения сезона
uchar                   bSeasonCurr;
