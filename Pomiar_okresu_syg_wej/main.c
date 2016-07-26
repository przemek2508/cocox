#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
#include <stm32f4xx_it.h>
#include "misc.h"


TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
TIM_ICInitTypeDef  TIM_ICInitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;


int main(void)
{
	SystemInit();


//-----------------------------TIM3 PWM 4 kana³y------------------------

	//TIM3
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);// zegar TIM3

	  /* GPIOC and GPIOB clock enable */
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE); // zegar GPIO


	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ; // GPIOA: TIM3_CH1 PA6, TIM3_CH2 PA7
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; // GPIOB: TIM3_CH1 PB0, TIM3_CH2 PB1
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);


	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3); // GPIO ->AF_TIM3
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3);
	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_TIM3);


	  TIM_TimeBaseStructure.TIM_Period = 665; // ustawienie czasu bazy
	  TIM_TimeBaseStructure.TIM_Prescaler = 0;
	  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	  /* --------------------PWM1 kana³ 1--------------------------- */
	  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = 0;
	  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

	  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

	  /* --------------------PWM1 kana³ 2--------------------------- */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = 0;

	  TIM_OC2Init(TIM3, &TIM_OCInitStructure);

	  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

	  /* --------------------PWM1 kana³ 3--------------------------- */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = 0;

	  TIM_OC3Init(TIM3, &TIM_OCInitStructure);

	  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

	  /* --------------------PWM1 kana³ 4--------------------------- */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = 0;

	  TIM_OC4Init(TIM3, &TIM_OCInitStructure);

	  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

	  TIM_ARRPreloadConfig(TIM3, ENABLE);

	  /* TIM3 enable counter */
	  TIM_Cmd(TIM3, ENABLE);



	  TIM3->CCR1 = 332;
	  TIM3->CCR2 = 0;
	  TIM3->CCR3 = 0;
	  TIM3->CCR4 = 0;



//------------------------------TIM4 przerwanie i pomiar--------------------------------------
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // zegar TIM4

	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); // zegar GPIO

	  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7; // TIM_Channel_2
	  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP ;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);

	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);

	  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; // Ÿród³o przerwania
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // wybranie priorytetu
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; // wybranie podpriorytetu
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // za³¹czenie przerwañ
	  NVIC_Init(&NVIC_InitStructure);


	  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; //PB7
	  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; // przerwanie na zboczu narastaj¹cym
	  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; // do³¹czenie portu do wejcia kana³u
	  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; //dzielnik zegara wejcia
	  TIM_ICInitStructure.TIM_ICFilter = 0x0;

	  TIM_PWMIConfig(TIM4, &TIM_ICInitStructure);


	  TIM_SelectInputTrigger(TIM4, TIM_TS_TI2FP2);  // wejœcie wyzwalania TIM4 - TI2FP2


	  TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Reset); //Slave reset
	  TIM_SelectMasterSlaveMode(TIM4,TIM_MasterSlaveMode_Enable);

	  TIM_Cmd(TIM4, ENABLE); // za³¹czenie TIM4

	  TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE); // za³¹czenie "pozwolenia" dla przechwycenia przerwañ dla CC2

  while (1)
  {

  }
}






