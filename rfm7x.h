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

#define RFM7x_REG_CONFIG                0x00 // 'Config'
#define RFM7x_REG_EN_AA                 0x01 // 'Enable Auto Acknowledgment'
#define RFM7x_REG_EN_RXADDR             0x02 // 'Enabled RX addresses'
#define RFM7x_REG_SETUP_AW              0x03 // 'Setup address width'
#define RFM7x_REG_SETUP_RETR            0x04 // 'Setup Auto. Retrans'
#define RFM7x_REG_RF_CH                 0x05 // 'RF channel'
#define RFM7x_REG_RF_SETUP              0x06 // 'RF setup'
#define RFM7x_REG_STATUS                0x07 // 'Status'
#define RFM7x_REG_OBSERVE_TX            0x08 // 'Observe TX'
#define RFM7x_REG_CD                    0x09 // 'Carrier Detect'
#define RFM7x_REG_RX_ADDR_P0            0x0A // 'RX address pipe0'
#define RFM7x_REG_RX_ADDR_P1            0x0B // 'RX address pipe1'
#define RFM7x_REG_RX_ADDR_P2            0x0C // 'RX address pipe2'
#define RFM7x_REG_RX_ADDR_P3            0x0D // 'RX address pipe3'
#define RFM7x_REG_RX_ADDR_P4            0x0E // 'RX address pipe4'
#define RFM7x_REG_RX_ADDR_P5            0x0F // 'RX address pipe5'
#define RFM7x_REG_TX_ADDR               0x10 // 'TX address'
#define RFM7x_REG_RX_PW_P0              0x11 // 'RX payload width, pipe0'
#define RFM7x_REG_RX_PW_P1              0x12 // 'RX payload width, pipe1'
#define RFM7x_REG_RX_PW_P2              0x13 // 'RX payload width, pipe2'
#define RFM7x_REG_RX_PW_P3              0x14 // 'RX payload width, pipe3'
#define RFM7x_REG_RX_PW_P4              0x15 // 'RX payload width, pipe4'
#define RFM7x_REG_RX_PW_P5              0x16 // 'RX payload width, pipe5'
#define RFM7x_REG_FIFO_STATUS           0x17 // 'FIFO Status Register'
#define RFM7x_REG_DYNPD                 0x1c // 'Enable dynamic payload length'
#define RFM7x_REG_FEATURE               0x1d // 'Feature' register address

// Status Register
#define RFM7x_STATUS_IRQ_RX_DR          0x40 
#define RFM7x_STATUS_IRQ_TX_DS          0x20 
#define RFM7x_STATUS_IRQ_MAX_RT         0x10
#define RFM7x_STATUS_IRQ_TX_FULL        0x01
#define RFM7x_STATUS_RBANK              0x80
#define RFM7x_STATUS_RX_PIPE_NUM        0x0E

// FIFO Status Register
#define RFM7x_FIFO_STATUS_TX_REUSE      0x40
#define RFM7x_FIFO_STATUS_TX_FULL       0x20
#define RFM7x_FIFO_STATUS_TX_EMPTY      0x10
#define RFM7x_FIFO_STATUS_RX_FULL       0x02
#define RFM7x_FIFO_STATUS_RX_EMPTY      0x01

// Config Register
#define RFM7x_CONFIG_MASK_RX_DR         0x40 // Mask interrupt caused by RX_DR when 1
#define RFM7x_CONFIG_MASK_TX_DS         0x20 // Mask interrupt caused by TX_DS when 1
#define RFM7x_CONFIG_MASK_MAX_RT        0x10 // Mask interrupt caused by MAX_RT when 1
#define RFM7x_CONFIG_EN_CRC             0x08
#define RFM7x_CONFIG_CRCO               0x04
#define RFM7x_CONFIG_POWER              0x02 // 1 - Power up ; 0 - Power down
#define RFM7x_CONFIG_PRIM_RX            0x01 // 1 - Receiver ; 0 - Transmitter

//EN_RXADDR

// Feature Register
#define RFM7x_FEATURE_EN_DPL            0x04
#define RFM7x_FEATURE_EN_ACK_PAY        0x02
#define RFM7x_FEATURE_EN_DYN_ACK        0x01

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

#define RFM7x_BANK0_REG_CONFIG     ((RFM7x_BANK0_CONF_PWR_UP << 1)|(RFM7x_BANK0_CONF_CRCO << 2)|(RFM7x_BANK0_CONF_EN_CRC << 3)|(RFM7x_BANK0_CONF_MASK_MAX_RT << 4)|(RFM7x_BANK0_CONF_MASK_TX_DS << 5)|(RFM7x_BANK0_CONF_MASK_RX_DR << 6))
#define RFM7x_BANK0_REG_EN_AA      ((RFM7x_BANK0_CONF_ENAA_P0 << 0)|(RFM7x_BANK0_CONF_ENAA_P1 << 1)|(RFM7x_BANK0_CONF_ENAA_P2 << 2)|(RFM7x_BANK0_CONF_ENAA_P3 << 3)|(RFM7x_BANK0_CONF_ENAA_P4 << 4)|(RFM7x_BANK0_CONF_ENAA_P5 << 5))
#define RFM7x_BANK0_REG_EN_RXADDR  ((RFM7x_BANK0_CONF_ERX_P0 << 0)|(RFM7x_BANK0_CONF_ERX_P1 << 1)|(RFM7x_BANK0_CONF_ERX_P2 << 2)|(RFM7x_BANK0_CONF_ERX_P3 << 3)|(RFM7x_BANK0_CONF_ERX_P4 << 4)|(RFM7x_BANK0_CONF_ERX_P5 << 5))
#define RFM7x_BANK0_REG_SETUP_AW   ((RFM7x_BANK0_CONF_AW))
#define RFM7x_BANK0_REG_SETUP_RETR ((RFM7x_BANK0_CONF_ARC)|(RFM7x_BANK0_CONF_ARD << 4))
#define RFM7x_BANK0_REG_RF_CH      (RFM7x_BANK0_CONF_RF_CH)

#if (RFM7x_MODULECHIP_USED == 4) // bk2411
	#define RFM7x_BANK0_REG_RF_SETUP ((RFM7x_BANK0_CONF_LNA_HCURR)|((RFM7x_BANK0_CONF_RF_PWR & 0x03) << 1)|((RFM7x_BANK0_CONF_RF_PWR >> 2) << 4)|(RFM7x_BANK0_CONF_RF_DR << 3)|(BK2411_BANK0_CONF_DREG_ON << 5)|(BK2411_BANK0_CONF_RSSI_EN << 6))
#else
	#define RFM7x_BANK0_REG_RF_SETUP ((RFM7x_BANK0_CONF_LNA_HCURR)|(RFM7x_BANK0_CONF_RF_PWR << 1)|((RFM7x_BANK0_CONF_RF_DR & 0x01) << 3)|((RFM7x_BANK0_CONF_RF_DR >> 1) << 5))
#endif

#define RFM7x_BANK0_REG_DYNPD      ((RFM7x_BANK0_CONF_DPL_P0 << 0)|(RFM7x_BANK0_CONF_DPL_P1 << 1)|(RFM7x_BANK0_CONF_DPL_P2 << 2)|(RFM7x_BANK0_CONF_DPL_P3 << 3)|(RFM7x_BANK0_CONF_DPL_P4 << 4)|(RFM7x_BANK0_CONF_DPL_P5 << 5))
#define RFM7x_BANK0_REG_FEATURE    ((RFM7x_BANK0_CONF_EN_DYN_ACK)|(RFM7x_BANK0_CONF_EN_ACK_PAY << 1)|(RFM7x_BANK0_CONF_EN_DPL << 2))

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

#if !defined(RFM7x_DO_NOT_INITIALIZE_EN_RXADDR_IF_SAME)||(RFM7x_BANK0_CONF_RF_CH != 0x02)
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

#define rfm7x_reg_write(__reg,__dat) rfm7x_cmd_write(RFM7x_CMD_WRITE_REG|(__reg),__dat)
#define rfm7x_reg_read(__reg) rfm7x_cmd_read(RFM7x_CMD_READ_REG|(__reg))

void rfm7x_cmd_write(uint8_t reg, uint8_t dat);
uint8_t rfm7x_cmd_read(uint8_t reg);

#define rfm7x_reg_buff_write(__reg,__buff,__len) rfm7x_cmd_buff_write(RFM7x_CMD_WRITE_REG|(__reg),__buff,__len)
#define rfm7x_reg_buff_read(__reg,__buff,__len) rfm7x_cmd_buff_read(RFM7x_CMD_READ_REG|(__reg),__buff,__len)

void rfm7x_cmd_buff_write(uint8_t reg, uint8_t *buff, uint8_t len);
void rfm7x_cmd_buff_read(uint8_t reg, uint8_t *buff, uint8_t len);

uint8_t rfm7x_is_present(void);

void rfm7x_power_up(void);
void rfm7x_power_down(void); // this function will not wait for finishing any ongoing transmission (results may be undefined)

void rfm7x_mode_receive(void);
void rfm7x_mode_transmit(void);

inline void rfm7x_mode_standby(void) { RFM7x_CE_LOW; }

inline uint8_t rfm7x_tx_fifo_full(void) { return (rfm7x_reg_read(RFM7x_REG_FIFO_STATUS) & (1<<5)) != 0; }
inline uint8_t rfm7x_tx_fifo_empty(void) { return (rfm7x_reg_read(RFM7x_REG_FIFO_STATUS) & (1<<4)) != 0; }
		
inline uint8_t rfm7x_rx_fifo_full(void) { return (rfm7x_reg_read(RFM7x_REG_FIFO_STATUS) & (1<<1)) != 0; }
inline uint8_t rfm7x_rx_fifo_empty(void) { return (rfm7x_reg_read(RFM7x_REG_FIFO_STATUS) & (1<<0)) != 0; }

inline uint8_t rfm7x_receive_next_pipe(void) { return (rfm7x_reg_read(RFM7x_REG_STATUS) >> 1) & 0x07; }
inline uint8_t rfm7x_receive_next_length(void) { return rfm7x_reg_read(RFM7x_CMD_R_RX_PL_WID); }

uint8_t rfm7x_receive(uint8_t *buff); // returns received length // 0x00 - nothing received
void rfm7x_receive_nocheck(uint8_t *buff);

uint8_t rfm7x_receive_p_(uint8_t *pipe, uint8_t *buff); // returns received length // 0x00 - nothing received
static inline uint8_t rfm7x_receive_p(uint8_t *buff, uint8_t *pipe) __attribute__((always_inline));
static inline uint8_t rfm7x_receive_p(uint8_t *buff, uint8_t *pipe) { return rfm7x_receive_p_(pipe, buff); }

inline void rfm7x_receive_nocheck_s(uint8_t *buff, uint8_t length) { rfm7x_cmd_buff_read(RFM7x_CMD_R_RX_PAYLOAD, buff, length); }
uint8_t rfm7x_receive_s(uint8_t *buff, uint8_t length); // returns number of received pipe // 0x07 - nothing received

uint8_t rfm7x_receive_f(uint8_t *buff, uint8_t *pipe, uint8_t *length);

inline void rfm7x_transmit(uint8_t *buff, uint8_t length) { rfm7x_cmd_buff_write(RFM7x_CMD_W_TX_PAYLOAD, buff, length); }
inline void rfm7x_transmit_noack(uint8_t *buff, uint8_t length) { rfm7x_cmd_buff_write(RFM7x_CMD_W_TX_PAYLOAD_NOACK, buff, length); }

// used in RX mode // transmit message while ACK'ing received packet on selected pipe
inline void rfm7x_rx_ack_transmit(uint8_t pipe, uint8_t *buff, uint8_t length) { rfm7x_cmd_buff_write(RFM7x_CMD_W_ACK_PAYLOAD | pipe, buff, length); }

//uint8_t rfm7x_available(uint8_t *pipe); // normal receive mode // 
// reset irq flags??

void rfm7x_rssi_set_threshold_step(uint8_t level); // linear scale from 0 (-97dBm) to 15 (-67dBm) // bk2423 is also linearized, some levels may be out of useable range (over -105dBm)
inline uint8_t rfm7x_read_CD(void) { rfm7x_reg_read(RFM7x_REG_CD); }

//config
inline void rfm7x_set_channel(uint8_t channel) { rfm7x_reg_write(RFM7x_REG_RF_CH, channel); } // 0-83 , 0-127 , clears MAX_RT counter
void rfm7x_set_crc_length(uint8_t len);

//bk2421/bk2423 aka rfm70/73
// 0 - -10 dBm
// 1 - -5 dBm
// 2 -  0 dBm
// 3 -  5 dBm

//bk2425 aka rfm75
// 0 - -25 dBm
// 1 - -18 dBm
// 2 - -12 dBm
// 3 - -7 dBm
// 4 - -1 dBm
// 5 - 4 dBm

//bk2411
// 0 - -35 dBm
// 1 - -25 dBm
// 2 - -15 dBm
// 3 - -5 dBm
// 4 - -5 dBm
// 5 - -5 dBm
// 6 - 0 dBm
// 7 - 5 dBm
void rfm7x_set_tx_pwr(uint8_t level);
void rfm7x_set_lna_gain(uint8_t enable);

// 0 - 1mbps
// 1 - 2mbps
// 2 - 250kbps // only 73/75
// 3 - 2mbps // only 73/75 (treat as reserved)
void rfm7x_set_datarate(uint8_t datarate);

//250us steps
inline void rfm7x_set_retransmits(uint8_t retransmits, uint8_t delay) { rfm7x_reg_write(RFM7x_REG_SETUP_RETR, (retransmits)|(delay<<4)); } 

// 3 to 5 bytes (2 byte width is reserved) 
inline void rfm7x_set_addres_width(uint8_t width) { rfm7x_reg_write(RFM7x_REG_SETUP_AW, width-2); } 

//0-32
inline void rfm7x_set_rx_pyaload_size(uint8_t pipe, uint8_t size) { rfm7x_reg_write(RFM7x_REG_RX_PW_P0+pipe, size); }

//void rfm7x_set_receiving_pipes(uint8_t mask);
//void rfm7x_set_autoack_pipes(uint8_t mask);
void rfm7x_enable_pipe_autoack(uint8_t pipe, uint8_t enabled);
void rfm7x_enable_pipe_receive(uint8_t pipe, uint8_t enabled);

//feature
void rfm7x_enable_dynamic_payload_feature(uint8_t enable);
void rfm7x_enable_ack_payload_feature(uint8_t enable);
void rfm7x_enable_noack_payload_feature(uint8_t enable);

// execute rfm7x_set_addres_width before (function reads AW from module)
//AVR: MSB       LSB
//  0x  44 33 22 11
void rfm7x_set_transmit_address(uint8_t* addr); // LSB first
void rfm7x_open_writing_pipe(uint64_t addr);

//pipe 1 and 2 (??)
void rfm7x_set_receive_address(uint8_t pipe, uint8_t* addr); // LSB first
inline void rfm7x_set_receive_address_pn(uint8_t pipe, uint8_t LSB_addr) { rfm7x_reg_write(RFM7x_REG_RX_ADDR_P0+pipe, LSB_addr); }

//all pipes
void rfm7x_open_reading_pipe(uint8_t pipe, uint64_t addr);

//bk2411 rssi
//bk2411 dreg

//observe tx
// lost packet reset

// irq ? 
//status flags

#endif /* RFM7x_H_ */