#include <GPIO.h>
#include <TIM4.h>
#include <SPI.h>




int8_t xL, xH, yL, yH;
int16_t x, y;


int main(void)
{
	SystemInit();

	GPIO_ini();
	TIM4_ini();
	SPI_ini();
	//Serial_ini(9600);

    SPI_Tx(0x20,0x67);
    SPI_Tx(0x24,0x48);

    while(1)
    {
    	  //Rx SPI data
    	  xH=SPI_Rx(0x29);
    	  xL=SPI_Rx(0x28);

    	  yH=SPI_Rx(0x2B);
    	  yL=SPI_Rx(0x2A);

    	  x= (xH << 8) + xL;
    	  y= (yH << 8) + yL;


    	  //use data
    	  if (x < 0)
    		  {
    		  	TIM4->CCR1 = -x;
    		  	TIM4->CCR3 = 0;
    		  }
    	  else
    		  {
    		  	TIM4->CCR1 = 0;
    		  	TIM4->CCR3 = x;
    		  }


    	  /*
    	  if (y < 0)
    		  {
    		  	TIM4->CCR4 = -y;
    		  	TIM4->CCR2 = 0;
    		  }
    	  else
    		  {
    		  	TIM4->CCR4 = 0;
    		  	TIM4->CCR2 = y;
    		  }
    		  */


    }
}

