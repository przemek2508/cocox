#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_i2c.h"
#include "I2C.h"
#include "delay.h"

// Function declarations
// typedef __w64 unsigned int size_t
int strlen(const char *);
char *strrev(char *);
char *itoa(int, char *, int);

int strlen(const char *str) {
	const char *s;

	s = str;
	while (*s)
		s++;
	return s - str;
}

char *strrev(char *str) {
	char *p1, *p2;

	if (!str || !*str)
		return str;

	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}

	return str;
}

char *itoa(int n, char *s, int b) {
	static char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	int i=0, sign;

	if ((sign = n) < 0)
		n = -n;

	do {
		s[i++] = digits[n % b];
	} while ((n /= b) > 0);

	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';

	return strrev(s);
}


int main()
{
  LCDI2C_init(0x27,20,4);
  LCDI2C_clear();
  LCDI2C_cursor_off();
  LCDI2C_clear();

  uint32_t a = 100000000;
  char str[20];
  while(1)
  {
	  LCDI2C_clear();
	  sprintf(str, "Siema %d...", a);
	  LCDI2C_setCursor(0,0);
	  LCDI2C_write_String(str);
	  a++;
	  Delay(100);
  }



}
