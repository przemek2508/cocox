#include "splot.h"
/* ----------------------------------------------------------------------
 * FIR LPF Example
 * ------------------------------------------------------------------- */

void splot_ini(void)
{
	arm_fir_init_f32(&S, NUM_TAPS, &firCoeffs32[0], &firStateF32[0], (int)ile_probek);
}

void splot(uint32_t wejscie, uint32_t wyjscie)
{
	arm_q15_to_float(wejscie,&FIRBufferIn[0],ile_probek);
	arm_fir_f15(&S,&FIRBufferIn[0],&FIRBufferOut[0],ile_probek);
	arm_float_to_q15(&FIRBufferOut[0], wyjscie,ile_probek);
}
