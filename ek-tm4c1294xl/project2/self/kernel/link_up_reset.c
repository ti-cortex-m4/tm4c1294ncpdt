/*------------------------------------------------------------------------------
link_up_reset.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/delay.h"
#include "../hardware/restart.h"
#include "../kernel/log.h"
#include "link_up_reset.h"



static volatile lur_t   enLinkUpReset;
static volatile uchar   cbLinkUpReset;



void InitLinkUpReset(void) {
    enLinkUpReset = LUR_LINK_UNKNOWN;
    cbLinkUpReset = 10;
}


void LinkUpReset_LinkUp(void) {
    enLinkUpReset = LUR_LINK_UP;
    cbLinkUpReset = 9;
}


void LinkUpReset_LinkDown(void) {
    enLinkUpReset = LUR_LINK_DOWN;
    cbLinkUpReset = 10;
}


void LinkUpReset_1Hz(void) {
    if ((cbLinkUpReset != 10) && (cbLinkUpReset > 0)) {
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
