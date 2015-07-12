/*------------------------------------------------------------------------------
FLASH_DEFINE1,H


------------------------------------------------------------------------------*/

#define MASK_FLASH1_SCK 0x0008 // PD3
#define MASK_FLASH1_SI  0x0002 // PD1
#define MASK_FLASH1_SO  0x0001 // PD0
#define MASK_FLASH1_CS  0x0004 // PD2

#define GPIO_FLASH1_SCK (GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0020) // PD3
#define GPIO_FLASH1_SI  (GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0008) // PD1
#define GPIO_FLASH1_SO  (GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0004) // PD0
#define GPIO_FLASH1_CS  (GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0010) // PD2
