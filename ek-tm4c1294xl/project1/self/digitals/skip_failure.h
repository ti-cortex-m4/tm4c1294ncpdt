/*------------------------------------------------------------------------------
skip_failure.h


------------------------------------------------------------------------------*/

extern  cache const             chSkipFailureEnbl;
extern  cache const             chSkipFailureRepeats;



void    InitSkipFailure(void);
void    ResetSkipFailure(void);

bool    SkipFailureEnbl(void);

void    SkipFailure_BeforeExtended(void);
void    SkipFailure_AfterExtended(void);

void    SkipFailure_InputStart(void);
void    SkipFailure_InputGoodCheck(void);

bool    SkipFailure_IsFailure(void);

bool    SkipFailure_IsCustomRepeats(void);
uchar   MaxRepeatsSkipFailure(void);
