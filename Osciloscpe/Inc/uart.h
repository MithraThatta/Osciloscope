#include "stm32f103xb.h"
#include <stdio.h>
#include <stdint.h>
#ifndef UART_H_
#define UART_H_

void TxInitialize(void);
char uart2_read(void);
void RxTxInitialize(void);
void RXNEIEInterrupt(void);
uint8_t bufferpop(void);
void bufferReset(void);
int EndCheck(void);

#endif /* UART_H_ */


/*if((USART2->SR & SR_RXNE))
	{
		key = USART2->DR;
		printf("you just input %d\r\n", (uint8_t)key);
		    	if (((key) == 4))
		    	{
		    		printf("This matches the key!\n");
		    	}
		    	else
		    	{
		    		printf("This does not match the key\n");
		    	}
	} */



/*
 *
 *
 * void ADC1_2_IRQHandler(void)
{
	if (ADC1->SR & (1U<<1))
	{
				uint32_t sensorvalue = ADC1->DR;
		    	printf("%d \n", (int)sensorvalue);
		    	for(int i = 0;i<200000;i++);
		    	startConversion();
	}
}
*/

