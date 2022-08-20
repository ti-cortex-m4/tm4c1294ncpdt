/*------------------------------------------------------------------------------
profile39_wrapper.h


------------------------------------------------------------------------------*/

#ifndef __PROFILE39_WRAPPER
#define __PROFILE39_WRAPPER


#define PROFILE39_REPEAT_OR_ERROR(error, method, action) { Error40(error); if (cbRepeat == 0) ErrorProfile(); else { ErrorLink(); cbRepeat--; method; SetCurr(action); } }


#endif



void    DISC_Profile39(void);
void    SNRM_Profile39(void);
void    AARQ_Profile39(void);
void    RR_Profile39(void);

bool    ValidateFrame_Profile39(void);

void    QueryTime_Profile39(void);
void    ReadTime_Profile39(void);

void    SetCorrectSecond39(sint  ddw);
void    QueryCorrect_Profile39(void);

void    QueryScaler_Profile39(void);
bool    ReadScaler_Profile39(void);

void    InitProfile_Profile39(void);
void    QueryProfile_Profile39(void);

void    Read1_Profile(void);
void    Read2_Profile(void);
void    Read3_Profile(void);

bool    UseBlocks_Profile39(void);
void    QueryNextBlock_Profile39(void);

void    Read4_Profile(void);
void    Read5_Profile(void);

bool2   FinishProfile_Profile39(void);
