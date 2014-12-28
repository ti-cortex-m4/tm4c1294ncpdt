/*------------------------------------------------------------------------------
UARTS.Ñ


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "inc/hw_ints.h"
#include        "inc/hw_memmap.h"
#include        "driverlib/gpio.h"
#include        "driverlib/pin_map.h"
#include        "driverlib/rom.h"
#include        "driverlib/sysctl.h"
#include        "driverlib/timer.h"
#include        "driverlib/uart.h"
#include        "serial0.h"


void UARTSend(const uint8_t *pui8Buffer) {
    while (*pui8Buffer) {
        ROM_UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
    }
}


void UARTSend2(const uint8_t *pui8Buffer, uint8_t wSize) {
    while (wSize-- > 0) {
        UARTCharPut(UART0_BASE, *pui8Buffer++);
    }
}


void InitUARTs(uint32_t ui32SysClock) {
    // Enable the GPIO port that is used for the on-board LED.
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

    // Enable the GPIO pins for the LED (PN0).
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);

    // Enable the peripherals used by this example.
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Set GPIO A0 and A1 as UART pins.
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8,UART_FIFO_RX1_8);
    UARTTxIntModeSet(UART0_BASE, UART_TXINT_MODE_EOT) ;
    //UARTFIFOEnable(INT_UART0);

    // Configure the UART for 115,200, 8-N-1 operation.
    ROM_UARTConfigSetExpClk(UART0_BASE, ui32SysClock, 9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    InitSerial0();

    // Enable the UART interrupt.
    ROM_IntEnable(INT_UART0);
    ROM_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);

    //UARTSend((uint8_t *)"Start");
}

/*
void UART0IntHandler2(void) {
uint32_t ui32Status;

    ui32Status = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, ui32Status);

    while(ROM_UARTCharsAvail(UART0_BASE)) {
        ROM_UARTCharPutNonBlocking(UART0_BASE, ROM_UARTCharGetNonBlocking(UART0_BASE));

        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        SysCtlDelay(5000);
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
    }
}
*/
