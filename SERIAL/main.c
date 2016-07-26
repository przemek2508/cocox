//#include <stm32f4xx.h>
#include "serial.h"




int main(void) {

  Serial_ini(921600);
  int i = 0;




  while (1){

  printf(" Odczytana wartosc to %d V!\r\n", i);
  i++;

}
}

