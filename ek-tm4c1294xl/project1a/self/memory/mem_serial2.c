/*------------------------------------------------------------------------------
MEM_SERIAL2!C

TODO: volatile
------------------------------------------------------------------------------*/

#include "../main.h"



// ������� � �������� ������
uchar           	mpbInBuff2[wINBUFF_SIZE], mpbOutBuff2[wOUTBUFF_SIZE];

// ������� �� �������� � ��������� �������
uint            	iwInBuff2, iwOutBuff2;

// ���������� ������������ ����
uint            	cwInBuff2, cwOutBuff2;

// �������� �������� �� ����
uint            	cwInDelay2;

// ���������� ��� �������� CRC
uchar           	bCRCHi2, bCRCLo2;

// ������� �������� ����
uint            	cwIn2;

// ��������� �������� ����
uchar           	bIn2;

// ������� �� �������� � ��������� ������� � ������ �����
uint            	iwPop2, iwPush2;

// ��������� ��� �������� ������ ��� ����������� � �������� ������
uchar           	*pbData2;

// ������ ��� �������� � �������������� ������� ������
uchar           	ibPacket2;