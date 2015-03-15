/*------------------------------------------------------------------------------
DIGITALS_PAUSE.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "digitals_status.h"



extern  uint                    wCurr;



// обработка задержки между запросами в прерывании
void    Pause(void)
{
  if (GetStatus() == 1) return;

  if ((GetCurr() == DEV_PAUSE) && (ibPortPause < bPORTS))
  {
    if (mpcwPause[ibPortPause] == 0)
    {
      wCurr = GetPause();
      mpSerial[ibPortPause] = SER_PAUSE;
    }
    else mpcwPause[ibPortPause]--;
  }
}



// подготовка обработки задержки между запросами
void    MakePause(uint  w)
{
  mpcwPause[ibPort] = (uint)(wFREQUENCY_T0*ePAUSE);   

  ibPortPause = ibPort;

  SetPause(w);
  SetCurr(DEV_PAUSE);
}


// подготовка обработки задержки между запросами
void    MakeLongPause(uint  w, uchar  bSecond)
{
  mpcwPause[ibPort] = (uint)(wFREQUENCY_T0*bSecond);   

  ibPortPause = ibPort;

  SetPause(w);
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
