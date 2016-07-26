#ifndef MAIN_H
#define MAIN_H


#include "arm_math.h"


#include <stdbool.h>

#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_adc.h>
#include <stm32f4xx_dac.h>
#include <stm32f4xx_dma.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>
#include <stm32f4xx_it.h>
#include <misc.h>

#define ile_probek 300
#define my_PEROID 20000
#define my_PRESCALER 1
#define NUM_TAPS              29



uint32_t ADC3ConvertedValue[ile_probek];
uint32_t ADC3ConvertedValue1[ile_probek];

uint32_t buff_wyj1[ile_probek];
uint32_t buff_wyj2[ile_probek];





#endif
