#include "DAC.h"


void TIM6_Config_DAC(void)
{
    TIM_TimeBaseInitTypeDef TIM6_TimeBase;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); // Zegar

    TIM6_TimeBase.TIM_Period        = 649;	// freq TIM6 = 72MHz / (prescaler+1) / (649+1) = sampling frequency 48kHz
    TIM6_TimeBase.TIM_Prescaler     = 0;
    TIM6_TimeBase.TIM_ClockDivision = 0;
    TIM6_TimeBase.TIM_CounterMode   = TIM_CounterMode_Up;  // Zliczanie w gore
    TIM_TimeBaseInit(TIM6, &TIM6_TimeBase);
    TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);

    TIM_Cmd(TIM6, ENABLE);	// Zalaczenie licznika
}

void DAC1_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	DAC_InitTypeDef DAC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	GPIO_InitTypeDef GPIO_Int;


	GPIO_Int.GPIO_Pin  = GPIO_Pin_4;
	GPIO_Int.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Int.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_Int);

	DAC_InitStructure.DAC_Trigger        = DAC_Trigger_T6_TRGO;  // TIM6 jako wyzwalacz DAC
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;	// Wylaczenie generacji flai
	DAC_InitStructure.DAC_OutputBuffer   = DAC_OutputBuffer_Enable;	// Bufor zalaczony
 	DAC_Init(DAC_Channel_1, &DAC_InitStructure);



 	DMA_DeInit(DMA1_Stream5);	// usuñ poprzedni¹ konfiguracjê DMA1_Stream5
 	DMA_InitStructure.DMA_Channel            = DMA_Channel_7;  // Najnizszy podpriorytet DMA
 	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&DAC->DHR12R1;		// lub 0x40007408; // DMA zapisuje wartosc do tego rejestru / adresu
 	DMA_InitStructure.DMA_Memory0BaseAddr    = (uint32_t)&testOutput[0];	// DMA pobiera dane z tego bufora
 	DMA_InitStructure.DMA_DIR                = DMA_DIR_MemoryToPeripheral;	// Transmisja Pamiec -> Peryferium
 	DMA_InitStructure.DMA_BufferSize         = ilosc_probek;			//SIZE_TAB;	// Rozmiar bufora
 	DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable; // Wylaczenie inkrementacji adresu peryferium
 	DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;	// Wlaczenie inkrementacji adresu pamieci
 	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	// 16-bit dana z peryferium
 	DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;		// 16-bit dana do transmisjii po stronie pamiêci
 	DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;	// Petla while dla bufora
 	DMA_InitStructure.DMA_Priority           = DMA_Priority_High;	// Wysoki priorytet
 	DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Disable;   // Wylaczenie FIFO
 	DMA_Init(DMA1_Stream5, &DMA_InitStructure);

 	DMA_Cmd(DMA1_Stream5, ENABLE);
 	DAC_Cmd(DAC_Channel_1, ENABLE);
 	DAC_DMACmd(DAC_Channel_1, ENABLE);
}


