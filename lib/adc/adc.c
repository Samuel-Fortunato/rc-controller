#include "adc.h"

#include <avr/io.h>

#include "prescaler.h"

uint8_t initialized = 0;

void adc_init(ADC_REF v_ref) {
	//	ADC 	enable	interrupt		prescaler
	ADCSRA = _BV(ADEN) | _BV(ADIE) | (ADC_PRESCALE & 0x0b0000111);
	
	//		voltage_reference	left align
	ADMUX = (v_ref << REFS0) | _BV(ADLAR);
	
	initialized = 1;
}

uint8_t adc_read8(ADC_CHANNEL channel, uint8_t *dest) {	
	if (!initialized) {
		return -1;
	}
	
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	
	ADCSRA |= _BV(ADSC);
	while ( bit_is_set(ADCSRA, _BV(ADSC)) );
	
	*dest = ADCH;
	
	return 0;
}
uint8_t adc_read10(ADC_CHANNEL channel, uint16_t *dest) {
	if (!initialized) {
		return -1;
	}
	
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	
	ADCSRA |= _BV(ADSC);
	while ( bit_is_set(ADCSRA, _BV(ADSC)) );
	
	*dest = ADC >> 6;
	
	return 0;
}

uint8_t adc_start_conv8(ADC_CHANNEL channel, void (*callback)(ADC_CHANNEL channel, uint8_t value)) {
	if (!initialized) {
		return -1;
	}
}
uint8_t adc_start_conv10(ADC_CHANNEL channel, void (*callback)(ADC_CHANNEL channel, uint16_t value)) {
	if (!initialized) {
		return -1;
	}
}