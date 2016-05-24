/*------------------------------------------------------------------------------
DEVICES!H


------------------------------------------------------------------------------*/

extern  uchar                   cbRepeat, cbIteration;

extern  uchar                   cbCorrects;

extern  uchar                   ibDig;

extern  time                    tiDig, tiDigPrev;

extern  extended                exExtended;

extern  bool                    fConnect;

extern  uchar                   cbWaitOnline;

extern  bool                    fKeyOn;



void    ShowProgressDigHou(void);
void    ShowProfileTime(time  ti);

bool    MakeStopHou(uint  wAdd);
bool    MakeStopHou2(uint  wAdd, uint  wRel);

void    RunDevices(void);
