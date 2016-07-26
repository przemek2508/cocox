#ifndef DAC_H
#define DAC_H

#include "main.h"

#define   DAC_DHR12R1_ADDR  0x40007408                           // DMA writes into this reg on every request


TIM_TimeBaseInitTypeDef TIM_TimeBase;
DAC_InitTypeDef DAC_InitStructure;
DMA_InitTypeDef DMA_InitStructure;
GPIO_InitTypeDef GPIO_Int;



void TIM6_Config(void);
void DAC1_Config(void);






#endif
