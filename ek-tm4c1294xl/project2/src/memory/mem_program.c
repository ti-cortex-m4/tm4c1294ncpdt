/*------------------------------------------------------------------------------
MEMORY_PROGRAM.C


------------------------------------------------------------------------------*/

#include "../main.h"



// флаги задания соответствующих программ
boolean                 boSetTime,
                        boSetDate,
                        boSetGroups,
                        boSetPassword;

// TODO: SaveFile
boolean                 boFirstReset;

// режим работы прибора
global                  enGlobal;
