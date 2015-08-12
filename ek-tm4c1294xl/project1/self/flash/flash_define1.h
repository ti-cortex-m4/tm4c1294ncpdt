/*------------------------------------------------------------------------------
FLASH_DEFINE1,H


------------------------------------------------------------------------------*/

#define MASK_FLASH1_SCK 0x0020 // PB5
#define MASK_FLASH1_SI  0x0010 // PE4
#define MASK_FLASH1_SO  0x0020 // PE5
#define MASK_FLASH1_CS  0x0010 // PB4

#define GPIO_FLASH1_SCK (GPIO_PORTB_AHB_BASE + GPIO_O_DATA + 0x0080) // PB5
#define GPIO_FLASH1_SI  (GPIO_PORTE_AHB_BASE + GPIO_O_DATA + 0x0040) // PE4
#define GPIO_FLASH1_SO  (GPIO_PORTE_AHB_BASE + GPIO_O_DATA + 0x0080) // PE5
#define GPIO_FLASH1_CS  (GPIO_PORTB_AHB_BASE + GPIO_O_DATA + 0x0040) // PB4
