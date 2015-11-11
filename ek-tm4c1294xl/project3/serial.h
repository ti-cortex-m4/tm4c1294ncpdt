//*****************************************************************************
//
// serial.h - Prototypes for the Serial Port Driver
//
// Copyright (c) 2008-2013 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 10636 of the RDK-S2E Firmware Package.
//
//*****************************************************************************

#ifndef __SERIAL_H__
#define __SERIAL_H__

//*****************************************************************************
//
// Values used to indicate various parity modes for SerialSetParity and
// SerialGetParity.
//
//*****************************************************************************
#define SERIAL_PARITY_NONE  ((uint8_t)1)
#define SERIAL_PARITY_ODD   ((uint8_t)2)
#define SERIAL_PARITY_EVEN  ((uint8_t)3)
#define SERIAL_PARITY_MARK  ((uint8_t)4)
#define SERIAL_PARITY_SPACE ((uint8_t)5)

//*****************************************************************************
//
// Values used to indicate various flow control modes for SerialSetFlowControl
// and SerialGetFlowControl.
//
//*****************************************************************************
#define SERIAL_FLOW_CONTROL_NONE ((uint8_t)1)
#define SERIAL_FLOW_CONTROL_HW   ((uint8_t)3)

//*****************************************************************************
//
// Values used to indicate various flow control modes for SerialSetFlowOut
// and SerialGetFlowOut.
//
//*****************************************************************************
#define SERIAL_FLOW_OUT_SET      ((uint8_t)11)
#define SERIAL_FLOW_OUT_CLEAR    ((uint8_t)12)

//*****************************************************************************
//
// Prototypes for the Serial interface functions.
//
//*****************************************************************************
extern tBoolean SerialSendFull(unsigned long ulPort);
extern void SerialSend(unsigned long ulPort, uint8_t ucChar);
extern long SerialReceive(unsigned long ulPort);
extern unsigned long SerialReceiveAvailable(unsigned long ulPort);
extern void SerialSetBaudRate(unsigned long ulPort, unsigned long ulBaudRate);
extern unsigned long SerialGetBaudRate(unsigned long ulPort);
extern void SerialSetDataSize(unsigned long ulPort, uint8_t ucDataSize);
extern uint8_t SerialGetDataSize(unsigned long ulPort);
extern void SerialSetParity(unsigned long ulPort, uint8_t ucParity);
extern uint8_t SerialGetParity(unsigned long ulPort);
extern void SerialSetStopBits(unsigned long ulPort, uint8_t ucStopBits);
extern uint8_t SerialGetStopBits(unsigned long ulPort);
extern void SerialSetFlowControl(unsigned long ulPort,
                                 uint8_t ucFlowControl);
extern uint8_t SerialGetFlowControl(unsigned long ulPort);
extern void SerialSetFlowOut(unsigned long ulPort, uint8_t ucFlowValue);
extern uint8_t SerialGetFlowOut(unsigned long ulPort);
extern void SerialPurgeData(unsigned long ulPort,
                            uint8_t ucPurgeCommand);
extern void SerialSetDefault(unsigned long ulPort);
extern void SerialSetFactory(unsigned long ulPort);
extern void SerialSetCurrent(unsigned long ulPort);
extern void SerialInit(void);

#endif // __SERIAL_H__
