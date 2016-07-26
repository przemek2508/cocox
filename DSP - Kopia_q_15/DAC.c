#include "DAC.h"

void TIM6_Config(void)
{

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

  TIM_TimeBaseStructInit(&TIM_TimeBase);
  TIM_TimeBase.TIM_Period        = my_PEROID - 1;
  TIM_TimeBase.TIM_Prescaler     = my_PRESCALER - 1;
  TIM_TimeBase.TIM_ClockDivision = 0;
  TIM_TimeBase.TIM_CounterMode   = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM6, &TIM_TimeBase);
  TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);

  //TIM_Cmd(TIM6, ENABLE); // TIM6 za³¹czany po wykonaniu splotu na pierwszym buforze (plik stm32f4xx_it.c)
}

void DAC1_Config(void)
{

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

  /* Konfiguracja GPIO jako funkcja alternatywna dla DAC */
  GPIO_Int.GPIO_Pin  = GPIO_Pin_5;
  GPIO_Int.GPIO_Mode = GPIO_Mode_AN;
  GPIO_Int.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_Int);

  /* Konfiguracja DAC */
  DAC_InitStructure.DAC_Trigger        = DAC_Trigger_T6_TRGO; // DAC wyzwalane poprzez wyjcie TIM6
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;	// Brak generacji fali trójk¹tnej lub szumu
  DAC_InitStructure.DAC_OutputBuffer   = DAC_OutputBuffer_Enable;	// W³¹czenie bufora wyjscioweho
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);

  /* Konfiguracja dla DMA1 Stream5 channel7 */
  DMA_DeInit(DMA1_Stream5);
  DMA_InitStructure.DMA_Channel            = DMA_Channel_7;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)DAC_DHR12R1_ADDR;
  DMA_InitStructure.DMA_Memory0BaseAddr    = (uint32_t)&buff_wyj1[0];
  DMA_InitStructure.DMA_DIR                = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize         = ile_probek;
  DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold      = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst        = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream5, &DMA_InitStructure);

  DMA_DoubleBufferModeConfig(DMA1_Stream5,(int32_t)&buff_wyj2[0],DMA_Memory_0);
  DMA_DoubleBufferModeCmd(DMA1_Stream5, ENABLE);

  DMA_Cmd(DMA1_Stream5, ENABLE);

  DAC_Cmd(DAC_Channel_1, ENABLE);

  DAC_DMACmd(DAC_Channel_1, ENABLE);
}
