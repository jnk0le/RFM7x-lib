/*!
 * \brief customize this hardcoded file for your platform
 *
 * \author Jan Oleksiewicz <jnk0le@hotmail.com>
 * \license SPDX-License-Identifier: MIT
 */

#if defined(ARDUINO)
	#include <Arduino.h>
	#include <SPI.h>
#elif defined(__AVR_ARCH__)
	#include <avr/io.h>
#else
	#include <cmsis_device.h>
#endif

#include "rfm7x_hardware.h"

void rfm7x_io_init(void) //hardcoded at the moment
{
	RFM7x_CSN_HI;
	RFM7x_CE_LOW;
	
	//set direction
#if defined(USE_EXAMPLE_SPI_MEGA328)
	//set ce to output
	//set csn to output
#elif defined(USE_EXAMPLE_SPI_XMEGA)

	PORTC.DIRSET = PIN4_bm | PIN1_bm; // as output
#elif defined(USE_EXAMPLE_SPI_STM32F0)

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	GPIOA->MODER  |= (0b01 << GPIO_MODER_MODER3_Pos) | (0b01 << GPIO_MODER_MODER4_Pos); // set PA3 and PA4 to output
#elif defined(USE_EXAMPLE_SPI_ARDUINO)
		
	pinMode(RFM7x_CE_ARDUINO_PIN,OUTPUT); // ce
	pinMode(RFM7x_CSN_ARDUINO_PIN,OUTPUT); //csn
#else // soft
	//set ce to output
	//set csn to output
#endif
}

void spi_init(void)
{
#if defined(USE_EXAMPLE_SPI_MEGA328)
	DDRB |= (1 << PB3) | (1 << PB5); // configure output pins
	PORTB |= (1 << PB4); // pullup miso

	SPCR |= (1 << SPE) | (1 << MSTR);
	SPSR |= (1 << SPI2X);
	
#elif defined(USE_EXAMPLE_SPI_XMEGA)
	PORTC.DIRSET = PIN5_bm | PIN7_bm; // sck , mosi
	PORTC.PIN6CTRL = PORT_OPC_PULLUP_gc; // pullup miso
	SPIC.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_0_gc | SPI_PRESCALER_DIV4_gc; // 32MHz/4
#elif defined(USE_EXAMPLE_SPI_STM32F0)

	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	GPIOA->MODER  |= (0b10 << GPIO_MODER_MODER5_Pos)|(0b10 << GPIO_MODER_MODER6_Pos)|(0b10 << GPIO_MODER_MODER7_Pos); // PA5, PA6, PA7 as alternate

	GPIOA->OSPEEDR |= (0b11 << GPIO_OSPEEDR_OSPEEDR5_Pos)|(0b11 << GPIO_OSPEEDR_OSPEEDR7_Pos); // set SCK and MOSI into high speed mode
	GPIOA->PUPDR |= (1 << GPIO_PUPDR_PUPDR6_Pos); // pullup miso

	SPI1->CR2 |= SPI_CR2_FRXTH; // RXNE treshold at 1 byte
	SPI1->CR1 = SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_SPE | (0b10 << SPI_CR1_BR_Pos) | SPI_CR1_MSTR; // soft NSS force to master, enable, PCLK/8, master
	//SSOE ???
#elif defined(USE_EXAMPLE_SPI_ARDUINO)
	SPI.begin();
	
	// necessary?
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE0);
	SPI.setClockDivider(SPI_CLOCK_DIV4);
#else
	// can be optimized into single write if port wiring allows
	SOFT_SPI_SCK_DIRSET();
	SOFT_SPI_MOSI_DIRSET();
	SOFT_SPI_MISO_DIRSET(); // always input after POR, can be commented out
	SOFT_SPI_MISO_PULLUP_SET(); // ??
#endif
}

uint8_t spi_rw(uint8_t data)
{
#if defined(USE_EXAMPLE_SPI_MEGA328)
	SPDR = data;
	while (!(SPSR & (1 << SPIF)));

	return SPDR;
	
#elif defined(USE_EXAMPLE_SPI_XMEGA)
	SPIC.DATA = dat;
	while(!(SPIC.STATUS & (1<<7))); // no SPIF defined

	return SPIC.DATA;

#elif defined(USE_EXAMPLE_SPI_STM32F0)
	
	while( (SPI1->SR & SPI_SR_BSY) );
	*(uint8_t *)&(SPI1->DR) = data; // cast to make 8 bit transfer and thus transmit only 8bit frame
	while( !(SPI1->SR & SPI_SR_RXNE) );
	data = SPI1->DR;
	return data;
#elif defined(USE_EXAMPLE_SPI_ARDUINO)
	uint8_t tmp = SPI.transfer(data);
	return tmp;
#else
	for(uint_fast8_t i = 0; i < 8; i++)
	{
		if (dat & 0x80) 
			SOFT_SPI_MOSI_HI();
		else 
			SOFT_SPI_MOSI_LO();
		
		_delay_us(0.125);
		SOFT_SPI_SCK_HI();
		_delay_us(0.125);
		
		dat <<= 1;
		data <<= 1;
		 
		if (SOFT_SPI_MISO_READ()) 
			data |= 0x01; // data++
		 
		_delay_us(0.125);
		SOFT_SPI_SCK_LO();
		_delay_us(0.125);
	 }
	 
	 return data;
#endif	
}

// void spi_reg_write(uint8_t reg, uint8_t dat)
// {
// 	spi_rw(reg);
// 	spi_rw(dat);
// }
// 
// uint8_t spi_reg_read(uint8_t reg)
// {
// 	uint8_t tmp;
// 	
// 	spi_rw(reg);
// 	tmp = spi_rw(0);
// 	
// 	return tmp; // spi_rw(spi_rw(reg))
// }

// void spi_reg_buff_write(uint8_t reg, uint8_t *buff, uint8_t len)
// {
// 	spi_rw(reg);
// 	
// 	for(uint8_t i=0; i<len; i++)
// 		spi_rw(buff[i]);
// }

void spi_buff_write(uint8_t *buff, uint8_t len)
{
	for(uint_fast8_t i=0; i<len; i++)
		spi_rw(buff[i]);
}

// void spi_reg_buff_read(uint8_t reg, uint8_t *buff, uint8_t len)
// {
// 	spi_rw(reg);
// 	
// 	for(uint8_t i=0; i<len; i++)
// 		buff[i] = spi_rw(0);
// }

void spi_buff_read(uint8_t *buff, uint8_t len)
{
	for(uint_fast8_t i=0; i<len; i++)
		buff[i] = spi_rw(0);
}
