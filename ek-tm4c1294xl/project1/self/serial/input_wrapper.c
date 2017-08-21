/*------------------------------------------------------------------------------
input_wrapper.c

Фасад для обработки приема по последовательных портах
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../digitals/skip_failure.h"
#include "input_wrapper.h"



void    InputStart(void)
{
  SkipFailure_Failure();
}


void    InputGoodCheck(void)
{
  SkipFailure_Success();
}
