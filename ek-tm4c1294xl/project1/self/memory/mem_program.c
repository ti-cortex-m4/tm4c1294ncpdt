/*------------------------------------------------------------------------------
MEM_PROGRAM.C


------------------------------------------------------------------------------*/

#include "../main.h"



// флаги задания соответствующих программ
bool                    boSetTime,
                        boSetDate,
                        boSetGroups,
                        boSetPassword;

// TODO: SaveFile
bool                    boFirstReset;

//
bool                    boEnblWatchdog;

//
uint                    cwWrnResetWDT;
