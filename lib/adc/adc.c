#include "adc.h"

#include <avr/io.h>

#include "prescaler.h"

uint8_t initialized = 0;
uint8_t interrupt = 0;

void adc_init(ADC_REF v_ref) {
	//	ADC 	enable		prescaler
	ADCSRA = _BV(ADEN) | (ADC_PRESCALE & 0x0b0000111);
	
	//		voltage_reference	left align
	ADMUX = (v_ref << REFS0) | _BV(ADLAR);
	
	initialized = 1;
}

uint8_t adc_read8(ADC_CHANNEL channel) {	
	if (!initialized) {
		return 0;
	}
	
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	
	ADCSRA |= _BV(ADSC);
	while ( bit_is_set(ADCSRA, _BV(ADSC)) );
		
	return ADCH;
}
uint16_t adc_read10(ADC_CHANNEL channel) {
	if (!initialized) {
		return 0;
	}
	
	ADCSRA |= _BV(ADSC);
	while ( bit_is_set(ADCSRA, _BV(ADSC)) );
	
	uint16_t value = ADC >> 6;
	
	return value;
}

void adc_start_conv8(ADC_CHANNEL channel, void (*callback)(ADC_CHANNEL channel, uint8_t value)) {
	return 0;
}
void adc_start_conv10(ADC_CHANNEL channel, void (*callback)(ADC_CHANNEL channel, uint16_t value)) {
	return 0;
}