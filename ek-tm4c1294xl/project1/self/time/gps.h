/*------------------------------------------------------------------------------
GPS.H


------------------------------------------------------------------------------*/

extern  char const              szTimeGPS[],
                                szDeltaTimeGPS[],
                                szTimeDateGPS[],
                                szVersionGPS[],
                                szBadTimeDateGPS[],
                                szBadDateGPS[],
                                szBadTimeGPS[];


void    InitGPS(void);
void    ResetGPS(void);

bool    ShowStatusGPS(void);
time2   ReadTimeDateGPS(void);
void    ShowTimeDateGPS(bool  fShowTimeDate);

void    SetupTimeGPS(void);
void    CorrectTimeGPS(void);

void    RunGPS(void);

