#include "splot.h"
/* ----------------------------------------------------------------------
 * FIR LPF Example
 * ------------------------------------------------------------------- */

void splot_ini(void)
{
	arm_fir_init_q15(&S, NUM_TAPS, &firCoeffs16[0], &firStateQ16[0], ile_probek); //inicjalizacja wspó³czynników dla filtra
}


void splot1()
{
	for (int i=0; i < ILE_BLOKOW; i++) // Wykonaj splot dla ka¿dego z bloków
	{
		arm_fir_fast_q15(&S,&ADC3ConvertedValue1[0] + (i * ROZMIAR_BLOKU), &buff_wyj1[0] + (i * ROZMIAR_BLOKU), ROZMIAR_BLOKU);
	}
}

void splot2()
{
	for (int i=0; i < ILE_BLOKOW; i++)
	{
		arm_fir_fast_q15(&S,&ADC3ConvertedValue2[0] + (i * ROZMIAR_BLOKU),&buff_wyj2[0] + (i * ROZMIAR_BLOKU), ROZMIAR_BLOKU);
	}
}
