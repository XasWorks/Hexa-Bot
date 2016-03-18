/*
 * TWIBasic.h
 *
 *  Created on: 29.02.2016
 *      Author: xasin
 */

#ifndef CODE_TWI_TWIBASIC_H_
#define CODE_TWI_TWIBASIC_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Buffer.h"

#include "TWI_StatCodes.h"

class TWI_Basic {
private:
	bool handleIdle();
	bool handleMT();
	bool handleMR();
	bool handleST();
	bool handleSR();

protected:

	// TWI Module interfacing functions
	void clearTWINT();	// Clear the TWINT-Flag. Begin transmission.

	void ACK(); 	// Set ACK Flag
	void NACK(); 	// Unset ACK Flag (NACK-Signal)

	uint8_t readSR();	// Read TWI status register

	void start();	// Start a TWI transmission
	void noStart();	// Clear TWSTA Flag
	void stop();	// Send a TWI stop signal

	// Virtual functions for handling the TWI
			// Idling function
	virtual void onIdle();
		// error function
	virtual void onError();

		// Master-Transmit finished
	virtual void onMTFinish();
		// Master-Read finished
	virtual void onMRFinish();

		// Slave-Transmit starting
	virtual void onSTStart();
		// Slave-Read finished
	virtual void onSRFinish();

public:

	static TWI_Basic *TWISys;

	uint8_t readLength = 0; 	// How many bytes should be read in?
	Buffer buf = Buffer();		// I/O Buffer

	TWI_Basic();	// Constructor

	void load(uint8_t data); 	// Load a data-byte into buffer.

	void update(); 	// Update the TWI interface. Called within ISR
};

#endif /* CODE_TWI_TWIBASIC_H_ */
