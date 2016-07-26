#ifndef MAIN_H
#define MAIN_H

/*
 * Biblioteki:
 * - do obs³ugi dsp
 * - do obs³ugi zmiennych boolowskich
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

#define my_PEROID 250 // Wartoæ do której licz¹ timery
#define my_PRESCALER 3	// Prescaler (dzielnik) dla timerów

#define ile_probek 100	// D³ugoæ tablic wejsciowych i wyjsciowych
#define NUM_TAPS 50	// D³ugoæ tablicy wspó³czynników filtra
#define ROZMIAR_BLOKU 50	// D³ugoæ bloku "przerabianego" na raz
#define ILE_BLOKOW ile_probek/ROZMIAR_BLOKU	// Iloæ bloków



extern uint16_t ADC3ConvertedValue1[ile_probek];
extern uint16_t ADC3ConvertedValue2[ile_probek];
extern uint16_t buff_wyj1[ile_probek];
extern uint16_t buff_wyj2[ile_probek];


extern const int16_t firCoeffs16[NUM_TAPS];


void GPIO_Config(void);


#endif
