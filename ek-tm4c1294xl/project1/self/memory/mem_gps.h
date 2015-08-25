/*------------------------------------------------------------------------------
MEM_GPS.H


------------------------------------------------------------------------------*/

extern  uchar                   bPortGps;

extern  uchar                   bStatusGps;

extern  uchar                   bVersionMaxGps, bVersionMinGps;

extern  time                    tiGps;

extern  uchar                   bGmtGps;

extern  bool                    mpboScheduleGps[48];

extern  uint                    mpcwGpsStatus[20];

extern  time                    tiPrevCorrect, tiPostCorrect;

extern  bool                    boSeasonGps;

extern  uchar                   bSeasonCurr;
