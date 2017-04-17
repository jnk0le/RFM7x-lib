#include <stdlib.h>
#include <string.h>

//avr headers
#include <avr/io.h>
#include <util/delay.h>

#include "spi.h"
#include "rfm7x.h"

char buf[32];

int main(void)
{
	uint32_t counter = 0;

	//PORTB.DIRSET = PIN0_bm | PIN1_bm | PIN2_bm;
	//clk_init();

	rfm_io_init();
	spi_init();

	//PORTB.OUTSET = PIN0_bm;
	while(!rfm7x_is_present()); // wait for end of rfm POR // it takes something about 16 ms
	//PORTB.OUTCLR = PIN0_bm;

	rfm7x_init();
	
	_delay_ms(2); // >1,5ms startup delay 
	rfm7x_toggle_reg4(); // couldn't reproduce any "PLL is not locked" condition, but better to do it after all (probably have to be executed after every power up)
	_delay_ms(0.5); // probably not necessary, but it is said to be used

	rfm7x_mode_transmit();

	while (1)
	{
		strcpy(buf,"counter: ");
		ltoa(counter, (char*)&buf[9], 10);

		while (rfm7x_tx_fifo_full())
		{
			uint8_t tmp = rfm7x_reg_read(RFM7x_REG_STATUS);
			if (tmp & RFM7x_STATUS_IRQ_MAX_RT)
			{
				//PORTB.OUTSET = PIN2_bm;

				rfm7x_mode_transmit(); // have the same affect as the following 2 lines

				//rfm7x_reg_write(RFM7x_CMD_WRITE_REG | RFM7x_REG_STATUS, 0x70); // nRF24l01+ and SI24R1 can live only with this line
				//rfm7x_reg_write(RFM7x_CMD_FLUSH_TX, 0); // but bk242x is "protected" from overrunning MAX_RT counter - it have to be executed to unlock any further transmissions in AA mode

				//_delay_ms(1);
				//PORTB.OUTCLR = PIN2_bm;
			}
		}

		rfm7x_transmit((uint8_t *)buf, strlen(buf));

		_delay_ms(100);
		counter++;

		//PORTB.OUTTGL = PIN1_bm;
	}
}