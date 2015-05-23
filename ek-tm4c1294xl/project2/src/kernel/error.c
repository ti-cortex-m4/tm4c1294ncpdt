/*------------------------------------------------------------------------------
ERROR.H


------------------------------------------------------------------------------*/

#include        <stdint.h>

// The error routine that is called if the driver library encounters an error.
#ifdef DEBUG
void __error__(char *pcFilename, uint32_t ui32Line) {
}
#endif
