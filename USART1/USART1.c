#include "USART1.h"

#define MAX_STRLEN 12
volatile char received_string[MAX_STRLEN+1];


void USART2_ini(uint32_t baudrate){

	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;


		 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
		 GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
		 GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
		 NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;



	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);


	USART_InitStruct.USART_BaudRate = baudrate;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART2, &USART_InitStruct);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);


	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART2, ENABLE);
}

void USART2_puts(volatile char *s){

	while(*s){
		while( !(USART2->SR & 0x00000040) );
		USART_SendData(USART2, *s);
		*s++;
	}
}

void USART2_puts_var(const char *s, int x)
{
	char str[30];
	sprintf(str, "%s = %d\r\n", s, x);
	USART2_puts(str);

}

void USART2_IRQHandler(void){


	if( USART_GetITStatus(USART2, USART_IT_RXNE) ){

		static uint8_t cnt = 0;
		char t = USART2->DR;

		if( (t != '\n') && (cnt < MAX_STRLEN) ){
			received_string[cnt] = t;
			cnt++;
		}
		else{
			cnt = 0;
			USART2_puts(received_string);
		}
	}
}
