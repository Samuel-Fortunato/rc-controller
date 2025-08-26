#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"

#define X1_PIN ADC0
#define Y1_PIN ADC1
#define X2_PIN ADC2
#define Y2_PIN ADC3

uint16_t reading;

int main() {
	uint8_t x1, y1, x2, y2;
	
	// global interrupt enable
	SREG |= _BV(7);
	
	adc_init(REF_AVCC);
	DIDR0 |= 0b00001111;
	
	DDRD = 0xFF;
	DDRB = 0xFF;
	
	while (1) {
		adc_read8(X1_PIN, &x1);
		adc_read8(Y1_PIN, &y1);
		adc_read8(X2_PIN, &x2);
		adc_read8(Y2_PIN, &y2);
		
		PORTD = x1;
		PORTB = y1;
	}
}
