#ifndef SERIAL_H
#define SERIAL_H

#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_usart.h>
#include <misc.h>


void Serial_ini(uint32_t baudrate);
void Serial_puts(volatile char *s);
void Serial_puts_var(const char *s, int x);
uint8_t Serial_get(void);
int _write( int file, char *ptr, int len );
void USART2_IRQHandler(void);



#endif
