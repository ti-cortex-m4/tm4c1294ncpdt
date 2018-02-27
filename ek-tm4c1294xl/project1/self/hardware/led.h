/*------------------------------------------------------------------------------
led.h


------------------------------------------------------------------------------*/

#define NO_LED



#ifdef NO_DISPLAY

void InitLED(void);

void OffLED0(void);
void OnLED0(void);
void OffLED1(void);
void OnLED1(void);

#endif
