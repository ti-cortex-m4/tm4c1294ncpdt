/*------------------------------------------------------------------------------
IMPULSES.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy.h"
#include        "../realtime/realtime.h"



volatile bool           fOnImpulse, fOnSecond;

static volatile bool    fEnabledImpulses = false;



void    EnableImpulses(void) {
	fEnabledImpulses = true;
}


void    DisableImpulses(void) {
	fEnabledImpulses = false;
}



void    Impulses_Timer1(void) {
	if (fEnabledImpulses)	{
		fOnImpulse = 1;
		mpwImpMntCan[ibSoftMnt][0]++;
	}
}



void    InitImpulses(void) {
	(enGlobal == GLB_WORK) ? EnableImpulses() : DisableImpulses();
}


void    StartImpulses(void) {
	EnableImpulses();
}
