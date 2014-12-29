/*------------------------------------------------------------------------------
SLIDE.H


------------------------------------------------------------------------------*/

extern  bool                    fSlide;
extern  uchar                   **ppszCurr;
extern  uchar                   **ppszFirst;

void    InitSlide(void);
void    LoadSlide(char  *ppszT[]);
void    ShowSlide(char  szT[]);
