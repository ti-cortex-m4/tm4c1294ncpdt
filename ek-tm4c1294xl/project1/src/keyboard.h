/*------------------------------------------------------------------------------
KEYBOARD.H


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_settings.h"
#include        "include/programs.h"
#include        "include/programs2.h"
#include        "delay.h"
#include        "beep.h"



extern  uchar const             mpbKeys[];

extern  uchar                   bKey;
extern  bool                    fKey;

extern  key                     enKeyboard;

extern  uchar                   bProgram;
extern  uint                    wProgram;

extern  time                    tiKey;

extern  uchar                   ibX, ibY, ibZ;

extern  volatile bool           fUpdateA, fUpdateB;



void    InitKeyboard(void);
void    ResetKeyboard(void);

void    NoProgram(void);
void    NoProgram2(void);
void    BlockProgram(uchar  bA);
void    BlockProgram2(uint  wA, bool fBeep);
void    BlockProgramExt(uchar  bA);
void    BlockPrograms(uchar  bA, uchar  bB);
void    NeedProgram(uchar  bA);
void    NeedPrograms(uchar  bA, uchar  bB);

void    Keyboard(void);

