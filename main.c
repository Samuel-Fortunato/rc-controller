#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"

uint16_t reading;

void stickX(ADC_CHANNEL channel, uint8_t value) {
	PORTD = value;
}

int main() {
	uint8_t x1, x2, y1, y2;
	
	// global interrupt enable
	SREG |= _BV(7);
	
	DDRD = 0xFF;
	DDRB = 0xFF;
	
	adc_init(REF_AVCC);
	DIDR0 |= 0b00001111;
	
	while (1) {
		PORTB = adc_start_conv8(ADC0, &(stickX));
	}
}
