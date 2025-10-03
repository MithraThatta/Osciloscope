#include "stm32f103xb.h"
#include <stdio.h>
#include <stdint.h>
#include <uart.h>
#define Baud 115200UL
#define SYS_FREQ 8000000UL
#define SR_TXE (1U<<7)
#define IOPAEN (1U<<2)
#define UART2EN (1U<<17)
#define SR_RXNE (1U<<5)



static void uart2_set_baud(uint32_t pclk, uint32_t baud);
int __io_putchar(int ch);
void TxInitialize(void);
char uart2_read(void);
void RxTxInitialize(void);
void RXNEIEInterrupt(void);
uint8_t bufferpop(void);
void bufferReset(void);
int EndCheck(void);

static uint8_t buffer[64];
static uint8_t* head = buffer;
static uint8_t* tail = buffer;

uint8_t bufferpop(void)
{
	uint8_t tmp = (*tail);
	tail = tail + 1;
	return tmp;
}

int __io_putchar(int ch)
{
	(*head) = ch;
	head = head+1;
	USART2->CR1 |= (1U<<7);//enable txie
	return ch;
}

void bufferReset(void)
{
	head = buffer;
	tail = buffer;
	return;
}

int EndCheck(void)
{
	if(head == tail)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void TxInitialize(void)
{
	//clock buses for UART,GPIOA activated//
		RCC->APB1ENR |= UART2EN;
	    RCC->APB2ENR |= IOPAEN;

	    //setting up PA2 for UART2 TX//
	    //set CRL to 1011 for PA2//
	    GPIOA->CRL |= (1U<<11);
	    GPIOA->CRL &=~ (1U<<10);
	    GPIOA->CRL |= (1U<<9);
	    GPIOA->CRL |= (1U<<8);


	    //set baud rate//
	        uart2_set_baud(SYS_FREQ,Baud);

	    //enable usart transmitter//
	    USART2->CR1 = (1U<<3);

	    //enable USART module//
	    USART2->CR1 |= (1U<<13);
}



static void uart2_set_baud(uint32_t pclk, uint32_t baud) {

        USART2->BRR = ((pclk+(baud/2U))/baud);
    }




void RxTxInitialize(void)
{
	//clock buses for UART,GPIOA activated//
		RCC->APB1ENR |= UART2EN;
	    RCC->APB2ENR |= IOPAEN;

	    //setting up PA2 for UART2 TX//
	    //set CRL to 1011 for PA2//
	    GPIOA->CRL |= (1U<<11);
	    GPIOA->CRL &=~ (1U<<10);
	    GPIOA->CRL |= (1U<<9);
	    GPIOA->CRL |= (1U<<8);

	    //set pa3, 0100//
	    GPIOA->CRL &=~ (1U<<12);
	    GPIOA->CRL &=~ (1U<<13);
	    GPIOA->CRL |= (1U<<14);
	    GPIOA->CRL &=~ (1U<<15);




	    //set baud rate//
	        uart2_set_baud(SYS_FREQ,Baud);

	    //enable usart transmitter//
	    USART2->CR1 = (1U<<3);
	    //enable usart reciever//
	    USART2->CR1 |= (1U<<2);

	    //enable USART module//
	    USART2->CR1 |= (1U<<13);
}

char uart2_read(void)
{
	//wait till theres something to read
	while(!(USART2->SR & SR_RXNE)){}
	//read data
	return USART2->DR;
}





void RXNEIEInterrupt(void)
{
	//clock buses for UART,GPIOA activated//
		RCC->APB1ENR |= UART2EN;
	    RCC->APB2ENR |= IOPAEN;

	    //setting up PA2 for UART2 TX//
	    //set CRL to 1011 for PA2//
	    GPIOA->CRL |= (1U<<11);
	    GPIOA->CRL &=~ (1U<<10);
	    GPIOA->CRL |= (1U<<9);
	    GPIOA->CRL |= (1U<<8);

	    //set pa3, 0100//
	    GPIOA->CRL &=~ (1U<<12);
	    GPIOA->CRL &=~ (1U<<13);
	    GPIOA->CRL |= (1U<<14);
	    GPIOA->CRL &=~ (1U<<15);




	    //set baud rate//
	        uart2_set_baud(SYS_FREQ,Baud);

	    //enable usart transmitter//
	    USART2->CR1 = (1U<<3);
	    //enable usart reciever//
	    USART2->CR1 |= (1U<<2);
	    //enable RXIE in CR1
	    USART2->CR1 |= (1U<<5);
	    //enable in NVIC
	  //  NVIC_SetPriority(USART2_IRQn, 1);
	    NVIC_EnableIRQ(USART2_IRQn);


	    //enable USART module//
	    USART2->CR1 |= (1U<<13);
}
