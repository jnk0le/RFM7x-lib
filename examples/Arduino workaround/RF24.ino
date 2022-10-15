/*!
 * \brief
 *
 * \author Jan Oleksiewicz <jnk0le@hotmail.com>
 * \license SPDX-License-Identifier: MIT
 */

// This is an example of using this library to force bk242x chips to work with various arduino libraries for nRF24l01(+)/SI24R1 
// Currently the usege is limited to preinitialization and handling weird conditions as addition for https://github.com/maniacbug/RF24
// It should work with other libraries also but you need to take care about used pins and differencies in transmission procedures
// make sure to alter hardcoded definitions in rfm7x_hardware.h and rfm7x_hardware.c
// also some definitions in rfm7x_config.h needs to be altered for flawless operations (mainly ACK bit)

// It is not intended to generate small and efficient code nor arduino is.
// NOT TESTED YET

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

#include "rfm7x.h" // not sure if it will just work or need to perform special "installation" process

//ce on pin 9
//csn on pin 10
RF24 radio(9,10);

void setup(void)
{
	rfm7x_io_init(); // hardcoded in rfm7x_hardware.h
	spi_init();

	while(!rfm7x_is_present()); // wait for end of rfm POR // it takes something about 16 ms

	rfm7x_init(); // initialize everything including magic registers
	
	delay(2); // >1,5ms startup delay
	rfm7x_toggle_reg4(); // couldn't reproduce any "PLL is not locked" condition, but better to do it after all (probably have to be executed after every power up)
	delay(1);
	
	// now initialize as before // reinitializing peripherals should not be a problem
	radio.begin();
	radio.setRetries(15,15);
	//...
}

int message_count;

void loop(void)
{
	//then follow regular examples with one exceptions

	bool ok = radio.write(&message_count, sizeof(int));
	// RF24::write will clear MAX_RT and flush TX_BUFFER so no need for unhanging procedure
	
	//...
	
	radio.writeAckPayload(1, &message_count, sizeof(int));
	
	// RF24::writeAckPayload is non blocking call so the following procedure have to be executed somehow after radio reaches all retransmissions
	// in this example we will just block until packet is sent out

	while(!rfm7x_tx_fifo_empty());
	
	//uint8_t tmp = rfm7x_reg_read(RFM7x_REG_STATUS);
	//if(tmp & RFM7x_STATUS_IRQ_MAX_RT)

	bool tx,fail,rx;
	radio.whatHappened(tx,fail,rx);
	if(fail)
	{
		rfm7x_reg_write(RFM7x_REG_STATUS, 0x10); // clear only MAX_RT flag // nRF24l01+ and SI24R1 can live with only this line
		rfm7x_reg_write(RFM7x_CMD_FLUSH_TX, 0); // but bk242x is "protected" from overrunning MAX_RT counter - FLUSH_TX have to be executed to unlock any further transmissions in AA mode
	}
	
	//...
}