/*------------------------------------------------------------------------------
led.h


------------------------------------------------------------------------------*/

//#define NO_LED



#ifdef NO_DISPLAY

void InitLED(void);

void LEDGreenOff(void);
void LEDGreenOn(void);
void LEDRedOff(void);
void LEDRedOn(void);

void RunLED_StartError(void);
void RunLED_RealTime(void);
void RunLED_Reset(void);

#endif
