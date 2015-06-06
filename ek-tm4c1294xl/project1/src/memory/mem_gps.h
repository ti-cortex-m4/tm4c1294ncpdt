/*------------------------------------------------------------------------------
MEM_GPS.H


------------------------------------------------------------------------------*/

extern  uchar                   bPortGPS;

extern  uchar                   bStatusGPS, bVersionMaxGPS, bVersionMinGPS;

extern  time                    tiGPS;

extern  uchar                   bGMT;

extern  bool                    mpboGPSRun[48];

extern  uint                    mpcwGPSRun[20];

extern  time                    tiPrevCorrect, tiPostCorrect;

extern  bool                    boSeasonGPS;

extern  uchar                   bSeasonCurr;
