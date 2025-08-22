#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"

uint8_t reading;

int main() {
	uint8_t x1, x2, y1, y2;
	
	// global interrupt enable
	SREG |= _BV(7);
	
	DDRD = 0xFF;
	
	adc_init(REF_AVCC);
	DIDR0 |= 0b00001111;
	
	while (1) {
		adc_read8(ADC0, &reading);
		PORTD = 1 << (reading / 32);
	}
}
