/*------------------------------------------------------------------------------
MAIN_DIGITALS,H


------------------------------------------------------------------------------*/

#include "main_basic.h"



// �������� �������
typedef struct
{
  uchar         ibPort;                 // ������ �����
  uchar         ibPhone;                // ������ ��������
  uchar         bDevice;                // ��� ������������ ��������
  uchar         bAddress;               // ���������� �����
  uchar         ibLine;                 // ��� �������
} digital;



// ������ ������
typedef struct
{
  char          szLine[bLINE_SIZE+1];
} line;



// ��� ������ ���������
typedef enum
{
  EXT_PROFILE_30MIN,
  EXT_CURRENT_3MIN,
  EXT_PROFILE_CHECKUP
} extended;



// ����� ������ �������� �������� ��������-230
typedef enum
{
  AUTOMATIC     = 0,
  SIZE_1        = 1,
  SIZE_16       = 2,
  SIZE_17       = 3,
  BY_DIGITAL    = 4
} profile2mode;
