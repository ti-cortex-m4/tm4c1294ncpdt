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


extern  cache const             chPortGPS;
extern  cache const             chGMT;



void    InitGPS(void);
void    ResetGPS(void);

bool    ShowStatusGPS(void);
time2   ReadTimeDateGPS(void);
void    ShowTimeDateGPS(bool  fShowTimeDate);

void    SetupTimeGPS(void);
void    CorrectTimeGPS(void);

void    RunGPS(void);

