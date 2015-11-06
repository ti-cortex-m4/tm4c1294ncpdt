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
#define SERIAL_PARITY_NONE  ((unsigned char)1)
#define SERIAL_PARITY_ODD   ((unsigned char)2)
#define SERIAL_PARITY_EVEN  ((unsigned char)3)
#define SERIAL_PARITY_MARK  ((unsigned char)4)
#define SERIAL_PARITY_SPACE ((unsigned char)5)

//*****************************************************************************
//
// Values used to indicate various flow control modes for SerialSetFlowControl
// and SerialGetFlowControl.
//
//*****************************************************************************
#define SERIAL_FLOW_CONTROL_NONE ((unsigned char)1)
#define SERIAL_FLOW_CONTROL_HW   ((unsigned char)3)

//*****************************************************************************
//
// Values used to indicate various flow control modes for SerialSetFlowOut
// and SerialGetFlowOut.
//
//*****************************************************************************
#define SERIAL_FLOW_OUT_SET      ((unsigned char)11)
#define SERIAL_FLOW_OUT_CLEAR    ((unsigned char)12)

//*****************************************************************************
//
// Prototypes for the Serial interface functions.
//
//*****************************************************************************
extern bool SerialSendFull(uint32_t ulPort);
extern void SerialSend(uint32_t ulPort, unsigned char ucChar);
extern long SerialReceive(uint32_t ulPort);
extern uint32_t SerialReceiveAvailable(uint32_t ulPort);
extern void SerialSetBaudRate(uint32_t ulPort, uint32_t ulBaudRate);
extern uint32_t SerialGetBaudRate(uint32_t ulPort);
extern void SerialSetDataSize(uint32_t ulPort, unsigned char ucDataSize);
extern unsigned char SerialGetDataSize(uint32_t ulPort);
extern void SerialSetParity(uint32_t ulPort, unsigned char ucParity);
extern unsigned char SerialGetParity(uint32_t ulPort);
extern void SerialSetStopBits(uint32_t ulPort, unsigned char ucStopBits);
extern unsigned char SerialGetStopBits(uint32_t ulPort);
extern void SerialSetFlowControl(uint32_t ulPort,
                                 unsigned char ucFlowControl);
extern unsigned char SerialGetFlowControl(uint32_t ulPort);
extern void SerialSetFlowOut(uint32_t ulPort, unsigned char ucFlowValue);
extern unsigned char SerialGetFlowOut(uint32_t ulPort);
extern void SerialPurgeData(uint32_t ulPort,
                            unsigned char ucPurgeCommand);
extern void SerialSetDefault(uint32_t ulPort);
extern void SerialSetFactory(uint32_t ulPort);
extern void SerialSetCurrent(uint32_t ulPort);
extern void SerialInit(void);

#endif // __SERIAL_H__
