/*------------------------------------------------------------------------------
link_up_reset.c


------------------------------------------------------------------------------*/

#include "../main.h"
//#include "../hardware/delay.h"
//#include "../hardware/hardware_restart.h"
//#include "../kernel/settings.h"
//#include "../kernel/log.h"
//#include "clock.h"
#include "link_up_reset.h"



static uint8_t cbLinkUpReset;



void InitLinkUpReset(void) {
    cbLinkUpReset = 10;
}


void LinkUpReset_Start(void) {
    cbLinkUpReset = 9;
}


void LinkUpReset_1Hz(void) {
    if (cbLinkUpReset != 10) && (cbLinkUpReset > 0) {
        cbLinkUpReset--;
    }
}


void RunLinkUpReset(void) {
    if (cbLinkUpReset == 0) {
        CONSOLE("link up restart \n");
        DelayMilliSecond(100);
        Restart();
    }
}
