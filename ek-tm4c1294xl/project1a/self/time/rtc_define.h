/*------------------------------------------------------------------------------
RTC_DEFINE.H


------------------------------------------------------------------------------*/

#define MASK_RTC_SCK    0x0008 // B3
#define MASK_RTC_SI     0x0002 // B1
#define MASK_RTC_SO     0x0001 // B0
#define MASK_RTC_CS     0x0004 // B2

#define GPIO_RTC_SCK    (GPIO_PORTB_AHB_BASE + GPIO_O_DATA + 0x0020) // B3
#define GPIO_RTC_SI     (GPIO_PORTB_AHB_BASE + GPIO_O_DATA + 0x0008) // B1
#define GPIO_RTC_SO     (GPIO_PORTB_AHB_BASE + GPIO_O_DATA + 0x0004) // B0
#define GPIO_RTC_CS     (GPIO_PORTB_AHB_BASE + GPIO_O_DATA + 0x0010) // B2
