/*------------------------------------------------------------------------------
MEM_CHECKUP.C


------------------------------------------------------------------------------*/

#include "../main.h"



// ����� �������� ��� �����������
bool                    boCheckupReadOnly;

// ����� ����������� �� �������� �������� ��������
ulong                   mpdwChannelsCheckup[(wHOURS/48)+1][4];

// ������� ������������
uchar                   cbCheckupErrorDay, cbCheckupErrorMon;
