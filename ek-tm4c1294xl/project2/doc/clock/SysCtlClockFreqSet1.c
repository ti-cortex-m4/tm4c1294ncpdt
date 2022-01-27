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
