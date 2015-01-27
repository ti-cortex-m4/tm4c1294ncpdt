/*------------------------------------------------------------------------------
 OUT_TARIFFS.C

TODO SaveTariffs
 ------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../ports.h"
#include        "../tariffs.h"



void    OutGetPublic(void)
{
	LongResult(boPublicCurr);
}


void    OutSetPublic(void)
{
	if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
	{
		if ((bInBuff5 == boTrue) || (bInBuff5 == boFalse))
		{
			boPublicCurr = bInBuff5;
			Result(bRES_OK);
		}
		else Result(bRES_BADDATA);
	}
	else Result(bRES_NEEDREPROGRAM);
}



void    OutGetOldMode(void)
{
	LongResult(bOldMode);
}


void    OutSetOldMode(void)
{
	if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
	{
		if (bInBuff5 <= bMAXOLDMODES)
		{
			MakeAllOldModes(bInBuff5);
			Result(bRES_OK);
		}
		else Result(bRES_BADDATA);
	}
	else Result(bRES_NEEDREPROGRAM);
}



void    OutGetOldPowTariffs(void)
{
	if ((boPublicCurr == boFalse) || (SuperUser() == 1))
	{
		if (bInBuff5 < 12)
		{
			ibMonth = bInBuff5;
			ibMode = 0;
			Common(PGetZonePowMonthMode(), sizeof(zones));
		}
		else Result(bRES_BADDATA);
	}
	else Result(bRES_BADMODE);
}


void    OutSetOldPowTariffs(void)
{
	if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
	{
		if (bInBuff5 < 12)
		{
			InitPop(7);
			Pop(&zoKey, sizeof(zones));

			if (TrueZone() == 1)
			{
				chOldMode = '_';
				SetCharPowMonths(bInBuff5, bInBuff5);
				LongResult(bRES_OK);
			}
			else Result(bRES_BADDATA);
		}
		else Result(bRES_BADADDRESS);
	}
	else Result(bRES_NEEDREPROGRAM);
}



void    OutGetOldEngTariffs(void)
{
	if ((boPublicCurr == boFalse) || (SuperUser() == 1))
	{
		if (bInBuff5 < 12)
		{
			ibMonth = bInBuff5;
			ibMode = 0;
			Common(PGetZoneEngMonthMode(), sizeof(zones));
		}
		else Result(bRES_BADDATA);
	}
	else Result(bRES_BADMODE);
}


void    OutSetOldEngTariffs(void)
{
	if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
	{
		if (bInBuff5 < 12)
		{
			InitPop(7);
			Pop(&zoKey, sizeof(zones));

			if (TrueZone() == 1)
			{
				chOldMode = '_';
				SetCharEngMonths(bInBuff5, bInBuff5);
				LongResult(bRES_OK);
			}
			else Result(bRES_BADDATA);
		}
		else Result(bRES_BADADDRESS);
	}
	else Result(bRES_NEEDREPROGRAM);
}



void    OutGetOldPubTariffs(void)
{
	if ((boPublicCurr == boTrue) || (SuperUser() == 1))
	{
		if (bInBuff5 < 12)
		{
			ibMonth = bInBuff5;
			ibMode = 0;
			Common(PGetZonePowMonthMode(), sizeof(zones));
		}
		else Result(bRES_BADDATA);
	}
	else Result(bRES_BADMODE);
}


void    OutSetOldPubTariffs(void)
{
	if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
	{
		if (bInBuff5 < 12)
		{
			InitPop(7);
			Pop(&zoKey, sizeof(zones));

			if (TrueZone() == 1)
			{
				chOldMode = '_';
				SetCharPowMonths(bInBuff5, bInBuff5);
				SetCharEngMonths(bInBuff5, bInBuff5);
				LongResult(bRES_OK);
			}
			else Result(bRES_BADDATA);
		}
		else Result(bRES_BADADDRESS);
	}
	else Result(bRES_NEEDREPROGRAM);
}



void    OutGetNewPowTariffs(void)
{
	if (boPublicCurr == boFalse)
	{
		if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
		{
			ibMonth = bInBuff5;
			ibMode = bInBuff6;
			Common(PGetZonePowMonthMode(), sizeof(zones));
		}
		else Result(bRES_BADDATA);
	}
	else Result(bRES_BADMODE);
}


void    OutSetNewPowTariffs(void)
{
	if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
	{
		if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
		{
			InitPop(7);
			Pop(&zoKey, sizeof(zones));

			if (TrueZone() == 1)
			{
				ibMode = bInBuff6;
				SetZonesPowMonthsMode(bInBuff5, bInBuff5);
				LongResult(bRES_OK);
			}
			else Result(bRES_BADDATA);
		}
		else Result(bRES_BADADDRESS);
	}
	else Result(bRES_NEEDREPROGRAM);
}



void    OutGetNewEngTariffs(void)
{
	if (boPublicCurr == boFalse)
	{
		if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
		{
			ibMonth = bInBuff5;
			ibMode = bInBuff6;
			Common(PGetZoneEngMonthMode(), sizeof(zones));
		}
		else Result(bRES_BADDATA);
	}
	else Result(bRES_BADMODE);
}


void    OutSetNewEngTariffs(void)
{
	if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
	{
		if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
		{
			InitPop(7);
			Pop(&zoKey, sizeof(zones));

			if (TrueZone() == 1)
			{
				ibMode = bInBuff6;
				SetZonesEngMonthsMode(bInBuff5, bInBuff5);
				LongResult(bRES_OK);
			}
			else Result(bRES_BADDATA);
		}
		else Result(bRES_BADADDRESS);
	}
	else Result(bRES_NEEDREPROGRAM);
}



void    OutGetNewPubTariffs(void)
{
	if (boPublicCurr == boTrue)
	{
		if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
		{
			ibMonth = bInBuff5;
			ibMode = bInBuff6;
			Common(PGetZonePowMonthMode(), sizeof(zones));
		}
		else Result(bRES_BADDATA);
	}
	else Result(bRES_BADMODE);
}


void    OutSetNewPubTariffs(void)
{
	if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
	{
		if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
		{
			InitPop(7);
			Pop(&zoKey, sizeof(zones));

			if (TrueZone() == 1)
			{
				ibMode = bInBuff6;
				SetZonesPowMonthsMode(bInBuff5, bInBuff5);
				SetZonesEngMonthsMode(bInBuff5, bInBuff5);
				LongResult(bRES_OK);
			}
			else Result(bRES_BADDATA);
		}
		else Result(bRES_BADADDRESS);
	}
	else Result(bRES_NEEDREPROGRAM);
}



void    OutGetTariffsDay(void)
{
	InitPushPtr();
	Push(&mpibPowCurrTariff, 48);
	Push(&mpibEngCurrTariff, 48);
	OutptrOutBuff(2 * 48);
}
