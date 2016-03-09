/*------------------------------------------------------------------------------
serials.h


------------------------------------------------------------------------------*/

extern  bool                    fSerialsManual;
extern  ulong                   mdwSerialValues[bCANALS];
extern  time                    mtiSerialTimes[bCANALS];
extern  bool                    mfSerialFlags[bCANALS];


extern  cache const             chSerialsManual;
extern  cache const             chSerialValues;
extern  cache const             chSerialTimes;
extern  cache const             chSerialFlags;



void    InitSerials(void);
void    ResetSerials(void);

void    ProcessSerial(uchar  ibDig, ulong  dwSerial);
