#pragma once

#include <avr/io.h>

typedef enum {
	REF_EXTERNAL = 0,
	REF_AVCC = 1,
	REF_INTERNAL = 3,
} ADC_REF;

typedef enum {
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7,
	ADC8,
	ADC_CHA_BG = 14,
	ADC_CHA_GND = 15,
} ADC_CHANNEL;

void adc_init(ADC_REF v_ref);

/*
	Reads the value on (channel) and returns the value
	Blocking - doesn't return until conversion is done
	8-bit result
*/
uint8_t adc_read8(ADC_CHANNEL channel);
/*	10-bit result */
uint16_t adc_read10(ADC_CHANNEL channel);

/*
	Starts conversion on (channel) and calls (callback) function when done
	
	Non-blocking:	waits while ADC is busy
					returns after conversion is started
	8-bit result
*/
void adc_start_conv8(ADC_CHANNEL channel, void (*callback)(ADC_CHANNEL channel, uint8_t value));
/*	10-bit result */
void adc_start_conv10(ADC_CHANNEL channel, void (*callback)(ADC_CHANNEL channel, uint16_t value));
