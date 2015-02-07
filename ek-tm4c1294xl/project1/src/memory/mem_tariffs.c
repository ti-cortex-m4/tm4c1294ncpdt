/*------------------------------------------------------------------------------
MEM_TARIFFS.S

 TODO add requests for tariffs for all modes
------------------------------------------------------------------------------*/

#include        "../main.h"



// ������ ����������
relax                  mpreRelaxs;

// ���������� ����������
time                    tiRelax;

// ������� ������������� ����������
boolean                 boRelaxsFlag;

// ���������� ����������
uchar                   ibRelaxsTariff;



// ������ �������� �������� �������� �� ������� � ������� ������ (��� �������� � �������)
zone                   mpzoPowMonthMode[12][bMODES],
                        mpzoEngMonthMode[12][bMODES];

// ������ �������� ������� ��� ������� �������� ������� ����� (��� �������� � �������)
uchar                   mpibPowCurrTariff[48],
                        mpibEngCurrTariff[48];

// ������ �������� ������� ��� ������� �������� ������� �����
uchar                   mpibPowPrevTariff[48],
                        mpibEngPrevTariff[48];

// ������� �����������/���������� �������� �������� �������� �� ������� � ���������� ������
boolean                 fPublicTariffsCurr,
                        fPublicTariffsPrev;

// ������ �������� ������� �������� ��� �� ����� � ������� (������ �������)
period                  mpeTariffPow[12],
                        mpeTariffEng[12];

// ������� ��������� ������� � �������� ��� (������ �������)
uchar                   bTariffsMode;



// �������� �������� �������
zone                   zoAlt,zoKey;

// ������ �������� �������� ��������
breaks                  brAlt,brKey;



// ���� ������������� �������� ��������
boolean                 boGapsFlag;

// ������ ������� �������� ��������
gap                    mpgaGaps;

// ����������
time                    tiGap;

// ������ �������� �������� �� ��� �� ������
uchar                   mpbGaps[365];
