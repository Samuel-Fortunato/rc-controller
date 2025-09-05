#include "adc/adc.h"

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t initialized = 0;

uint8_t async_10bit;
ADC_CHANNEL async_channel;
void (*_callback8)(ADC_CHANNEL channel, uint8_t value);
void (*_callback10)(ADC_CHANNEL channel, uint16_t value);

void adc_init(ADC_REF v_ref, uint8_t prescaler) {
	//	ADC 	enable		prescaler
	ADCSRA = _BV(ADEN) | (prescaler & 0b00000111);
	
	//		voltage_reference
	ADMUX = (v_ref << REFS0);
	
	initialized = 1;
}

// Synchronous functions
int8_t adc_read8(ADC_CHANNEL channel, uint8_t *dest) {	
	if (!initialized) {
		return -1;
	}
	
	// wait for any previous conversion to finish
	while ( bit_is_set(ADCSRA, ADSC) );
	
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA &= ~_BV(ADIE);
	
	ADCSRA |= _BV(ADSC);
	while ( bit_is_set(ADCSRA, ADSC) );
	
	*dest = ADC >> 2;
	
	return 0;
}
int8_t adc_read10(ADC_CHANNEL channel, uint16_t *dest) {
	if (!initialized) {
		return -1;
	}
	
	// wait for any previous conversion to finish
	while ( bit_is_set(ADCSRA, ADSC) );
	
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA &= ~_BV(ADIE);
	
	ADCSRA |= _BV(ADSC);
	while ( bit_is_set(ADCSRA, ADSC) );
	
	*dest = ADC;
	
	return 0;
}


// Asynchronous functions
int8_t adc_start_conv8(ADC_CHANNEL channel, void (*callback)(ADC_CHANNEL channel, uint8_t value)) {
	if (!initialized) {
		return -1;
	}
	if ( bit_is_set(ADCSRA, ADSC) ) {
		return -2;
	}
	
	async_channel = channel;
	async_10bit = 0;
	_callback8 = callback;
	
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA |= _BV(ADIF);	// clear interrupt flag
	ADCSRA |= _BV(ADIE);
	
	ADCSRA |= _BV(ADSC);
	
	return 0;
}
int8_t adc_start_conv10(ADC_CHANNEL channel, void (*callback)(ADC_CHANNEL channel, uint16_t value)) {
	if (!initialized) {
		return -1;
	}
	if ( bit_is_set(ADCSRA, ADSC) ) {
		return -2;
	}
	
	async_channel = channel;
	async_10bit = 1;
	_callback10 = callback;
	
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA |= _BV(ADIF);	// clear interrupt flag
	ADCSRA |= _BV(ADIE);
	
	ADCSRA |= _BV(ADSC);
	
	return 0;
}


// Interrupt
ISR(ADC_vect) {
	ADCSRA &= ~_BV(ADIE);
	
	if (async_10bit) {
		_callback10(async_channel , ADC);
	}
	else {
		_callback8(async_channel , ADC >> 2);
	}
}