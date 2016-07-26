#ifndef USART1_H
#define USART1_H

#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_usart.h>
#include <misc.h>


void USART2_ini(uint32_t baudrate);
void USART2_puts(volatile char *s);
void USART2_puts_var(const char *s, int x);
void USART2_IRQHandler(void);



#endif
