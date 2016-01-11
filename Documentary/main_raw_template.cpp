#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_ISR1 1000

ISR(TIMER1_COMPA_vect) {
}


int main() {

	//CTC Register 1A set up for F_ISR Speed
	OCR1A = F_CPU/64/F_ISR1 -1;
	//Clock select to 64-prescaler, CTC mode
	TCCR1B |= ((1<< CS11) | (1<< CS10) | (1<< WGM12));
	//Timer output/compare match 1A bit set
	TIMSK1 |= (1<< OCIE1A);

	//Enable global interrupts
	sei();
	
	while(true) {
	}
	
	return 0;
}
