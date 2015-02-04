/*------------------------------------------------------------------------------
 OUT_TARIFFS.C

TODO SaveTariffs
 ------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_tariffs.h"
#include        "../keyboard.h"
#include        "../ports.h"
#include        "../access.h"
#include        "../tariffs/tariffs.h"
#include        "../tariffs/oldtariffs.h"
#include        "../tariffs/zones.h"



void    OutGetPublic(void)
{
	LongResult(boPublicCurr);
}


void    OutSetPublic(void)
{
	if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
	{
		if ((bInBuff5 == true) || (bInBuff5 == false))
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
	if ((boPublicCurr == false) || (SuperUser() == 1))
	{
		if (bInBuff5 < 12)
			Common(PGetZonePowMonthMode(bInBuff5, 0), sizeof(zones));
		else
			Result(bRES_BADDATA);
	}
	else Result(bRES_BADMODE);
}


void    OutSetOldPowTariffs(void)
{
uchar  chOldMode;

	if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
	{
		if (bInBuff5 < 12)
		{
			InitPop(7);
			Pop(&zoKey, sizeof(zones));

			if (TrueZone() == 1)
			{
				chOldMode = '_';
				SetCharPowMonths(bInBuff5, bInBuff5, &zoKey, chOldMode);
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
	if ((boPublicCurr == false) || (SuperUser() == 1))
	{
		if (bInBuff5 < 12)
			Common(PGetZoneEngMonthMode(bInBuff5, 0), sizeof(zones));
		else
			Result(bRES_BADDATA);
	}
	else Result(bRES_BADMODE);
}


void    OutSetOldEngTariffs(void)
{
uchar  chOldMode;

	if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
	{
		if (bInBuff5 < 12)
		{
			InitPop(7);
			Pop(&zoKey, sizeof(zones));

			if (TrueZone() == 1)
			{
				chOldMode = '_';
				SetCharEngMonths(bInBuff5, bInBuff5, &zoKey, chOldMode);
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
	if ((boPublicCurr == true) || (SuperUser() == 1))
	{
		if (bInBuff5 < 12)
			Common(PGetZonePowMonthMode(bInBuff5, 0), sizeof(zones));
		else
			Result(bRES_BADDATA);
	}
	else Result(bRES_BADMODE);
}


void    OutSetOldPubTariffs(void)
{
uchar  chOldMode;

	if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
	{
		if (bInBuff5 < 12)
		{
			InitPop(7);
			Pop(&zoKey, sizeof(zones));

			if (TrueZone() == 1)
			{
				chOldMode = '_';
				SetCharPowMonths(bInBuff5, bInBuff5, &zoKey, chOldMode);
				SetCharEngMonths(bInBuff5, bInBuff5, &zoKey, chOldMode);
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
	if (boPublicCurr == false)
	{
		if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
			Common(PGetZonePowMonthMode(bInBuff5, bInBuff6), sizeof(zones));
		else
			Result(bRES_BADDATA);
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
				SetZonesPowMonthsMode(bInBuff5, bInBuff5, bInBuff6, &zoKey);
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
	if (boPublicCurr == false)
	{
		if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
			Common(PGetZoneEngMonthMode(bInBuff5, bInBuff6), sizeof(zones));
		else
			Result(bRES_BADDATA);
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
				SetZonesEngMonthsMode(bInBuff5, bInBuff5, bInBuff6, &zoKey);
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
	if (boPublicCurr == true)
	{
		if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
			Common(PGetZonePowMonthMode(bInBuff5, bInBuff6), sizeof(zones));
		else
			Result(bRES_BADDATA);
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
				SetZonesPowMonthsMode(bInBuff5, bInBuff5, bInBuff6, &zoKey);
				SetZonesEngMonthsMode(bInBuff5, bInBuff5, bInBuff6, &zoKey);
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
