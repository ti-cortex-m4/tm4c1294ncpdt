/*------------------------------------------------------------------------------
current40_wrapper.h


------------------------------------------------------------------------------*/

#ifndef __CURRENT40_WRAPPER
#define __CURRENT40_WRAPPER


#define CURRENT40_REPEAT_OR_ERROR(error, method, action) { Error40(error); if (cbRepeat == 0) ErrorCurrent(); else { ErrorLink(); cbRepeat--; method; SetCurr(action); } }


#endif



void    ClearLine40(void);
uchar   IncLine40(void);
uchar   GetLine40(void);

void    DISC_Current40(void);
void    SNRM_Current40(void);
void    AARQ_Current40(void);
void    RR_Current40(void);

bool    ValidateFrame_Current40(void);

void    QueryValue_Current40(void);
bool    ReadValue_Current40(void);

void    QueryScaler_Current40(void);
bool    ReadScaler_Current40(void);

void    ReadCurrent40(void);
