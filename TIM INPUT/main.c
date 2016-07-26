#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "misc.h"
#include "stm32f4xx_it.h"

//--------------- Definicje struktur ------------
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
TIM_ICInitTypeDef  TIM_ICInitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
//-------Funkcje------------
void TIM5_Init_Output(void);
void TIM4_Init_Input(void);

int main(void)
{
	TIM5_Init_Output();
	TIM4_Init_Input();

  while (1){};
}

void TIM5_Init_Output(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//TIM5 w≥aczenie zegara
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//GPIOA w≥aczenie zegara

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5); // Pod≥πczenie pinu 0 do TIM5 w funkcji alternatywnej
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5); //
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM5); //
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM5); //

	//konfiguracja czasu "bazy"
	/*
	 *  CzestotliwoÊ TIM5 = 16 MHz
	 *  czÍstotliwoÊ PWM = CzÍst TIM5/Prescaler/(Period+1)
	*/
	TIM_TimeBaseStructure.TIM_Period = 999;
	TIM_TimeBaseStructure.TIM_Prescaler = 50;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

	/* -------------PWM1 konfiguracja: kanal 1 ---------------------*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM5, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

	/* -------------PWM1 konfiguracja: kanal 2--------------------- */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC2Init(TIM5, &TIM_OCInitStructure);

	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);

	/*------------ PWM1 konfiguracja: kanal 3 ----------------------*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC3Init(TIM5, &TIM_OCInitStructure);

	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);


	/* ---------------PWM1 konfiguracja: kanal 4 -----------------*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC4Init(TIM5, &TIM_OCInitStructure);

	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM5, ENABLE);

	/* TIM5- wlaczenie */
	TIM_Cmd(TIM5, ENABLE);

	TIM5->CCR1 = 999; // Wype≥nienie 100%
	TIM5->CCR2 = 499; // Wype≥nienie 50%
	TIM5->CCR3 = 299; // Wype≥nienie 30%
	TIM5->CCR4 = 0;   // Wype≥nienie 0%
}

void TIM4_Init_Input(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7; // TIM4 Channel_2 (PB7)
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4); // Pod≥πczenie pinu 7 do TIM4 w funkcji alternatywnej

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; // Przerwanie dla TIM4
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; // TIM4 Channel_2 (PB7)
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; // Zbocze narastajπce
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; // Wejcia
						//TIM 1, 2, 3, 4 po≥πczone odpowiednio do CH_1, CH_2, CH_3, CH_4
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; //Bez preskalera
	TIM_ICInitStructure.TIM_ICFilter = 0x0; //Bez filtra

	TIM_PWMIConfig(TIM4, &TIM_ICInitStructure);
	TIM_SelectInputTrigger(TIM4, TIM_TS_TI2FP2); // èrÛd≥o wyzwalania
												// filtrowane wejcie 2
	TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Reset); // Tryb slave
  	  	  	  	  	  	  	  	  	  	  	  	  	// zbocze narastajπce
													//reinicjalizuje licznik i rejestry
	TIM_SelectMasterSlaveMode(TIM4,TIM_MasterSlaveMode_Enable);
	TIM_Cmd(TIM4, ENABLE); // Za≥πczenie TIM4
	TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE); // Za≥πczenie øπdania przerwania przez CCR2
}

