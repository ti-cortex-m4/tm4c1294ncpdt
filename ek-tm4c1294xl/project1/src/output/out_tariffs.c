/*------------------------------------------------------------------------------
 OUT_TARIFFS.C

TODO ������ ������� �������� �� modes
 ------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_tariffs.h"
#include        "../keyboard.h"
#include        "../ports.h"
#include        "../access.h"
#include        "../flash/files.h"
#include        "../tariffs/tariffs.h"
#include        "../tariffs/oldtariffs.h"
#include        "../tariffs/zones.h"



void    OutGetPublicTariffs(void)
{
	LongResult(fPublicTariffsCurr);
}


void    OutSetPublicTariffs(void)
{
	if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
	{
		if ((bInBuff5 == true) || (bInBuff5 == false))
		{
			fPublicTariffsCurr = bInBuff5;
			SaveFile(&flPublicTariffs);
			Result(bRES_OK);
		}
		else Result(bRES_BADDATA);
	}
	else Result(bRES_NEEDREPROGRAM);
}



void    OutGetNewPowTariffs(void)
{
	if (fPublicTariffsCurr == false)
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
zones  zo;

	if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
	{
		if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
		{
			InitPop(7);
			Pop(&zo, sizeof(zones));

			if (TrueZone() == 1)
			{
				SetZonesPowMonthsMode(bInBuff5, bInBuff5, bInBuff6, &zo);
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
	if (fPublicTariffsCurr == false)
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
zones  zo;

	if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
	{
		if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
		{
			InitPop(7);
			Pop(&zo, sizeof(zones));

			if (TrueZone() == 1)
			{
				SetZonesEngMonthsMode(bInBuff5, bInBuff5, bInBuff6, &zo);
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
	if (fPublicTariffsCurr == true)
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
zones  zo;

	if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
	{
		if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
		{
			InitPop(7);
			Pop(&zo, sizeof(zones));

			if (TrueZone() == 1)
			{
				SetZonesPowMonthsMode(bInBuff5, bInBuff5, bInBuff6, &zo);
				SetZonesEngMonthsMode(bInBuff5, bInBuff5, bInBuff6, &zo);
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
