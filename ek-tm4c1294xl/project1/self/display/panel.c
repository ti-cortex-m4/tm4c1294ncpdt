/*------------------------------------------------------------------------------
panel.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../output/response_crc.h"
#include "../output/esc/response_esc.h"
#include "panel.h"



#ifdef NO_DISPLAY
void    RunPanel(void)
{
  RunResponseCRC_All_Panel();
  RunResponseEsc_All_Panel(); // TODO
}
#endif
