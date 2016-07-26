#include <stm32f4xx.h>
#include "USART1.h"






int main(void) {
  int x = 50;
  USART2_ini(9600, Pins_Pack_1);
  USART2_puts_var("x", x);



  while (1){
  }
}

