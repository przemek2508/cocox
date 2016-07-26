#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
#include <stm32f4xx_it.h>
#include "misc.h"

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
TIM_ICInitTypeDef TIM_ICInitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;





int main(void)
{
	SystemInit();

//---------------------------TIM4 konfiguracja PWM------------------

	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//TIM4 w³aczenie zegara
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//GPIOD w³aczenie zegara

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	  GPIO_Init(GPIOD, &GPIO_InitStructure);


	  GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
	  GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);



	  //konfiguracja czasu "bazy"
	  TIM_TimeBaseStructure.TIM_Period = 999;
	  TIM_TimeBaseStructure.TIM_Prescaler = 4200;
	  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);


	  /* -------------PWM1 konfiguracja: kanal 1 ---------------------*/
	  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = 0;
	  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	  TIM_OC1Init(TIM4, &TIM_OCInitStructure);

	  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	  /* -------------PWM1 konfiguracja: kanal 2--------------------- */
	  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = 0;
	  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	  TIM_OC2Init(TIM4, &TIM_OCInitStructure);

	  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	  /*------------ PWM1 konfiguracja: kanal 3 ----------------------*/
	  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = 0;
	  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	  TIM_OC3Init(TIM4, &TIM_OCInitStructure);

	  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);


	  /* ---------------PWM1 konfiguracja: kanal 4 -----------------*/
	  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = 0;
	  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	  TIM_OC4Init(TIM4, &TIM_OCInitStructure);

	  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);



	  TIM_ARRPreloadConfig(TIM4, ENABLE);


	  /* TIM4 - wlaczenie */
	  TIM_Cmd(TIM4, ENABLE);



	  TIM4->CCR1 = 999;
	  TIM4->CCR2 = 499;
	  TIM4->CCR3 = 749;
	  TIM4->CCR4 = 100;





//--------------------------TIM3 - odczyt-----------------------
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //Zegar TIM3
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //Zegar GPIOA

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7; //PA6 jako TIM_Channel_1
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3); // PA6 -> AF_TIM3

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; // obs³uga przerwania
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	  TIM_ICInitStructure.TIM_ICFilter = 0x0;

	  TIM_PWMIConfig(TIM3, &TIM_ICInitStructure);

	  /* Select the TIM4 Input Trigger: TI2FP2 */
	  TIM_SelectInputTrigger(TIM3, TIM_TS_TI2FP2);

	  /* Select the slave Mode: Reset Mode */
	  TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
	  TIM_SelectMasterSlaveMode(TIM3,TIM_MasterSlaveMode_Enable);

	  /* TIM enable counter */
	  TIM_Cmd(TIM3, ENABLE);

	  /* Enable the CC2 Interrupt Request */
	  TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);

  while (1)
  {

  }
}






