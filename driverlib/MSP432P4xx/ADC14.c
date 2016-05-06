/*
 * ADC14.c
 *
 *  Created on: 02/05/2016
 *      Author: Marco Moreira
 */

#include <adc14.h>
void startConversion();
void initADC14()
{
		ADC14->CTL0 |= (1<<4);  // enable adc block
		ADC14->CTL0 |= (1<<18); // repeat single channel
		ADC14->CTL0 |= ((1<<19)|(1<<20)); // ADC14 clock MCLK= REF(3Mhz)
		ADC14->CTL0 |= ((1<<31)|(1<<24)); // 3Mhz/32/5 =~ 19khz
		ADC14->CTL1 &=~ ((1<<5)|(1<<4)); // 8-bit resolution
		ADC14->MCTL[0] &=~ ((1<<11)|(1<<10)|(1<<9)|(1<<8)); // VR+ = AVCC , V(R-) = AVSS
		ADC14->IER0 |= (1<<0); // interrompe quando a mem0 tiver alguma valor
		ADC14->CTL0 |= (1<<26); // SAMPCON signal is sourced from the sampling timer.
		ADC14->MCTL[0] |= ADC14_MCTLN_INCH_0; // A0 = p5.5 A22 = temperature sensor


		REFCTL0 |= ((1<<5)|(1<<4)); // reference voltage 2.5V
		REFCTL0 |= (1<<0); // enable reference voltage


		startConversion();
		NVIC->ICER[0] |= (1<<24); // 24 interrupt vector
		NVIC->ISER[0] |= (1<<24);

}
uint8_t readADC14()
{

	uint8_t result = ADC14->MEM[0];
	float normalizedResult = 0;
	normalizedResult = (result * 3.3) / 255;
	return  normalizedResult;
}
void startConversion()
{
	ADC14->CTL0 |= (1<<0) | (1<<1); // start sample and conversion
}
void clearIRQFlagADC14()
{
	ADC14->CLRIFGR0 |= (1<<24);
	NVIC->ICER[1] |= (1<<24); // clear interrupt register posição 24 do vetor de interrupção precisa usar o registrador ICER0
	startConversion();
}
