/*------------------------------------------------------------------------------
UARTS.�


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



void    InitUart0(uint32_t  ui32SysClock)
{
//    // Enable the GPIO port that is used for the on-board LED.
//    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
//
//    // Enable the GPIO pins for the LED (PN0).
//    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);

    // Enable the peripherals used by this example.
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Set GPIO A0 and A1 as UART pins.
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
    UARTTxIntModeSet(UART0_BASE, UART_TXINT_MODE_EOT);
    //TODO UARTFIFOEnable(INT_UART0);

    // Enable the UART interrupt.
    ROM_IntEnable(INT_UART0);
    ROM_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);
}


void    InitUart2(uint32_t  ui32SysClock)
{
//    // Enable the GPIO port that is used for the on-board LED.
//    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
//
//    // Enable the GPIO pins for the LED (PN0).
//    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);

    // Enable the peripherals used by this example.
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Set GPIO A0 and A1 as UART pins.
    GPIOPinConfigure(GPIO_PA6_U2RX);
    GPIOPinConfigure(GPIO_PA7_U2TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    UARTFIFOLevelSet(UART2_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
    UARTTxIntModeSet(UART2_BASE, UART_TXINT_MODE_EOT);
    //TODO UARTFIFOEnable(INT_UART2);

    // Enable the UART interrupt.
    ROM_IntEnable(INT_UART2);
    ROM_UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);
}
