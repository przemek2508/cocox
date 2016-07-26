#ifndef MAIN_H
#define MAIN_H


#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_adc.h>
#include <stm32f4xx_dma.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>
#include <misc.h>

#define ile_probek 1000

uint16_t ADC3ConvertedValue[ile_probek];

void TIM3_Config_ADC(void);
void ADC3_CH12_DMA_Config(void);



#endif
