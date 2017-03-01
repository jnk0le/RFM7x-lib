#include <avr/io.h>
#include <util/delay.h>
#include "spi_soft.h"

void spi_init(void)
{
	// can be optimized into single write if wiring allows
	SOFT_SPI_SCK_DIRSET();
	SOFT_SPI_MOSI_DIRSET();
	SOFT_SPI_MISO_DIRSET(); // always input after POR, can be commented out
	SOFT_SPI_MISO_PULLUP_SET();
}

uint8_t spi_xfer(uint8_t dat)
{
	for(uint8_t i = 0; i < 8; i++)
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
}

// internally used alias for spi function (to not force name for generic spi transfer function)
uint8_t rfm7x_xfer_spi(uint8_t dat) __attribute__ ((alias ("spi_xfer")));

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
	for(uint8_t i=0; i<len; i++)
		spi_xfer(buff[i]);
}

void rfm7x_buff_write(uint8_t *buff, uint8_t len) __attribute__((alias("spi_buff_write")));

// void spi_reg_buff_read(uint8_t reg, uint8_t *buff, uint8_t len)
// {
// 	spi_xfer(reg);
//
// 	for(uint8_t i=0; i<len; i++)
// 		buff[i] = spi_xfer(0);
// }

void spi_buff_read(uint8_t *buff, uint8_t len)
{
	for(uint8_t i=0; i<len; i++)
		buff[i] = spi_xfer(0);
}

void rfm7x_buff_read(uint8_t *buff, uint8_t len) __attribute__((alias("spi_buff_read")));