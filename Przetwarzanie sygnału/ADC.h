#ifndef ADC_H
#define ADC_H


#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_adc.h>
#include <stm32f4xx_dma.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>

#define ADC3_DR_ADDRESS     ((uint32_t)0x4001224C)

#define ilosc_probek 20000
extern uint16_t testInput[ilosc_probek];


void TIM3_Config_ADC(void);
void ADC3_CH12_DMA_Config(void);



#endif
