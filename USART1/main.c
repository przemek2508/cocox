#include <stm32f4xx.h>
#include "USART1.h"






int main(void) {
  int x = 50;
  USART2_ini(9600);
  USART2_puts("Elo\r\n");
  USART2_puts_var("y", x);


  while (1){
  }
}

