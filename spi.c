#include <avr/io.h>
#include "spi.h"

// internally used alias for spi function (to not force name for generic spi transfer functions)
uint8_t rfm7x_xfer_spi(uint8_t dat) __attribute__ ((alias ("spi_xfer")));
void rfm7x_buff_write(uint8_t *buff, uint8_t len) __attribute__ ((alias ("spi_buff_write")));
void rfm7x_buff_read(uint8_t *buff, uint8_t len) __attribute__ ((alias ("spi_buff_read")));

void spi_init(void)
{
#if defined(USE_SPI_MEGA328)
	
	DDRB |= (1 << PB3) | (1 << PB5); // configure output pins
	PORTB |= (1 << PB4); // pullup miso 

	SPCR |= (1 << SPE) | (1 << MSTR); //DORD ?
	SPSR |= (1 << SPI2X);
	
#elif defined(USE_SPI_XMEGA)
	PORTC.DIRSET = PIN5_bm | PIN7_bm; // sck , mosi
	PORTC.PIN6CTRL = PORT_OPC_PULLUP_gc; // pullup miso
	SPIC.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_0_gc | SPI_PRESCALER_DIV4_gc; // 32MHz/4
#else
	// can be optimized into single write if port wiring allows
	SOFT_SPI_SCK_DIRSET();
	SOFT_SPI_MOSI_DIRSET();
	SOFT_SPI_MISO_DIRSET(); // always input after POR, can be commented out
	SOFT_SPI_MISO_PULLUP_SET();
#endif
}

uint8_t spi_xfer(uint8_t dat) // spi on PORTC in this case
{
#if defined(USE_SPI_MEGA328)
	SPDR = dat;
	while (!(SPSR & (1 << SPIF)));

	return SPDR;
	
#elif defined(USE_SPI_XMEGA)
	SPIC.DATA = dat;
	while(!(SPIC.STATUS & (1<<7))); // no SPIF defined

	return SPIC.DATA;
	
#else
	for(uint_fast8_t i = 0; i < 8; i++)
	{
		if (dat & 0x80) 
			SOFT_SPI_MOSI_HI();
		else 
			SOFT_SPI_MOSI_LO();
		
		_delay_us(0.5);
		SOFT_SPI_SCK_HI();
		_delay_us(0.5);
		
		dat <<= 1;
		 
		if (SOFT_SPI_MISO_READ()) 
			dat |= 0x01; // dat++
		 
		_delay_us(0.5);
		SOFT_SPI_SCK_LO();
		_delay_us(0.5);
	 }
	 
	 return dat;
#endif	
}

// void spi_reg_write(uint8_t reg, uint8_t dat)
// {
// 	spi_xfer(reg);
// 	spi_xfer(dat);
// }
// 
// uint8_t spi_reg_read(uint8_t reg)
// {
// 	uint8_t tmp;
// 	
// 	spi_xfer(reg);
// 	tmp = spi_xfer(0);  
// 	
// 	return tmp; // spi_xfer(spi_xfer(reg))
// }

// void spi_reg_buff_write(uint8_t reg, uint8_t *buff, uint8_t len)
// {
// 	spi_xfer(reg);
// 	
// 	for(uint8_t i=0; i<len; i++)
// 		spi_xfer(buff[i]);
// }

void spi_buff_write(uint8_t *buff, uint8_t len)
{
	for(uint_fast8_t i=0; i<len; i++)
		spi_xfer(buff[i]);
}

// void spi_reg_buff_read(uint8_t reg, uint8_t *buff, uint8_t len)
// {
// 	spi_xfer(reg);
// 	
// 	for(uint8_t i=0; i<len; i++)
// 		buff[i] = spi_xfer(0);
// }

void spi_buff_read(uint8_t *buff, uint8_t len)
{
	for(uint_fast8_t i=0; i<len; i++)
		buff[i] = spi_xfer(0);
}