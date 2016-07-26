#ifndef MAIN_H
#define MAIN_H


#include "arm_math.h"
#include "math_helper.h"

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


#define ile_probek 64
#define my_PEROID 65000
#define my_PRESCALER 1




float32_t ADC3ConvertedValue[ile_probek];
float32_t ADC3ConvertedValue1[ile_probek];

float32_t buff_wyj1[ile_probek * 2];
float32_t buff_wyj2[ile_probek * 2];





#endif
