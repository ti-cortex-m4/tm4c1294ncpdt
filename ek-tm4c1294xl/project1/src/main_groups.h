#include        "main_basic.h"



// тип 'узел группы'
typedef struct
{
  uchar         ibCanal;                // индекс канала
} nodes;


// тип 'группа'
typedef struct
{
  uchar         bSize;                  // количество узлов в группе
  nodes         mpnoNodes[bCANALS];     // узлы группы
} groups;
