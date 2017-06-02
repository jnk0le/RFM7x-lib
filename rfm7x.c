//**************************************************************
//Compiler          : AVR-GCC
//Author            : jnk0le@hotmail.com
//                    https://github.com/jnk0le
//License           : MIT
//**************************************************************

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <stdint.h>
#include "rfm7x.h"

#if defined(__AVR_ARCH__)&&!defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
	const __flash uint8_t rfm7x_init_struct[] =
#else
	const uint8_t rfm7x_init_struct[] = // generic for all architectures // table will be placed in SRAM if your mcu doesn't have unified memory space (flash + ram)  
#endif
	{
		////////////////////////////////////////// bank 1 initialization registers //////////////////////////////////////////
		// datasheet values are given as little endian - LSB should be first
		// "replacing" manual have big endian order - MSB should be first
		// of course they are different and no one knows which ones are correct
		// regs 0 to 8 are double reversed so MSB is written first // regs 9 to 14 are LSB first // reg 8 is also LSB first

#if (RFM7x_MODULECHIP_USED == 0 || RFM7x_MODULECHIP_USED == 1) // BK2421 aka RFM70 + BK2401
		
		0x40,  0x4B,  0x01,  0xE2, // reg 0
		0xC0,  0x4B,  0x00,  0x00, // reg 1
		0xD0,  0xFC,  0x8C,  0x02, // reg 2
	
		// reg 3
	#if (RFM70_BANK1_REG3_MODE == 0)
		0x99,  0x00,  0x39,  0x41,
	#elif (RFM70_BANK1_REG3_MODE == 1)
		0xF9,  0x00,  0x39,  0x41,  // AN0007 "high power mode" 3-15dBm - requires additional low-pass filter to pass FCC tests
	#elif (RFM70_BANK1_REG3_MODE == 2)
		0x03,  0x00,  0x12,  0x00,
	#endif
	
		// reg 4
	#if (RFM70_BANK1_REG4_MODE == 0)
		0xD9,  0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x86,  0x0B,
	#elif (RFM70_BANK1_REG4_MODE == 1)
		0xC9,  0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x86,  0x0B,
	#elif (RFM70_BANK1_REG4_MODE == 2)
		0xF9,  0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x86,  0x0B,
	#elif (RFM70_BANK1_REG4_MODE == 3)
		0xB9,  0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x86,  0x0B,
	#elif (RFM70_BANK1_REG4_MODE == 4)
		0x09,  0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x86,  0x0B,
	#elif (RFM70_BANK1_REG4_MODE == 5)
		0xD9,  0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x86,  0x21,
	#elif (RFM70_BANK1_REG4_MODE == 6)
		0xD9,  0x86|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x82,  0x1B,
	#elif (RFM70_BANK1_REG4_MODE == 7)
		0xF9,  0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x84,  0x0B,
	#elif (RFM70_BANK1_REG4_MODE == 8)
		0xF9,  0x86|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x84,  0x1B,
	#elif (RFM70_BANK1_REG4_MODE == 9)
		0xF9,  0x86|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x80,  0x1B,
	#elif (RFM70_BANK1_REG4_MODE == 10)
		0xF9,  0x86|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x82,  0x1B,
	#endif

		// reg 5
	#if (RFM70_BANK1_REG5_MODE == 0)
		0x24,  0x06,  0x7F,  0xA6, // rfm73 // RSSI disabled
	#elif (RFM70_BANK1_REG5_MODE == 1)
		(RFM73_RSSI_THRESHOLD_LEVEL << 2),  0x02,  0x7F,  0xA6, // replace manual // RSSI enabled
	#endif

		0x00,  0x00,  0x00,  0x00, // reg 6
		0x00,  0x00,  0x00,  0x00, // reg 7
		0x00,  0x00,  0x00,  0x00, // reg 8
		0x00,  0x00,  0x00,  0x00, // reg 9
		0x00,  0x00,  0x00,  0x00, // reg A
		0x00,  0x00,  0x00,  0x00, // reg B

		// reg C
	#if (RFM70_BANK1_REGC_MODE == 0)
		0x00,  0x12,  0x73,  0x00,
	#elif (RFM70_BANK1_REGC_MODE == 1)
		0x00,  0x12,  0x73,  0x05,
	#elif (RFM70_BANK1_REGC_MODE == 2)
		0x00,  0x1a,  0x73,  0x00,
	#endif

		// reg D
	#if (RFM70_BANK1_REGD_MODE == 0)
		0x36,  0xB4,  0x80,  0x00,
	#elif (RFM70_BANK1_REGD_MODE == 1)
		0x46,  0xB4,  0x80,  0x00,
	#endif

		// reg E
	#if (RFM70_BANK1_RAMP_CURVE_MODE == 0)
		0x41,0x20,0x08,0x04,0x81,0x20,0xCF,0xF7,0xFE,0xFF,0xFF // put the ',' at the beginning of the next entry to fix compiler errors if no long address/bank0 is defined 
	#elif (RFM70_BANK1_RAMP_CURVE_MODE == 1)
		0x41,0x10,0x04,0x82,0x20,0x08,0x08,0xF2,0x7D,0xEF,0xFF // put the ',' at the beginning of the next entry to fix compiler errors if no long address/bank0 is defined 
	#endif
	
#elif (RFM7x_MODULECHIP_USED == 2) // BK2423 aka RFM73
		
		0x40,  0x4B,  0x01,  0xE2, // reg 0
		0xC0,  0x4B,  0x00,  0x00, // reg 1
		0xD0,  0xFC,  0x8C,  0x02, // reg 2
	
		// reg 3
	#if (RFM73_BANK1_REG3_MODE == 0)
		0x99,  0x00,  0x39,  0x41,
	#elif (RFM73_BANK1_REG3_MODE == 1)
		0xF9,  0x00,  0x39,  0x41,  // AN0007 "high power mode" 3-15dBm - requires additional low-pass filter to pass FCC tests
	#elif (RFM73_BANK1_REG3_MODE == 2)
		0x03,  0x00,  0x12,  0x00,
	#endif
	
		// reg 4
	#if (RFM73_BANK1_REG4_MODE == 0)
		0xD9,  0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x86,  0x0B, // rfm73 and rfm70 // probably worser
	#elif (RFM73_BANK1_REG4_MODE == 1)
		0xD9,  0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x82,  0x1B, // replace manual
	#elif (RFM73_BANK1_REG4_MODE == 2)
		0xF9,  0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x84,  0x0B, // AN0007 "high power mode" 3-15dBm - requires additional low-pass filter to pass FCC tests
	#elif (RFM73_BANK1_REG4_MODE == 3)
		0xD9,  0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x86,  0x1B,
	#elif (RFM73_BANK1_REG4_MODE == 4)
		0xF9,  0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x84,  0x1B,
	#elif (RFM73_BANK1_REG4_MODE == 5)
		0xF9,  0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x80,  0x1B,
	#elif (RFM73_BANK1_REG4_MODE == 6)
		0xD9,  0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x86,  0x21, // single carrier or constant wave ?
	#elif (RFM73_BANK1_REG4_MODE == 7)
		0xF9,  0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x82,  0x1B,
	#elif (RFM73_BANK1_REG4_MODE == 8)
		0xF9,  0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x86,  0x0B,
	#elif (RFM73_BANK1_REG4_MODE == 9)
		0xB9,  0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x86,  0x0B,
	#elif (RFM73_BANK1_REG4_MODE == 10)
		0xB9,  0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x82,  0x1B,
	#elif (RFM73_BANK1_REG4_MODE == 11)
		0x09,  0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x86,  0x0B, 
	#elif (RFM73_BANK1_REG4_MODE == 12)
		0x09,  0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x82,  0x1B, 
	#endif

		// reg 5
	#if (RFM73_BANK1_REG5_MODE == 0)
		0x24,  0x06,  0x7F,  0xA6, // rfm73 // RSSI disabled
	#elif (RFM73_BANK1_REG5_MODE == 1)
		(RFM73_RSSI_THRESHOLD_LEVEL << 2),  0x02,  0x7F,  0xA6, // replace manual // RSSI enabled
	#endif

		0x00,  0x00,  0x00,  0x00, // reg 6
		0x00,  0x00,  0x00,  0x00, // reg 7
		0x00,  0x00,  0x00,  0x00, // reg 8
		0x00,  0x00,  0x00,  0x00, // reg 9
		0x00,  0x00,  0x00,  0x00, // reg A
		0x00,  0x00,  0x00,  0x00, // reg B

		// reg C
	#if (RFM73_BANK1_REGC_MODE == 0)
		0x00,  0x10|(RFM73_CONFIG_COMPATIBLE_MODE << 1), 0x73,  0x00, // 120 us PLL // compatible with rfm70
	#elif (RFM73_BANK1_REGC_MODE == 1)
		0x00,  0x10|(RFM73_CONFIG_COMPATIBLE_MODE << 1), 0x73,  0x05, // 130 us PLL // compatible with nrf24l01+
	#elif (RFM73_BANK1_REGC_MODE == 2)
		0x00,  0x18|(RFM73_CONFIG_COMPATIBLE_MODE << 1), 0x73,  0x00, // 120 us PLL // initial value after power up
	#elif (RFM73_BANK1_REGC_MODE == 3)
		0x00,  0x18|(RFM73_CONFIG_COMPATIBLE_MODE << 1), 0x73,  0x05, // 130 us PLL // initial value after power up
	#endif

		// reg D
	#if (RFM73_BANK1_REGD_MODE == 0)
		0x36,  0xB4,  0x80,  0x00, // datasheet and initial value after power up
	#elif (RFM73_BANK1_REGD_MODE == 1)
		0x46,  0xB4,  0x80,  0x00, // replace manual and libraries
	#endif

		// reg E
	#if (RFM73_BANK1_RAMP_CURVE_MODE == 0)
		0x41,0x10,0x04,0x82,0x20,0x08,0x08,0xF2,0x7D,0xEF,0xFF // put the ',' at the beginning of the next entry to fix compiler errors if no long address/bank0 is defined 
	#elif (RFM73_BANK1_RAMP_CURVE_MODE == 1)
		0x41,0x20,0x08,0x04,0x81,0x20,0xCF,0xF7,0xFE,0xFF,0xFF // put the ',' at the beginning of the next entry to fix compiler errors if no long address/bank0 is defined 
	#endif

#elif (RFM7x_MODULECHIP_USED == 3) // bk2425 aka RFM75

		0x40,  0x4B,  0x01,  0xE2,    // reg 0
		0xC0,  0x4B,  0x00,  0x00,    // reg 1
		0xD0,  0xFC,  0x8C,  0x02,    // reg 2
	
		// reg 3
	#if (RFM75_BANK1_REG3_MODE == 0)
		0x99,  0x00,  0x39,  0x21,
	#elif (RFM75_BANK1_REG3_MODE == 1)
		0x03,  0x00,  0x12,  0x00,
	#elif (RFM75_BANK1_REG3_MODE == 2)
		0xF9,  0x00,  0x39,  0x21,
	#elif (RFM75_BANK1_REG3_MODE == 3)
		0x99,  0x00,  0x39,  0x41,
	#elif (RFM75_BANK1_REG3_MODE == 4)                                                                  
		0xF9,  0x00,  0x39,  0x41,
	#endif
	
		// reg 4
	#if (RFM75_BANK1_REG4_MODE == 0)
		0xC1|(RFM75_CONFIG_txIctrl << 3),  0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5),  0x82,  0x1B,
	#elif (RFM75_BANK1_REG4_MODE == 1)
		0xC1|(RFM75_CONFIG_txIctrl << 3),  0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5),  0x82,  0xDB,
	#elif (RFM75_BANK1_REG4_MODE == 2)
		0xC1|(RFM75_CONFIG_txIctrl << 3),  0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5),  0x8A,  0xDB,
	#elif (RFM75_BANK1_REG4_MODE == 3)
		0xC1|(RFM75_CONFIG_txIctrl << 3),  0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5),  0x82,  0x21,
	#elif (RFM75_BANK1_REG4_MODE == 4)
		0xC1|(RFM75_CONFIG_txIctrl << 3),  0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5),  0x80,  0x1B,
	#elif (RFM75_BANK1_REG4_MODE == 5)
		0xC1|(RFM75_CONFIG_txIctrl << 3),  0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5),  0x80,  0xDB,
	#elif (RFM75_BANK1_REG4_MODE == 6)
		0xC1|(RFM75_CONFIG_txIctrl << 3),  0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5),  0x88,  0xDB,
	#endif
	
		// reg 5
	#if (RFM75_BANK1_REG5_MODE == 0)
		0x24,  0x06,  0x0F,  0xA6,
	#elif (RFM75_BANK1_REG5_MODE == 1)
		0x24,  0x06,  0x0F,  0xB6,
	#elif (RFM75_BANK1_REG5_MODE == 2)
		0x24,  0x02,  0x0F,  0xA6,
	#elif (RFM75_BANK1_REG5_MODE == 3)
		0x24,  0x02,  0x0F,  0xB6,
	#elif (RFM75_BANK1_REG5_MODE == 4)
		(RFM75_UNDOCUMENTED_RSSI_THRESHOLD_LEVEL << 2),  0x02,  0x0F,  0xA6,
	#elif (RFM75_BANK1_REG5_MODE == 5)
		(RFM75_UNDOCUMENTED_RSSI_THRESHOLD_LEVEL << 2),  0x02,  0x0F,  0xB6,
	#elif (RFM75_BANK1_REG5_MODE == 6)
		0x24,  0x06,  0x7F,  0xA6
	#elif (RFM75_BANK1_REG5_MODE == 7)
		0x24,  0x06,  0x7F,  0xB6
	#elif (RFM75_BANK1_REG5_MODE == 8)
		(RFM75_UNDOCUMENTED_RSSI_THRESHOLD_LEVEL << 2),  0x02,  0x7F,  0xA6,
	#elif (RFM75_BANK1_REG5_MODE == 9)
		(RFM75_UNDOCUMENTED_RSSI_THRESHOLD_LEVEL << 2),  0x02,  0x7F,  0xB6,
	#endif

		0x00,  0x00,  0x00,  0x00, // reg 6
		0x00,  0x00,  0x00,  0x00, // reg 7
		0x00,  0x00,  0x00,  0x00, // reg 8
		0x00,  0x00,  0x00,  0x00, // reg 9
		0x00,  0x00,  0x00,  0x00, // reg A
		0x00,  0x00,  0x00,  0x00, // reg B

		// reg C
	#if (RFM75_BANK1_REGC_MODE == 0)
		0x00,  0x10|(RFM75_CONFIG_COMPATIBLE_MODE << 1),  0x73,  0x00, // 120 us PLL // compatible with rfm70
	#elif (RFM75_BANK1_REGC_MODE == 1)
		0x00,  0x10|(RFM75_CONFIG_COMPATIBLE_MODE << 1),  0x73,  0x05, // 130 us PLL // compatible with nrf24l01+
	#elif (RFM75_BANK1_REGC_MODE == 2)
		0x00,  0x18|(RFM75_CONFIG_COMPATIBLE_MODE << 1),  0x73,  0x00, // 120 us PLL
	#elif (RFM75_BANK1_REGC_MODE == 3)
		0x00,  0x18|(RFM75_CONFIG_COMPATIBLE_MODE << 1),  0x73,  0x05, // 130 us PLL
	#endif

		// reg D
	#if (RFM75_BANK1_REGD_MODE == 0)
		0x36,  0xB4,  0x80,  0x00,
	#elif (RFM75_BANK1_REGD_MODE == 1)
		0x46,  0xB4,  0x80,  0x00, 
	#endif

		// reg E
	#if (RFM75_BANK1_RAMP_CURVE_MODE == 0)
		0x41,0x20,0x08,0x04,0x81,0x20,0xCF,0xF7,0xFE,0xFF,0xFF // put the ',' at the beginning of the next entry to fix compiler errors if no long address/bank0 is defined 
	#elif (RFM75_BANK1_RAMP_CURVE_MODE == 1)
		0x41,0x10,0x04,0x82,0x20,0x08,0x08,0xF2,0x7D,0xEF,0xFF // put the ',' at the beginning of the next entry to fix compiler errors if no long address/bank0 is defined 
	#endif
	
#elif (RFM7x_MODULECHIP_USED == 4) // bk2411/2412
	
		0x41,  0x4B,  0x01,  0xF2, // reg 0
		0xC0,  0x4B,  0x06,  0x30, // reg 1
		0xA0,  0xFC,  0xC4,  0x00, // reg 2
		
		// reg 3
	#if (BK2411_BANK1_REG3_MODE == 0)
		0x17,  0x00,  0x35,  0x60,    
	#elif (BK2411_BANK1_REG3_MODE == 1)
		0x03,  0x00,  0x12,  0x00,
	#endif
		
		// reg 4
	#if (BK2411_BANK1_REG4_MODE == 0)
		0x41,  0x99,  0x00,  0x0B,
	#elif (BK2411_BANK1_REG4_MODE == 1)
		0x41,  0x99,  0x10,  0x0B,
	#elif (BK2411_BANK1_REG4_MODE == 2)
		0x41,  0x11,  0x04,  0x21,
	#elif (BK2411_BANK1_REG4_MODE == 3)
		0x41,  0x98|(BK2411_XTALFC >> 3),  0x00|(BK2411_XTALFC << 5),  0x0B,
	#elif (BK2411_BANK1_REG4_MODE == 4)
		0x41,  0x98|(BK2411_XTALFC >> 3),  0x10|(BK2411_XTALFC << 5),  0x0B,
	#elif (BK2411_BANK1_REG4_MODE == 5)
		0x41,  0x10|(BK2411_XTALFC >> 3),  0x04|(BK2411_XTALFC << 5),  0x21,
	#endif
	
		(BK2411_RSSI_THRESHOLD_LEVEL << 2),  0x01,  0x17,  0xBE, // reg 5

		0x00,  0x00,  0x40,  0x00,    // reg 6
		0x00,  0x00,  0x00,  0x00,    // reg 7
	
		0x00,  0x00,  0x00,  0x00,    // reg 8
	
		0x00,  0x00,  0x00,  0x00,    // reg 9
		0xF6,  0x4E,  0xF5,  0xF6,    // reg A
		0x5C,  0x18,  0x51,  0xD6,    // reg B
		
		// reg C
	#if (BK2411_BANK1_REGC_MODE == 0)
		0x40,  0x55,  0x00,  0x2D,
	#elif (BK2411_BANK1_REGC_MODE == 1)
		0x60,  0x50,  0x00,  0x2D,
	#elif (BK2411_BANK1_REGC_MODE == 2)
		0x00|(BK2411_TX_RAMP_SEL << 5),  0x50|(BK2411_TX_LOCK_SEL << 1)|(BK2411_TX_RAMP_SEL >> 3),  0x00,  0x2D,
	#endif
	
		// reg D
	#if (BK2411_BANK1_REGD_MODE == 0)
		0x00,  0x70,  0x00,  0x00,
	#elif (BK2411_BANK1_REGD_MODE == 1)
		0x00,  0x04,  0x00,  0x00,
	#elif (BK2411_BANK1_REGD_MODE == 2)
		0x00,  0x74,  0x00,  0x00,
	#elif (BK2411_BANK1_REGD_MODE == 3)
		0xFF,  0x71,  0x00,  0x00,
	#elif (BK2411_BANK1_REGD_MODE == 4)
		0xFF,  0x05,  0x00,  0x00,
	#elif (BK2411_BANK1_REGD_MODE == 5)
		0xFF,  0x75,  0x00,  0x00,
	#elif (BK2411_BANK1_REGD_MODE == 3)
		(BK2411_LEN_LONG), (BK2411_LONG_PL)|(BK2411_GFSK_BT << 1)|(BK2411_MODU_MOD << 2)|(BK2411_CYST_ACCU <<4),  0x00,  0x00,
	#endif
	
		0x41,0x10,0x08,0x82,0x40,0x10,0x08,0xF2,0x7C,0xEF,0xCF // put the ',' at the beginning of the next entry to fix compiler errors if no long address/bank0 is defined 
#endif
		////////////////////////////////////////// bank 0 initialization registers //////////////////////////////////////////
#ifndef RFM7x_DO_NOT_INITIALIZE_BANK0
		,RFM7x_BANK0_REG_CONFIG, // PTX/PRX mode - doesn't care, it will be set later with rest commands
		RFM7x_BANK0_REG_EN_AA,
		RFM7x_BANK0_REG_EN_RXADDR,
		RFM7x_BANK0_REG_SETUP_AW,
		RFM7x_BANK0_REG_SETUP_RETR,
		RFM7x_BANK0_REG_RF_CH,
		RFM7x_BANK0_REG_RF_SETUP,
	
		0x07, // status register that have to be initialized - not documented
		0x00, // status register that have to be initialized - not documented
		0x00 // status register that have to be initialized - not documented	
	
	#ifndef RFM7x_DO_NOT_INITIALIZE_P2_RX_ADDRESS_AND_PAYLOAD_LEN_REGS
		,0xE7, // pipe0 default address // just dummy byte to fill space for loading whole bank0 in one-run // single byte write might be undefined 
		0xC2, // pipe1 default address // just dummy byte to fill space for loading whole bank0 in one-run // single byte write might be undefined
		
		RFM7x_PIPE2_RX_ADDRESS,  // pipe 2 address // LSB only
		RFM7x_PIPE3_RX_ADDRESS,  // pipe 3 address // LSB only
		RFM7x_PIPE4_RX_ADDRESS,  // pipe 4 address // LSB only
		RFM7x_PIPE5_RX_ADDRESS  // pipe 5 address // LSB only
	#endif
	
	#if !defined(RFM7x_DO_NOT_INITIALIZE_RX_PAYLOAD_LEN_REGS)&&!defined(RFM7x_DO_NOT_INITIALIZE_P2_RX_ADDRESS_AND_PAYLOAD_LEN_REGS)
		,0xE7, // TX default address // just dummy byte to fill space for loading whole bank0 in one-run // single byte write might be undefined
		
		RFM7x_PIPE0_RX_PAYLOAD_LEN,  // pipe 0 - payload length // 0 equals to dynamic payload ??
		RFM7x_PIPE1_RX_PAYLOAD_LEN,  // pipe 1 - payload length // 0 equals to dynamic payload ??
		RFM7x_PIPE2_RX_PAYLOAD_LEN,  // pipe 2 - payload length // 0 equals to dynamic payload ??
		RFM7x_PIPE3_RX_PAYLOAD_LEN,  // pipe 3 - payload length // 0 equals to dynamic payload ??
		RFM7x_PIPE4_RX_PAYLOAD_LEN,  // pipe 4 - payload length // 0 equals to dynamic payload ??
		RFM7x_PIPE5_RX_PAYLOAD_LEN,  // pipe 5 - payload length // 0 equals to dynamic payload ??
	
		0x00 // status register that have to be initialized - not documented
	#endif
		
		//0x00, // dummy
		//0x00, // dummy
		//0x00, // dummy
		//0x00, // dummy
		
		//RFM7x_BANK0_REG_DYNPD,
		//RFM7x_BANK0_REG_FEATURE
		
	#if defined(RFM7x_TX_ADDRESS)&&!defined(RFM7x_USE_PIPE0_ADDRESS_FOR_TX_ADDRESS)
		,RFM7x_TX_ADDRESS
	#endif	
	#ifdef RFM7x_PIPE0_RX_ADDRESS
		,RFM7x_PIPE0_RX_ADDRESS
	#endif
	#ifdef RFM7x_PIPE1_RX_ADDRESS	
		,RFM7x_PIPE1_RX_ADDRESS
	#endif
		
#endif //RFM7x_DO_NOT_INITIALIZE_BANK0
	};

	void rfm7x_init(void) // everything is loaded from one big table // this function is 1:1 copy of the prematured one in C, so it is mostly optimized to waste as little as possible fo RAM (for UCs as small as attiny2313) // on other arch it could be done somehow better // use buff_write() instead of writing in loops ????    
	{	
	#ifdef RFM7x_ATOMIC_REG_ACCES
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	#endif
		{
		#if defined(__AVR_ARCH__)&&!defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
			const __flash uint8_t *p_init_struct = rfm7x_init_struct;
		#else
			const uint8_t *p_init_struct = rfm7x_init_struct;
		#endif
			
			if((0x80 & rfm7x_reg_read(RFM7x_REG_STATUS)) == 0)
				rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // select bank 1
			
			for(uint_fast8_t i=0; i<RFM7x_BANK1_ENTRIES; i++)
			{
			#if defined(__AVR_ARCH__)&&!defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
				if(i != RFM7x_BANK1_ENTRIES-1)
				{
					rfm7x_reg_buff_write_P(i, p_init_struct, 4);
					p_init_struct+=4;
				}
				else
				{
					rfm7x_reg_buff_write_P(i, p_init_struct, 11);
					p_init_struct+=11;
				}
			#else
				if(i != RFM7x_BANK1_ENTRIES-1)
				{
					rfm7x_reg_buff_write(i, (uint8_t*)p_init_struct, 4);
					p_init_struct+=4;
				}
				else
				{
					rfm7x_reg_buff_write(i, (uint8_t*)p_init_struct, 11);
					p_init_struct+=11;
				}
			#endif
			}
			
			rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // toggle to bank 0
			
			rfm7x_reg_write(RFM7x_REG_FEATURE, 0x01); // check if "feature register" is writable before (de)activating it
			
			if(!rfm7x_reg_read(RFM7x_REG_FEATURE))
				rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x73); // activate feature register if not activated
			
			for(uint_fast8_t i = 0; i<RFM7x_BANK0_ENTRIES; i++)
			{
				rfm7x_reg_write(i, *p_init_struct++);
			}
			
		#if defined(RFM7x_TX_ADDRESS)||defined(RFM7x_USE_PIPE0_ADDRESS_FOR_TX_ADDRESS)
			#if defined(__AVR_ARCH__)&&!defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
				rfm7x_reg_buff_write_P(RFM7x_REG_TX_ADDR, p_init_struct, RFM7x_TX_ADDRESS_SIZE);
			#else
				rfm7x_reg_buff_write(RFM7x_REG_TX_ADDR, (uint8_t*)p_init_struct, RFM7x_TX_ADDRESS_SIZE);
			#endif
			
			#ifndef RFM7x_USE_PIPE0_ADDRESS_FOR_TX_ADDRESS
				p_init_struct += RFM7x_TX_ADDRESS_SIZE;
			#endif
		#endif
		
		#ifdef RFM7x_PIPE0_RX_ADDRESS
			#if defined(__AVR_ARCH__)&&!defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
				rfm7x_reg_buff_write_P(RFM7x_REG_RX_ADDR_P0, p_init_struct, RFM7x_PIPE0_RX_ADDRESS_SIZE);
			#else
				rfm7x_reg_buff_write(RFM7x_REG_RX_ADDR_P0, (uint8_t*)p_init_struct, RFM7x_PIPE0_RX_ADDRESS_SIZE);
			#endif
			
			p_init_struct += RFM7x_PIPE0_RX_ADDRESS_SIZE;
		#endif
		
		#ifdef RFM7x_PIPE1_RX_ADDRESS
			#if defined(__AVR_ARCH__)&&!defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
				rfm7x_reg_buff_write_P(RFM7x_REG_RX_ADDR_P1, p_init_struct, RFM7x_PIPE1_RX_ADDRESS_SIZE);
			#else
				rfm7x_reg_buff_write(RFM7x_REG_RX_ADDR_P1, (uint8_t*)p_init_struct, RFM7x_PIPE1_RX_ADDRESS_SIZE);
			#endif
		#endif
			
		#ifdef RFM7x_DO_NOT_INITIALIZE_BANK0
			rfm7x_reg_write(RFM7x_REG_STATUS, 0x07);
			rfm7x_reg_write(RFM7x_REG_OBSERVE_TX, 0x00);
			rfm7x_reg_write(RFM7x_REG_CD, 0x00);
			rfm7x_reg_write(RFM7x_REG_FIFO_STATUS, 0x00);
		
		#elif defined(RFM7x_DO_NOT_INITIALIZE_RX_PAYLOAD_LEN_REGS)||defined(RFM7x_DO_NOT_INITIALIZE_P2_RX_ADDRESS_AND_PAYLOAD_LEN_REGS)
			rfm7x_reg_write(RFM7x_REG_FIFO_STATUS, 0x00);
		#endif
			
			rfm7x_reg_write(RFM7x_REG_DYNPD, RFM7x_BANK0_REG_DYNPD);
			rfm7x_reg_write(RFM7x_REG_FEATURE, RFM7x_BANK0_REG_FEATURE);
		}
	}

#if defined(__AVR_ARCH__)&&!defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
	const __flash uint8_t rfm7x_REG4_toggle_struct[] =
#else
	const uint8_t rfm7x_REG4_toggle_struct[] = 
#endif
	{
#if (RFM7x_MODULECHIP_USED == 0 || RFM7x_MODULECHIP_USED == 1) // BK2421 aka RFM70 + BK2401
		
	#if (RFM70_BANK1_REG4_MODE == 0)
		0xD9,  0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x86,  0x0B
	#elif (RFM70_BANK1_REG4_MODE == 1)
		0xC9,  0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x86,  0x0B
	#elif (RFM70_BANK1_REG4_MODE == 2)
		0xF9,  0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x86,  0x0B
	#elif (RFM70_BANK1_REG4_MODE == 3)
		0xB9,  0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x86,  0x0B
	#elif (RFM70_BANK1_REG4_MODE == 4)
		0x09,  0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x86,  0x0B
	#elif (RFM70_BANK1_REG4_MODE == 5)
		0xD9,  0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x86,  0x21
	#elif (RFM70_BANK1_REG4_MODE == 6)
		0xD9,  0x86|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x82,  0x1B
	#elif (RFM70_BANK1_REG4_MODE == 7)
		0xF9,  0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x84,  0x0B
	#elif (RFM70_BANK1_REG4_MODE == 8)
		0xF9,  0x86|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x84,  0x1B
	#elif (RFM70_BANK1_REG4_MODE == 9)
		0xF9,  0x86|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x80,  0x1B
	#elif (RFM70_BANK1_REG4_MODE == 10)
		0xF9,  0x86|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4),  0x82,  0x1B
	#endif

#elif (RFM7x_MODULECHIP_USED == 2) // BK2423 aka RFM73
	
	#if (RFM73_BANK1_REG4_MODE == 0)
		0xD9,  0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x86,  0x0B // rfm73 and rfm70 // probably worser
	#elif (RFM73_BANK1_REG4_MODE == 1)
		0xD9,  0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x82,  0x1B // replace manual
	#elif (RFM73_BANK1_REG4_MODE == 2)
		0xF9,  0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x84,  0x0B // AN0007 "high power mode" 3-15dBm - requires additional low-pass filter to pass FCC tests
	#elif (RFM73_BANK1_REG4_MODE == 3)
		0xD9,  0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x86,  0x1B
	#elif (RFM73_BANK1_REG4_MODE == 4)
		0xF9,  0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x84,  0x1B
	#elif (RFM73_BANK1_REG4_MODE == 5)
		0xF9,  0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x80,  0x1B
	#elif (RFM73_BANK1_REG4_MODE == 6)
		0xD9,  0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x86,  0x21
	#elif (RFM73_BANK1_REG4_MODE == 7)
		0xF9,  0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x82,  0x1B
	#elif (RFM73_BANK1_REG4_MODE == 8)
		0xF9,  0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x86,  0x0B
	#elif (RFM73_BANK1_REG4_MODE == 9)
		0xB9,  0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x86,  0x0B
	#elif (RFM73_BANK1_REG4_MODE == 10)
		0xB9,  0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x82,  0x1B
	#elif (RFM73_BANK1_REG4_MODE == 11)
		0x09,  0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x86,  0x0B
	#elif (RFM73_BANK1_REG4_MODE == 12)
		0x09,  0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4),  0x82,  0x1B
	#endif

#elif (RFM7x_MODULECHIP_USED == 3) // bk2425 aka RFM75

	#if (RFM75_BANK1_REG4_MODE == 0)
		0xC1|(RFM75_CONFIG_txIctrl << 3),  0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5),  0x82,  0x1B
	#elif (RFM75_BANK1_REG4_MODE == 1)
		0xC1|(RFM75_CONFIG_txIctrl << 3),  0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5),  0x82,  0xDB
	#elif (RFM75_BANK1_REG4_MODE == 2)
		0xC1|(RFM75_CONFIG_txIctrl << 3),  0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5),  0x8A,  0xDB
	#elif (RFM75_BANK1_REG4_MODE == 3)
		0xC1|(RFM75_CONFIG_txIctrl << 3),  0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5),  0x82,  0x21
	#elif (RFM75_BANK1_REG4_MODE == 4)
		0xC1|(RFM75_CONFIG_txIctrl << 3),  0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5),  0x80,  0x1B
	#elif (RFM75_BANK1_REG4_MODE == 5)
		0xC1|(RFM75_CONFIG_txIctrl << 3),  0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5),  0x80,  0xDB
	#elif (RFM75_BANK1_REG4_MODE == 6)
		0xC1|(RFM75_CONFIG_txIctrl << 3),  0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5),  0x88,  0xDB
	#endif
	
#elif (RFM7x_MODULECHIP_USED == 4) // bk2411/2412
	
	#if (BK2411_BANK1_REG4_MODE == 0)
		0x41,  0x99,  0x00,  0x0B
	#elif (BK2411_BANK1_REG4_MODE == 1)
		0x41,  0x99,  0x10,  0x0B
	#elif (BK2411_BANK1_REG4_MODE == 2)
		0x41,  0x11,  0x04,  0x21
	#elif (BK2411_BANK1_REG4_MODE == 3)
		0x41,  0x98|(BK2411_XTALFC >> 3),  0x00|(BK2411_XTALFC << 5),  0x0B
	#elif (BK2411_BANK1_REG4_MODE == 4)
		0x41,  0x98|(BK2411_XTALFC >> 3),  0x10|(BK2411_XTALFC << 5),  0x0B
	#elif (BK2411_BANK1_REG4_MODE == 5)
		0x41,  0x10|(BK2411_XTALFC >> 3),  0x04|(BK2411_XTALFC << 5),  0x21
	#endif
	
#endif	
	};

void rfm7x_toggle_reg4(void) // to premature 
{
//	one of the chinese documents (rfm73 -> rfm75 migration) says that it should be executed after every PWR_UP, not only during initialization
	
// 	4. RFM75 PowerUP after the first packet of data sent unsuccessful solution
// 	RFM75 from the POWER DOWN state to switch to POWER UP state, send the first packet is not successful, the reason
// 	Is the PLL is not locked, the solution is as follows:
// 	Before transmitting data normally, please follow the following procedure:
// 	Power up = 1
// 	Wait for 2ms
// 	Operate the bank1 register, writing a 1 to bit 25 of register 04
// 	Wait 20us
// 	Operate the bank1 register, writing a 0 to bit 25 of register 04
// 	Wait for 0.5ms.
// 	Then normal launch.

//	AN0008
//	9.  Toggle REG4<25?26>, write 1 to bit25, bit 26, then write 0 to them.

	//RFM7x_CSN_LOW;
	//	rfm7x_xfer_spi(0x04|0x20);
	//	rfm7x_xfer_spi(rfm7x_init_struct[16] | 0x06);
	//	rfm7x_xfer_spi(rfm7x_init_struct[17]); 
	//	rfm7x_xfer_spi(rfm7x_init_struct[18]);
	//	rfm7x_xfer_spi(rfm7x_init_struct[19]);
	//RFM7x_CSN_HI;
	//	_delay_us(20); // if not required then this function may not be required, so better to leave it here
	//RFM7x_CSN_LOW;
	//	rfm7x_xfer_spi(0x04|0x02);
	//	rfm7x_xfer_spi(rfm7x_init_struct[16]);
	//	rfm7x_xfer_spi(rfm7x_init_struct[17]);
	//	rfm7x_xfer_spi(rfm7x_init_struct[18]);
	//	rfm7x_xfer_spi(rfm7x_init_struct[19]);
	//RFM7x_CSN_HI;
	
#ifdef RFM7x_ATOMIC_REG_ACCES 
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#endif
	{
		rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // toggle to bank 1
	
	#if defined(__AVR_ARCH__)&&!defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
		rfm7x_reg_buff_write_P(0x04,rfm7x_REG4_toggle_struct,4);
		_delay_us(20); // if not required then this function may not be required, so better to leave it here
		rfm7x_reg_buff_write_P(0x04,&rfm7x_init_struct[16],4);
	#else
		rfm7x_reg_buff_write(0x04,(uint8_t*)rfm7x_REG4_toggle_struct,4);
		_delay_us(20); // if not required then this function may not be required, so better to leave it here
		rfm7x_reg_buff_write(0x04,(uint8_t*)&rfm7x_init_struct[16],4);
	#endif

		rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // toggle to bank 0
	}
}

void rfm7x_cmd_write(uint8_t reg, uint8_t dat)
{
#ifdef RFM7x_ATOMIC_REG_ACCES
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#endif
	{
		RFM7x_CSN_LOW;
		rfm7x_xfer_spi(reg);
		rfm7x_xfer_spi(dat);
		RFM7x_CSN_HI;
	}
}

uint8_t rfm7x_cmd_read(uint8_t reg)
{
	uint8_t tmp;
	
#ifdef RFM7x_ATOMIC_REG_ACCES
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#endif
	{
		RFM7x_CSN_LOW;
		rfm7x_xfer_spi(reg);
		tmp = rfm7x_xfer_spi(0);  // rfm7x_xfer_spi(rfm7x_xfer_spi())
		RFM7x_CSN_HI;
	}
	
	return tmp;
}

#ifdef RFM7x_USE_UNIVERSAL_SPI_BUFF_RW_FUNCTIONS
	void rfm7x_cmd_buff_write(uint8_t reg, uint8_t *buff, uint8_t len)
	{
	#ifdef RFM7x_ATOMIC_REG_ACCES
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	#endif
		{
			RFM7x_CSN_LOW;
			rfm7x_xfer_spi(reg);
			rfm7x_buff_write(buff, len);
			RFM7x_CSN_HI;
		}
	}

	void rfm7x_cmd_buff_read(uint8_t reg, uint8_t *buff, uint8_t len)
	{
	#ifdef RFM7x_ATOMIC_REG_ACCES
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	#endif
		{
			RFM7x_CSN_LOW;
			rfm7x_xfer_spi(reg);
			rfm7x_buff_read(buff, len);
			RFM7x_CSN_HI;
		}
	}
#else
	void rfm7x_cmd_buff_write(uint8_t reg, uint8_t *buff, uint8_t len)
	{
	#ifdef RFM7x_ATOMIC_REG_ACCES
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	#endif
		{
			RFM7x_CSN_LOW;
			
			rfm7x_xfer_spi(reg);
			
			for(uint_fast8_t i=0; i<len; i++)
				rfm7x_xfer_spi(buff[i]);
			
			RFM7x_CSN_HI;
		}
	}

	void rfm7x_cmd_buff_read(uint8_t reg, uint8_t *buff, uint8_t len)
	{
	#ifdef RFM7x_ATOMIC_REG_ACCES
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	#endif
		{
			RFM7x_CSN_LOW;
			
			rfm7x_xfer_spi(reg);
			
			for(uint_fast8_t i=0; i<len; i++)
				buff[i] = rfm7x_xfer_spi(0);

			RFM7x_CSN_HI;
		}
	}
#endif

#if defined(__AVR_ARCH__)&&!defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH) // temporary workaround ??
	void rfm7x_cmd_buff_write_P(uint8_t reg, const __flash uint8_t* buff, uint8_t len) // __memx ????
	{
		RFM7x_CSN_LOW;
		
		rfm7x_xfer_spi(reg);

		for(uint_fast8_t i=0; i<len; i++)
			rfm7x_xfer_spi(buff[i]);
		
		RFM7x_CSN_HI;
	}
#endif

uint8_t rfm7x_is_present(void)
{
 	uint8_t tmp1, tmp2;
 	tmp1 = rfm7x_reg_read(RFM7x_REG_STATUS);
 	rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53);
 	tmp2 = rfm7x_reg_read(RFM7x_REG_STATUS);
 	rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53);
 	return (tmp1 ^ tmp2) == 0x80;
}

void rfm7x_power_up(void)
{	
	uint8_t tmp = rfm7x_reg_read(RFM7x_REG_CONFIG);
	tmp |= 0x02; // set PWR_UP bit
	rfm7x_reg_write(RFM7x_REG_CONFIG, tmp);
}

void rfm7x_power_down(void)
{
	RFM7x_CE_LOW;
	
	uint8_t tmp = rfm7x_reg_read(RFM7x_REG_CONFIG);
	tmp &= 0xFD; // clear PWR_UP bit
	rfm7x_reg_write(RFM7x_REG_CONFIG, tmp);
}

void rfm7x_mode_receive(void)
{
	RFM7x_CE_LOW;
	uint8_t tmp;
	
	//tmp = rfm7x_reg_read(RFM7x_REG_STATUS);
	// handle requests here ??
	//rfm7x_reg_write(RFM7x_REG_STATUS, tmp); // clear interrupt requests
	
	rfm7x_reg_write(RFM7x_REG_STATUS, 0x70); // clear interrupt requests
	
	tmp = rfm7x_reg_read(RFM7x_REG_CONFIG);
	tmp |= 0x01; // set RX bit
	rfm7x_reg_write(RFM7x_REG_CONFIG, tmp);
	
#ifdef RFM7x_FLUSH_TX_AND_RX_WHILE_SWITCHING_MODES
	rfm7x_cmd_write(RFM7x_CMD_FLUSH_TX, 0);
#endif
	rfm7x_cmd_write(RFM7x_CMD_FLUSH_RX, 0); // it have to be flushed, otherwise doesn't work
		
	RFM7x_CE_HI;
}

void rfm7x_mode_transmit(void)
{
	RFM7x_CE_LOW;
	uint8_t tmp;

	//tmp = rfm7x_reg_read(RFM7x_REG_STATUS);
	// handle requests here ??
	//rfm7x_reg_write(RFM7x_REG_STATUS, tmp); // clear interrupt requests
	
	rfm7x_reg_write(RFM7x_REG_STATUS, 0x70); // clear interrupt requests, otherwise further communication is not possible if MAX_RT is asserted
	
	tmp = rfm7x_reg_read(RFM7x_REG_CONFIG);
	tmp &= 0xFE; // clear RX bit
	rfm7x_reg_write(RFM7x_REG_CONFIG, tmp);
	
#ifdef RFM7x_FLUSH_TX_AND_RX_WHILE_SWITCHING_MODES
	rfm7x_cmd_write(RFM7x_CMD_FLUSH_RX, 0);
#endif
	rfm7x_cmd_write(RFM7x_CMD_FLUSH_TX, 0); // it have to be flushed, otherwise chip doesn't work
	
	RFM7x_CE_HI;
}

uint8_t rfm7x_receive(uint8_t *buff)
{
	uint8_t p = rfm7x_receive_next_pipe();
	
	if(p == 0x07)
		return 0;
	
	uint8_t len = rfm7x_receive_next_length();
	
	rfm7x_cmd_buff_read(RFM7x_CMD_R_RX_PAYLOAD, buff, len);
	
	return len;
}

void rfm7x_receive_nocheck(uint8_t *buff)
{
	uint8_t len = rfm7x_receive_next_length();
	rfm7x_cmd_buff_read(RFM7x_CMD_R_RX_PAYLOAD, buff, len);
}

uint8_t rfm7x_receive_p_(uint8_t *pipe, uint8_t *buff)
{
	uint8_t p = rfm7x_receive_next_pipe();
	
	if(p == 0x07)
		return 0;
	
	*pipe = p;
	uint8_t len = rfm7x_receive_next_length();
	
	rfm7x_cmd_buff_read(RFM7x_CMD_R_RX_PAYLOAD, buff, len);
	
	return len;
}

uint8_t rfm7x_receive_s(uint8_t *buff, uint8_t length)
{
	uint8_t p = rfm7x_receive_next_pipe();
	
	if(p == 0x07)
		return p;
	
	rfm7x_cmd_buff_read(RFM7x_CMD_R_RX_PAYLOAD, buff, length);

	return p;
}

uint8_t rfm7x_receive_f(uint8_t *buff, uint8_t *pipe, uint8_t *length)
{
	uint8_t p = rfm7x_receive_next_pipe();
	
	if(p == 0x07)
		return 0;
	
	uint8_t len = rfm7x_receive_next_length();
	
	*pipe = p;
	*length = len;
	
	rfm7x_cmd_buff_read(RFM7x_CMD_R_RX_PAYLOAD, buff, len);
	
	return 1;
}

void rfm7x_set_rssi_threshold_step(uint8_t level)
{
#ifdef RFM7x_ATOMIC_REG_ACCES 
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#endif
	{
		rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // toggle to bank 1
	
		RFM7x_CSN_LOW;
			rfm7x_xfer_spi(0x05|0x20);
		
		#if (RFM7x_MODULECHIP_USED == 2)
			uint8_t tmp;
			
			switch(level)
			{
				case 0: tmp = 0x00; break;
				case 1: tmp = 0x02; break;
				case 2: tmp = 0x01; break;
				case 3: tmp = 0x03; break;
				case 4: tmp = 0x08; break;
				case 5: tmp = 0x0A; break;
				case 6: tmp = 0x09; break;
				case 7: tmp = 0x0B; break;
				case 8: tmp = 0x04; break;
				case 9: tmp = 0x06; break;
				case 10: tmp = 0x05; break;
				case 11: tmp = 0x07; break;
				case 12: tmp = 0x0C; break;
				case 13: tmp = 0x0E; break;
				case 14: tmp = 0x0D; break;
				case 15: tmp = 0x0F; break;
				default: tmp = level; break;
			}
			
			rfm7x_xfer_spi(tmp << 2); 
		#else
			rfm7x_xfer_spi(level << 2); 
		#endif
			rfm7x_xfer_spi(rfm7x_init_struct[21]);
			rfm7x_xfer_spi(rfm7x_init_struct[22]);
			rfm7x_xfer_spi(rfm7x_init_struct[23]);
		RFM7x_CSN_HI;
	
		rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // toggle to bank 0
	}
}

void rfm7x_set_crc_length(uint8_t len)
{
	uint8_t tmp = rfm7x_reg_read(RFM7x_REG_CONFIG);
	
	tmp &= ~(RFM7x_CONFIG_EN_CRC|RFM7x_CONFIG_CRCO); // clear EN_CRC and CRCO
	
	if(len == 0)
	{
		rfm7x_reg_write(RFM7x_REG_EN_AA, 0); // Auto ACK have to be disabled before disabling CRC
		rfm7x_reg_write(RFM7x_REG_CONFIG, tmp);
	}
	else
	{
		tmp |= (RFM7x_CONFIG_EN_CRC); // set EN_CRC
		
		if(len & 0x02) // if 2 byte encoding scheme is selected, set CRCO
			 tmp |= (RFM7x_CONFIG_CRCO);
		
		//rfm7x_reg_write(RFM7x_REG_EN_AA, 0x3f); //????
		rfm7x_reg_write(RFM7x_REG_CONFIG, tmp);
	}
}

void rfm7x_set_tx_pwr(uint8_t level)
{
	uint8_t tmp = rfm7x_reg_read(RFM7x_REG_RF_SETUP);
	
#if (RFM7x_MODULECHIP_USED == 0)|(RFM7x_MODULECHIP_USED == 1)|(RFM7x_MODULECHIP_USED == 2)
	
	tmp |= (level << 1);
	rfm7x_reg_write(RFM7x_REG_RF_SETUP, tmp);
	
#elif (RFM7x_MODULECHIP_USED == 3) // bk2425
	
	uint8_t txictrl_tmp = 0;
	
	switch(level)
	{
		default:
		case 0: // -25 dBm
		case 1: // -18 dBm
			break;
		case 2: // -12 dBm
			level -= 1;
			txictrl_tmp = 1;
			break;
			
		case 3: // -7 dBm
			level -= 1;
			txictrl_tmp = 2;
			break;
			
		case 4: // -1 dBm
			level -= 1;
			break;
			
		case 5: // 4 dBm
			level -= 2;
			txictrl_tmp = 7;
			break;
	}
	
	tmp |= (level << 1);
	rfm7x_reg_write(RFM7x_REG_RF_SETUP, tmp);
	
#ifdef RFM7x_ATOMIC_REG_ACCES 
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#endif
	{
		rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // toggle to bank 1
	
		RFM7x_CSN_LOW;
			rfm7x_xfer_spi(0x04|0x20);
			rfm7x_xfer_spi((rfm7x_init_struct[16] & 0x38)|txictrl_tmp); 
			rfm7x_xfer_spi(rfm7x_init_struct[17]);
			rfm7x_xfer_spi(rfm7x_init_struct[18]);
			rfm7x_xfer_spi(rfm7x_init_struct[19]);
		RFM7x_CSN_HI;
			
		rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // toggle to bank 0
	}
	
#elif (RFM7x_MODULECHIP_USED == 4)// bk2411 
	
	tmp |= ((level & 0x03) << 1) | ((level >> 2) << 4); // to optimize ?
	rfm7x_reg_write(RFM7x_REG_RF_SETUP, tmp);
	
#endif
}

void rfm7x_set_lna_gain(uint8_t enable)
{
	uint8_t tmp = rfm7x_reg_read(RFM7x_REG_RF_SETUP);
	
	if(enable)
		tmp |= RFM7x_RF_SETUP_LNA_HCURR;
	else
		tmp &= ~(RFM7x_RF_SETUP_LNA_HCURR);
		
	rfm7x_reg_write(RFM7x_REG_RF_SETUP, tmp);
}

void rfm7x_set_datarate(uint8_t datarate)
{
	uint8_t tmp = rfm7x_reg_read(RFM7x_REG_RF_SETUP);
	
#if (RFM7x_MODULECHIP_USED == 0)|(RFM7x_MODULECHIP_USED == 1)|(RFM7x_MODULECHIP_USED == 4) // bk2401/bk2421/bk2411 
	tmp &= ~(RFM7x_RF_SETUP_RF_DR_HIGH);
	
	if(datarate & 0x01)
		tmp |= RFM7x_RF_SETUP_RF_DR_HIGH;
	
	//tmp |= ((datarate & 0x01) << 3);
#elif (RFM7x_MODULECHIP_USED == 2)|(RFM7x_MODULECHIP_USED == 3) // bk2423/bk2425
	tmp &= ~(RFM7x_RF_SETUP_RF_DR_HIGH|RFM7x_RF_SETUP_RF_DR_LOW);
	
	if(datarate & 0x01)
		tmp |= RFM7x_RF_SETUP_RF_DR_HIGH;
	
	if(datarate & 0x02)
		tmp |= RFM7x_RF_SETUP_RF_DR_LOW;
	
	//tmp |= ((datarate & 0x01) << 3)|(((datarate >> 1) & 0x01) << 5);
#endif

	rfm7x_reg_write(RFM7x_REG_RF_SETUP, tmp);
}

void rfm7x_enable_pipe_autoack(uint8_t pipe, uint8_t enabled)
{
	uint8_t tmp = rfm7x_reg_read(RFM7x_REG_EN_AA);
	
	tmp &= ~(1 << pipe);
	
	if(enabled)
		tmp |= (1 << pipe);
	
	rfm7x_reg_write(RFM7x_REG_EN_AA, tmp);
}

void rfm7x_enable_pipe_receive(uint8_t pipe, uint8_t enabled)
{
	uint8_t tmp = rfm7x_reg_read(RFM7x_REG_EN_RXADDR);
	
	tmp &= ~(1 << pipe);
	
	if(enabled)
		tmp |= (1 << pipe);
	
	rfm7x_reg_write(RFM7x_REG_EN_RXADDR, tmp);
}

void rfm7x_enable_dynamic_payload_feature(uint8_t enable)
{
	uint8_t tmp = rfm7x_reg_read(RFM7x_REG_FEATURE);
	
	tmp &= ~(RFM7x_FEATURE_EN_DPL);
	
	if(enable)
		tmp |= RFM7x_FEATURE_EN_DPL;
		
	rfm7x_reg_write(RFM7x_REG_FEATURE, tmp);
}

void rfm7x_enable_ack_payload_feature(uint8_t enable)
{
	uint8_t tmp = rfm7x_reg_read(RFM7x_REG_FEATURE);
	
	tmp &= ~(RFM7x_FEATURE_EN_ACK_PAY);
	
	if(enable)
		tmp |= RFM7x_FEATURE_EN_ACK_PAY;
	
	rfm7x_reg_write(RFM7x_REG_FEATURE, tmp);
}

void rfm7x_enable_noack_payload_feature(uint8_t enable)
{
	uint8_t tmp = rfm7x_reg_read(RFM7x_REG_FEATURE);
	
	tmp &= ~(RFM7x_FEATURE_EN_DYN_ACK);
	
	if(enable)
		tmp |= RFM7x_FEATURE_EN_DYN_ACK;
	
	rfm7x_reg_write(RFM7x_REG_FEATURE, tmp);	
}

void rfm7x_set_transmit_address(uint8_t* addr) 
{
	uint8_t size = rfm7x_reg_read(RFM7x_REG_SETUP_AW);
	size += 2;
	rfm7x_reg_buff_write(RFM7x_REG_TX_ADDR, addr, size);
}

void rfm7x_open_writing_pipe(uint64_t addr)
{
	uint8_t size = rfm7x_reg_read(RFM7x_REG_SETUP_AW);
	size += 2;
	
	//initialize also RX0 ?
	rfm7x_reg_buff_write(RFM7x_REG_TX_ADDR, (uint8_t *)&addr, size); // just push that onto the stack, forget about shifts
}

//pipe 1 and 2 (??)
void rfm7x_set_receive_address(uint8_t pipe, uint8_t* addr) 
{
	uint8_t size = rfm7x_reg_read(RFM7x_REG_SETUP_AW);
	size += 2;
	rfm7x_reg_buff_write(RFM7x_REG_RX_ADDR_P0+pipe, addr, size);
}

void rfm7x_open_reading_pipe(uint8_t pipe, uint64_t addr)
{
	rfm7x_enable_pipe_receive(pipe, 1);
	
	if(pipe >= 2)
	{
		rfm7x_reg_write(RFM7x_REG_RX_ADDR_P0+pipe, (addr & 0xff));
	}
	else
	{
		uint8_t size = rfm7x_reg_read(RFM7x_REG_SETUP_AW);
		size += 2;
	
		rfm7x_reg_buff_write(RFM7x_REG_RX_ADDR_P0+pipe, (uint8_t *)&addr, size); // just push that onto the stack, forget about shifts // LE archs only ?
	}
}