/*!
 * \brief
 *
 * \author Jan Oleksiewicz <jnk0le@hotmail.com>
 * \license SPDX-License-Identifier: MIT
 */

#include <stdlib.h>
#include <string.h>

//avr headers
#include <avr/io.h>
#include <util/delay.h>

#include "rfm7x.h"
#include "usart.h"

uint8_t buf[32];

int main(void)
{
	uint8_t pipe, len;

	uart_init(BAUD_CALC(115200));

	rfm7x_io_init();
	spi_init();

	while (!rfm7x_is_present()) // wait for end of rfm POR // it takes something about 16 ms
	{
		uart_putc('q');
		_delay_ms(0.5);
	}
	uart_puts("\r\n");

	rfm7x_init();
	
	_delay_ms(2); // >1,5ms startup delay
	rfm7x_toggle_reg4(); // couldn't reproduce any "PLL is not locked" condition, but better to do it after all (probably have to be executed after every power up)
	_delay_ms(0.5); // probably not necessary, but it is said to be used

	rfm7x_mode_receive();

	while (1)
	{
		if ((len = rfm7x_receive(buf)))
		{
			uart_putstrl((char*)buf, len);
			uart_puts("\r\n");
		}
	}
}