/*------------------------------------------------------------------------------
MEM_SCHEDULE.C


------------------------------------------------------------------------------*/

#include "../main.h"



//  ������ ������ �������� ��������� �� ������ � ���������
bool                    mpboEnblPrtHou[bPORTS][48];

//  ������ ��������� ������� �������� ��������� �� ���������
bool                    mpboCtrlHou[48];



// ������ �����������
bool                    mpboRecalcHou[48];

// �������
bool                    boRecalcAlways;

// ���������� ����������
bool                    boRecalcCurr;
