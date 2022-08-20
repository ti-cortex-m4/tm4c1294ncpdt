#if 0
//*****************************************************************************
//
// sysctl.c - Driver for the system controller.
//
// Copyright (c) 2005-2013 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
// 
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the  
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// This is part of revision 2.0 of the Tiva Peripheral Driver Library.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup sysctl_api
//! @{
//
//*****************************************************************************

#include "main.h"
/*
#include <stdbool.h>
#include <stdint.h>
#include "hw_ints.h"
#include "hw_sysctl.h"
#include "hw_types.h"
#include "sysctl_ed.h"
*/
//#include "hw_nvic.h"
//#include "hw_flash.h"
//#include "cpu.h"
//#include "debug.h"
//#include "interrupt.h"

//*****************************************************************************
//
// The flash shift used in the math to calculate the flash sector size.
//
//*****************************************************************************
#ifndef FLASH_PP_MAINSS_S
#define FLASH_PP_MAINSS_S       16
#endif

//*****************************************************************************
//
// This macro converts the XTAL value provided in the ui32Config parameter to
// an index to the g_pui32Xtals array.
//
//*****************************************************************************
#define SysCtlXtalCfgToIndex(a) ((a & 0x7c0) >> 6)

//*****************************************************************************
//
// An array that maps the crystal number in RCC to a frequency.
//
//*****************************************************************************
static const uint32_t g_pui32Xtals[] =
{
    1000000,
    1843200,
    2000000,
    2457600,
    3579545,
    3686400,
    4000000,
    4096000,
    4915200,
    5000000,
    5120000,
    6000000,
    6144000,
    7372800,
    8000000,
    8192000,
    10000000,
    12000000,
    12288000,
    13560000,
    14318180,
    16000000,
    16384000,
    18000000,
    20000000,
    24000000,
    25000000
};

//*****************************************************************************
//
// Maximum number of VCO entries in the g_pui32XTALtoVCO and
// g_pui32VCOFrequencies structures for a device.
//
//*****************************************************************************
#define MAX_VCO_ENTRIES         2
#define MAX_XTAL_ENTRIES        18

//*****************************************************************************
//
// These macros are used in the g_pui32XTALtoVCO table to make it more
// readable.
//
//*****************************************************************************
#define PLL_M_TO_REG(mi, mf)                                                  \
        ((uint32_t)mi | (uint32_t)(mf << SYSCTL_PLLFREQ0_MFRAC_S))
#define PLL_N_TO_REG(n)                                                       \
        ((uint32_t)(n - 1) << SYSCTL_PLLFREQ1_N_S)

//*****************************************************************************
//
// Look up of the values that go into the PLLFREQ0 and PLLFREQ1 registers.
//
//*****************************************************************************
static const uint32_t g_pppui32XTALtoVCO[MAX_VCO_ENTRIES][MAX_XTAL_ENTRIES][2] =
{
    {
        //
        // VCO 320 MHz
        //
        { PLL_M_TO_REG(64, 0),   PLL_N_TO_REG(1) },     // 5 MHz
        { PLL_M_TO_REG(62, 512), PLL_N_TO_REG(1) },     // 5.12 MHz
        { PLL_M_TO_REG(160, 0),  PLL_N_TO_REG(3) },     // 6 MHz
        { PLL_M_TO_REG(52, 85),  PLL_N_TO_REG(1) },     // 6.144 MHz
        { PLL_M_TO_REG(43, 412), PLL_N_TO_REG(1) },     // 7.3728 MHz
        { PLL_M_TO_REG(40, 0),   PLL_N_TO_REG(1) },     // 8 MHz
        { PLL_M_TO_REG(39, 64),  PLL_N_TO_REG(1) },     // 8.192 MHz
        { PLL_M_TO_REG(32, 0),   PLL_N_TO_REG(1) },     // 10 MHz
        { PLL_M_TO_REG(80, 0),   PLL_N_TO_REG(3) },     // 12 MHz
        { PLL_M_TO_REG(26, 43),  PLL_N_TO_REG(1) },     // 12.288 MHz
        { PLL_M_TO_REG(23, 613), PLL_N_TO_REG(1) },     // 13.56 MHz
        { PLL_M_TO_REG(22, 358), PLL_N_TO_REG(1) },     // 14.318180 MHz
        { PLL_M_TO_REG(20, 0),   PLL_N_TO_REG(1) },     // 16 MHz
        { PLL_M_TO_REG(19, 544), PLL_N_TO_REG(1) },     // 16.384 MHz
        { PLL_M_TO_REG(160, 0),  PLL_N_TO_REG(9) },     // 18 MHz
        { PLL_M_TO_REG(16, 0),   PLL_N_TO_REG(1) },     // 20 MHz
        { PLL_M_TO_REG(40, 0),   PLL_N_TO_REG(3) },     // 24 MHz
        { PLL_M_TO_REG(64, 0),   PLL_N_TO_REG(5) },     // 25 MHz
    },
    {
        //
        // VCO 480 MHz
        //
        { PLL_M_TO_REG(96, 0),   PLL_N_TO_REG(1) },     // 5 MHz
        { PLL_M_TO_REG(93, 768), PLL_N_TO_REG(1) },     // 5.12 MHz
        { PLL_M_TO_REG(80, 0),   PLL_N_TO_REG(1) },     // 6 MHz
        { PLL_M_TO_REG(78, 128), PLL_N_TO_REG(1) },     // 6.144 MHz
        { PLL_M_TO_REG(65, 107), PLL_N_TO_REG(1) },     // 7.3728 MHz
        { PLL_M_TO_REG(60, 0),   PLL_N_TO_REG(1) },     // 8 MHz
        { PLL_M_TO_REG(58, 608), PLL_N_TO_REG(1) },     // 8.192 MHz
        { PLL_M_TO_REG(48, 0),   PLL_N_TO_REG(1) },     // 10 MHz
        { PLL_M_TO_REG(40, 0),   PLL_N_TO_REG(1) },     // 12 MHz
        { PLL_M_TO_REG(39, 64),  PLL_N_TO_REG(1) },     // 12.288 MHz
        { PLL_M_TO_REG(35, 408), PLL_N_TO_REG(1) },     // 13.56 MHz
        { PLL_M_TO_REG(33, 536), PLL_N_TO_REG(1) },     // 14.318180 MHz
        { PLL_M_TO_REG(30, 0),   PLL_N_TO_REG(1) },     // 16 MHz
        { PLL_M_TO_REG(29, 304), PLL_N_TO_REG(1) },     // 16.384 MHz
        { PLL_M_TO_REG(80, 0),   PLL_N_TO_REG(3) },     // 18 MHz
        { PLL_M_TO_REG(24, 0),   PLL_N_TO_REG(1) },     // 20 MHz
        { PLL_M_TO_REG(20, 0),   PLL_N_TO_REG(1) },     // 24 MHz
        { PLL_M_TO_REG(96, 0),   PLL_N_TO_REG(5) },     // 25 MHz
    },
};

//*****************************************************************************
//
// The mapping of system clock frequency to flash memory timing parameters.
//
//*****************************************************************************
static const struct
{
    uint32_t ui32Frequency;
    uint32_t ui32MemTiming;
}
g_sXTALtoMEMTIM[] =
{
    { 16000000, (SYSCTL_MEMTIM0_FBCHT_0_5 | SYSCTL_MEMTIM0_FBCE |
                 (0 << SYSCTL_MEMTIM0_FWS_S) |
                 SYSCTL_MEMTIM0_EBCHT_0_5 | SYSCTL_MEMTIM0_EBCE |
                 (0 << SYSCTL_MEMTIM0_EWS_S) |
                 SYSCTL_MEMTIM0_MB1) },
    { 30000000, (SYSCTL_MEMTIM0_FBCHT_1 | SYSCTL_MEMTIM0_FBCE |
                 (1 << SYSCTL_MEMTIM0_FWS_S) |
                 SYSCTL_MEMTIM0_EBCHT_1 | SYSCTL_MEMTIM0_EBCE |
                 (1 << SYSCTL_MEMTIM0_EWS_S) |
                 SYSCTL_MEMTIM0_MB1) },
    { 50000000, (SYSCTL_MEMTIM0_FBCHT_1_5 | SYSCTL_MEMTIM0_FBCE |
                 (2 << SYSCTL_MEMTIM0_FWS_S) |
                 SYSCTL_MEMTIM0_EBCHT_1_5 | SYSCTL_MEMTIM0_EBCE |
                 (2 << SYSCTL_MEMTIM0_EWS_S) |
                 SYSCTL_MEMTIM0_MB1) },
    { 60000000, (SYSCTL_MEMTIM0_FBCHT_2 | (3 << SYSCTL_MEMTIM0_FWS_S) |
                 SYSCTL_MEMTIM0_EBCHT_2 | (3 << SYSCTL_MEMTIM0_EWS_S) |
                 SYSCTL_MEMTIM0_MB1) },
    { 80000000, (SYSCTL_MEMTIM0_FBCHT_2_5 | (4 << SYSCTL_MEMTIM0_FWS_S) |
                 SYSCTL_MEMTIM0_EBCHT_2_5 | (4 << SYSCTL_MEMTIM0_EWS_S) |
                 SYSCTL_MEMTIM0_MB1) },
    { 100000000, (SYSCTL_MEMTIM0_FBCHT_3 | (5 << SYSCTL_MEMTIM0_FWS_S) |
                  SYSCTL_MEMTIM0_EBCHT_3 | (5 << SYSCTL_MEMTIM0_EWS_S) |
                  SYSCTL_MEMTIM0_MB1) },
    { 120000000, (SYSCTL_MEMTIM0_FBCHT_3_5 | (6 << SYSCTL_MEMTIM0_FWS_S) |
                  SYSCTL_MEMTIM0_EBCHT_3_5 | (6 << SYSCTL_MEMTIM0_EWS_S) |
                  SYSCTL_MEMTIM0_MB1) },
};

//[-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]
//*****************************************************************************
//
// Get the correct memory timings for a given system clock value.
//
//*****************************************************************************
static uint32_t
_SysCtlMemTimingGet(uint32_t ui32SysClock)
{
    uint_fast8_t ui8Idx;

    //
    // Loop through the flash memory timings.
    //
    for(ui8Idx = 0;
        ui8Idx < (sizeof(g_sXTALtoMEMTIM) / sizeof(g_sXTALtoMEMTIM[0]));
        ui8Idx++)
    {
        //
        // See if the system clock frequency is less than the maximum frequency
        // for this flash memory timing.
        //
        if(ui32SysClock <= g_sXTALtoMEMTIM[ui8Idx].ui32Frequency)
        {
            //
            // This flash memory timing is the best choice for the system clock
            // frequency, so return it now.
            //
            return(g_sXTALtoMEMTIM[ui8Idx].ui32MemTiming);
        }
    }

    //
    // An appropriate flash memory timing could not be found, so the device is
    // being clocked too fast.  Return the default flash memory timing.
    //
    return(0);
}

//[-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]
//*****************************************************************************
//
// Calculate the system frequency from the register settings base on the
// oscillator input.
//
//*****************************************************************************
static uint32_t
_SysCtlFrequencyGet(uint32_t ui32Xtal)
{
    uint32_t ui32Result;
    uint_fast16_t ui16F1, ui16F2;
    uint_fast16_t ui16PInt, ui16PFract;
    uint_fast8_t ui8Q, ui8N;

    //
    // Extract all of the values from the hardware registers.
    //
    ui16PFract = ((HWREG(SYSCTL_PLLFREQ0) & SYSCTL_PLLFREQ0_MFRAC_M) >>
                  SYSCTL_PLLFREQ0_MFRAC_S);
    ui16PInt = HWREG(SYSCTL_PLLFREQ0) & SYSCTL_PLLFREQ0_MINT_M;
    ui8Q = (((HWREG(SYSCTL_PLLFREQ1) & SYSCTL_PLLFREQ1_Q_M) >>
             SYSCTL_PLLFREQ1_Q_S) + 1);
    ui8N = (((HWREG(SYSCTL_PLLFREQ1) & SYSCTL_PLLFREQ1_N_M) >>
             SYSCTL_PLLFREQ1_N_S) + 1);

    //
    // Divide the crystal value by N.
    //
    ui32Xtal /= (uint32_t)ui8N;

    //
    // Calculate the multiplier for bits 9:5.
    //
    ui16F1 = ui16PFract / 32;

    //
    // Calculate the multiplier for bits 4:0.
    //
    ui16F2 = ui16PFract - (ui16F1 * 32);

    //
    // Get the integer portion.
    //
    ui32Result = ui32Xtal * (uint32_t)ui16PInt;

    //
    // Add first fractional bits portion(9:0).
    //
    ui32Result += (ui32Xtal * (uint32_t)ui16F1) / 32;

    //
    // Add the second fractional bits portion(4:0).
    //
    ui32Result += (ui32Xtal * (uint32_t)ui16F2) / 1024;

    //
    // Divide the result by Q.
    //
    ui32Result = ui32Result / (uint32_t)ui8Q;

    //
    // Return the resulting PLL frequency.
    //
    return(ui32Result);
}

//*****************************************************************************
//
// Look up of the possible VCO frequencies.
//
//*****************************************************************************
static const uint32_t g_pui32VCOFrequencies[MAX_VCO_ENTRIES] =
{
    320000000,                              // VCO 320
    480000000,                              // VCO 480
};

//*****************************************************************************
//
// The base addresses of the various peripheral control registers.
//
//*****************************************************************************
#define SYSCTL_PPBASE           0x400fe300
#define SYSCTL_SRBASE           0x400fe500
#define SYSCTL_RCGCBASE         0x400fe600
#define SYSCTL_SCGCBASE         0x400fe700
#define SYSCTL_DCGCBASE         0x400fe800
#define SYSCTL_PCBASE           0x400fe900
#define SYSCTL_PRBASE           0x400fea00


//*****************************************************************************
//
//! Provides a small delay.
//!
//! \param ui32Count is the number of delay loop iterations to perform.
//!
//! This function provides a means of generating a constant length delay.  It
//! is written in assembly to keep the delay consistent across tool chains,
//! avoiding the need to tune the delay based on the tool chain in use.
//!
//! The loop takes 3 cycles/loop.
//!
//! \return None.
//
//*****************************************************************************
#if defined(ewarm) || defined(DOXYGEN)
void
SysCtlDelay(uint32_t ui32Count)
{
    __asm("    subs    r0, #1\n"
          "    bne.n   SysCtlDelay\n"
          "    bx      lr");
}
#endif
#if defined(codered) || defined(gcc) || defined(sourcerygxx)
void __attribute__((naked))
SysCtlDelay(uint32_t ui32Count)
{
    __asm("    subs    r0, #1\n"
          "    bne     SysCtlDelay\n"
          "    bx      lr");
}
#endif
#if defined(rvmdk) || defined(__ARMCC_VERSION)
__asm void
SysCtlDelay(uint32_t ui32Count)
{
    subs    r0, #1;
    bne     SysCtlDelay;
    bx      lr;
}
#endif
//
// For CCS implement this function in pure assembly.  This prevents the TI
// compiler from doing funny things with the optimizer.
//
#if defined(ccs)
__asm("    .sect \".text:SysCtlDelay\"\n"
      "    .clink\n"
      "    .thumbfunc SysCtlDelay\n"
      "    .thumb\n"
      "    .global SysCtlDelay\n"
      "SysCtlDelay:\n"
      "    subs r0, #1\n"
      "    bne.n SysCtlDelay\n"
      "    bx lr\n");
#endif

//[-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-][-]
//*****************************************************************************
//
//! Configures the system clock.
//!
//! \param ui32Config is the required configuration of the device clocking.
//! \param ui32SysClock is the requested processor frequency.
//!
//! This function configures the main system clocking for the device.  The
//! input frequency, oscillator source, whether or not to enable the PLL, and
//! the system clock divider are all configured with this function.  This
//! function configures the system frequency to the closest available divisor
//! of one of the fixed PLL VCO settings provided in the \e ui32Config
//! parameter.  The caller sets the \e ui32SysClock parameter to request the
//! system clock frequency, and this function then attempts to match this using
//! the values provided in the \e ui32Config parameter.  If this function
//! cannot exactly match the requested frequency, it picks the closest
//! frequency that is lower than the requested frequency.  The \e ui32Config
//! parameter provides the remaining configuration options using a set of
//! defines that are a logical OR of several different values, many of which
//! are grouped into sets where only one of the set can be chosen.  This
//! function returns the current system frequency which may not match the
//! requested frequency.
//!
//! The oscillator source is chosen with one of the following values:
//!
//! - \b SYSCTL_OSC_INT to use the 16-MHz precision internal oscillator.
//! - \b SYSCTL_OSC_INT30 to use the internal low frequency oscillator.
//! - \b SYSCTL_OSC_EXT32 to use the hibernate modules 32.786-kHz oscillator.
//! This option is only available on devices that include the hibernation
//! module.
//!
//! The system clock source is chosen with one of the following values:
//!
//! - \b SYSCTL_USE_PLL is used to select the PLL output as the system clock.
//! - \b SYSCTL_USE_OSC is used to choose one of the oscillators as the
//! system clock.
//!
//! The PLL VCO frequency is chosen with one of the the following values:
//!
//! - \b SYSCTL_CFG_VCO_480 to set the PLL VCO output to 480-MHz
//! - \b SYSCTL_CFG_VCO_320 to set the PLL VCO output to 320-MHz
//!
//! Example: Configure the system clocking to be 40 MHz with a 320-MHz PLL
//! setting using the 16-MHz internal oscillator.
//!
//! \verbatim
//! SysCtlClockFreqSet(SYSCTL_OSC_INT | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_320,
//!                    40000000);
//! \endverbatim
//!
//! \note This function cannot be used with Blizzard-class devices.  For
//! Blizzard-class devices use the SysCtlClockSet() function.
//!
//! \return The actual configured system clock frequency in Hz or zero if the
//! value could not be changed due to a parameter error or PLL lock failure.
//
//*****************************************************************************
uint32_t
SysCtlClockFreqSet(uint32_t ui32Config, uint32_t ui32SysClock)
{
    int32_t i32Timeout, i32VCOIdx, i32XtalIdx;
    uint32_t ui32MOSCCTL;
    uint32_t ui32SysDiv, ui32Osc, ui32OscSelect, ui32RSClkConfig;
    //bool bNewPLL;
    unsigned char bNewPLL;

    //
    // Get the index of the crystal from the ui32Config parameter.
    //
    i32XtalIdx = SysCtlXtalCfgToIndex(ui32Config);

    //
    // Determine which non-PLL source was selected.
    //
    if((ui32Config & 0x38) == SYSCTL_OSC_INT)
    {
        //
        // Use the nominal frequency for the PIOSC oscillator and set the
        // crystal select.
        //
        ui32Osc = 16000000;
        ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_PIOSC;
        ui32OscSelect |= SYSCTL_RSCLKCFG_PLLSRC_PIOSC;

        //
        // Force the crystal index to the value for 16-MHz.
        //
        i32XtalIdx = SysCtlXtalCfgToIndex(SYSCTL_XTAL_16MHZ);
    }
    else if((ui32Config & 0x38) == SYSCTL_OSC_INT30)
    {
        //
        // Use the nominal frequency for the low frequency oscillator.
        //
        ui32Osc = 30000;
        ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_LFIOSC;
    }
    else if((ui32Config & 0x38) == (SYSCTL_OSC_EXT32 & 0x38))
    {
        //
        // Use the RTC frequency.
        //
        ui32Osc = 32768;
        ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_RTC;
    }
    else if((ui32Config & 0x38) == SYSCTL_OSC_MAIN)
    {
        //
        // Bounds check the source frequency for the main oscillator.  The is
        // because the PLL tables in the g_pppui32XTALtoVCO structure range
        // from 5MHz to 25MHz.
        //
        if((i32XtalIdx > (SysCtlXtalCfgToIndex(SYSCTL_XTAL_25MHZ))) ||
           (i32XtalIdx < (SysCtlXtalCfgToIndex(SYSCTL_XTAL_5MHZ))))
        {
            return(0);
        }

        ui32Osc = g_pui32Xtals[i32XtalIdx];

        //-ƒл€ синхронизации УSystem ClockФ выбираетс€ внешний резонатор УMain OSCФ по обоим лини€м
        //-RSCLKCFG: OSCSRC  =3 (источник частоты foscclk   = MOSC)
        //           PLLSRC  =3 (источник частоты PLL       = MOSC)
        // Set the PLL source select to MOSC.
        //ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_MOSC;
        //ui32OscSelect |= SYSCTL_RSCLKCFG_PLLSRC_MOSC;

        // »—ѕ–ј¬Ћ≈Ќќ:

        // Set the PLL source select to MOSC.
        ui32OscSelect = SYSCTL_RSCLKCFG_PLLSRC_MOSC;   // (источник частоты PLL = MOSC, источник частоты foscclk = PIOSC)
        //ui32OscSelect |= SYSCTL_RSCLKCFG_OSCSRC_MOSC;

        //
        // Clear MOSC power down, high oscillator range setting, and no crystal
        // present setting.
        //
        ui32MOSCCTL = HWREG(SYSCTL_MOSCCTL) &
                      ~(SYSCTL_MOSCCTL_OSCRNG | SYSCTL_MOSCCTL_PWRDN |
                        SYSCTL_MOSCCTL_NOXTAL);

        //
        // Increase the drive strength for MOSC of 10 MHz and above.
        //
        if(i32XtalIdx >= (SysCtlXtalCfgToIndex(SYSCTL_XTAL_10MHZ) -
                          (SysCtlXtalCfgToIndex(SYSCTL_XTAL_5MHZ))))
        {
            ui32MOSCCTL |= SYSCTL_MOSCCTL_OSCRNG;
        }

        HWREG(SYSCTL_MOSCCTL) = ui32MOSCCTL;
    }
    else
    {
        //
        // This was an invalid request because no oscillator source was
        // indicated.
        //
        ui32Osc = 0;
        ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_PIOSC;
    }

    //
    // Check if the running with the PLL enabled was requested.
    //
    if((ui32Config & SYSCTL_USE_OSC) == SYSCTL_USE_PLL)
    {
        //
        // ui32Config must be SYSCTL_OSC_MAIN or SYSCTL_OSC_INT.
        //
        if(((ui32Config & 0x38) != SYSCTL_OSC_MAIN) &&
           ((ui32Config & 0x38) != SYSCTL_OSC_INT))
        {
            return(0);
        }

        //
        // Get the VCO index out of the ui32Config parameter.
        //
        i32VCOIdx = (ui32Config >> 24) & 7;

        //
        // Check that the VCO index is not out of bounds.
        //
        ASSERT(i32VCOIdx < MAX_VCO_ENTRIES);

        //
        // Set the memory timings for the PIOSC since we are about to switch
        // back to PIOSC.
        //
        HWREG(SYSCTL_MEMTIM0) = _SysCtlMemTimingGet(16000000);

        //
        // Clear the old PLL divider and source in case it was set.
        //
        ui32RSClkConfig = HWREG(SYSCTL_RSCLKCFG) &
                          ~(SYSCTL_RSCLKCFG_PSYSDIV_M |
                            SYSCTL_RSCLKCFG_OSCSRC_M |
                            SYSCTL_RSCLKCFG_PLLSRC_M | SYSCTL_RSCLKCFG_USEPLL);

        //
        // Update the memory timings to match running from PIOSC.
        //
        ui32RSClkConfig |= SYSCTL_RSCLKCFG_MEMTIMU;

        //
        // Update clock configuration to switch back to PIOSC.
        //
        HWREG(SYSCTL_RSCLKCFG) = ui32RSClkConfig;

        //
        // The table starts at 5 MHz so modify the index to match this.
        //
        i32XtalIdx -= SysCtlXtalCfgToIndex(SYSCTL_XTAL_5MHZ);

        //
        // If there were no changes to the PLL do not force the PLL to lock by
        // writing the PLL settings.
        //
        if((HWREG(SYSCTL_PLLFREQ1) !=
            g_pppui32XTALtoVCO[i32VCOIdx][i32XtalIdx][1]) ||
           (HWREG(SYSCTL_PLLFREQ0) !=
            (g_pppui32XTALtoVCO[i32VCOIdx][i32XtalIdx][0] |
             SYSCTL_PLLFREQ0_PLLPWR)))
        {
            bNewPLL = 1;//true;
        }
        else
        {
            bNewPLL = 0;//false;
        }

        //
        // If there are new PLL settings write them.
        //
        if(bNewPLL)
        {
            //
            // Set the oscillator source.
            //
            HWREG(SYSCTL_RSCLKCFG) |= ui32OscSelect;

            //
            // Set the M, N and Q values provided from the table and preserve
            // the power state of the main PLL.
            //
            HWREG(SYSCTL_PLLFREQ1) =
                g_pppui32XTALtoVCO[i32VCOIdx][i32XtalIdx][1];
            HWREG(SYSCTL_PLLFREQ0) =
                (g_pppui32XTALtoVCO[i32VCOIdx][i32XtalIdx][0] |
                 (HWREG(SYSCTL_PLLFREQ0) & SYSCTL_PLLFREQ0_PLLPWR));
        }

        //
        // Calculate the System divider such that we get a frequency that is
        // the closest to the requested frequency without going over.
        //
        ui32SysDiv = (g_pui32VCOFrequencies[i32VCOIdx] + ui32SysClock - 1) /
                     ui32SysClock;

        //
        // Calculate the actual system clock.
        //
        ui32SysClock = _SysCtlFrequencyGet(ui32Osc) / ui32SysDiv;

        //
        // Set the Flash and EEPROM timing values.
        //
        HWREG(SYSCTL_MEMTIM0) = _SysCtlMemTimingGet(ui32SysClock);

        //
        // Check if the PLL is already powered up.
        //
        if(HWREG(SYSCTL_PLLFREQ0) & SYSCTL_PLLFREQ0_PLLPWR)
        {
            if(bNewPLL == 1)//true)
            {
                //
                // Trigger the PLL to lock to the new frequency.
                //
                HWREG(SYSCTL_RSCLKCFG) |= SYSCTL_RSCLKCFG_NEWFREQ;
            }
        }
        else
        {
            //
            // Power up the PLL.
            //
            HWREG(SYSCTL_PLLFREQ0) |= SYSCTL_PLLFREQ0_PLLPWR;
        }

        //
        // Wait until the PLL has locked.
        //
        for(i32Timeout = 32768; i32Timeout > 0; i32Timeout--)
        {
            if((HWREG(SYSCTL_PLLSTAT) & SYSCTL_PLLSTAT_LOCK))
            {
                break;
            }
        }

        //
        // If the loop above did not timeout then switch over to the PLL
        //
        if(i32Timeout)
        {
            ui32RSClkConfig = HWREG(SYSCTL_RSCLKCFG);
            ui32RSClkConfig |= ((ui32SysDiv - 1) <<
                                SYSCTL_RSCLKCFG_PSYSDIV_S) | ui32OscSelect |
                               SYSCTL_RSCLKCFG_USEPLL;
            ui32RSClkConfig |= SYSCTL_RSCLKCFG_MEMTIMU;

            //
            // Set the new clock configuration.
            //
            HWREG(SYSCTL_RSCLKCFG) = ui32RSClkConfig;
        }
        else
        {
            ui32SysClock = 0;
        }
    }
    else
    {
        //
        // Set the Flash and EEPROM timing values for PIOSC.
        //
        HWREG(SYSCTL_MEMTIM0) = _SysCtlMemTimingGet(16000000);

        //
        // Make sure that the PLL is powered down since it is not being used.
        //
        HWREG(SYSCTL_PLLFREQ0) &= ~SYSCTL_PLLFREQ0_PLLPWR;

        //
        // Clear the old PLL divider and source in case it was set.
        //
        ui32RSClkConfig = HWREG(SYSCTL_RSCLKCFG);
        ui32RSClkConfig &= ~(SYSCTL_RSCLKCFG_OSYSDIV_M |
                             SYSCTL_RSCLKCFG_OSCSRC_M |
                             SYSCTL_RSCLKCFG_USEPLL);

        //
        // Update the memory timings.
        //
        ui32RSClkConfig |= SYSCTL_RSCLKCFG_MEMTIMU;

        //
        // Set the new clock configuration.
        //
        HWREG(SYSCTL_RSCLKCFG) = ui32RSClkConfig;

        //
        // If zero given as the system clock then default to divide by 1.
        //
        if(ui32SysClock == 0)
        {
            ui32SysDiv = 0;
        }
        else
        {
            //
            // Calculate the System divider based on the requested
            // frequency.
            //
            ui32SysDiv = ui32Osc / ui32SysClock;

            //
            // If the system divisor is not already zero, subtract one to
            // set the value in the register which requires the value to
            // be n-1.
            //
            if(ui32SysDiv != 0)
            {
                ui32SysDiv -= 1;
            }

            //
            // Calculate the system clock.
            //
            ui32SysClock = ui32Osc / (ui32SysDiv + 1);
        }

        //
        // Set the memory timing values for the new system clock.
        //
        HWREG(SYSCTL_MEMTIM0) = _SysCtlMemTimingGet(ui32SysClock);

        //
        // Set the new system clock values.
        //
        ui32RSClkConfig = HWREG(SYSCTL_RSCLKCFG);
        ui32RSClkConfig |= (ui32SysDiv << SYSCTL_RSCLKCFG_OSYSDIV_S) |
                           ui32OscSelect;

        //
        // Update the memory timings.
        //
        ui32RSClkConfig |= SYSCTL_RSCLKCFG_MEMTIMU;

        //
        // Set the new clock configuration.
        //
        HWREG(SYSCTL_RSCLKCFG) = ui32RSClkConfig;
    }

    return(ui32SysClock);
}

//*****************************************************************************
//
//! Resets the device.
//!
//! This function performs a software reset of the entire device.  The
//! processor and all peripherals are reset and all device registers are
//! returned to their default values (with the exception of the reset cause
//! register, which maintains its current value but has the software reset
//! bit set as well).
//!
//! \return This function does not return.
//
//*****************************************************************************
void
SysCtlReset(void)
{
    //
    // Perform a software reset request.  This request causes the device to
    // reset, no further code is executed.
    //
    HWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;

    //
    // The device should have reset, so this should never be reached.  Just in
    // case, loop forever.
    //
    while(1)
    {
    }
}


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
#endif
