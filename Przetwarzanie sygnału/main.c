#include <stm32f4xx.h>
#include "arm_math.h"
#include "math_helper.h"
#include "DAC.h"
#include "ADC.h"

uint16_t testInput[ilosc_probek];
float32_t refOutput[ilosc_probek];
uint16_t testOutput[ilosc_probek];

/*
#define ilosc_probek 20000
#define prog 150.05f
#define BLOCK_SIZE 32
#define NUM_TAPS 29




static float32_t firState[BLOCK_SIZE + NUM_TAPS -1];

const float32_t firCoeffs[NUM_TAPS] = {
		//tu wpisaæ z Matlaba - fir1(NUM_TAPS, skalar <0;1> lub wektor 2 el., typ filtru, okno)
};


uint32_t blockSize = BLOCK_SIZE;
uint32_t numBlocks = ilosc_probek/BLOCK_SIZE;

float32_t snr; 										// stosunek sygna³/szum

*/
int main()
{
	SystemInit();

	ADC3_CH12_DMA_Config();
	TIM3_Config_ADC();

	DAC1_Config();
	TIM6_Config_DAC();




	/*
	uint32_t i;										// iterator
	arm_fir_instance_f32 S;
	arm_status status;								// przechowuje status operacji mat.
	uint16_t  *input, *output;

	input = &testInput[0];
	output = &testOutput[0];

	arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&firCoeffs[0], &firState[0], blockSize);

	for(i=0; i < numBlocks; i++)
	    {
		  // funkcja przetwarzaj¹ca dane wejciowe
	      arm_fir_f32(&S, input + (i * blockSize), output + (i * blockSize), blockSize);
	    }


	snr = arm_snr_f32(&refOutput[0], &testOutput[0], ilosc_probek);

	  if (snr < prog)
	    {
	      status = ARM_MATH_TEST_FAILURE;
	    }
	  else
	    {
	      status = ARM_MATH_SUCCESS;
	    }

	  if( status != ARM_MATH_SUCCESS)
	      {
	        while(1);
	      }
	      */
}
