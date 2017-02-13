#ifndef RFM7x_H_
#define RFM7x_H_

/************************************************************************************
 *  Author: jnk0le@hotmail.com                                                      *
 *  https://github.com/jnk0le                                                       *
 *  This library is distributed under MIT license terms                             *
 ************************************************************************************/

#include "rfm7x_config.h"

#define RFM7x_CMD_READ_REG              0x00
#define RFM7x_CMD_WRITE_REG             0x20
#define RFM7x_CMD_R_RX_PAYLOAD          0x61 
#define RFM7x_CMD_W_TX_PAYLOAD          0xA0
#define RFM7x_CMD_FLUSH_TX              0xE1
#define RFM7x_CMD_FLUSH_RX              0xE2
#define RFM7x_CMD_REUSE_TX_PL           0xE3
#define RFM7x_CMD_W_TX_PAYLOAD_NOACK    0xB0
#define RFM7x_CMD_W_ACK_PAYLOAD         0xA8
#define RFM7x_CMD_ACTIVATE              0x50
#define RFM7x_CMD_R_RX_PL_WID           0x60
#define RFM7x_CMD_NOP                   0xFF

#define RFM7x_REG_CONFIG                0x00 // 'Config' register address
#define RFM7x_REG_EN_AA                 0x01 // 'Enable Auto Acknowledgment' register address
#define RFM7x_REG_EN_RXADDR             0x02 // 'Enabled RX addresses' register address
#define RFM7x_REG_SETUP_AW              0x03 // 'Setup address width' register address
#define RFM7x_REG_SETUP_RETR            0x04 // 'Setup Auto. Retrans' register address
#define RFM7x_REG_RF_CH                 0x05 // 'RF channel' register address
#define RFM7x_REG_RF_SETUP              0x06 // 'RF setup' register address
#define RFM7x_REG_STATUS                0x07 // 'Status' register address
#define RFM7x_REG_OBSERVE_TX            0x08 // 'Observe TX' register address
#define RFM7x_REG_CD                    0x09 // 'Carrier Detect' register address
#define RFM7x_REG_RX_ADDR_P0            0x0A // 'RX address pipe0' register address
#define RFM7x_REG_RX_ADDR_P1            0x0B // 'RX address pipe1' register address
#define RFM7x_REG_RX_ADDR_P2            0x0C // 'RX address pipe2' register address
#define RFM7x_REG_RX_ADDR_P3            0x0D // 'RX address pipe3' register address
#define RFM7x_REG_RX_ADDR_P4            0x0E // 'RX address pipe4' register address
#define RFM7x_REG_RX_ADDR_P5            0x0F // 'RX address pipe5' register address
#define RFM7x_REG_TX_ADDR               0x10 // 'TX address' register address
#define RFM7x_REG_RX_PW_P0              0x11 // 'RX payload width, pipe0' register address
#define RFM7x_REG_RX_PW_P1              0x12 // 'RX payload width, pipe1' register address
#define RFM7x_REG_RX_PW_P2              0x13 // 'RX payload width, pipe2' register address
#define RFM7x_REG_RX_PW_P3              0x14 // 'RX payload width, pipe3' register address
#define RFM7x_REG_RX_PW_P4              0x15 // 'RX payload width, pipe4' register address
#define RFM7x_REG_RX_PW_P5              0x16 // 'RX payload width, pipe5' register address
#define RFM7x_REG_FIFO_STATUS           0x17 // 'FIFO Status Register' register address
#define RFM7x_REG_DYNPD                 0x1c // 'Enable dynamic payload length' register address
#define RFM7x_REG_FEATURE               0x1d // 'Feature' register address

// Status Register
#define RFM7x_STATUS_IRQ_RX_DR          0x40 // Status bit RX_DR IRQ
#define RFM7x_STATUS_IRQ_TX_DS          0x20 // Status bit TX_DS IRQ
#define RFM7x_STATUS_IRQ_MAX_RT         0x10 // Status bit MAX_RT IRQ
#define RFM7x_STATUS_IRQ_TX_FULL        0x01
#define RFM7x_STATUS_RBANK              0x80
#define RFM7x_STATUS_RX_PIPE_NUM        0x0E

// Config Register
// #define RFM7x_CONFIG_MASK_RX_DR         0x40 // Mask interrupt caused by RX_DR when 1
// #define RFM7x_CONFIG_MASK_TX_DS         0x20 // Mask interrupt caused by TX_DS when 1
// #define RFM7x_CONFIG_MASK_MAX_RT        0x10 // Mask interrupt caused by MAX_RT when 1
// #define RFM7x_CONFIG_POWER              0x02 // 1 - Power up ; 0 - Power down
// #define RFM7x_CONFIG_PRIM_RX            0x01 // 1 - Receiver ; 0 - Transmitter

// FIFO Status Register
#define RFM7x_FIFO_STATUS_TX_REUSE      0x40
#define RFM7x_FIFO_STATUS_TX_FULL       0x20
#define RFM7x_FIFO_STATUS_TX_EMPTY      0x10
#define RFM7x_FIFO_STATUS_RX_FULL       0x02
#define RFM7x_FIFO_STATUS_RX_EMPTY      0x01

// Feature Register
//#define RFM7x_FEATURE_EN_DPL            0x04
//#define RFM7x_FEATURE_EN_ACK_PAY        0x02
//#define RFM7x_FEATURE_EN_DYN_ACK        0x01
 
#define RFM7x_BANK0_ENTRIS_BASE 3 // just 3 regs

#ifdef FM7x_PIPE0_RX_PAYLOAD_LEN // a crude way to do it
	#define FM7x_BANK0_ADDENTRY_A 1
#else
	#define FM7x_BANK0_ADDENTRY_A 0
#endif
#ifdef FM7x_PIPE1_RX_PAYLOAD_LEN // it could be somehow better
	#define FM7x_BANK0_ADDENTRY_B 1
#else
	#define FM7x_BANK0_ADDENTRY_B 0
#endif
#ifdef FM7x_PIPE2_RX_PAYLOAD_LEN 
	#define FM7x_BANK0_ADDENTRY_C 1
#else
	#define FM7x_BANK0_ADDENTRY_C 0
#endif
#ifdef FM7x_PIPE3_RX_PAYLOAD_LEN 
	#define FM7x_BANK0_ADDENTRY_D 1
#else
	#define FM7x_BANK0_ADDENTRY_D 0
#endif
#ifdef FM7x_PIPE4_RX_PAYLOAD_LEN 
	#define FM7x_BANK0_ADDENTRY_E 1
#else
	#define FM7x_BANK0_ADDENTRY_E 0
#endif
#ifdef FM7x_PIPE5_RX_PAYLOAD_LEN 
	#define FM7x_BANK0_ADDENTRY_F 1
#else
	#define FM7x_BANK0_ADDENTRY_F 0
#endif

#ifdef RFM7x_PIPE2_RX_ADDRESS
	#define FM7x_BANK0_ADDENTRY_G 1
#else
	#define FM7x_BANK0_ADDENTRY_G 0
#endif
#ifdef RFM7x_PIPE3_RX_ADDRESS
	#define FM7x_BANK0_ADDENTRY_H 1
#else
	#define FM7x_BANK0_ADDENTRY_H 0
#endif
#ifdef RFM7x_PIPE4_RX_ADDRESS
	#define FM7x_BANK0_ADDENTRY_I 1
#else
	#define FM7x_BANK0_ADDENTRY_I 0
#endif
#ifdef RFM7x_PIPE5_RX_ADDRESS
	#define FM7x_BANK0_ADDENTRY_J 1
#else
	#define FM7x_BANK0_ADDENTRY_J 0
#endif

#define RFM7x_BANK0_REG_CONFIG     ((RFM7x_CONFIG_PWR_UP << 1)|(RFM7x_CONFIG_CRCO << 2)|(RFM7x_CONFIG_EN_CRC << 3)|(RFM7x_CONFIG_MASK_MAX_RT << 4)|(RFM7x_CONFIG_MASK_TX_DS << 5)|(RFM7x_CONFIG_MASK_RX_DR << 6))
#define RFM7x_BANK0_REG_EN_AA      ((RFM7x_CONFIG_ENAA_P0 << 0)|(RFM7x_CONFIG_ENAA_P1 << 1)|(RFM7x_CONFIG_ENAA_P2 << 2)|(RFM7x_CONFIG_ENAA_P3 << 3)|(RFM7x_CONFIG_ENAA_P4 << 4)|(RFM7x_CONFIG_ENAA_P5 << 5))
#define RFM7x_BANK0_REG_EN_RXADDR  ((RFM7x_CONFIG_ERX_P0 << 0)|(RFM7x_CONFIG_ERX_P1 << 1)|(RFM7x_CONFIG_ERX_P2 << 2)|(RFM7x_CONFIG_ERX_P3 << 3)|(RFM7x_CONFIG_ERX_P4 << 4)|(RFM7x_CONFIG_ERX_P5 << 5))
#define RFM7x_BANK0_REG_SETUP_AW   ((RFM7x_CONFIG_AW))
#define RFM7x_BANK0_REG_SETUP_RETR ((RFM7x_CONFIG_ARC)|(RFM7x_CONFIG_ARD << 4))
#define RFM7x_BANK0_REG_RF_CH      (RFM7x_CONFIG_RF_CH)

#if (RFM7x_MODULECHIP_USED == 4) // bk2411
	#define RFM7x_BANK0_REG_RF_SETUP ((RFM7x_CONFIG_LNA_HCURR)|((RFM7x_CONFIG_RF_PWR & 0x03) << 1)|((RFM7x_CONFIG_RF_PWR >> 2) << 4)|(RFM7x_CONFIG_RF_DR << 3)|(BK2411_CONFIG_DREG_ON << 5)|(BK2411_CONFIG_RSSI_EN << 6))
#else
	#define RFM7x_BANK0_REG_RF_SETUP ((RFM7x_CONFIG_LNA_HCURR)|(RFM7x_CONFIG_RF_PWR << 1)|((RFM7x_CONFIG_RF_DR & 0x01) << 3)|((RFM7x_CONFIG_RF_DR >> 1) << 5))
#endif

#define RFM7x_BANK0_REG_DYNPD      ((RFM7x_CONFIG_DPL_P0 << 0)|(RFM7x_CONFIG_DPL_P1 << 1)|(RFM7x_CONFIG_DPL_P2 << 2)|(RFM7x_CONFIG_DPL_P3 << 3)|(RFM7x_CONFIG_DPL_P4 << 4)|(RFM7x_CONFIG_DPL_P5 << 5))
#define RFM7x_BANK0_REG_FEATURE    ((RFM7x_CONFIG_EN_DYN_ACK)|(RFM7x_CONFIG_EN_ACK_PAY << 1)|(RFM7x_CONFIG_EN_DPL << 2))

#if !defined(RFM7x_DO_NOT_INITIALIZE_EN_AA_IF_SAME)||(RFM7x_BANK0_REG_EN_AA != 0x3f)
	#define FM7x_BANK0_ADDCONFENTRY_A 1
#else
	#define FM7x_BANK0_ADDCONFENTRY_A 0
#endif

#if !defined(RFM7x_DO_NOT_INITIALIZE_EN_RXADDR_IF_SAME)||(RFM7x_BANK0_REG_EN_RXADDR != 0x03)
	#define FM7x_BANK0_ADDCONFENTRY_B 1
#else
	#define FM7x_BANK0_ADDCONFENTRY_B 0
#endif

#if !defined(RFM7x_DO_NOT_INITIALIZE_SETUP_AW_IF_SAME)||(RFM7x_BANK0_REG_SETUP_AW != 0x03)
	#define FM7x_BANK0_ADDCONFENTRY_C 1
#else
	#define FM7x_BANK0_ADDCONFENTRY_C 0
#endif

#if !defined(RFM7x_DO_NOT_INITIALIZE_SETUP_RETR_IF_SAME)||(RFM7x_BANK0_REG_SETUP_RETR != 0x03)
	#define FM7x_BANK0_ADDCONFENTRY_D 1
#else
	#define FM7x_BANK0_ADDCONFENTRY_D 0
#endif

#if !defined(RFM7x_DO_NOT_INITIALIZE_EN_RXADDR_IF_SAME)||(RFM7x_CONFIG_RF_CH != 0x02)
	#define FM7x_BANK0_ADDCONFENTRY_E 1
#else
	#define FM7x_BANK0_ADDCONFENTRY_E 0
#endif

#if !defined(RFM7x_DO_NOT_INITIALIZE_DYNPD_IF_SAME)||(RFM7x_BANK0_REG_DYNPD != 0)
	#define FM7x_BANK0_ADDCONFENTRY_F 1
#else
	#define FM7x_BANK0_ADDCONFENTRY_F 0
#endif

#ifdef RFM7x_INITIALIZE_BANK0_STATUS_REGISTERS
	#define FM7x_BANK0_ADDENTRY_STATUS 4
#else
	#define FM7x_BANK0_ADDENTRY_STATUS 0
#endif

#ifdef RFM7x_DO_NOT_INITIALIZE_BANK0
	#define RFM7x_BANK0_ENTRIES 0
#else
	#define RFM7x_BANK0_ENTRIES ((RFM7x_BANK0_ENTRIS_BASE) + (FM7x_BANK0_ADDENTRY_A) + (FM7x_BANK0_ADDENTRY_B) + (FM7x_BANK0_ADDENTRY_C) + (FM7x_BANK0_ADDENTRY_D) + (FM7x_BANK0_ADDENTRY_E) + (FM7x_BANK0_ADDENTRY_F) + (FM7x_BANK0_ADDENTRY_G) + (FM7x_BANK0_ADDENTRY_H) + (FM7x_BANK0_ADDENTRY_I) + (FM7x_BANK0_ADDENTRY_J) + (FM7x_BANK0_ADDCONFENTRY_A) + (FM7x_BANK0_ADDCONFENTRY_B) + (FM7x_BANK0_ADDCONFENTRY_C) + (FM7x_BANK0_ADDCONFENTRY_D) + (FM7x_BANK0_ADDCONFENTRY_E) + (FM7x_BANK0_ADDCONFENTRY_F) + (FM7x_BANK0_ADDENTRY_STATUS))
#endif

#if (RFM7x_MODULECHIP_USED == 0 || RFM7x_MODULECHIP_USED == 1) // BK2421 aka RFM70 + BK2401
//#elif (RFM7x_MODULECHIP_USED == 1) // BK2421 aka RFM70

	#ifdef RFM70_INITIALIZE_BANK1_RESERVED_REGISTERS
		#define RFM7x_BANK1_ENTRIES 15 // including RAMP_CURVE 
	#else
		#define RFM7x_BANK1_ENTRIES 9 // including RAMP_CURVE 
	#endif

#elif (RFM7x_MODULECHIP_USED == 2) // BK2423 aka RFM73

	#ifdef RFM73_INITIALIZE_BANK1_RESERVED_REGISTERS
		#define RFM7x_BANK1_ENTRIES 15 // including RAMP_CURVE 
	#else
		#define RFM7x_BANK1_ENTRIES 9 // including RAMP_CURVE 
	#endif

#elif (RFM7x_MODULECHIP_USED == 3) // bk2425 aka RFM75
	
	#ifdef RFM75_INITIALIZE_BANK1_RESERVED_REGISTERS
		#define RFM7x_BANK1_ENTRIES 15 // including RAMP_CURVE 
	#else
		#define RFM7x_BANK1_ENTRIES 9 // including RAMP_CURVE 
	#endif
	
#elif (RFM7x_MODULECHIP_USED == 4) // bk2411/2412
	
	#ifdef BK2411_INITIALIZE_BANK1_RESERVED_REGISTERS
		#define RFM7x_BANK1_ENTRIES 15 // including RAMP_CURVE
	#else
		#define RFM7x_BANK1_ENTRIES 14 // including RAMP_CURVE
	#endif
	
#endif

#if defined(RFM7x_TX_ADDRESS)&&defined(RFM7x_PIPE0_RX_ADDRESS)&&defined(RFM7x_PIPE1_RX_ADDRESS)
	#define RFM7x_LONG_ADDR_ENTRIES 3
#elif (defined(RFM7x_TX_ADDRESS)&&defined(RFM7x_PIPE0_RX_ADDRESS))||(defined(RFM7x_PIPE0_RX_ADDRESS)&&defined(RFM7x_PIPE1_RX_ADDRESS))||(defined(RFM7x_TX_ADDRESS)&&defined(RFM7x_PIPE1_RX_ADDRESS))
	#define RFM7x_LONG_ADDR_ENTRIES 2
#elif defined(RFM7x_TX_ADDRESS)||defined(RFM7x_PIPE0_RX_ADDRESS)||defined(RFM7x_PIPE1_RX_ADDRESS)
	#define RFM7x_LONG_ADDR_ENTRIES 1
#else
	#define RFM7x_LONG_ADDR_ENTRIES 0
#endif

void rfm7x_init(void);
void rfm7x_toggle_reg4(void); // one of the chinese AN's (rfm73 -> rfm75) says that it should be executed after every PWR_UP, not only during initialization

void rfm7x_reg_write(uint8_t reg, uint8_t dat);
uint8_t rfm7x_reg_read(uint8_t reg);

void rfm7x_reg_buff_write(uint8_t reg, uint8_t *buff, uint8_t len);
void rfm7x_reg_buff_read(uint8_t reg, uint8_t *buff, uint8_t len);

uint8_t rfm7x_is_present(void);

void rfm7x_power_up(void);
void rfm7x_power_down(void);

void rfm7x_mode_receive(void);
void rfm7x_mode_transmit(void);

inline void rfm7x_return_standby_I(void) { RFM7x_CE_LOW; }

inline uint8_t rfm7x_tx_fifo_full(void) { return (rfm7x_reg_read(RFM7x_REG_FIFO_STATUS) & (1<<5)) != 0; }
inline uint8_t rfm7x_tx_fifo_empty(void) { return (rfm7x_reg_read(RFM7x_REG_FIFO_STATUS) & (1<<4)) != 0; }
		
inline uint8_t rfm7x_rx_fifo_full(void) { return (rfm7x_reg_read(RFM7x_REG_FIFO_STATUS) & (1<<1)) != 0; }
inline uint8_t rfm7x_rx_fifo_empty(void) { return (rfm7x_reg_read(RFM7x_REG_FIFO_STATUS) & (1<<0)) != 0; }

inline uint8_t rfm7x_receive_next_pipe(void) { return (rfm7x_reg_read(RFM7x_REG_STATUS) >> 1) & 0x07; }
inline uint8_t rfm7x_receive_next_length(void) { return rfm7x_reg_read(RFM7x_CMD_R_RX_PL_WID); }

uint8_t rfm7x_receive(uint8_t *buff); // returns received length // 0x00 - nothing received
void rfm7x_receive_nocheck(uint8_t *buff);
uint8_t rfm7x_receive_p(uint8_t *pipe, uint8_t *buff); // returns received length // 0x00 - nothing received

inline void rfm7x_receive_nocheck_s(uint8_t *buff, uint8_t length) { rfm7x_reg_buff_read(RFM7x_CMD_R_RX_PAYLOAD, buff, length); }
uint8_t rfm7x_receive_s(uint8_t *buff, uint8_t length); // returns number of received pipe // 0x07 - nothing received

inline void rfm7x_transmit(uint8_t *buff, uint8_t length) { rfm7x_reg_buff_write(RFM7x_CMD_W_TX_PAYLOAD, buff, length); }
inline void rfm7x_transmit_noack(uint8_t *buff, uint8_t length) { rfm7x_reg_buff_write(RFM7x_CMD_W_TX_PAYLOAD_NOACK, buff, length); }

// used in RX mode // transmit message while ACK'ing received packet on selected pipe
inline void rfm7x_rx_ack_transmit(uint8_t pipe, uint8_t *buff, uint8_t length) { rfm7x_reg_buff_write(RFM7x_CMD_W_ACK_PAYLOAD | pipe, buff, length); }

//uint8_t rfm7x_available(uint8_t *pipe); // normal receive mode // 
// reset irq flags??

void rfm7x_rssi_set_threshold_step(uint8_t level); // linear scale from 0 (-97dBm) to 15 (-67dBm) // bk2423 is also linearized, some levels may be out of useable range (over -105dBm)
inline uint8_t rfm7x_read_CD(void) { rfm7x_reg_read(RFM7x_REG_CD); }

//config
inline void rfm7x_set_channel(uint8_t channel) { rfm7x_reg_write(RFM7x_CMD_WRITE_REG|RFM7x_REG_RF_CH, channel); } // 0-83 , 0-127 , clears MAX_RT counter
void rfm7x_set_crc_length(uint8_t len);

//aw and addresses

//datarate
//pwr

//pipes
//AA

//DPL
//ACK_PAY
//DYN_ACK

// irq ? 
//status flags

#endif /* RFMTST_H_ */