#include "main.h"

bool czy_splot_buff_1 = false;
bool czy_splot_buff_2 = false;
int x = 0;
int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef      GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init (GPIOD, &GPIO_InitStructure);

	GPIO_ToggleBits(GPIOD, GPIO_Pin_14);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init (GPIOD, &GPIO_InitStructure);


	SystemInit();


	DAC1_Config();
	TIM6_Config_DAC();


	ADC3_CH12_DMA_Config();
	TIM3_Config_ADC();




    while(1)
    {
    	if (czy_splot_buff_1)
    	{
    		czy_splot_buff_1 = false;
    		splot_buff_1();
    	}

    	if (czy_splot_buff_2)
    	{
    		czy_splot_buff_2 = false;
    	    splot_buff_2();
    	}



    }
}
