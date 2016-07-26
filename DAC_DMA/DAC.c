#include "DAC.h"

void TIM6_Config(void)
{

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

  TIM_TimeBaseStructInit(&TIM_TimeBase);
  TIM_TimeBase.TIM_Period        = 20000;
  TIM_TimeBase.TIM_Prescaler     = 0;
  TIM_TimeBase.TIM_ClockDivision = 0;
  TIM_TimeBase.TIM_CounterMode   = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM6, &TIM_TimeBase);
  TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);

  TIM_Cmd(TIM6, ENABLE);
}

void DAC1_Config(void)
{

	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	  GPIO_Int.GPIO_Pin  = GPIO_Pin_5;
	  GPIO_Int.GPIO_Mode = GPIO_Mode_AN;
	  GPIO_Int.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIOA, &GPIO_Int);



	  DAC_InitStructure.DAC_Trigger        = DAC_Trigger_T6_TRGO;
	  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	  DAC_InitStructure.DAC_OutputBuffer   = DAC_OutputBuffer_Enable;
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);

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

  //DMA_Cmd(DMA1_Stream5, ENABLE);
  //DAC_Cmd(DAC_Channel_1, ENABLE);
  //DAC_DMACmd(DAC_Channel_1, ENABLE);

  DMA_DoubleBufferModeConfig(DMA1_Stream5,(int32_t)&buff_wyj2[0],DMA_Memory_0);
  DMA_DoubleBufferModeCmd(DMA1_Stream5, ENABLE);
  DMA_Cmd(DMA1_Stream5, ENABLE);
  DAC_Cmd(DAC_Channel_1, ENABLE);
  DAC_DMACmd(DAC_Channel_1, ENABLE);
}
