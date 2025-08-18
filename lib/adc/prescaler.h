#pragma once

#if (F_CPU / 2 < 50000)
	#error "ADC frequency too low"
#elif (F_CPU / 128 > 200000)
	#error "ADC frequency too high"
#elif (F_CPU / 2 >= 50000) && (F_CPU / 4 <= 200000)
	#define ADC_PRESCALE 0
#elif (F_CPU / 4 >= 50000) && (F_CPU / 4 <= 200000)
	#define ADC_PRESCALE 2
#elif (F_CPU / 8 >= 50000) && (F_CPU / 8 <= 200000)
	#define ADC_PRESCALE 3
#elif (F_CPU / 16 >= 50000) && (F_CPU / 16 <= 200000)
	#define ADC_PRESCALE 4
#elif (F_CPU / 32 >= 50000) && (F_CPU / 32 <= 200000)
	#define ADC_PRESCALE 5
#elif (F_CPU / 64 >= 50000) && (F_CPU / 64 <= 200000)
	#define ADC_PRESCALE 6
#elif (F_CPU / 128 >= 50000) && (F_CPU / 128 <= 200000)
	#define ADC_PRESCALE 7
#else
	#error "No valid VAR found for this F_CPU"
#endif
