/*------------------------------------------------------------------------------
DEVICE_Q!H


------------------------------------------------------------------------------*/

#define MAX_LINE_Q      4



extern  uchar                   ibLineQ;



double  PopDoubleQ(void);
double  PopDoubleQ_WithSign(void);
ulong   PopLongQ(void);

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
void    ReadHeaderQ(uchar  ibLine);
bool    ReadDataQ(void);

void    ReadCurrentQ(void);



