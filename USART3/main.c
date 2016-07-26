#include <stm32f4xx.h>
#include "USART3.h"






int main(void) {
  int x = 50;
  USART3_ini(9600, Pins_Pack_1);
  USART3_puts(x);



  while (1){
  }
}

