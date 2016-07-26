#ifndef USART3_H
#define USART3_H

#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_usart.h>
#include <misc.h>


#define USARTx USART3
#define  GPIO_Alternat_function GPIO_AF_USART3


uint32_t Pins_Pack_1;
uint32_t Pins_Pack_2;
uint32_t Pins_Pack_3;
uint32_t Pins_Pack_4;

uint32_t GPIO_Pin_x1;
uint32_t GPIO_Pin_x2;





void USART3_ini(uint32_t baudrate, uint32_t Pins);
void USART3_puts(volatile char *s);
void USART3_puts_var(volatile char *e, int x);
void USART3_IRQHandler(void);







#endif
