/*------------------------------------------------------------------------------
SERIALS.H


------------------------------------------------------------------------------*/

extern  bool                    fSerialsManual;
extern  ulong                   mdwSerialValues[bCANALS];
extern  bool                    mfSerialFlags[bCANALS];


extern  cache const             chSerialsManual;
extern  cache const             chSerialValues;
extern  cache const             chSerialFlags;



void    InitSerials(void);
void    ResetSerials(void);

void    SaveSerial(uchar  ibDig, ulong  dwSerial);
void    ShowSerial(ulong  dwSerial);
