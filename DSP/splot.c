#include "splot.h"

int32_t splot_buff_1(void)
{
	 arm_status status;                           /* Status of the example */
	  arm_cfft_radix4_instance_f32 cfft_instance;  /* CFFT Structure instance */
	  /* CFFT Structure instance pointer */
	  arm_cfft_radix4_instance_f32 *cfft_instance_ptr =
	      (arm_cfft_radix4_instance_f32*) &cfft_instance;
	  /* Initialise the fft input buffers with all zeros */
	  arm_fill_f32(0.0,  buff_wej_dodatkowy_1, ile_probek);
	  arm_fill_f32(0.0,  buff_wej_dodatkowy_2, ile_probek);
	  /* Copy the input values to the fft input buffers */
	  arm_copy_f32(ADC3ConvertedValue,  buff_wej_dodatkowy_1, ile_probek/2);
	  arm_copy_f32(buff_odp_imp_filtr,  buff_wej_dodatkowy_2, ile_probek/2);
	  /* Initialize the CFFT function to compute 64 point fft */
	  status = arm_cfft_radix4_init_f32(cfft_instance_ptr, 64, 0, 1);
	  /* Transform input a[n] from time domain to frequency domain A[k] */
	  arm_cfft_radix4_f32(cfft_instance_ptr, buff_wej_dodatkowy_1);
	  /* Transform input b[n] from time domain to frequency domain B[k] */
	  arm_cfft_radix4_f32(cfft_instance_ptr, buff_wej_dodatkowy_2);
	  /* Complex Multiplication of the two input buffers in frequency domain */
	  arm_cmplx_mult_cmplx_f32(buff_wej_dodatkowy_1, buff_wej_dodatkowy_2, buff_wyj1, ile_probek/2);
	  /* Initialize the CIFFT function to compute 64 point ifft */
	  status = arm_cfft_radix4_init_f32(cfft_instance_ptr, 64, 1, 1);
	  /* Transform the multiplication output from frequency domain to time domain,
	     that gives the convolved output  */
	  arm_cfft_radix4_f32(cfft_instance_ptr, buff_wyj1);

	    status = ARM_MATH_SUCCESS;
  }


int32_t splot_buff_2(void)
{
	arm_status status;                           /* Status of the example */
	arm_cfft_radix4_instance_f32 cfft_instance;  /* CFFT Structure instance */
	/* CFFT Structure instance pointer */
	arm_cfft_radix4_instance_f32 *cfft_instance_ptr =
		      (arm_cfft_radix4_instance_f32*) &cfft_instance;
    /* Initialise the fft input buffers with all zeros */
	arm_fill_f32(0.0,  buff_wej_dodatkowy_1, ile_probek);
	arm_fill_f32(0.0,  buff_wej_dodatkowy_2, ile_probek);
	/* Copy the input values to the fft input buffers */
	arm_copy_f32(ADC3ConvertedValue1,  buff_wej_dodatkowy_1, ile_probek);
	arm_copy_f32(buff_odp_imp_filtr,  buff_wej_dodatkowy_2, ile_probek);
	/* Initialize the CFFT function to compute 64 point fft */
	status = arm_cfft_radix4_init_f32(cfft_instance_ptr, 64, 0, 1);
	/* Transform input a[n] from time domain to frequency domain A[k] */
	arm_cfft_radix4_f32(cfft_instance_ptr, buff_wej_dodatkowy_1);
	/* Transform input b[n] from time domain to frequency domain B[k] */
	arm_cfft_radix4_f32(cfft_instance_ptr, buff_wej_dodatkowy_2);
	/* Complex Multiplication of the two input buffers in frequency domain */
	arm_cmplx_mult_cmplx_f32(buff_wej_dodatkowy_1, buff_wej_dodatkowy_2, buff_wyj1, ile_probek);
	/* Initialize the CIFFT function to compute 64 point ifft */
	status = arm_cfft_radix4_init_f32(cfft_instance_ptr, 64, 1, 1);
	/* Transform the multiplication output from frequency domain to time domain,
		     that gives the convolved output  */
	arm_cfft_radix4_f32(cfft_instance_ptr, buff_wyj1);

	status = ARM_MATH_SUCCESS;
}
