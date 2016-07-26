#include "stm32f4xx.h"
#include "TIM.h"
#include "SPI.h"

int8_t xL, xH;
int16_t x;

int war_neutralna = 500;

int main(void)
{
	SystemInit();
	TIM4_ini();
	SPI_ini();

	SPI_Tx(0x20,0x67);
	SPI_Tx(0x24,0x48);
  while (1){

	    //Rx SPI data
	     xH=SPI_Rx(0x29);
	     xL=SPI_Rx(0x28);
	     x= (xH << 8) + xL;

	     //use data
	     if (x < -war_neutralna)
	     {
	    	TIM4->CCR1 = -x+war_neutralna;
	      	TIM4->CCR3 = 0;
	     }
	     else if (x > war_neutralna)
	     {
	    	TIM4->CCR1 = 0;
	      	TIM4->CCR3 = x-war_neutralna;
	     }
	     else
	     {
	    	 TIM4->CCR1 = 0;
	    	 TIM4->CCR3 = 0;
	     }


  }
}







