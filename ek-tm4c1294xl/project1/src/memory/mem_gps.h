/*------------------------------------------------------------------------------
MEM_GPS.H


------------------------------------------------------------------------------*/

extern  uchar                   bPortGPS;

extern  uchar                   bStatusGPS, bVersionMaxGPS, bVersionMinGPS;

extern  time                    tiGPS;

extern  uchar                   bGMT;

extern  boolean                 mpboGPSRun[48];

extern  uint                    mpcwGPSRun[20];

extern  time                    tiPrevCorrect, tiPostCorrect;

extern  boolean                 boSeasonGPS;

extern  uchar                   bSeasonCurr;
