/*------------------------------------------------------------------------------
MEM_LIMITS,C


------------------------------------------------------------------------------*/

#include "../main.h"



// ���� ������������� ������� ������� ������
bool                    fUseBounds;

// ������ �������� ������� ������� ������
uint                    mpcwStartRelCan[bCANALS];

// ������ �������� ������� ������� ������
uint                    mpcwStartAbs16Can[bCANALS];

// ������ �������� ������� ������� ������
ulong                   mpcdwStartAbs32Can[bCANALS];

// ������ ��������� ������ ������
bool                    mpboStartCan[bCANALS];

// ������ �������� ������� ������� ������
uint                    mpcwStopCan[bCANALS];

// ������ �������������� �������� ������� ������� ������
uint                    mpcwStopAuxCan[bCANALS];