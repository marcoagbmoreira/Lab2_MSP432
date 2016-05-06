//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include "Timer32.h"
#include "ADC14.h"
int i = 0;
void main(void)
{
	
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
   initTimer32();

   initADC14();
    P1DIR |= (1<<0); // output P1.0

    //P6.0 tertiary module function (ADC)
    P5->SEL0 |= (1<<5); // p5.5 as adc input
    P5->SEL1 |= (1<<5);
    P5->IES |= 0x0A;
    P5DIR &=~(1<<5);
    while(1)
    {
    delay_msTimer32(500); // em ms
	  P1OUT ^= BIT0; // toogle output
	};
}
void ADC14_IRQHandler(void)
{
	float value = readADC14();
	clearIRQFlagADC14();
}
/* Timer32 ISR */
void T32_INT1_IRQHandler(void)
{

	P1OUT ^= BIT0; // toogle output

	clearIRQFlagTimer32();
}

