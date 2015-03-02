/*------------------------------------------------------------------------------
PRINT.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "utils/uartstdio.h"
#include        "print.h"



void    PrintStart(void) {
//	InitConsole();
}


void    PrintString(const char *pcString, ...) {
	UARTprintf(pcString);
}


void    PrintStop(void) {

}
