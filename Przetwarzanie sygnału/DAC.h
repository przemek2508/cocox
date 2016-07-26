#ifndef DAC_H
#define DAC_H

#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_dac.h>
#include <stm32f4xx_dma.h>
#include <stm32f4xx_tim.h>


#define ilosc_probek 20000
extern uint16_t testOutput[ilosc_probek];


void TIM6_Config_DAC(void);
void DAC1_Config(void);			// Deklaracja funkcji DAC1_Config






#endif
