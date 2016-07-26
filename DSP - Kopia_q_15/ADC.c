#include "ADC.h"


void TIM3_Config_ADC(void) //Konfiguracja TIM3
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //Za³¹czenie zegara dla szyny obs³uguj¹cej TIM3

    TIM_TimeBaseInitTypeDef TIM3_TimeBase; //Definicja struktury
    TIM3_TimeBase.TIM_Period        = my_PEROID - 1; 	// Wartoæ do której licz¹ timery
    TIM3_TimeBase.TIM_Prescaler     = my_PRESCALER - 1;	// Prescaler (dzielnik) dla TIM3
    TIM3_TimeBase.TIM_ClockDivision = 0;	// Dzielnik zegara
    TIM3_TimeBase.TIM_CounterMode   = TIM_CounterMode_Up;  // Zliczanie w górê
    TIM_TimeBaseInit(TIM3, &TIM3_TimeBase);	// Zainicjalizuj powy¿sz¹ konfiguracjê
    TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update); // Aktualizacja stanu jako wyjcie

    TIM_Cmd(TIM3, ENABLE);	// Zalaczenie licznika/timera
}

void ADC3_CH12_DMA_Config(void)	//Konfiguracja ADC i DMA
{
	/*
	 * Definicje struktur
	 */
	ADC_InitTypeDef       ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	DMA_InitTypeDef       DMA_InitStructure;
	GPIO_InitTypeDef      GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Za³¹czenie zegarów dla ADC3, DMA2 i GPIOC */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;	// Pin jako funkcja alternatywna
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Konfiguracja dla DMA2 Stream1 channel2 */
	DMA_DeInit(DMA2_Stream1);	// Deinicjalizacja poprzednich struktur dla DMA2 Stream1
	DMA_InitStructure.DMA_Channel 				= DMA_Channel_2;	// Wybór kana³u (narzucony)
	DMA_InitStructure.DMA_PeripheralBaseAddr 	= (uint32_t)&ADC3->DR;	// Adres peryferium
	DMA_InitStructure.DMA_Memory0BaseAddr 		= (uint32_t)&ADC3ConvertedValue1[0]; // Adres tablicy do której zapisywane s¹ wartoci
	DMA_InitStructure.DMA_DIR 					= DMA_DIR_PeripheralToMemory;	// Kierunek przepisywania, peryferium->pamiêæ
	DMA_InitStructure.DMA_BufferSize 			= (int)ile_probek;	// D³ugoæ zapisywanej tablicy
	DMA_InitStructure.DMA_PeripheralInc 		= DMA_PeripheralInc_Disable;	// Wy³¹czenie inkrementacji adresu peryferium
	DMA_InitStructure.DMA_MemoryInc 			= DMA_MemoryInc_Enable;	// W³¹czenie inkrementacji adresu pamiêci
	DMA_InitStructure.DMA_PeripheralDataSize 	= DMA_PeripheralDataSize_HalfWord;	// Rozmiar danych odbieranych z peryferium (16 bit)
	DMA_InitStructure.DMA_MemoryDataSize 		= DMA_MemoryDataSize_HalfWord;	// Rozmiar danych zapisywanych do pamiêci (16 bit)
	DMA_InitStructure.DMA_Mode 					= DMA_Mode_Circular; // Pêtla nieskoñczona dla zapisu
	DMA_InitStructure.DMA_Priority 				= DMA_Priority_High;	// Wysoki priorytet DMA
	DMA_InitStructure.DMA_FIFOMode 				= DMA_FIFOMode_Disable; // Tryb bezporedni
	DMA_InitStructure.DMA_FIFOThreshold 		= DMA_FIFOThreshold_HalfFull; // Próg dla FIFO
	DMA_InitStructure.DMA_MemoryBurst 			= DMA_MemoryBurst_Single;	// Przenoszona jest na raz tylko jedna próbka do pamiêci
	DMA_InitStructure.DMA_PeripheralBurst 		= DMA_PeripheralBurst_Single; // Przenoszona jest na raz tylko jedna próbka z peryferium
	DMA_DoubleBufferModeConfig(DMA2_Stream1,&ADC3ConvertedValue2[0],DMA_Memory_0);	// Tryb double buffer, okreslenie drugiego bufora oraz który zapisywany jest pierwszy
	DMA_DoubleBufferModeCmd(DMA2_Stream1, ENABLE);	// Za³¹czenie trybu double buffer
	DMA_Init(DMA2_Stream1, &DMA_InitStructure);	// Zainicjalizuj powy¿sz¹ konfiguracjê

	DMA_Cmd(DMA2_Stream1, ENABLE);	// Za³¹czenie DMA2 Stream1

	DMA_ITConfig(DMA2_Stream1,DMA_IT_TC, ENABLE);// Przerwanie po 1 i 2 buforze

	/* Konfiguracja przerwania */
	NVIC_InitStructure.NVIC_IRQChannel 						= DMA2_Stream1_IRQn;	// Funkcja obs³ugi przerwania																																				//co przerwie
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0;	// Priorytet																											//piorytet (0 najwiekszy) -3 jest dla resetu; -1, -2 bledy systemowe
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 7;	// Podpriorytet 																																		//podpriorytet
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;	// W³¹czenie obs³ugi przerwania																																				// wlaczenie
	NVIC_Init(&NVIC_InitStructure);	// Zainicjalizuj powy¿sz¹ konfiguracjê

	/* Konfiguracja GPIO jako wejcie dla ADC3 */
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Konfiguracja dla ADC3 Channel12 */
	ADC_DeInit();	// Deinicjalizacja poprzednich struktur dla ADC
	ADC_CommonInitStructure.ADC_Mode 			= ADC_Mode_Independent; // Tryb obs³ugi jednego ADC
	ADC_CommonInitStructure.ADC_Prescaler 		= ADC_Prescaler_Div2;	// Prescaler dla ADC
	ADC_CommonInitStructure.ADC_DMAAccessMode 	= ADC_DMAAccessMode_Disabled; // Wy³¹czenie obs³ugi DMA dla wielu ADC
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles; // OpóŸnienie próbkowania
	ADC_CommonInit(&ADC_CommonInitStructure);	// Zainicjalizuj powy¿sz¹ konfiguracjê

	ADC_InitStructure.ADC_Resolution 			= ADC_Resolution_12b; // Rozdzielczoæ 12 bitowa
	ADC_InitStructure.ADC_ScanConvMode 			= DISABLE; // Wy³¹czenie skanowania
	ADC_InitStructure.ADC_ContinuousConvMode 	= DISABLE; // Wy³¹czenie ci¹g³ego trybu dla wielu ADC
	ADC_InitStructure.ADC_ExternalTrigConvEdge 	= ADC_ExternalTrigConvEdge_Rising; // Wyzwalania próbkowania na zbocze narastaj¹ce
	ADC_InitStructure.ADC_ExternalTrigConv 		= ADC_ExternalTrigConv_T3_TRGO; // Wyzwalanie poprzez wyjcie TIM3
	ADC_InitStructure.ADC_DataAlign 			= ADC_DataAlign_Right;	// Przesuñ bity w prawo
	ADC_InitStructure.ADC_NbrOfConversion 		= 1; // Iloæ kana³ów ADC3
	ADC_Init(ADC3, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 1, ADC_SampleTime_3Cycles); // Ustawianie kana³u ADC

	ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE); // Za³¹czenie zapytania przez DMA po konwersji

	ADC_Cmd(ADC3, ENABLE); // Za³¹czenie ADC3

	ADC_DMACmd(ADC3, ENABLE); // Za³¹czenie ADC3 dla DMA
}
