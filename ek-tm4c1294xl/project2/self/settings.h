/*------------------------------------------------------------------------------
SETTINGS.H


------------------------------------------------------------------------------*/

#include "main.h"



extern uint32_t dwIP;
extern uint32_t dwGateway;
extern uint32_t dwNetmask;



void InitSettings(void);
uint32_t SaveSettings(void);
uint32_t LoadSettings(void);
