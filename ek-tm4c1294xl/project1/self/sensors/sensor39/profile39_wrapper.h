/*------------------------------------------------------------------------------
profile39_wrapper.h


------------------------------------------------------------------------------*/

void    DISC_Profile39(void);
void    AARQ_Profile39(void);
void    RR_Profile39(void);

bool    ValidateFrame_Profile39(void);

void    QueryTime_Profile39(void);
void    ReadTime_Profile39(void);

void    QueryScaler_Profile39(void);
bool    ReadScaler_Profile39(void);

void    InitProfile39_Profile(void);
void    QueryProfile39_Profile(void);

void    Read1_Profile(void);
void    Read2_Profile(void);
void    Read3_Profile(void);

bool    UseBlocks_Profile(void);
void    QueryNextBlock39_Profile(void);

void    Read4_Profile(void);
void    Read5_Profile(void);

bool2   FinishProfile_Profile39(void);
