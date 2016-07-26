#include <GPIO.h>
#include <SPI.h>




int8_t tL, tH, cL, cH;
int16_t t, c;


int main(void)
{
	SystemInit();

	GPIO_ini();
	SPI_ini();
	//Serial_ini(9600);

    //SPI_Tx(0x20,0x67);
    //SPI_Tx(0x24,0x48);

	SPI_Tx(0x12,0x00);

	for(int i=0;i<1000000;i++);

    while(1)
    {



    	tL = SPI_Rx(0x03);
    	tH = SPI_Rx(0x02);
    	t= (tH << 8) + tL;

    	t= (2500 -((t-472)*10000/535))/10;
    	cL = SPI_Rx(0x01);
    	cH = SPI_Rx(0x00);
    	c	= (cH << 8) + cL;


    	for(int i=0;i<1000000;i++);


    	/*
    	  //Rx SPI data
    	  xH=SPI_Rx(0x29);
    	  xL=SPI_Rx(0x28);

    	  yH=SPI_Rx(0x2B);
    	  yL=SPI_Rx(0x2A);

    	  x= (xH << 8) + xL;
    	  y= (yH << 8) + yL;


   */


    }
}

