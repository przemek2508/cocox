#include "main.h" // Dodanie pliku nag��wkowego

uint16_t ADC3ConvertedValue1[ile_probek];	// Tablica wej�ciowa nr. 1
uint16_t ADC3ConvertedValue2[ile_probek];	// Tablica wej�ciowa nr. 2
uint16_t buff_wyj1[ile_probek];				// Tablica wyj�ciowa nr. 1
uint16_t buff_wyj2[ile_probek];				// Tablica wyj�ciowa nr. 2

int main(void)
{
	SystemInit();
	GPIO_Config();	// Konfiguracja diod i przycisku
	GPIO_ToggleBits(GPIOD, GPIO_Pin_14);	// Zmnie� stan pinu na odwrotny
	splot_ini();	// Konfiguracja filtru
	TIM6_Config();	// Konfiguracja timera nr. 6
	DAC1_Config();	// Konfiguracja i inicjalizacja DAC i DMA
	TIM3_Config_ADC();	// Konfiguracja i inicjalizacja timera nr. 3
	ADC3_CH12_DMA_Config();		// Konfiguracja i inicjalizacja ADC i DMA
    while(1)	// P�tla niesko�czona
    {
    }
}

void GPIO_Config()
{
	/* Konfiguracja GPIO do kontroli pracy aplikacji*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	//Za��czenie zegara dla szyny obs�uguj�cej GPIOD

	GPIO_InitTypeDef      GPIO_InitStructure;	//Definicja struktury
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;	//Piny poddawane konfiguracji:
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	// Jako wj�cie
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	// Push/Pull
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // Cz�stotliwo� pracy
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	// Brak rezystor�w podci�gaj�cych
	GPIO_Init (GPIOD, &GPIO_InitStructure);	// Zainicjalizuj powy�sz� konfiguracj�

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	// Pin jako wej�cie
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; // Podci�gni�ty do GND rezystorem
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
