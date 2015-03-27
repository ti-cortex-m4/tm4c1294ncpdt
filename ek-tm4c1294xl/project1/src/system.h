/*------------------------------------------------------------------------------
SYSTEM.H


------------------------------------------------------------------------------*/

#ifndef __SYSTEM
#define __SYSTEM


// ������� ���������� Timer0, ��
#define wFREQUENCY_T0   350

// ������� ���������� Timer1, ��
#define wFREQUENCY_T1   1


// ����� ��������� ������
#define bPACKET_HEADER  8

// ����� ��������� ������ ��� �������� ������ �� ���������
#define bHEADER         15


// ������ �������� � ��������� ������� ������
#define wINBUFF_SIZE    0x0800
#define wOUTBUFF_SIZE   0x1900


// ������� ���������� Timer0, ��
#define wFREQUENCY_T0   350


// ���������� ������
#define bPORTS          4

// ���������� ���������
#define bBAUDS          9

// ���������� ����� ��������
#define bPARITYS        5

// ���������� ������� ������
#define bSTREAMS        5


// ������ ������ ����������
#define bDISPLAY        16

// ������ ������ ��� ������ ������� �� ������������
#define bMARGIN         32


// ���������� �������
#define bTARIFFS        4

// ���������� ������� ��������� ��������� �������
#define bBREAKS         6

// ���������� ����� ������� � ����������� �� ��� ������ (����� ������� ������� �������): �����, �������, �����������
#define bMODES          3

// ���������� ���������� �� ���
#define bRELAXS         40

// ���������� ������� ��� ������� �������� ��������
#define bGAPS           11

// ���������� ����� ������� � ����������� �� ��� ������ (������ ������� ������� ��������)
#define bTARIFFSMODES	  5


// �������� ������ �������
#define bMAXVERSION     4

// �������� ������ �������
#define bMINVERSION     18


// ���������� �������
#define bCANALS         64

// ���������� �����
#define bGROUPS         32

// ���������� ����� �������� ���������
#define bDEVICES        3

// ���������� ����� ����� � �������� ��������
#define bCHANNELS       128


// ����������� ���
#define bMINYEAR        15

// ������������ ���
#define bMAXYEAR        99

// ������ ����������� ��������
#define bMINUTES        40

// ������ ����������� ��������
#define wHOURS          (uint)(5*48)

// ������ ����������� ��������
#define wHOURS_62       (uint)(5*48)

// ������ �������� ��������
#define bDAYS           14

// ������ �������� �������� (����������� 12 !)
#define bMONTHS         12

// ������������ ���������� ���� � ����������� ���������
#define bMAXDAYS_OFF    30


// ������ ����������� ������
#define bPHONENUMBER    13

// ������ �����
#define bNAME           32


// ������������ ���������� �������� ��� ������ ������ � �������� ���������
#define bMINORREPEATS   5


// ������� ����� ������� ���������� �������
#define bMAXWAITQUERY   20

// ������������ ����� ���������� � ������ connect ��� ����������, ������
#define bMAXWAITONLINE  30


// ����� ����� �������� ���������� �������� � ������ ��������� ��������
#define ePAUSE          0.1


#ifndef SKIP_B

// ������ ����� ��������� ������� ��� �������� �������� ��������-230, ������ 
#define bMINORCORRECT_B 3

// ������� ����� ��������� ������� ��� �������� �������� ��������-230, ������ 
#define bMAJORCORRECT_B 230

// ������� ����� ��������� ������� ��� �������� �������� ��������-230, ������ 
#define wLIMITCORRECT_B 1800

//
#define bBLOCKS_B       20

#endif


#endif
