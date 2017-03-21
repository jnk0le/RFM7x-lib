#ifndef SPI_H_
#define SPI_H_

//#define USE_SPI_MEGA328
//#define USE_SPI_XMEGA

#if !defined(USE_SPI_MEGA328)&&!defined(USE_SPI_XMEGA)
	// tiny 2313 in this case
	// PB5 MOSI
	// PB6 MISO
	// PB7 SCK

	#define SOFT_SPI_MOSI_DIRSET()     DDRB |= (1<<PB5)
	#define SOFT_SPI_MISO_DIRSET()     DDRB &= ~(1<<PB6)
	#define SOFT_SPI_SCK_DIRSET()      DDRB |= (1<<PB7)
	#define SOFT_SPI_MISO_PULLUP_SET() PORTB |= (1<<PB6)

	#define SOFT_SPI_MOSI_HI()         PORTB |= (1<<PB5)
	#define SOFT_SPI_MOSI_LO()         PORTB &= ~(1<<PB5)

	#define SOFT_SPI_SCK_HI()          PORTB |= (1<<PB7)
	#define SOFT_SPI_SCK_LO()          PORTB &= ~(1<<PB7)

	#define SOFT_SPI_MISO_READ()       PINB & (1<<PB6)
#endif

void spi_init(void);

uint8_t spi_xfer(uint8_t dat);
uint8_t rfm7x_xfer_spi(uint8_t dat); // internally used alias for spi function (to not force name for generic spi transfer function)

//universal spi functions (no CSN/SS handling)
void spi_reg_write(uint8_t reg, uint8_t dat);
uint8_t spi_reg_read(uint8_t reg);

void spi_reg_buff_write(uint8_t reg, uint8_t *buff, uint8_t len);
void spi_buff_write(uint8_t *buff, uint8_t len);

void spi_reg_buff_read(uint8_t reg, uint8_t *buff, uint8_t len);
void spi_buff_read(uint8_t *buff, uint8_t len);

#endif /* SPI_H_ */