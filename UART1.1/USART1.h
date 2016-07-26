#ifndef USART1_H
#define USART1_H

#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_usart.h>
#include <misc.h>


#define USARTx USART2
#define  GPIO_Alternat_function GPIO_AF_USART2


uint32_t Pins_Pack_1;
uint32_t Pins_Pack_2;


uint32_t GPIO_Pin_x1;
uint32_t GPIO_Pin_x2;

void USART2_ini(uint32_t baudrate, uint32_t Pins);
void USART2_puts(volatile char *s);
void USART2_puts_var(volatile  char *e, int x);
void USART2_IRQHandler(void);



#endif
