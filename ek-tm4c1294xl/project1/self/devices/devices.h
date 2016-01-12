/*------------------------------------------------------------------------------
DEVICES!H


------------------------------------------------------------------------------*/

extern  uchar                   cbRepeat, cbRepeat2;

extern  uchar                   cbCorrects;

extern  uchar                   ibDig;

extern  time                    tiDig, tiDigPrev;

extern  extended                exExtended;

extern  bool                    fConnect;

extern  uchar                   cbWaitOnline;

extern  bool                    fKeyOn;



void    ShowProgressDigHou(void);

bool    MakeStopHou(uint  wAdd);
bool    MakeStopHou2(uint  wAdd, uint  wRel);

void    RunDevices(void);
