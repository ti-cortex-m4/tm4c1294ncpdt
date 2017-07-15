/*------------------------------------------------------------------------------
DIAGRAM!H


------------------------------------------------------------------------------*/

extern cache const             chEnblDiagram;



void    InitDiagram(void);
void    ResetDiagram(void);

bool    ClearDiagram(void);

void    MakeDiagram(uchar  ibCan, double  db);
void    NextHouDiagram(void);

void    OutDiagram(bool  fDouble);
