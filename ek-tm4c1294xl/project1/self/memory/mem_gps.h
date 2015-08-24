/*------------------------------------------------------------------------------
MEM_GPS.H


------------------------------------------------------------------------------*/

extern  uchar                   bPortGps;

extern  uchar                   bStatusGps;

extern  uchar                   bVersionMaxGps, bVersionMinGps;

extern  time                    tiGps;

extern  uchar                   bGmtGps;

extern  bool                    mpboGpsSchedule[48];

extern  uint                    mpcwGpsSchedule[20];

extern  time                    tiPrevCorrect, tiPostCorrect;

extern  bool                    boSeasonGps;

extern  uchar                   bSeasonCurr;
