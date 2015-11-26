/*------------------------------------------------------------------------------
BULK!H


------------------------------------------------------------------------------*/

#define ENABLE_BULK



extern  cache const             chBulkEnbl;
extern  cache const             chBulkSize;
extern  cache const             chBulkMaxDelay;



void    InitBulk(void);
void    ResetBulk(void);

void    AnswerBulk0(void);
void    AnswerBulk1(void);
void    AnswerBulk2(void);
void    AnswerBulk3(void);

void    OutByteBulk0(void);
void    OutByteBulk1(void);
void    OutByteBulk2(void);
void    OutByteBulk3(void);

void    RunBulk0(void);
void    RunBulk1(void);
void    RunBulk2(void);
void    RunBulk3(void);

void    OutBulk(void);
