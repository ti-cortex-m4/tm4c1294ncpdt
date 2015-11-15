#******************************************************************************
#
# Makefile - Rules for building the S2E Application.
#
# Copyright (c) 2014-2015 Texas Instruments Incorporated.  All rights reserved.
# Software License Agreement
# 
# Texas Instruments (TI) is supplying this software for use solely and
# exclusively on TI's microcontroller products. The software is owned by
# TI and/or its suppliers, and is protected under applicable copyright
# laws. You may not combine this software with "viral" open-source
# software in order to form a larger program.
# 
# THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
# NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
# NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
# CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
# DAMAGES, FOR ANY REASON WHATSOEVER.
# 
# This is part of revision 2.1.0.12573 of the EK-TM4C1294XL Firmware Package.
#
#******************************************************************************

#
# Defines the part type that this project uses.
#
PART=TM4C1294NCPDT

#
# The base directory for TivaWare.
#
ROOT=../../../..

#
# Include the common make definitions.
#
include ${ROOT}/makedefs

#
# Where to find source files that do not live in this directory.
#
VPATH=../../../../third_party/FreeRTOS/Source/portable/GCC/ARM_CM4F
VPATH+=../../../../third_party/FreeRTOS/Source/portable/MemMang/
VPATH+=../../../../third_party/FreeRTOS/Source
VPATH+=../drivers
VPATH+=../../../../third_party/lwip-1.4.1/apps/httpserver_raw
VPATH+=../../../../utils

#
# Where to find header files that do not live in the source directory.
#
IPATH=.
IPATH+=..
IPATH+=../../../..
IPATH+=../../../../third_party/FreeRTOS/Source/portable/GCC/ARM_CM4F
IPATH+=../../../../third_party/FreeRTOS
IPATH+=../../../../third_party/lwip-1.4.1/apps
IPATH+=../../../../third_party/FreeRTOS/Source/include
IPATH+=../../../../third_party/lwip-1.4.1/ports/tiva-tm4c129/include
IPATH+=../../../../third_party/lwip-1.4.1/src/include
IPATH+=../../../../third_party/lwip-1.4.1/src/include/ipv4
IPATH+=../../../../third_party

#
# The default rule, which causes the S2E Application to be built.
#
all: ${COMPILER}
all: ${COMPILER}/enet_s2e.axf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir -p ${COMPILER}

#
# Rules for building the S2E Application.
#
${COMPILER}/enet_s2e.axf: ${COMPILER}/config.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/croutine.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/eeprom_pb.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/enet_fs.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/enet_s2e.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/heap_2.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/httpd.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/idle_task.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/list.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/locator.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/lwip_task.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/lwiplib.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/pinout.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/port.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/queue.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/ringbuf.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/serial.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/serial_task.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/tasks.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/telnet.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/timers.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/uartstdio.o
${COMPILER}/enet_s2e.axf: ${COMPILER}/ustdlib.o
${COMPILER}/enet_s2e.axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
${COMPILER}/enet_s2e.axf: enet_s2e.ld
SCATTERgcc_enet_s2e=enet_s2e.ld
ENTRY_enet_s2e=ResetISR
CFLAGSgcc=-DTARGET_IS_TM4C129_RA1

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
