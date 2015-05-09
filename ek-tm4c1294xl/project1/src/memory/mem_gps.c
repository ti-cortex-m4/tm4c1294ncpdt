/*------------------------------------------------------------------------------
MEM_GPS.C


------------------------------------------------------------------------------*/

#include "../main.h"



// номер порта часов GPS
uchar                   bPortGPS;

// глобальные переменные
uchar                   bStatusGPS, bVersionMaxGPS, bVersionMinGPS;

// глобальная переменная
time                    tiGPS;

// часовой пояс
uchar                   bGMT;

// график коррекции времени
boolean                 mpboGPSRun[48];

// счётчики событий
uint                    mpcwGPSRun[20];

// значения времени до/после последней коррекции
time                    tiPrevCorrect, tiPostCorrect;
