#ifndef SPI_H
#define SPI_H

#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_spi.h>

GPIO_InitTypeDef GPIO_InitStructure;
SPI_InitTypeDef SPI_InitStruct;

void SPI_ini(void);
void SPI_Tx(uint8_t adress, uint8_t data);
uint8_t SPI_Rx(uint8_t adress);



#endif
