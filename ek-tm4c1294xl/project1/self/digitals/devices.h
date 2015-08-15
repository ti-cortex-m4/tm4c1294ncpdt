/*------------------------------------------------------------------------------
DEVICES.H
              

------------------------------------------------------------------------------*/

extern  message                 mpszDevices[bDEVICES+1];
extern  uchar const             mpbMaxLines[bDEVICES+1];



bool    IsValidDevice(uchar  ibDevice);
void    ShowDeviceName(uchar  ibDevice);
