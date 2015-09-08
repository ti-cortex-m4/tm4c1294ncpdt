/*------------------------------------------------------------------------------
KEYBOARD.H


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../include/programs.h"
#include "../time/delay.h"
#include "../hardware/beep.h"



extern  uchar const             mpbKeys[];

extern  volatile uchar          bKey;
extern  volatile bool           fKey;

extern  key                     enKeyboard;

extern  uint                    wProgram;

extern  uchar                   ibX, ibY;



void    InitKeyboard(void);
void    ResetKeyboard(void);

void    NoProgram(void);
void    BlockProgram(uchar  bA);
void    BlockProgram2(uint  wA, bool fBeep);
void    BlockProgramExt(uchar  bA);
void    BlockPrograms(uchar  bA, uchar  bB);
void    NeedProgram(uchar  bA);
void    NeedPrograms(uchar  bA, uchar  bB);

void    RunKeyboard(void);

