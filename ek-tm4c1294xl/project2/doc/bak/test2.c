#if 0
    //*****************************************************************************
    #include "../../hw_ints.h"
    #include "../../hw_memmap.h"
    #include "../../hw_types.h"
    #include "../../src/ethernet.h"
    #include "../../src/flash.h"
    #include "../../src/gpio.h"
    #include "../../src/interrupt.h"
    #include "../../src/sysctl.h"
    #include "../../src/systick.h"
    #include "../../src/uart.h"
    #include "lwip/api.h"
    #include "lwip/def.h"
    #include "lwip/mem.h"
    #include "lwip/opt.h"
    #include "lwip/pbuf.h"
    #include "lwip/stats.h"
    #include "lwip/sys.h"
    #include "lwip/tcpip.h"
    #include "netif/etharp.h"
    #include "config.h"
    #include "luminaryif.h"
    #include "telnet.h"

    //*****************************************************************************
    //
    //! \page ser2enet_intro Introduction
    //!
    //! The Serial to Ethernet Converter provides a means of accessing the UART on
    //! a Stellaris device via a network connection.  The UART can be connected to
    //! the UART on a non-networked device, providing the ability to access the
    //! device via a network.  This can be useful to overcome the cable length
    //! limitations of a UART connection (in fact, the cable can become thousands
    //! of miles long) and to provide networking capability to existing devices
    //! without modifing the device's operation.
    //!
    //! The telnet protocol (as defined by RFC854) is used to make the connection
    //! across the network.  The Serial to Ethernet Converter provides the telnet
    //! server, and a connection is made to the converter using a telnet client.
    //! In its simplest form, a telnet client is simply a TCP connect to the
    //! appropriate port.  Telnet interprets 0xff as a command indicator (known as
    //! the Interpret As Command, or IAC, byte).  Consecutive IAC bytes are used to
    //! transfer an actual 0xff byte; thus, the only special processing required is
    //! to translate 0xff to 0xff 0xff when sending, and to translate 0xff 0xff to
    //! 0xff when receiving.
    //!
    //! The WILL, WONT, DO, DONT option negotiation protocol is also imlpemented.
    //! This is a simple means of determining if capabilities are present, and for
    //! enabling or disabling features that do not require configuration.  Through
    //! the use of this negotiation protocol, telnet clients and servers are able
    //! to easily match capabilities and avoid trying to configure features that
    //! are not shared by both ends of the connection (which would therefore result
    //! in the negotiation sequence being sent as actual data instead of being
    //! absorbed by the client or server).
    //!
    //! In this implementation, only the SUPPRESS_GA option is supported; all other
    //! options are negatively responded to in order to prevent the client from
    //! trying to use them.
    //!
    //! The converter can be configured to use a static IP configuration or to use
    //! DHCP to obtain its IP configuration.  Since the converter is providing a
    //! telnet server, the effective use of DHCP requires a reservation in the DHCP
    //! server so that the converter gets the same IP address each time it is
    //! connected to the network.
    //
    //*****************************************************************************

    //*****************************************************************************
    //
    //! \defgroup ser2enet_api Definitions
    //! @{
    //
    //*****************************************************************************

    //*****************************************************************************
    //
    //! The number of times per second that the SysTick timer generates a processor
    //! interrupt.
    //
    //*****************************************************************************
    #define SYSTICKHZ               100

    //*****************************************************************************
    //
    //! The number of milliseconds between SysTick generated processor interrupts.
    //
    //*****************************************************************************
    #define SYSTICKMS               (1000 / SYSTICKHZ)

    //*****************************************************************************
    //
    //! The bit in #g_ulFlags that indicates that a SysTick interrupt has occurred.
    //
    //*****************************************************************************
    #define FLAG_SYSTICK            0

    //*****************************************************************************
    //
    //! The bit in #g_ulFlags that indicates that an Ethernet controller interrupt
    //! has occurred.
    //
    //*****************************************************************************
    #define FLAG_RXPKT              1

    //*****************************************************************************
    //
    //! The bit in #g_ulFlags that indicates that a UART receive interrupt has
    //! occurred.
    //
    //*****************************************************************************
    #define FLAG_RXUART             2

    //*****************************************************************************
    //
    //! A set of flags that indicate the occurrence of interrupts.  The bits in
    //! this word are defined by #FLAG_SYSTICK, #FLAG_RXPKT, and #FLAG_RXUART.
    //
    //*****************************************************************************
    static volatile unsigned long g_ulFlags;

    //*****************************************************************************
    //
    //! The possible states of the telnet option parser.
    //
    //*****************************************************************************
    typedef enum
    {
        //
        //! The telnet option parser is in its normal mode.  Characters are passed
        //! as is until an IAC byte is received.
        //
        STATE_NORMAL,

        //
        //! The previous character received by the telnet option parser was an IAC
        //! byte.
        //
        STATE_IAC,

        //
        //! The previous character sequence received by the telnet option parser
        //! was IAC WILL.
        //
        STATE_WILL,

        //
        //! The previous character sequence received by the telnet option parser
        //! was IAC WONT.
        //
        STATE_WONT,

        //
        //! The previous character sequence received by the telnet option parser
        //! was IAC DO.
        //
        STATE_DO,

        //
        //! The previous character sequence received by the telnet option parser
        //! was IAC DONT.
        //
        STATE_DONT
    }
    tTelnetState;

    //*****************************************************************************
    //
    //! The current state of the telnet option parser.
    //
    //*****************************************************************************
    static tTelnetState g_eState;

    //*****************************************************************************
    //
    //! A structure that contains the state of the options supported by the telnet
    //! server, along with the possible flags.
    //
    //*****************************************************************************
    typedef struct
    {
        //
        //! The option byte.
        //
        unsigned char ucOption;

        //
        //! The flags for this option.  The bits in this byte are defined by
        //! OPT_FLAG_WILL and OPT_FLAG_DO.
        //
        unsigned char ucFlags;
    }
    tTelnetOpts;

    //*****************************************************************************
    //
    //! The bit in the ucFlags member of #tTelnetOpts that is set when the remote
    //! client has sent a WILL request and the server has accepted it.
    //
    //*****************************************************************************
    #define OPT_FLAG_WILL           1

    //*****************************************************************************
    //
    //! The bit in the ucFlags member of #tTelnetOpts that is set when the remote
    //! client has sent a DO request and the server has accepted it.
    //
    //*****************************************************************************
    #define OPT_FLAG_DO             2

    //*****************************************************************************
    //
    //! The telnet options supported by this server.
    //
    //*****************************************************************************
    static tTelnetOpts g_psOptions[] =
    {
        //
        // This telnet server will always suppress go ahead generation, regardless
        // of this setting.
        //
        { TELNET_OPT_SUPPRESS_GA, (1 << OPT_FLAG_WILL) },
    };

    //*****************************************************************************
    //
    //! The initialization sequence sent to a remote telnet client when it first
    //! connects to the telnet server.
    //
    //*****************************************************************************
    static const unsigned char g_pucTelnetInit[] =
    {
        TELNET_IAC, TELNET_DO, TELNET_OPT_SUPPRESS_GA
    };

    //*****************************************************************************
    //
    //! The lwIP network interface structure for the Stellaris Ethernet controller.
    //
    //*****************************************************************************
    static struct netif g_sEMAC_if;

    //*****************************************************************************
    //
    //! The lwIP TCP fast timer, used to determine the rate at which to call
    //! tcp_fasttmr().
    //
    //*****************************************************************************
    static unsigned long g_ulTCPFastTimer = 0;

    //*****************************************************************************
    //
    //! The lwIP TCP slow timer, used to determine the rate at which to call
    //! tcp_slowtimer().
    //
    //*****************************************************************************
    static unsigned long g_ulTCPSlowTimer = 0;

    //*****************************************************************************
    //
    //! The lwIP ARP timer, used to determine the rate at which to call
    //! etharp_tmr().
    //
    //*****************************************************************************
    static unsigned long g_ulARPTimer = 0;

    //*****************************************************************************
    //
    //! The lwIP DHCP coarse timer, used to determine the rate at which to call
    //! dhcp_coarse_tmr().
    //
    //*****************************************************************************
    #if defined(USE_DHCP) || defined(DOXYGEN)
    static unsigned long g_ulDHCPCoarseTimer = 0;
    #endif

    //*****************************************************************************
    //
    //! The lwIP DHCP fine timer, used to determine the rate at which to call
    //! dhcp_fine_tmr().
    //
    //*****************************************************************************
    #if defined(USE_DHCP) || defined(DOXYGEN)
    static unsigned long g_ulDHCPFineTimer = 0;
    #endif

    //*****************************************************************************
    //
    //! The size of the buffers used for transmitting to and receiving from the
    //! UART.
    //
    //*****************************************************************************
    #define UART_BUF_SIZE           256

    //*****************************************************************************
    //
    //! The buffer used to hold characters received from the UART.
    //
    //*****************************************************************************
    static unsigned char g_pucRXBuffer[UART_BUF_SIZE];

    //*****************************************************************************
    //
    //! The buffer used to hold characters to be sent to the UART.
    //
    //*****************************************************************************
    static unsigned char g_pucTXBuffer[UART_BUF_SIZE];

    //*****************************************************************************
    //
    //! The offset into the UART receive buffer (#g_pucRXBuffer) where the next
    //! character is to be read.  The buffer is empty when this is equal to the
    //! write offset (#g_ulRXWrite), and is full when the write offset is one
    //! character behind the read offset (modulo the buffer size).
    //
    //*****************************************************************************
    static unsigned long g_ulRXRead;

    //*****************************************************************************
    //
    //! The offset into the UART receive buffer (#g_pucRXBuffer) where the next
    //! character is to be written.  The buffer is empty when this is equal to the
    //! read offset (#g_ulRXRead), and is full when the write offset is one
    //! character behind the read offset (modulo the buffer size).
    //
    //*****************************************************************************
    static unsigned long g_ulRXWrite;

    //*****************************************************************************
    //
    //! The offset into the UART transmit buffer (#g_pucTXBuffer) where the next
    //! character is to be read.  The buffer is empty when this is equal to the
    //! write offset (#g_ulTXWrite), and is full when the write offset is one
    //! character behind the read offset (modulo the buffer size).
    //
    //*****************************************************************************
    static unsigned long g_ulTXRead;

    //*****************************************************************************
    //
    //! The offset into the UART transmit buffer (#g_pucTXBuffer) where the next
    //! character is to be written.  The buffer is empty when this is equal to the
    //! read offset (#g_ulTXRead), and is full when the write offset is one
    //! character behind the read offset (modulo the buffer size).
    //
    //*****************************************************************************
    static unsigned long g_ulTXWrite;

    //*****************************************************************************
    //
    //! A buffer used to construct a packet of data to be transmitted to the telnet
    //! client.
    //
    //*****************************************************************************
    static unsigned char g_pucTelnetBuffer[512];

    //*****************************************************************************
    //
    //! The number of bytes of valid data in the telnet packet buffer
    //! (#g_pucTelnetBuffer).
    //
    //*****************************************************************************
    static unsigned long g_ulTelnetLength;

    //*****************************************************************************
    //
    //! A pointer to the telnet session PCB data structure.
    //
    //*****************************************************************************
    static struct tcp_pcb *g_psTelnetPCB = NULL;

    //*****************************************************************************
    //
    //! A counter for the TCP connection timeout.
    //
    //*****************************************************************************
    #if TELNET_TIMEOUT || defined(DOXYGEN)
    static unsigned long g_ulConnectionTimeout;
    #endif

    //*****************************************************************************
    //
    // The error routine that is called if the driver library encounters an error.
    //
    //*****************************************************************************
    #ifdef DEBUG
    void
    __error__(char *pcFilename, unsigned long ulLine)
    {
    }
    #endif

    //*****************************************************************************
    //
    //! Handles the SysTick interrupt.
    //!
    //! This function is called when the SysTick timer expires.  It increments the
    //! lwIP timers and sets a flag indicating that the timeout functions need to
    //! be called if necessary.
    //!
    //! \return None.
    //
    //*****************************************************************************
    void
    SysTickIntHandler(void)
    {
        //
        // Increment the assorted timers.
        //
        g_ulTCPFastTimer += SYSTICKMS;
        g_ulTCPSlowTimer += SYSTICKMS;
        g_ulARPTimer += SYSTICKMS;
    #ifdef USE_DHCP
        g_ulDHCPCoarseTimer += SYSTICKMS;
        g_ulDHCPFineTimer += SYSTICKMS;
    #endif

        //
        // Indicate that a SysTick has occurred.
        //
        HWREGBITW(&g_ulFlags, FLAG_SYSTICK) = 1;
    }

    //*****************************************************************************
    //
    //! Handles the Ethernet interrupt.
    //!
    //! This function is called when the Ethernet controller generates an interrupt
    //! as a result of the reception of a packet.  It sets a flag indicating that
    //! lwIP should read the packet when possible.
    //!
    //! \return None.
    //
    //*****************************************************************************
    void
    EthernetIntHandler(void)
    {
        unsigned long ulTemp;

        //
        // Read and clear the interrupt(s).
        //
        ulTemp = EthernetIntStatus(ETH_BASE, false);
        EthernetIntClear(ETH_BASE, ulTemp);

        //
        // See if the Ethernet receive interrupt occurred.
        //
        if(ulTemp & ETH_INT_RX)
        {
            //
            // Indicate that the Ethernet receive intererupt occurred.
            //
            HWREGBITW(&g_ulFlags, FLAG_RXPKT) = 1;

            //
            // Disable the receive interrupt.
            //
            EthernetIntDisable(ETH_BASE, ETH_INT_RX);
        }

        //
        // See if the Ethernet transmit interrupt occurred.
        //
        if(ulTemp & ETH_INT_TX)
        {
            //
            // Disable the transmit interrupt.
            //
            EthernetIntDisable(ETH_BASE, ETH_INT_TX);
        }
    }

    //*****************************************************************************
    //
    //! Handles the UART interrupt.
    //!
    //! This function is called when the UART generates an interrupt.  An interrupt
    //! will be generated when data is received and when the transmit FIFO becomes
    //! half empty.  The transmit and receive FIFOs are processed as appropriate.
    //!
    //! \return None.
    //
    //*****************************************************************************
    void
    UARTIntHandler(void)
    {
        unsigned long ulStatus;
        unsigned char ucChar;

        //
        // Get the cause of the interrupt.
        //
        ulStatus = UARTIntStatus(UART0_BASE, true);

        //
        // Clear the cause of the interrupt.
        //
        UARTIntClear(UART0_BASE, ulStatus);

        //
        // See if there is data to be processed in the receive FIFO.
        //
        if(ulStatus & (UART_INT_RT | UART_INT_RX))
        {
            //
            // Loop while there are characters available in the receive FIFO.
            //
            while(UARTCharsAvail(UART0_BASE))
            {
                //
                // Get the next character from the receive FIFO.
                //
                ucChar = UARTCharGet(UART0_BASE);

                //
                // See if this character is 0xff and there is space for two
                // characters in the receive FIFO.
                //
                if((ucChar == 0xff) &&
                   (((g_ulRXWrite + 1) % UART_BUF_SIZE) != g_ulRXRead) &&
                   (((g_ulRXWrite + 2) % UART_BUF_SIZE) != g_ulRXRead))
                {
                    //
                    // Write the 0xff into the receive FIFO twice since 0xff is the
                    // interpret as command (IAC) byte for telnet, and a doubled
                    // 0xff is interpreted as a single 0xff byte.
                    //
                    g_pucRXBuffer[g_ulRXWrite] = ucChar;
                    g_ulRXWrite = (g_ulRXWrite + 1) % UART_BUF_SIZE;
                    g_pucRXBuffer[g_ulRXWrite] = ucChar;
                    g_ulRXWrite = (g_ulRXWrite + 1) % UART_BUF_SIZE;
                }

                //
                // See if the character is not 0xff adn there is space for a
                // character in the receive FIFO.
                //
                if((ucChar != 0xff) &&
                   (((g_ulRXWrite + 1) % UART_BUF_SIZE) != g_ulRXRead))
                {
                    g_pucRXBuffer[g_ulRXWrite] = ucChar;
                    g_ulRXWrite = (g_ulRXWrite + 1) % UART_BUF_SIZE;
                }
            }

            //
            // Set a flag indicating that there are newly received characters that
            // need to be handled.
            //
            HWREGBITW(&g_ulFlags, FLAG_RXUART) = 1;
        }

        //
        // See if there is space to be filled in the transmit FIFO.
        //
        if(ulStatus & UART_INT_TX)
        {
            //
            // Loop while there is space in the transmit FIFO and characters to be
            // sent.
            //
            while((g_ulTXRead != g_ulTXWrite) && UARTSpaceAvail(UART0_BASE))
            {
                //
                // Write the next character into the transmit FIFO.
                //
                UARTCharPut(UART0_BASE, g_pucTXBuffer[g_ulTXRead]);

                //
                // Advance the read offset.
                //
                g_ulTXRead = (g_ulTXRead + 1) % UART_BUF_SIZE;
            }
        }
    }

    //*****************************************************************************
    //
    //! Sends a character to the UART.
    //!
    //! \param ucChar is the character to be sent.
    //!
    //! This function sends a character to the UART.  The character will either be
    //! directly written into the UART FIFO or into the UART transmit buffer, as
    //! appropriate.
    //!
    //! \return None.
    //
    //*****************************************************************************
    static void
    UARTSend(unsigned char ucChar)
    {
        //
        // Disable the UART transmit interrupt while determining how to handle this
        // character.  Failure to do so could result in the loss of this character,
        // or stalled output due to this character being placed into the UART
        // transmit buffer but never transferred out into the UART FIFO.
        //
        UARTIntDisable(UART0_BASE, UART_INT_TX);

        //
        // See if the transmit buffer is empty and there is space in the FIFO.
        //
        if((g_ulTXRead == g_ulTXWrite) && UARTSpaceAvail(UART0_BASE))
        {
            //
            // Write this character directly into the FIFO.
            //
            UARTCharPut(UART0_BASE, ucChar);
        }

        //
        // See if there is room in the transmit buffer.
        //
        else if(((g_ulTXWrite + 1) % UART_BUF_SIZE) != g_ulTXRead)
        {
            //
            // Put this character into the transmit buffer.
            //
            g_pucTXBuffer[g_ulTXWrite] = ucChar;

            //
            // Increment the transmit buffer write pointer.
            //
            g_ulTXWrite = (g_ulTXWrite + 1) % UART_BUF_SIZE;
        }

        //
        // Enable the UART transmit interrupt.
        //
        UARTIntEnable(UART0_BASE, UART_INT_TX);
    }

    //*****************************************************************************
    //
    //! Closes an existing Ethernet connection.
    //!
    //! \param pcb is the pointer to the TCP control structure.
    //!
    //! This function is called when the the TCP connection should be closed.
    //!
    //! \return None.
    //
    //*****************************************************************************
    static void
    TelnetClose(struct tcp_pcb *pcb)
    {
        //
        // Clear out all of the TCP callbacks.
        //
        tcp_arg(pcb, NULL);
        tcp_sent(pcb, NULL);
        tcp_recv(pcb, NULL);
        tcp_err(pcb, NULL);
        tcp_poll(pcb, NULL, 1);

        //
        // Clear the telnet data structure pointer, to indicate that
        // we are no longer connected.
        //
        g_psTelnetPCB = NULL;

        //
        // Close the TCP connection.
        //
        tcp_close(pcb);
    }

    //*****************************************************************************
    //
    //! Processes a telnet WILL request.
    //!
    //! \param ucOption is the telnet option in question.
    //!
    //! This function will handle a WILL request for a telnet option.  If it is an
    //! option that is known by the telnet server, a DO response will be generated
    //! if the option is not already enabled.  For unknown options, a DONT response
    //! will always be generated.
    //!
    //! The response (if any) is written into the telnet transmit buffer.
    //!
    //! \return None.
    //
    //*****************************************************************************
    static void
    TelnetProcessWill(unsigned char ucOption)
    {
        unsigned long ulIdx;

        //
        // Loop through the known options.
        //
        for(ulIdx = 0; ulIdx < (sizeof(g_psOptions) / sizeof(g_psOptions[0]));
            ulIdx++)
        {
            //
            // See if this option matches the option in question.
            //
            if(g_psOptions[ulIdx].ucOption == ucOption)
            {
                //
                // See if the WILL flag for this option has already been set.
                //
                if(HWREGBITB(&(g_psOptions[ulIdx].ucFlags), OPT_FLAG_WILL) == 0)
                {
                    //
                    // Set the WILL flag for this option.
                    //
                    HWREGBITB(&(g_psOptions[ulIdx].ucFlags), OPT_FLAG_WILL) = 1;

                    //
                    // Send a DO response to this option.
                    //
                    g_pucTelnetBuffer[g_ulTelnetLength++] = TELNET_IAC;
                    g_pucTelnetBuffer[g_ulTelnetLength++] = TELNET_DO;
                    g_pucTelnetBuffer[g_ulTelnetLength++] = ucOption;
                }

                //
                // Return without any further processing.
                //
                return;
            }
        }

        //
        // This option is not recognized, so send a DONT response.
        //
        g_pucTelnetBuffer[g_ulTelnetLength++] = TELNET_IAC;
        g_pucTelnetBuffer[g_ulTelnetLength++] = TELNET_DONT;
        g_pucTelnetBuffer[g_ulTelnetLength++] = ucOption;
    }

    //*****************************************************************************
    //
    //! Processes a telnet WONT request.
    //!
    //! \param ucOption is the telnet option in question.
    //!
    //! This function will handle a WONT request for a telnet option.  If it is an
    //! option that is known by the telnet server, a DONT response will be
    //! generated if the option is not already disabled.  For unknown options, a
    //! DONT response will always be generated.
    //!
    //! The response (if any) is written into the telnet transmit buffer.
    //!
    //! \return None.
    //
    //*****************************************************************************
    static void
    TelnetProcessWont(unsigned char ucOption)
    {
        unsigned long ulIdx;

        //
        // Loop through the known options.
        //
        for(ulIdx = 0; ulIdx < (sizeof(g_psOptions) / sizeof(g_psOptions[0]));
            ulIdx++)
        {
            //
            // See if this option matches the option in question.
            //
            if(g_psOptions[ulIdx].ucOption == ucOption)
            {
                //
                // See if the WILL flag for this option is currently set.
                //
                if(HWREGBITB(&(g_psOptions[ulIdx].ucFlags), OPT_FLAG_WILL) == 1)
                {
                    //
                    // Clear the WILL flag for this option.
                    //
                    HWREGBITB(&(g_psOptions[ulIdx].ucFlags), OPT_FLAG_WILL) = 0;

                    //
                    // Send a DONT response to this option.
                    //
                    g_pucTelnetBuffer[g_ulTelnetLength++] = TELNET_IAC;
                    g_pucTelnetBuffer[g_ulTelnetLength++] = TELNET_DONT;
                    g_pucTelnetBuffer[g_ulTelnetLength++] = ucOption;
                }

                //
                // Return without any further processing.
                //
                return;
            }
        }

        //
        // This option is not recognized, so send a DONT response.
        //
        g_pucTelnetBuffer[g_ulTelnetLength++] = TELNET_IAC;
        g_pucTelnetBuffer[g_ulTelnetLength++] = TELNET_DONT;
        g_pucTelnetBuffer[g_ulTelnetLength++] = ucOption;
    }

    //*****************************************************************************
    //
    //! Processes a telnet DO request.
    //!
    //! \param ucOption is the telnet option in question.
    //!
    //! This function will handle a DO request for a telnet optoin.  If it is an
    //! option that is known by the telnet server, a WILL response will be
    //! generated if the option is not already enabled.  For unknown options, a
    //! WONT response will always be generated.
    //!
    //! The response (if any) is written into the telnet transmit buffer.
    //!
    //! \return None.
    //
    //*****************************************************************************
    static void
    TelnetProcessDo(unsigned char ucOption)
    {
        unsigned long ulIdx;

        //
        // Loop through the known options.
        //
        for(ulIdx = 0; ulIdx < (sizeof(g_psOptions) / sizeof(g_psOptions[0]));
            ulIdx++)
        {
            //
            // See if this option matches the option in question.
            //
            if(g_psOptions[ulIdx].ucOption == ucOption)
            {
                //
                // See if the DO flag for this option has already been set.
                //
                if(HWREGBITB(&(g_psOptions[ulIdx].ucFlags), OPT_FLAG_DO) == 0)
                {
                    //
                    // Set the DO flag for this option.
                    //
                    HWREGBITB(&(g_psOptions[ulIdx].ucFlags), OPT_FLAG_DO) = 1;

                    //
                    // Send a WILL response to this option.
                    //
                    g_pucTelnetBuffer[g_ulTelnetLength++] = TELNET_IAC;
                    g_pucTelnetBuffer[g_ulTelnetLength++] = TELNET_WILL;
                    g_pucTelnetBuffer[g_ulTelnetLength++] = ucOption;
                }

                //
                // Return without any further processing.
                //
                return;
            }
        }

        //
        // This option is not recognized, so send a WONT response.
        //
        g_pucTelnetBuffer[g_ulTelnetLength++] = TELNET_IAC;
        g_pucTelnetBuffer[g_ulTelnetLength++] = TELNET_WONT;
        g_pucTelnetBuffer[g_ulTelnetLength++] = ucOption;
    }

    //*****************************************************************************
    //
    //! Processes a telnet DONT request.
    //!
    //! \param ucOption is the telnet option in question.
    //!
    //! This funciton will handle a DONT request for a telnet option.  If it is an
    //! option that is known by the telnet server, a WONT response will be
    //! generated if the option is not already disabled.  For unknown options, a
    //! WONT resopnse will always be generated.
    //!
    //! The response (if any) is written into the telnet transmit buffer.
    //!
    //! \return None.
    //
    //*****************************************************************************
    static void
    TelnetProcessDont(unsigned char ucOption)
    {
        unsigned long ulIdx;

        //
        // Loop through the known options.
        //
        for(ulIdx = 0; ulIdx < (sizeof(g_psOptions) / sizeof(g_psOptions[0]));
            ulIdx++)
        {
            //
            // See if this option matches the option in question.
            //
            if(g_psOptions[ulIdx].ucOption == ucOption)
            {
                //
                // See if the DO flag for this option is currently set.
                //
                if(HWREGBITB(&(g_psOptions[ulIdx].ucFlags), OPT_FLAG_DO) == 1)
                {
                    //
                    // Clear the DO flag for this option.
                    //
                    HWREGBITB(&(g_psOptions[ulIdx].ucFlags), OPT_FLAG_DO) = 0;

                    //
                    // Send a WONT response to this option.
                    //
                    g_pucTelnetBuffer[g_ulTelnetLength++] = TELNET_IAC;
                    g_pucTelnetBuffer[g_ulTelnetLength++] = TELNET_WONT;
                    g_pucTelnetBuffer[g_ulTelnetLength++] = ucOption;
                }

                //
                // Return without any further processing.
                //
                return;
            }
        }

        //
        // This option is not recognized, so send a WONT response.
        //
        g_pucTelnetBuffer[g_ulTelnetLength++] = TELNET_IAC;
        g_pucTelnetBuffer[g_ulTelnetLength++] = TELNET_WONT;
        g_pucTelnetBuffer[g_ulTelnetLength++] = ucOption;
    }

    //*****************************************************************************
    //
    //! Processes a character received from the telnet port.
    //!
    //! \param ucChar is the character in question.
    //!
    //! This function processes a character received from the telnet port, handling
    //! the interpretation of telnet commands (as indicated by the telnet interpret
    //! as command (IAC) byte).
    //!
    //! \return None.
    //
    //*****************************************************************************
    static void
    TelnetProcessCharacter(unsigned char ucChar)
    {
        //
        // Determine the current state of the telnet command parser.
        //
        switch(g_eState)
        {
            //
            // The normal state of the parser, were each character is either sent
            // to the UART or is a telnet IAC character.
            //
            case STATE_NORMAL:
            {
                //
                // See if this character is the IAC character.
                //
                if(ucChar == TELNET_IAC)
                {
                    //
                    // Skip this character and go to the IAC state.
                    //
                    g_eState = STATE_IAC;
                }
                else
                {
                    //
                    // Write this character to the UART.
                    //
                    UARTSend(ucChar);
                }

                //
                // This state has been handled.
                //
                break;
            }

            //
            // The previous character was the IAC character.
            //
            case STATE_IAC:
            {
                //
                // Determine how to interpret this character.
                //
                switch(ucChar)
                {
                    //
                    // See if this character is also an IAC character.
                    //
                    case TELNET_IAC:
                    {
                        //
                        // Send 0xff to the UART.
                        //
                        UARTSend(ucChar);

                        //
                        // Switch back to normal mode.
                        //
                        g_eState = STATE_NORMAL;

                        //
                        // This character has been handled.
                        //
                        break;
                    }

                    //
                    // See if this character is the WILL request.
                    //
                    case TELNET_WILL:
                    {
                        //
                        // Switch to the WILL mode; the next character will have
                        // the option in question.
                        //
                        g_eState = STATE_WILL;

                        //
                        // This character has been handled.
                        //
                        break;
                    }

                    //
                    // See if this character is the WONT request.
                    //
                    case TELNET_WONT:
                    {
                        //
                        // Switch to the WONT mode; the next character will have
                        // the option in question.
                        //
                        g_eState = STATE_WONT;

                        //
                        // This character has been handled.
                        //
                        break;
                    }

                    //
                    // See if this character is the DO request.
                    //
                    case TELNET_DO:
                    {
                        //
                        // Switch to the DO mode; the next character will have the
                        // option in question.
                        //
                        g_eState = STATE_DO;

                        //
                        // This character has been handled.
                        //
                        break;
                    }

                    //
                    // See if this character is the DONT request.
                    //
                    case TELNET_DONT:
                    {
                        //
                        // Switch to the DONT mode; the next character will have
                        // the option in question.
                        //
                        g_eState = STATE_DONT;

                        //
                        // This character has been handled.
                        //
                        break;
                    }

                    //
                    // See if this character is the AYT request.
                    //
                    case TELNET_AYT:
                    {
                        //
                        // Send a short string back to the client so that it knows
                        // that we're still alive.
                        //
                        g_pucTelnetBuffer[g_ulTelnetLength++] = '\r';
                        g_pucTelnetBuffer[g_ulTelnetLength++] = '\n';
                        g_pucTelnetBuffer[g_ulTelnetLength++] = '[';
                        g_pucTelnetBuffer[g_ulTelnetLength++] = 'Y';
                        g_pucTelnetBuffer[g_ulTelnetLength++] = 'e';
                        g_pucTelnetBuffer[g_ulTelnetLength++] = 's';
                        g_pucTelnetBuffer[g_ulTelnetLength++] = ']';
                        g_pucTelnetBuffer[g_ulTelnetLength++] = '\r';
                        g_pucTelnetBuffer[g_ulTelnetLength++] = '\n';

                        //
                        // Switch back to normal mode.
                        //
                        g_eState = STATE_NORMAL;

                        //
                        // This character has been handled.
                        //
                        break;
                    }

                    //
                    // Explicitly ignore the GA and NOP request, plus provide a
                    // catch-all ignore for unrecognized requests.
                    //
                    case TELNET_GA:
                    case TELNET_NOP:
                    default:
                    {
                        //
                        // Switch back to normal mode.
                        //
                        g_eState = STATE_NORMAL;

                        //
                        // This character has been handled.
                        //
                        break;
                    }
                }

                //
                // This state has been handled.
                //
                break;
            }

            //
            // The previous character sequence was IAC WILL.
            //
            case STATE_WILL:
            {
                //
                // Process the WILL request on this option.
                //
                TelnetProcessWill(ucChar);

                //
                // Switch back to normal mode.
                //
                g_eState = STATE_NORMAL;

                //
                // This state has been handled.
                //
                break;
            }

            //
            // The previous character sequence was IAC WONT.
            //
            case STATE_WONT:
            {
                //
                // Process the WONT request on this option.
                //
                TelnetProcessWont(ucChar);

                //
                // Switch back to normal mode.
                //
                g_eState = STATE_NORMAL;

                //
                // This state has been handled.
                //
                break;
            }

            //
            // The previous character sequence was IAC DO.
            //
            case STATE_DO:
            {
                //
                // Process the DO request on this option.
                //
                TelnetProcessDo(ucChar);

                //
                // Switch back to normal mode.
                //
                g_eState = STATE_NORMAL;

                //
                // This state has been handled.
                //
                break;
            }

            //
            // The previous character sequence was IAC DONT.
            //
            case STATE_DONT:
            {
                //
                // Process the DONT request on this option.
                //
                TelnetProcessDont(ucChar);

                //
                // Switch back to normal mode.
                //
                g_eState = STATE_NORMAL;

                //
                // This state has been handled.
                //
                break;
            }

            //
            // A catch-all for unknown states.  This should never be reached, but
            // is provided just in case it is ever needed.
            //
            default:
            {
                //
                // Switch back to normal mode.
                //
                g_eState = STATE_NORMAL;

                //
                // This state has been handled.
                //
                break;
            }
        }
    }

    //*****************************************************************************
    //
    //! Receives a TCP packet from lwIP for the telnet server.
    //!
    //! \param arg is not used in this implementation.
    //! \param pcb is the pointer to the TCP control structure.
    //! \param p is the pointer to the PBUF structure containing the packet data.
    //! \param err is used to indicate if any errors are associated with the
    //! incoming packet.
    //!
    //! This function is called when the lwIP TCP/IP stack has an incoming packet
    //! to be processed.
    //!
    //! \return This function will return an lwIP defined error code.
    //
    //*****************************************************************************
    static err_t
    TelnetReceive(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
    {
        struct pbuf *q;
        unsigned long ulIdx;
        unsigned char *pucData;

        //
        // Process the incoming packet.
        //
        if((err == ERR_OK) && (p != NULL))
        {
            //
            // Accept the packet from TCP.
            //
            tcp_recved(pcb, p->tot_len);

            //
            // Loop through the pbufs in this packet.
            //
            for(q = p, pucData = q->payload; q != NULL; q = q->next)
            {
                //
                // Loop through the bytes in this pbuf.
                //
                for(ulIdx = 0; ulIdx < q->len; ulIdx++)
                {
                    //
                    // Process this character.
                    //
                    TelnetProcessCharacter(pucData[ulIdx]);
                }
            }

            //
            // Free the pbuf.
            //
            pbuf_free(p);
        }

        //
        // If a null packet is passed in, close the connection.
        //
        else if((err == ERR_OK) && (p == NULL))
        {
            TelnetClose(pcb);
        }

        //
        // Return okay.
        //
        return(ERR_OK);
    }

    //*****************************************************************************
    //
    //! Handles lwIP TCP/IP errors.
    //!
    //! \param arg is not used in this implementation.
    //! \param err is the error that was detected.
    //!
    //! This function is called when the lwIP TCP/IP stack has detected an error.
    //! The connection is no longer valid.
    //!
    //! \return None.
    //
    //*****************************************************************************
    static void
    TelnetError(void *arg, err_t err)
    {
        //
        // Reset our connection.
        //
        g_psTelnetPCB = NULL;
    }

    //*****************************************************************************
    //
    //! Handles lwIP TCP/IP polling and timeout requests.
    //!
    //! \param arg is not used in this implementation.
    //! \param pcb is the pointer to the TCP control structure.
    //!
    //! This function is called when the lwIP TCP/IP stack has no incoming or
    //! outgoing data.  It can be used to reset an idle connection.
    //!
    //! \return This function will return an lwIP defined error code.
    //
    //*****************************************************************************
    static err_t
    TelnetPoll(void *arg, struct tcp_pcb *pcb)
    {
        //
        // Increment the timeout value and close the telnet connection if the
        // configured timeout has been exceeded.
        //
    #if TELNET_TIMEOUT
        g_ulConnectionTimeout++;
        if(g_ulConnectionTimeout > TELNET_TIMEOUT)
        {
            //
            // Close the telnet connection.
            //
            tcp_abort(g_psTelnetPCB);
            g_psTelnetPCB = NULL;
        }
    #endif

        //
        // Return OK.
        //
        return(ERR_OK);
    }

    //*****************************************************************************
    //
    //! Handles acknowledgment of data transmitted via Ethernet.
    //!
    //! \param arg is not used in this implementation.
    //! \param pcb is the pointer to the TCP control structure.
    //! \param len is the length of the data transmitted.
    //!
    //! This function is called when the lwIP TCP/IP stack has received an
    //! acknowledgment for data that has been transmitted.
    //!
    //! \return This function will return an lwIP defined error code.
    //
    //*****************************************************************************
    static err_t
    TelnetSent(void *arg, struct tcp_pcb *pcb, u16_t len)
    {
        //
        // Reset the connection timeout.
        //
    #if TELNET_TIMEOUT
        g_ulConnectionTimeout = 0;
    #endif

        //
        // Return OK.
        //
        return(ERR_OK);
    }

    //*****************************************************************************
    //
    //! Accepts a TCP connection for the telnet port.
    //!
    //! \param arg is not used in this implementation.
    //! \param pcb is the pointer to the TCP control structure.
    //! \param err is not used in this implementation.
    //!
    //! This function is called when the lwIP TCP/IP stack has an incoming
    //! connection request on the telnet port.
    //!
    //! \return This function will return an lwIP defined error code.
    //
    //*****************************************************************************
    static err_t
    TelnetAccept(void *arg, struct tcp_pcb *pcb, err_t err)
    {
        unsigned long ulIdx;

        //
        // Check if already connected.
        //
        if(g_psTelnetPCB)
        {
            //
            // If we already have a connection, kill it and start over.
            //
            TelnetClose(g_psTelnetPCB);
        }

        //
        // Set the connection timeout to 0.
        //
    #if TELNET_TIMEOUT
        g_ulConnectionTimeout = 0;
    #endif

        //
        // Set the connection as busy.
        //
        g_psTelnetPCB = pcb;

        //
        // Setup the TCP connection priority.
        //
        tcp_setprio(pcb, TCP_PRIO_MIN);

        //
        // Setup the TCP callback argument.
        //
        tcp_arg(pcb, NULL);

        //
        // Setup the TCP receive function.
        //
        tcp_recv(pcb, TelnetReceive);

        //
        // Setup the TCP error function.
        //
        tcp_err(pcb, TelnetError);

        //
        // Setup the TCP polling function/interval.
        //
        tcp_poll(pcb, TelnetPoll, (1000 / TCP_SLOW_INTERVAL));

        //
        // Setup the TCP sent callback function.
        //
        tcp_sent(pcb, TelnetSent);

        //
        // Send the telnet initialization string.
        //
        for(ulIdx = 0; ulIdx < sizeof(g_pucTelnetInit); ulIdx++)
        {
            g_pucTelnetBuffer[g_ulTelnetLength++] = g_pucTelnetInit[ulIdx];
        }

        //
        // Return a success code.
        //
        return(ERR_OK);
    }

    //*****************************************************************************
    //
    //! Initializes the lwIP TCP/IP stack.
    //!
    //! This function handles the initialization of the lwIP TCP/IP stack, along
    //! with configuration of the Ethernet controller and the lwIP driver for it.
    //!
    //! \return None.
    //
    //*****************************************************************************
    static void
    lwIPInit(void)
    {
        struct ip_addr xIpAddr, xNetMask, xGateway;
        unsigned long ulUser0, ulUser1;
        unsigned char pucMACArray[8];
        void *pcb;

        //
        // Configure the hardware MAC address for Ethernet controller filtering of
        // incoming packets.
        //
        FlashUserGet(&ulUser0, &ulUser1);
        pucMACArray[0] = ((ulUser0 >>  0) & 0xff);
        pucMACArray[1] = ((ulUser0 >>  8) & 0xff);
        pucMACArray[2] = ((ulUser0 >> 16) & 0xff);
        pucMACArray[3] = ((ulUser1 >>  0) & 0xff);
        pucMACArray[4] = ((ulUser1 >>  8) & 0xff);
        pucMACArray[5] = ((ulUser1 >> 16) & 0xff);

        //
        // Program the hardware with it's MAC address (for filtering).
        //
        EthernetMACAddrSet(ETH_BASE, pucMACArray);

        //
        // Low-Level initialization of the lwIP stack modules.
        //
        stats_init();
        sys_init();
        mem_init();
        memp_init();
        pbuf_init();
        etharp_init();
        ip_init();
        udp_init();
        tcp_init();
        netif_init();

        //
        // Create, configure and add the Ethernet controller interface.
        //
    #ifdef USE_STATIC_IP
        IP4_ADDR(&xIpAddr, STATIC_IPADDR0, STATIC_IPADDR1, STATIC_IPADDR2,
                 STATIC_IPADDR3);
        IP4_ADDR(&xNetMask, STATIC_NETMASK0, STATIC_NETMASK1, STATIC_NETMASK2,
                 STATIC_NETMASK3);
        IP4_ADDR(&xGateway, STATIC_GWADDR0, STATIC_GWADDR1, STATIC_GWADDR2,
                 STATIC_GWADDR3);
    #else
        IP4_ADDR(&xIpAddr, 0, 0, 0, 0);
        IP4_ADDR(&xNetMask, 0, 0, 0, 0);
        IP4_ADDR(&xGateway, 0, 0, 0, 0);
    #endif
        netif_add(&g_sEMAC_if, &xIpAddr, &xNetMask, &xGateway, NULL,
                  ethernetif_init, ip_input);
        netif_set_default(&g_sEMAC_if);
    #ifdef USE_DHCP
        dhcp_start(&g_sEMAC_if);
    #endif

        //
        // Bring the interface up.
        //
        netif_set_up(&g_sEMAC_if);

        //
        // Disable Ethernet TX Packet Interrupt.
        //
        EthernetIntDisable(ETH_BASE, ETH_INT_TX);

        //
        // Initialize the application to listen on the telnet port.
        //
        pcb = tcp_new();
        tcp_bind(pcb, IP_ADDR_ANY, TELNET_PORT);
        pcb = tcp_listen(pcb);
        tcp_accept(pcb, TelnetAccept);
    }

    //*****************************************************************************
    //
    //! Handles the main application loop.
    //!
    //! This function initializes and configures the device and the software, then
    //! performs the main loop.  All the actual TCP/IP processing occurs within
    //! this function (since lwIP is not reentrant).
    //!
    //! \return Never returns.
    //
    //*****************************************************************************
    int
    main(void)
    {
        unsigned long ulIdx, ulLen;

        //
        // Set the processor to run at 50 MHz, allowing UART operation at up to
        // 3.125 MHz.
        //
        SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_8MHZ);

        //
        // Enable the UART and the GPIO module that its pins are routed through.
        //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

        //
        // Configure the UART pins appropriately.
        //
        GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

        //
        // Configure the UART.
        //
        UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), UART_BAUDRATE,
                            UART_DATABITS | UART_PARITY | UART_STOPBITS);

        //
        // Enable the UART transmit and receive interrupts.
        //
        UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);
        IntEnable(INT_UART0);

        //
        // Enable and reset the Ethernet controller.
        //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_ETH);
        SysCtlPeripheralReset(SYSCTL_PERIPH_ETH);

        //
        // Configure LED0/LED1 to output the Ethernet link and activity indicators.
        //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3, GPIO_DIR_MODE_HW);
        GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);

        //
        // Configure SysTick for a periodic interrupt.
        //
        SysTickPeriodSet(SysCtlClockGet() / SYSTICKHZ);
        SysTickEnable();
        SysTickIntEnable();

        //
        // Initialize all of the lwIP code, as needed, which will also initialize
        // the low-level Ethernet code.
        //
        lwIPInit();

        //
        // Main Application Loop (for systems with no RTOS).  Run every SYSTICK.
        //
        while(true)
        {
            //
            // Wait for an event to occur.
            //
            SysCtlSleep();

            //
            // Reset the length of the telnet packet to be sent.
            //
            g_ulTelnetLength = 0;

            //
            // Check if a SYSTICK has occurred.
            //
            if(HWREGBITW(&g_ulFlags, FLAG_SYSTICK))
            {
                //
                // Clear the SysTick interrupt flag.
                //
                HWREGBITW(&g_ulFlags, FLAG_SYSTICK) = 0;

                //
                // Call the ARP timer when appropriate.
                //
                if(g_ulARPTimer >= ARP_TMR_INTERVAL)
                {
                    g_ulARPTimer = 0;
                    etharp_tmr();
                }

                //
                // Call the TCP slow timer when appropriate.
                //
                if(g_ulTCPSlowTimer >= TCP_SLOW_INTERVAL)
                {
                    g_ulTCPSlowTimer = 0;
                    tcp_slowtmr();
                }

                //
                // Call the TCP fast timer when appropriate.
                //
                if(g_ulTCPFastTimer >= TCP_FAST_INTERVAL)
                {
                    g_ulTCPFastTimer = 0;
                    tcp_fasttmr();
                }

                //
                // Call the DHCP coarse timer when appropriate.
                //
    #ifdef USE_DHCP
                if(g_ulDHCPCoarseTimer >= (DHCP_COARSE_TIMER_SECS * 1000))
                {
                    g_ulDHCPCoarseTimer = 0;
                    dhcp_coarse_tmr();
                }
    #endif

                //
                // Call the DHCP fine timer when appropriate.
                //
    #ifdef USE_DHCP
                if(g_ulDHCPFineTimer >= DHCP_FINE_TIMER_MSECS)
                {
                    g_ulDHCPFineTimer = 0;
                    dhcp_fine_tmr();
                }
    #endif
            }

            //
            // Check to see if data was received from the Ethernet controller.
            //
            if(HWREGBITW(&g_ulFlags, FLAG_RXPKT))
            {
                //
                // Clear the Rx Packet interrupt flag.
                //
                HWREGBITW(&g_ulFlags, FLAG_RXPKT) = 0;

                //
                // Check and process incoming packets
                //
                while(ethernetif_input(&g_sEMAC_if) == true)
                {
                }

                //
                // Enable Ethernet RX Packet Interrupts.
                //
                EthernetIntEnable(ETH_BASE, ETH_INT_RX);
            }

            //
            // Check to see if data was received from the UART.
            //
            if(HWREGBITW(&g_ulFlags, FLAG_RXUART))
            {
                //
                // Clear the UART receive interrupt flag.
                //
                HWREGBITW(&g_ulFlags, FLAG_RXUART) = 0;

                //
                // See if there is an active telnet connection.
                //
                if(g_psTelnetPCB)
                {
                    //
                    // Get the current receive buffer write pointer since this may
                    // change during this processing.
                    //
                    ulLen = g_ulRXWrite;

                    //
                    // See if the write pointer is before the read pointer.
                    //
                    if(ulLen < g_ulRXRead)
                    {
                        //
                        // Copy the characters from the read pointer to the end of
                        // the receive buffer into the telnet packet buffer.
                        //
                        for(ulIdx = g_ulRXRead; ulIdx < UART_BUF_SIZE; ulIdx++)
                        {
                            g_pucTelnetBuffer[g_ulTelnetLength++] =
                                g_pucRXBuffer[ulIdx];
                        }

                        //
                        // Copy the characters from the beginning of the receive
                        // buffer to the write pointer into the telnet packet
                        // buffer.
                        //
                        for(ulIdx = 0; ulIdx < ulLen; ulIdx++)
                        {
                            g_pucTelnetBuffer[g_ulTelnetLength++] =
                                g_pucRXBuffer[ulIdx];
                        }
                    }

                    //
                    // Otherwise, the read pointer is before the write pointer.
                    //
                    else
                    {
                        //
                        // Copy the characters in the receive buffer from the read
                        // pointer to the write pointer into the telnet packet
                        // buffer.
                        //
                        for(ulIdx = g_ulRXRead; ulIdx < ulLen; ulIdx++)
                        {
                            g_pucTelnetBuffer[g_ulTelnetLength++] =
                                g_pucRXBuffer[ulIdx];
                        }
                    }

                    //
                    // Move the read pointer to the write pointer, indicating that
                    // those characters have been transmitted.
                    //
                    g_ulRXRead = ulLen;
                }

                //
                // Otherwise, there is no telnet connection.
                //
                else
                {
                    //
                    // Move the read pointer to the write pointer, discarding the
                    // characters received on the UART.
                    //
                    g_ulRXRead = g_ulRXWrite;
                }
            }

            //
            // See if there is a telnet connection and there are characters in the
            // telnet packet buffer.
            //
            if(g_psTelnetPCB && (g_ulTelnetLength != 0))
            {
                //
                // Send the contents of the telnet packet buffer on the telnet
                // connection.
                //
                tcp_write(g_psTelnetPCB, g_pucTelnetBuffer, g_ulTelnetLength, 1);
                tcp_output(g_psTelnetPCB);
            }
        }
    }

    //*****************************************************************************
    //
    // Close the Doxygen group.
    //! @}
    //
    //*****************************************************************************
#endif
