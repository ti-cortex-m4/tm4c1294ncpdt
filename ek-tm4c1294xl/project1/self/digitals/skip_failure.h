/*------------------------------------------------------------------------------
skip_failure.h


------------------------------------------------------------------------------*/

extern  cache const             chSkipFailure;



void    InitSkipFailure(void);
void    ResetSkipFailure(void);

bool    SkipFailureEnbl(void);

void    SkipFailure_Start(void);
void    SkipFailure_Success(void);
void    SkipFailure_Failure(void);
bool    SkipFailure_IsFailure(void);
