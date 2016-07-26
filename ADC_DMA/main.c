#include "main.h"
#include "ADC.h"


int main(void)
{

	ADC3_CH12_DMA_Config();
	TIM3_Config_ADC();
    while(1)
    {
    }
}

