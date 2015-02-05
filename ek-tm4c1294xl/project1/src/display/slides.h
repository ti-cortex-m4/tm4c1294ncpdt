/*------------------------------------------------------------------------------
SLIDES.H


------------------------------------------------------------------------------*/

extern  bool                    fSlide;
extern  char const              **ppszCurr;
extern  char const              **ppszFirst;



void    InitSlide(void);

void    LoadSlide(char const  *ppszT[]);
void    ShowSlide(char  szT[]);
void    NextSlide(void);
