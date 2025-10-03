#include "stm32f103xb.h"
#include <stdio.h>
#include <stdint.h>
#include <uart.h>
//PA1-ADC12_IN1, using ADC1 here

void InitADC1(void)
{


	//setup pa1
	RCC->APB2ENR |= (1U<<2);
	GPIOA->CRL &=~ (1U<<3);
	GPIOA->CRL &=~ (1U<<2);
	GPIOA->CRL &=~ (1U<<1);
	GPIOA->CRL &=~ (1U<<0);

	//clock access to adc1
		RCC->APB2ENR |= (1U<<9);


//set adc sequence register, sqr1 goes first, ADC->SQR =
	ADC1->SQR3 = (1U<<0);
//set length of 1 in seq reg 1. Length is just how many channels ur sampling
	ADC1->SQR1 = 0x00;
//turn on ADC via CR2, ADOn
    ADC1->CR2 |= (1U<<0);
}


//start conversion in seaparate function

void startConversion(void)
{
	//CR2 SWST ART, start with a software trigger
	ADC1->CR2 |= (1U<<0);
}


uint32_t adc_read(void)
{
	//wait for adc conversion to be complete via EOC in Status register
	while (!(ADC1->SR & (1U<<1))){}

	//read converted result
	return (ADC1->DR);

}

void InitADC1INTERRUPT(void)
{


	//setup pa1
	RCC->APB2ENR |= (1U<<2);
	GPIOA->CRL &=~ (1U<<3);
	GPIOA->CRL &=~ (1U<<2);
	GPIOA->CRL &=~ (1U<<1);
	GPIOA->CRL &=~ (1U<<0);

	//clock access to adc1
		RCC->APB2ENR |= (1U<<9);


//set adc sequence register, sqr1 goes first, ADC->SQR =
	ADC1->SQR3 = (1U<<0);
//set length of 1 in seq reg 1. Length is just how many channels ur sampling
	ADC1->SQR1 = 0x00;

// turn on EOCIE, sends interrupt when a conversion ends, when EOC is flagged
	ADC1->CR1 |= (1U<<5);

//enable NVIC interrupt for this
	//NVIC_SetPriority(ADC1_2_IRQn, 2);
	NVIC_EnableIRQ(ADC1_2_IRQn);

	__enable_irq();
//turn on ADC via CR2, ADOn
    ADC1->CR2 |= (1U<<0);
}
