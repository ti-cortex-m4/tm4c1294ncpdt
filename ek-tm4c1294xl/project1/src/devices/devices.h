/*------------------------------------------------------------------------------
DIGITALS_RUN.H


------------------------------------------------------------------------------*/

extern  uchar                   ibDig;

extern  extended                exExtended;

extern  bool                    fConnect;

extern  uchar                   cbWaitOnline;

extern  bool                    fKeyOn;



extern  file const              flSeparateCan;
extern  file const              flHideMessages;



void    InitDevices(void);
void    ResetDevices(void);

void    RunDevices(void);
