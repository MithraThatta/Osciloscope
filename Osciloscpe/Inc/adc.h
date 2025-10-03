#include "stm32f103xb.h"
#include <stdio.h>
#include <stdint.h>
#include <uart.h>


#ifndef ADC_H_
#define ADC_H_
#define ADC1En   (1U<<9)

void InitADC1(void);
void startConversion(void);
uint32_t adc_read(void);
void InitADC1INTERRUPT(void);

#endif /* ADC_H_ */



