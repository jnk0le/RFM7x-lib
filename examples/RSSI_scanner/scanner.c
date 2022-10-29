/*!
 * \brief
 *
 * \author Jan Oleksiewicz <jnk0le@hotmail.com>
 * \license SPDX-License-Identifier: MIT
 */

#include <avr/io.h>
#include <stdio.h>

//#include "uart.h"
#include "rfm7x.h"

int main(void)
{
	uint8_t Trssi[16];
	
	//clk_init();

	rfm7x_io_init();
	spi_init();

	//uart_init();

	while (!rfm7x_is_present()); //wait for end of rfm POR // it takes something about 16 ms

	rfm7x_init();

	_delay_ms(2); // >1,5ms startup delay 
	rfm7x_toggle_reg4(); // couldn't reproduce any "PLL is not locked" condition, but better to do it after all (probably have to be executed after every power up)
	_delay_ms(0.5); // probably not necessary, but it is said to be used

	while (1)
	{
		printf("\n\nScanning 127 channels through 16 RSSI levels\n\n");
		printf("\t<lower ----------------- rssi threshold ------------------ higher>\n");

		printf("channel\t");
		for (int i = 0; i<16; i++)
			printf("%4d", i);
		printf("\n");

		for (int ch = 0; ch<127; ch++)
		{
			rfm7x_set_channel(ch);
			memset(Trssi, 0, 16);

			for (int rep = 0; rep<255; rep++)
			{
				for (int level = 0; level<16; level++)
				{
					rfm7x_set_rssi_threshold_step(level);

					rfm7x_mode_receive();
					_delay_us(300); //130us + 128us 
					Trssi[level] += (rfm7x_read_CD() & 1);
					rfm7x_mode_standby();
				}
			}

			printf("%d\t", ch);
			for (int i = 0; i<16; i++)
				printf("%4d", Trssi[i]);

			printf("\n");
		}

		printf("press any key to continue ...");
		getc(stdin);
		//while(!uart_getc());
	}
}