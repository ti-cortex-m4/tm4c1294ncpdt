/*------------------------------------------------------------------------------
MEM_GPS.C


------------------------------------------------------------------------------*/

#include "../main.h"



// ����� ����� ����� GPS
uchar                   bPortGPS;

// ���������� ����������
uchar                   bStatusGPS, bVersionMaxGPS, bVersionMinGPS;

// ���������� ����������
time                    tiGPS;

// ������� ����
uchar                   bGMT;

// ������ ��������� �������
boolean                 mpboGPSRun[48];

// �������� �������
uint                    mpcwGPSRun[20];

// �������� ������� ��/����� ��������� ���������
time                    tiPrevCorrect, tiPostCorrect;
