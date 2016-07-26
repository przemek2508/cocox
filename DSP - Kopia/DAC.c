#include "DAC.h"


void TIM6_Config_DAC(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); // Zegar

    TIM6_TimeBase.TIM_Period        = my_PEROID;						//(uint16_t)PERIOD;		// Obliczona wartosc do ktorej zlicza licznik
    TIM6_TimeBase.TIM_Prescaler     = my_PRESCALER;
    TIM6_TimeBase.TIM_ClockDivision = 0;
    TIM6_TimeBase.TIM_CounterMode   = TIM_CounterMode_Up;  // Zliczanie w gore
    TIM_TimeBaseInit(TIM6, &TIM6_TimeBase);
    TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);

    //TIM_Cmd(TIM6, ENABLE);	// Zalaczenie licznika w stm32f4xx_it.c

}

void DAC1_Config(void)
{

	DAC_DeInit();
	DMA_DeInit(DMA1_Stream6);	// usuñ poprzedni¹ konfiguracjê DMA1_Stream5

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);


	GPIO_Int.GPIO_Pin  = GPIO_Pin_5;
	GPIO_Int.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Int.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_Int);


	DAC_InitStructure.DAC_Trigger        = DAC_Trigger_T6_TRGO;  // TIM6 jako wyzwalacz DAC
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;	// Wylaczenie generacji flai
	DAC_InitStructure.DAC_OutputBuffer   = DAC_OutputBuffer_Enable;	// Bufor zalaczony
 	DAC_Init(DAC_Channel_2, &DAC_InitStructure);




 	DMA_InitStructure.DMA_Channel            = DMA_Channel_7;  // Najnizszy podpriorytet DMA
 	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&DAC->DHR12R2;		// lub 0x40007408; // DMA zapisuje wartosc do tego rejestru / adresu
 	DMA_InitStructure.DMA_Memory0BaseAddr    = (uint32_t)&ADC3ConvertedValue[0];	// DMA pobiera dane z tego bufora
 	DMA_InitStructure.DMA_DIR                = DMA_DIR_MemoryToPeripheral;	// Transmisja Pamiec -> Peryferium
 	DMA_InitStructure.DMA_BufferSize         = ile_probek;			//SIZE_TAB;	// Rozmiar bufora
 	DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable; // Wylaczenie inkrementacji adresu peryferium
 	DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;	// Wlaczenie inkrementacji adresu pamieci
 	DMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_Word;
 	DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Word;
 	DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
 	DMA_InitStructure.DMA_Priority           = DMA_Priority_High;	// Wysoki priorytet
 	DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Disable;   // Wylaczenie FIFO
 	DMA_Init(DMA1_Stream6, &DMA_InitStructure);
 	//DMA_Cmd(DMA1_Stream6, ENABLE);
 	//DAC_Cmd(DAC_Channel_2, ENABLE);
 	//DAC_DMACmd(DAC_Channel_2, ENABLE);



 	/* podwójny buffer */
 	DMA_DoubleBufferModeConfig(DMA1_Stream6,(int32_t)&ADC3ConvertedValue1[0],DMA_Memory_0);
 	DMA_DoubleBufferModeCmd(DMA1_Stream6, ENABLE);
 	DMA_Cmd(DMA1_Stream6, ENABLE);
 	DAC_Cmd(DAC_Channel_2, ENABLE);
 	DAC_DMACmd(DAC_Channel_2, ENABLE);

}

