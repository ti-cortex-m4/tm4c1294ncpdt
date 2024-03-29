/*------------------------------------------------------------------------------
MEM_CURRENT!C


------------------------------------------------------------------------------*/

#include "../main.h"



// ������ ������� ������� (� ���������)
ulong                   mpdwBase[bCANALS];

// ������ ������� ������� (� ��������� �������)
float                   mpreBase[bCANALS];

// ������ �������/���� ���������� ������� �������
time                    mptiBase[bCANALS];

// ������ ������ ��������� ������� �������
bool                    mpboBase[bCANALS];

// ������ ��� �������� ������� �������� ���� ������� ������ ��������
ulong                   mpdwBaseDig[bCHANNELS];

// ������ �������/���� ���������
time                    mptiOffs[bCANALS];

// ���������� ����������
time                    tiOffs;

// ������� ��������������� ����������
uint                    mpwTrue[bCANALS],
                        mpwFalse[bCANALS],
                        mpwOverflow[bCANALS],
                        mpwUnderflow[bCANALS],
                        mpwRepeat[bCANALS];



// ������� ��������������� ����������
uint                    mpwMore100[bCANALS],
                        mpwMore1000[bCANALS],
                        mpwMore10000[bCANALS];

// ������� ��������������� ����������
time                    mptiBaseOK[bCANALS],
                        mptiBaseError[bCANALS];



// ���������� �����������
bool                    fEnblCurrent2;

// ���� ������� �������
bool                    fCurrent2First;

// ������� ����� �������
uchar                   mpbCurrent2Curr[8],
                        mpbCurrent2Prev[8],
                        mpbCurrent2Buff[8];

// �������� ���������� �����������
uint                    mpwCurrent2Mnt[bCANALS];

// �������� ������������
uint                    mpwCurrent2Overflow[bCANALS];
