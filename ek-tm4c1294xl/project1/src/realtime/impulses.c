/*------------------------------------------------------------------------------
IMPULSES.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy.h"
#include        "realtime.h"



static volatile bool    fImpulses = false;



void    EnableImpulses(void)
{
	fImpulses = true;
}


void    DisableImpulses(void)
{
	fImpulses = false;
}



void    Impulses_Timer1(void)
{
	if (fImpulses)
	{
		mpwImpMntCan[ibSoftMnt][0]++;
	}
}
