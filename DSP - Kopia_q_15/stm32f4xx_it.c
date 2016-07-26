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

bool czy_pierwszy_raz = true;  // Zmienna informuj�ca czy jest to pierwsze przerwanie
int czy_pierwszy_bufor = 1;	// Zmienna informuj�ca czy przerabany ma by� drugi bufor
void DMA2_Stream1_IRQHandler(void) // Funkcja obs�ugo przerwania dla DMA2 Stream1
{
	DMA_ClearITPendingBit(DMA2_Stream1, DMA_IT_TCIF1); // Zeruj flag� przerwania
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == RESET) // Wykonaj poni�sze instrukcje jeli przycisk nie jest wcisni�ty
	{
		GPIO_ToggleBits(GPIOD, GPIO_Pin_13); // Zmie� stan pinu na przeciwny
			if (czy_pierwszy_bufor == 1)	// Wykonaj poni�sze instrukcje jeli obrabiany ma by� pierwszy bufor
				{
					GPIO_ToggleBits(GPIOD, GPIO_Pin_15);	// Zmie� stan pinu na przeciwny
					splot1(); // Wykonaj funkcj� splotu
					for(int i = 0; i< ile_probek; i++)
					{
						buff_wyj1[i]=buff_wyj1[i]>>1; // Przesu� bity w prawo o jeden
					}

					GPIO_ToggleBits(GPIOD, GPIO_Pin_15);	// Zmie� stan pinu na przeciwny

				}
			else	// Wykonaj poni�sze instrukcje jeli obrabiany ma by� drugi bufor
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
	else	// Wykonaj poni�sze instrukcje jeli przycisk jest wcisni�ty
	{

		if (czy_pierwszy_bufor == 1)	// Wykonaj poni�sze instrukcje jeli obrabiany ma by� pierwszy bufor
		{
			for(int i = 0; i< ile_probek; i++)
			{
				buff_wyj1[i]=ADC3ConvertedValue1[i]; // Przepisz pr�bki
			}

		}
		else	// Wykonaj poni�sze instrukcje jeli obrabiany ma by� drugi bufor
		{
			for(int i = 0; i< ile_probek; i++)
			{
				buff_wyj2[i]=ADC3ConvertedValue2[i];
			}
		}

	}


	czy_pierwszy_bufor = ~czy_pierwszy_bufor;	// Zmie� warto� na przeciwn� (w praktyce zmiana wygl�da nast�puj�co 1->-2, -2->1)

	if (czy_pierwszy_raz)	// Wykonaj poni�sze instrukcje jeli jest to pierwsze przerwanie
	{
		TIM_Cmd(TIM6, ENABLE); // Za��cz TIM6 i tym samym rozpocznij prac� DAC
		czy_pierwszy_raz = false; // Zmie� stan zmiennej
	}

}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
