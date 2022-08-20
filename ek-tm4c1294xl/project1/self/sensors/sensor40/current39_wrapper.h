/*------------------------------------------------------------------------------
current39_wrapper.h


------------------------------------------------------------------------------*/

#ifndef __CURRENT39_WRAPPER
#define __CURRENT39_WRAPPER


#define CURRENT39_REPEAT_OR_ERROR(error, method, action) { Error40(error); if (cbRepeat == 0) ErrorCurrent(); else { ErrorLink(); cbRepeat--; method; SetCurr(action); } }


#endif



void    ClearLine39(void);
uchar   IncLine39(void);
uchar   GetLine39(void);

void    DISC_Current39(void);
void    SNRM_Current39(void);
void    AARQ_Current39(void);
void    RR_Current39(void);

bool    ValidateFrame_Current39(void);

void    QueryValue_Current39(void);
bool    ReadValue_Current39(void);

void    QueryScaler_Current39(void);
bool    ReadScaler_Current39(void);

void    ReadCurrent39(void);
