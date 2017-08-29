/*------------------------------------------------------------------------------
skip_failure.h


------------------------------------------------------------------------------*/

extern  cache const             chSkipFailureEnbl;
extern  cache const             chSkipFailureRepeats;



void    InitSkipFailure(void);
void    ResetSkipFailure(void);

bool    SkipFailureEnbl(void);
uchar   SkipFailureRepeats(void);

void    SkipFailure_BeforeExtended(void);
void    SkipFailure_AfterExtended(void);

void    SkipFailure_InputStart(void);
void    SkipFailure_InputGoodCheck(void);

bool    SkipFailure_IsFailure(void);
bool    SkipFailure_IsFailureMsg(void);

bool    SkipFailure_IsReducedRepeats(void);
