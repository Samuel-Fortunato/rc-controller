#include <avr/io.h>
#include <util/delay.h>

#include "adc/adc.h"
#include "adc/prescaler.h"

#define X1_PIN ADC0
#define Y1_PIN ADC1
#define X2_PIN ADC2
#define Y2_PIN ADC3

#define BATT_PIN ADC4

int main() {
	uint16_t battery_sensor;
	
	adc_init(REF_AVCC, ADC_PRESCALE);
	DIDR0 |= 0b00011111;
	
	DDRB = 0xFF;
	DDRD = 0b00000111;
	
	while (1) {
		adc_read10(BATT_PIN, &battery_sensor);
		
		PORTD = battery_sensor >> 2;
		
		if ( battery_sensor > 777 ) {
			PORTB = _BV(2);					// normal
		}
		else if ( battery_sensor > 754 ) {
			PORTB = _BV(1);					// low
		}
		else if ( battery_sensor > 709 ) {
			PORTB = _BV(0);					// warn
		}
		else {
			PORTB = 0x00;					// cutoff
		}
	}
}
