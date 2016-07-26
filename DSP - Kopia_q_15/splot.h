#ifndef SPLOT_H
#define SPLOT_H

#include "main.h"

void splot_ini(void);
void splot1(void);
void splot2(void);


arm_fir_instance_q15 S;  //wskazuje na wyst¹pienie struktury filtru FIR

static int16_t firStateQ16[ROZMIAR_BLOKU + NUM_TAPS - 1];

/*
 FIR GAUSSIAN
 FS = 168674 Hz
 */

/*
 * Wspó³czynniki filtra
 */
const int16_t firCoeffs16[NUM_TAPS] = {
		//Odciecie przy 1kHz NUM_TAPS = 10
		 640,   2192,   5552,  10320,  14048,  14048,  10320,   5552,   2192,
		      640


		// Odciecie przy 100 Hz    NUM_TAPS = 50
 /*

	     112,    144,    192,    240,    304,    368,    448,    544,    656,
	      768,    896,   1040,   1200,   1360,   1520,   1680,   1856,   2016,
	     2160,   2304,   2432,   2528,   2608,   2672,   2688,   2688,   2672,
	     2608,   2528,   2432,   2304,   2160,   2016,   1856,   1680,   1520,
	     1360,   1200,   1040,    896,    768,    656,    544,    448,    368,
	      304,    240,    192,    144,    112
 */


	};


#endif
