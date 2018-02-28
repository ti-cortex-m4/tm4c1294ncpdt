/*------------------------------------------------------------------------------
panel.c


------------------------------------------------------------------------------*/

//#include <stdint.h>
//#include <stdbool.h>
//#include "driverlib/interrupt.h"
#include "../main.h"
//#include "../serial/speeds.h"
//#include "../hardware/system_clock.h"
//#include "../hardware/watchdog.h"
//#include "../isr/timer0.h"
//#include "../isr/timer1.h"
//#include "../isr/timer2.h"
//#include "../isr/timer3.h"
//#include "../isr/serial0.h"
//#include "../isr/serial1.h"
//#include "../isr/serial2.h"
//#include "../isr/serial3.h"
#include "../output/response_crc.h"
#include "../output/esc/response_esc.h"
//#include "../display/display.h"
//#include "../display/messages.h"
#include "panel.h"



#ifdef NO_DISPLAY

void    StartPanel(void)
{
}


void    RunPanel(void)
{
  RunResponseCRC_All_Panel(); // TODO
  RunResponseEsc_All_Panel(); // TODO
}

#endif
