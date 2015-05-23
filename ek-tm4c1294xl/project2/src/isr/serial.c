/*------------------------------------------------------------------------------
SERIAL,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "serial.h"



const uchar             szPacketCRC[bPACKET_HEADER] = {0xCA, 0xE0, 0xEB, 0xFE, 0xEC, 0xED, 0xFB, 0x20};

const uchar             szPacketCtrlZ[1] = { 0x1A };
