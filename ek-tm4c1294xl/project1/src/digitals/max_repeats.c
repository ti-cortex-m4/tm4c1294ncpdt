/*------------------------------------------------------------------------------
MAX_REPEATS.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../flash/files.h"



// количество повторов при ошибках обмена со счетчиками
uchar                   bMaxRepeats;

file const              flMaxRepeats = {MAX_REPEATS, &bMaxRepeats, sizeof(uchar)};



void    InitMaxRepeats(void) 
{
  LoadFile(&flMaxRepeats);

  if ((bMaxRepeats <= 0) || (bMaxRepeats > 20))
  {
    bMaxRepeats = bMINORREPEATS;
    SaveFile(&flMaxRepeats);
  }
}


void    ResetMaxRepeats(void)
{
  bMaxRepeats = bMINORREPEATS;
  SaveFile(&flMaxRepeats);
}


uchar   GetMaxRepeats(void)
{
  return bMaxRepeats;
}
