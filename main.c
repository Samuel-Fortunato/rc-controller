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
	
	DDRD = 0xFF;
	DDRB = 0xFF;
	
	while (1) {
		adc_read10(BATT_PIN, &battery_sensor);
		
		PORTD = battery_sensor;
		PORTB = battery_sensor >> 8;
	}
}
