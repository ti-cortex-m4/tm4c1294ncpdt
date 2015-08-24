/*------------------------------------------------------------------------------
GPS.H


------------------------------------------------------------------------------*/

#include "../memory/mem_gps.h"



extern  char const              szTimeGPS[],
                                szDeltaTimeGPS[],
                                szTimeDateGPS[],
                                szVersionGPS[],
                                szBadTimeDateGPS[],
                                szBadDateGPS[],
                                szBadTimeGPS[];


extern  cache const             chPortGps;
extern  cache const             chGmtGps;
extern  cache const             chSeasonGps;
extern  cache const             chScheduleGps;



void    InitGps(void);
void    ResetGps(void);

bool    ShowStatusGps(void);
time2   ReadTimeDateGps(void);
void    ShowTimeDateGps(bool  fShowTimeDate);

void    SetupTimeGPS(void);
void    CorrectTimeGPS(void);

void    RunGPS(void);

