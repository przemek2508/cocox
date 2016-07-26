#ifndef DAC_H
#define DAC_H

#include "main.h"


TIM_TimeBaseInitTypeDef TIM6_TimeBase;
DAC_InitTypeDef DAC_InitStructure;
DMA_InitTypeDef DMA_InitStructure;
GPIO_InitTypeDef GPIO_Int;

void TIM6_Config_DAC(void);
void DAC1_Config(void);			// Deklaracja funkcji DAC1_Config
void DAC1_buff_wyj_1(void);
void DAC1_buff_wyj_2(void);




#endif
