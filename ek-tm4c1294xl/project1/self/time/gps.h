/*------------------------------------------------------------------------------
GPS.H


------------------------------------------------------------------------------*/

extern  static char const       szTimeGPS[],
                                szDeltaTimeGPS[],
                                szTimeDateGPS[],
                                szVersionGPS[],
                                szBadTimeDateGPS[],
                                szBadDateGPS[],
                                szBadTimeGPS[];


void    InitGPS(void);
void    ResetGPS(void);

bool    ShowStatusGPS(void);
uchar   ReadTimeDateGPS(void);
void    ShowTimeDateGPS(bool  fShow);

void    SetupTimeGPS(void);
void    CorrectTimeGPS(void);

void    RunGPS(void);

