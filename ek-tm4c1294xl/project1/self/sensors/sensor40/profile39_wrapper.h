/*------------------------------------------------------------------------------
profile40_wrapper.h


------------------------------------------------------------------------------*/

#ifndef __PROFILE40_WRAPPER
#define __PROFILE40_WRAPPER


#define PROFILE40_REPEAT_OR_ERROR(error, method, action) { Error40(error); if (cbRepeat == 0) ErrorProfile(); else { ErrorLink(); cbRepeat--; method; SetCurr(action); } }


#endif



void    DISC_Profile40(void);
void    SNRM_Profile40(void);
void    AARQ_Profile40(void);
void    RR_Profile40(void);

bool    ValidateFrame_Profile40(void);

void    QueryTime_Profile40(void);
void    ReadTime_Profile40(void);

void    SetCorrectSecond40(sint  ddw);
void    QueryCorrect_Profile40(void);

void    QueryScaler_Profile40(void);
bool    ReadScaler_Profile40(void);

void    InitProfile_Profile40(void);
void    QueryProfile_Profile40(void);

void    Read1_Profile(void);
void    Read2_Profile(void);
void    Read3_Profile(void);

bool    UseBlocks_Profile40(void);
void    QueryNextBlock_Profile40(void);

void    Read4_Profile(void);
void    Read5_Profile(void);

bool2   FinishProfile_Profile40(void);
