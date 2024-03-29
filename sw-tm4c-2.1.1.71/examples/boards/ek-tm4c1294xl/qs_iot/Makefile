#******************************************************************************
#
# Makefile - Rules for building the Quickstart application to talk to a cloud server..
#
# Copyright (c) 2013-2015 Texas Instruments Incorporated.  All rights reserved.
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
# This is part of revision 2.1.1.71 of the EK-TM4C1294XL Firmware Package.
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
VPATH=../drivers
VPATH+=../../../../third_party/exosite
VPATH+=../../../../utils

#
# Where to find header files that do not live in the source directory.
#
IPATH=.
IPATH+=..
IPATH+=../../../..
IPATH+=../../../../third_party/lwip-1.4.1/apps
IPATH+=../../../../third_party/exosite
IPATH+=../../../../third_party/lwip-1.4.1/ports/tiva-tm4c129/include
IPATH+=../../../../third_party/lwip-1.4.1/src/include
IPATH+=../../../../third_party/lwip-1.4.1/src/include/ipv4
IPATH+=../../../../third_party

#
# The default rule, which causes the Quickstart application to talk to a cloud server. to be built.
#
all: ${COMPILER}
all: ${COMPILER}/qs_iot.axf

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
# Rules for building the Quickstart application to talk to a cloud server..
#
${COMPILER}/qs_iot.axf: ${COMPILER}/buttons.o
${COMPILER}/qs_iot.axf: ${COMPILER}/cmdline.o
${COMPILER}/qs_iot.axf: ${COMPILER}/commands.o
${COMPILER}/qs_iot.axf: ${COMPILER}/eth_client_lwip.o
${COMPILER}/qs_iot.axf: ${COMPILER}/exosite.o
${COMPILER}/qs_iot.axf: ${COMPILER}/exosite_hal_lwip.o
${COMPILER}/qs_iot.axf: ${COMPILER}/exosite_meta.o
${COMPILER}/qs_iot.axf: ${COMPILER}/flash_pb.o
${COMPILER}/qs_iot.axf: ${COMPILER}/http.o
${COMPILER}/qs_iot.axf: ${COMPILER}/locator.o
${COMPILER}/qs_iot.axf: ${COMPILER}/lwiplib.o
${COMPILER}/qs_iot.axf: ${COMPILER}/pinout.o
${COMPILER}/qs_iot.axf: ${COMPILER}/qs_iot.o
${COMPILER}/qs_iot.axf: ${COMPILER}/requests.o
${COMPILER}/qs_iot.axf: ${COMPILER}/ringbuf.o
${COMPILER}/qs_iot.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/qs_iot.axf: ${COMPILER}/stats.o
${COMPILER}/qs_iot.axf: ${COMPILER}/tictactoe.o
${COMPILER}/qs_iot.axf: ${COMPILER}/uartstdio.o
${COMPILER}/qs_iot.axf: ${COMPILER}/ustdlib.o
${COMPILER}/qs_iot.axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
${COMPILER}/qs_iot.axf: qs_iot.ld
SCATTERgcc_qs_iot=qs_iot.ld
ENTRY_qs_iot=ResetISR
CFLAGSgcc=-DTARGET_IS_TM4C129_RA0 -DLWIP_1_4_1 -DUSE_HTTP_1_0 -DUART_BUFFERED

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
