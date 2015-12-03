/*------------------------------------------------------------------------------
DEVICE_Q!H


------------------------------------------------------------------------------*/

#define Q_LINES   4



double  PopDoubleQ(void);

void    QueryCloseQ(void);
void    QueryOptionQ(void);
void    QueryCorrectQ(void);
void    QueryEnergyAbsQ(void);
void    QueryEnergyDayQ(time  ti);
void    QueryEnergyMonQ(time  ti);
void    QueryEnergySpecQ(void);
void    ReadEnergyQ(void);

void    InitHeaderQ(void);
void    QueryHeaderQ(void);
void    ReadHeaderQ(void);
bool    ReadDataQ(void);

void    ReadCurrentQ(void);



