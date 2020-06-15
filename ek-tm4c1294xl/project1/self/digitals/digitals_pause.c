/*------------------------------------------------------------------------------
DIGITALS_PAUSE!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "digitals_status.h"
#include "digitals_pause.h"



// счётчик для отрабоки задержки между запросами
uint                    mpcwPause[bPORTS];



extern  volatile device         deCurr;



// обработка задержки между запросами в прерывании
void    Pause(void)
{
  if (GetStatus() == 1) return;

  if ((GetCurr() == DEV_PAUSE) && (ibPortPause < bPORTS))
  {
    if (mpcwPause[ibPortPause] == 0)
    {
      deCurr = GetPause();
      mpSerial[ibPortPause] = SER_PAUSE;
    }
    else mpcwPause[ibPortPause]--;
  }
}



// подготовка обработки задержки между запросами
void    MakePause(device  de)
{
  mpcwPause[ibPort] = (uint)(wFREQUENCY_T0*ePAUSE);   

  ibPortPause = ibPort;

  SetPause(de);
  SetCurr(DEV_PAUSE);
}


// подготовка обработки задержки между запросами
void    MakeLongPause(device  de, uchar  bSecond)
{
  mpcwPause[ibPort] = (uint)(wFREQUENCY_T0*bSecond);   

  ibPortPause = ibPort;

  SetPause(de);
  SetCurr(DEV_PAUSE);
}



// повтор обработки задержки 
void    NextPause(void)
{
  if (ibPortPause < bPORTS)
  {
    mpcwPause[ibPortPause] = (uint)(wFREQUENCY_T0*ePAUSE);
    SetCurr(DEV_PAUSE);
  }
}
