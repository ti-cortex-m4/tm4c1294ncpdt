/*------------------------------------------------------------------------------
MEM_ENERGY.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// ������� ����������� ��������� (�� ������� ����������)
uint                    mpwImpCurrMntCan[bCANALS];

// ������� ����������� ��������� (�� ����������) TODO volatile
uint                    mpwImpMntCan[bMINUTES][bCANALS];

// ������� ����������� ��������� (�� ���������)
uint                    mpwImpHouCan[2][bCANALS];

// ������� ����������� ��������� �� ������� (�� ������, ������� � �����)
impulse                 mpimDayCan[2][bCANALS],
                        mpimMonCan[2][bCANALS],
                        mpimAbsCan[bCANALS];

// ���������� ����������
impulse                 imAlt;

// ������ ��������� ��������� �� ����� ������
real                    mpreCntMonCan[2][bCANALS];

// ������� ���������� �������� �� ������� (�� ������ � �������)
power                   mppoDayGrp[2][bGROUPS],
                        mppoMonGrp[2][bGROUPS];
