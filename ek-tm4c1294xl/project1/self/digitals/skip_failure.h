/*------------------------------------------------------------------------------
skip_failure.h


------------------------------------------------------------------------------*/

extern  cache const             chSkipFailureEnbl;
extern  cache const             chSkipFailureRepeats;



void    InitSkipFailure(void);
void    ResetSkipFailure(void);

bool    SkipFailureEnbl(void);

void    SkipFailure_Start(void);
void    SkipFailure_Success(void);
void    SkipFailure_Failure(void);
bool    SkipFailure_IsFailure(void);

bool    SkipFailure_IsCustomRepeats(void);
uchar   MaxRepeatsSkipFailure(void);
