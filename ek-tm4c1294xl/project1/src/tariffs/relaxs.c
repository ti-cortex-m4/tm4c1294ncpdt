/*------------------------------------------------------------------------------
RELAXS.C

 ���������
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_tariffs.h"
#include "../flash/files.h"
#include "../time/timedate.h"
#include "tariffs.h"
#include "relaxs.h"



file const              flRelaxsFlag = {RELAXS_FLAG, &boRelaxsFlag, sizeof(bool)};
file const              flRelaxsTariff = {RELAXS_TARIFF, &ibRelaxsTariff, sizeof(uchar)};
file const              flRelaxs = {RELAXS_TARIFF, &reRelaxs, sizeof(relaxs)};



void    InitRelaxs(void)
{
	LoadFile(&flRelaxsFlag);
	LoadFile(&flRelaxsTariff);
	LoadFile(&flRelaxs);
}


void    ResetRelaxs(void)
{
  boRelaxsFlag = false;
  SaveFile(&flRelaxsFlag);

  ibRelaxsTariff = 1;
  SaveFile(&flRelaxsTariff);

  memset(&reRelaxs, 0, sizeof(relaxs));
	SaveFile(&flRelaxs);
}


void    DefaultRelaxs(void)
{
static uchar const  mpRelaxs[8*3] = {
	1,  1,  2,
  2,  1,  2,
  7,  1,  2,
  8,  3,  2,
  1,  5,  2,
  9,  5,  2,
  7, 11,  2,
 25, 12,  2
};

uchar  i, j;

  memset(&reRelaxs, 0, sizeof(relaxs));

  SetRelaxSize(0);

  j = 0;
  for (i=0; i<sizeof(mpRelaxs)/3; i++)
  {
    tiRelax.bDay    = mpRelaxs[j++];
    tiRelax.bMonth  = mpRelaxs[j++];
    tiRelax.bSecond = mpRelaxs[j++];  // ��� ���������: �����, �������, �����������

    SetRelaxDate(i);
    SetRelaxSize(GetRelaxSize() + 1);
  }

	SaveFile(&flRelaxs);
}



uchar   GetRelaxSize(void)
{
  return reRelaxs.bSize;
}


void    SetRelaxSize(uchar  bSize)
{
  reRelaxs.bSize = bSize;
}



void    GetRelaxDate(uchar  ibRelax)
{
  tiRelax = reRelaxs.mptiDate[ibRelax];
}


void    SetRelaxDate(uchar  ibRelax)
{
  reRelaxs.mptiDate[ibRelax] = tiRelax;
}



// ���������� ��� ��� ������
uchar   GetMode(time  ti)
{
uchar  i;

  if (bOldTrfMode == 0)                // ��� ����� �������� � ����������� ����
    return(0);                          // �����

  for (i=0; i<GetRelaxSize(); i++)
  {
    GetRelaxDate(i);

    if ((tiRelax.bDay   == ti.bDay) &&
        (tiRelax.bMonth == ti.bMonth))
      return(tiRelax.bSecond);          // ��� �������� ��� ������������ �� ������ ����������
  }

  i = GetWeekdayYMD(ti.bYear, ti.bMonth, ti.bDay);

  if (i < 5)  return(0);                // �����
  else 
  if (i == 5) return(1);                // �������
  else        return(2);                // �����������
}
