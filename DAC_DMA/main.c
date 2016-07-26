#include "main.h"
#include "DAC.h"


uint32_t buff_wyj1[ile_probek]= { 4095, 4095, 4095, 4095, 4095, 50, 0, 300, 200, 300 };
uint32_t buff_wyj2[ile_probek]= { 4095, 4095, 4095, 4095, 4095, 0, 0, 0, 0, 0 };

int main(void)
{

	SystemInit();
	TIM6_Config();
	DAC1_Config();

    while(1)
    {
    }
}
