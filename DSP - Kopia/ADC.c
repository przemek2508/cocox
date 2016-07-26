#include "ADC.h"


void TIM3_Config_ADC(void)
{
    TIM_TimeBaseInitTypeDef TIM3_TimeBase;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // Zegar

    TIM3_TimeBase.TIM_Period        = my_PEROID;
    TIM3_TimeBase.TIM_Prescaler     = my_PRESCALER;
    TIM3_TimeBase.TIM_ClockDivision = 0;
    TIM3_TimeBase.TIM_CounterMode   = TIM_CounterMode_Up;  // Zliczanie w gore
    TIM_TimeBaseInit(TIM3, &TIM3_TimeBase);
    TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);

    TIM_Cmd(TIM3, ENABLE);	// Zalaczenie licznika
}

void ADC3_CH12_DMA_Config(void)
{


  ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  DMA_InitTypeDef       DMA_InitStructure;
  GPIO_InitTypeDef      GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable ADC3, DMA2 and GPIO clocks ****************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

  /* DMA2 Stream1 channel2 configuration **************************************/

  DMA_DeInit(DMA2_Stream1);
  DMA_InitStructure.DMA_Channel 				= DMA_Channel_2;
  DMA_InitStructure.DMA_PeripheralBaseAddr 		= (uint32_t)&ADC3->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr 		= (uint32_t)&ADC3ConvertedValue[0];
  DMA_InitStructure.DMA_DIR 					= DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize 				= (int)ile_probek;
  DMA_InitStructure.DMA_PeripheralInc 			= DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc 				= DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize 		= DMA_PeripheralDataSize_Word;
  DMA_InitStructure.DMA_MemoryDataSize 			= DMA_MemoryDataSize_Word;
  DMA_InitStructure.DMA_Mode 					= DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority 				= DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode 				= DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold 			= DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst 			= DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst 		= DMA_PeripheralBurst_Single;
  DMA_DoubleBufferModeConfig(DMA2_Stream1,&ADC3ConvertedValue1[0],DMA_Memory_0);
  DMA_DoubleBufferModeCmd(DMA2_Stream1, ENABLE);
  DMA_Init(DMA2_Stream1, &DMA_InitStructure);

  DMA_Cmd(DMA2_Stream1, ENABLE);

 // DMA_ITConfig(DMA2_Stream1, DMA_IT_HT | DMA_IT_TC, ENABLE);// przerwanie po 1 i 2 buforze


  NVIC_InitStructure.NVIC_IRQChannel 						= DMA2_Stream1_IRQn; 																																				//co przerwie
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 		= 0; 																															//piorytet (0 najwiekszy) -3 jest dla resetu; -1, -2 bledy systemowe
  NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 7; 																																		//podpriorytet
  NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE; 																																				// wlaczenie
  NVIC_Init(&NVIC_InitStructure);

  /* Configure ADC3 Channel12 pin as analog input ******************************/
  GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);


  ADC_DeInit();
  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode 				= ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler 		= ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode 	= ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay 	= ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);

  /* ADC3 Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution 				= ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode 			= DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode 		= DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge 	= ADC_ExternalTrigConvEdge_Rising;
  ADC_InitStructure.ADC_ExternalTrigConv 		= ADC_ExternalTrigConv_T3_TRGO;
  ADC_InitStructure.ADC_DataAlign 				= ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion 		= 1;
  ADC_Init(ADC3, &ADC_InitStructure);

  /* ADC3 regular channel12 configuration *************************************/
  ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 1, ADC_SampleTime_3Cycles);

 /* Enable DMA request after last transfer (Single-ADC mode) */
  ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);



  /* Enable ADC3 */
  ADC_Cmd(ADC3, ENABLE);

  /* Enable ADC3 DMA */
  ADC_DMACmd(ADC3, ENABLE);
}
