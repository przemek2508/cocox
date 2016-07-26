#ifndef MAIN_H
#define MAIN_H

/*
 * Biblioteki:
 * - do obs�ugi dsp
 * - do obs�ugi zmiennych boolowskich
 * - do stm21f4
 */
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

#define my_PEROID 250 // Warto� do kt�rej licz� timery
#define my_PRESCALER 3	// Prescaler (dzielnik) dla timer�w

#define ile_probek 100	// D�ugo� tablic wejsciowych i wyjsciowych
#define NUM_TAPS 50	// D�ugo� tablicy wsp�czynnik�w filtra
#define ROZMIAR_BLOKU 50	// D�ugo� bloku "przerabianego" na raz
#define ILE_BLOKOW ile_probek/ROZMIAR_BLOKU	// Ilo� blok�w



extern uint16_t ADC3ConvertedValue1[ile_probek];
extern uint16_t ADC3ConvertedValue2[ile_probek];
extern uint16_t buff_wyj1[ile_probek];
extern uint16_t buff_wyj2[ile_probek];


extern const int16_t firCoeffs16[NUM_TAPS];


void GPIO_Config(void);


#endif
