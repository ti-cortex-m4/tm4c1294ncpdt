/*------------------------------------------------------------------------------
DEVICE_Q.H


------------------------------------------------------------------------------*/

#define Q_LINES   4

double  PopDoubleQ(void);

void    QueryCloseQ(void);
void    QueryOptionQ(void);
void    QueryCorrectQ(void);
void    QueryEnergyAbsQ(void);
void    QueryEnergyDayQ(void);
void    QueryEnergyMonQ(void);
void    QueryEnergySpecQ(void);
void    ReadEnergyQ(void);

void    InitHeaderQ(void);
void    QueryHeaderQ(void);
void    ReadHeaderQ(void);
bool    ReadDataQ(void);

void    ReadCurrentQ(void);



