/*------------------------------------------------------------------------------
BEEP.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "delay.h"



void    SoundOn(void) {
}


void    SoundOff(void) {
}



void    InitBeep(void) {
  SoundOff();       
}



void    Beep(void) {
  SoundOn();  Delay(50);
  SoundOff(); Delay(50);
}


void    LongBeep(void) {
  Beep(); Beep(); Beep();
}

