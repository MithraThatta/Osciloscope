#include "stm32f103xb.h"
#include <stdio.h>
#include <stdint.h>
#include <uart.h>
#include "adc.h"
void PrintADC();

static uint32_t ADCbuffer[5];
static uint32_t* ADChead = ADCbuffer;
static uint32_t* ADCtail = ADCbuffer;
int main(void)
{
	InitADC1INTERRUPT();
	RXNEIEInterrupt();
	startConversion();

    while(1)
    {

    	while ((ADChead >= ADCtail))
    	{
    		for(int i =0;i<5000;i++);
    		uint32_t tmp = *(ADCtail);
    		float tmp3 = ((float)tmp/1221);
    		printf("%f\n", tmp3);
    		ADCtail = ADCtail+1;


    		if (ADCtail == ADCbuffer+5)
    		{
    			ADCtail = ADCbuffer;
    		}
    	}



    }

}

void USART2_IRQHandler(void)
{
	if (USART2->SR & (1U<<7))
		{
			if(EndCheck()==1)
				{
					USART2->CR1 &=~ (1U<<7);
					bufferReset();

				}

				if (EndCheck()==0)
				{
					USART2->DR = bufferpop();
				}
		}

}

void bufferAdd(uint32_t val)
{
	if(ADChead == ADCbuffer+5)
	{
		ADChead = ADCbuffer;
	}
	*ADChead = val;
	ADChead = ADChead+1;

}

void ADC1_2_IRQHandler(void)
{
	if (ADC1->SR & (1U<<1))
	{
		uint32_t tmp2 = (ADC1->DR);
		bufferAdd(tmp2);
		startConversion();
	}
}


