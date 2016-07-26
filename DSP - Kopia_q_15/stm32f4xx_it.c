/**
  ******************************************************************************
  * @file    ADC_Interleaved_DMAmode2/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"

/** @addtogroup STM32F4_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup ADC_Interleaved_DMAmode2
  * @{
  */ 
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
/*
void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}
*/


/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
} */

/**
  * @}
  */ 

/**
  * @}
  */ 

bool czy_pierwszy_raz = true;  // Zmienna informuj¹ca czy jest to pierwsze przerwanie
int czy_pierwszy_bufor = 1;	// Zmienna informuj¹ca czy przerabany ma byæ drugi bufor
void DMA2_Stream1_IRQHandler(void) // Funkcja obs³ugo przerwania dla DMA2 Stream1
{
	DMA_ClearITPendingBit(DMA2_Stream1, DMA_IT_TCIF1); // Zeruj flagê przerwania
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == RESET) // Wykonaj poni¿sze instrukcje jeli przycisk nie jest wcisniêty
	{
		GPIO_ToggleBits(GPIOD, GPIO_Pin_13); // Zmieñ stan pinu na przeciwny
			if (czy_pierwszy_bufor == 1)	// Wykonaj poni¿sze instrukcje jeli obrabiany ma byæ pierwszy bufor
				{
					GPIO_ToggleBits(GPIOD, GPIO_Pin_15);	// Zmieñ stan pinu na przeciwny
					splot1(); // Wykonaj funkcjê splotu
					for(int i = 0; i< ile_probek; i++)
					{
						buff_wyj1[i]=buff_wyj1[i]>>1; // Przesuñ bity w prawo o jeden
					}

					GPIO_ToggleBits(GPIOD, GPIO_Pin_15);	// Zmieñ stan pinu na przeciwny

				}
			else	// Wykonaj poni¿sze instrukcje jeli obrabiany ma byæ drugi bufor
				{
					GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
					splot2();
					for(int i = 0; i< ile_probek; i++)
					{
						buff_wyj2[i]=buff_wyj2[i]>>1;
					}
					GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
				}


	}
	else	// Wykonaj poni¿sze instrukcje jeli przycisk jest wcisniêty
	{

		if (czy_pierwszy_bufor == 1)	// Wykonaj poni¿sze instrukcje jeli obrabiany ma byæ pierwszy bufor
		{
			for(int i = 0; i< ile_probek; i++)
			{
				buff_wyj1[i]=ADC3ConvertedValue1[i]; // Przepisz próbki
			}

		}
		else	// Wykonaj poni¿sze instrukcje jeli obrabiany ma byæ drugi bufor
		{
			for(int i = 0; i< ile_probek; i++)
			{
				buff_wyj2[i]=ADC3ConvertedValue2[i];
			}
		}

	}


	czy_pierwszy_bufor = ~czy_pierwszy_bufor;	// Zmieñ wartoæ na przeciwn¹ (w praktyce zmiana wygl¹da nastêpuj¹co 1->-2, -2->1)

	if (czy_pierwszy_raz)	// Wykonaj poni¿sze instrukcje jeli jest to pierwsze przerwanie
	{
		TIM_Cmd(TIM6, ENABLE); // Za³¹cz TIM6 i tym samym rozpocznij pracê DAC
		czy_pierwszy_raz = false; // Zmieñ stan zmiennej
	}

}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
