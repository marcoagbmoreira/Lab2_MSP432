//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include "Timer32.h"
#include "ADC14.h"
static volatile uint_fast8_t resultsBuffer[0x80];
static volatile uint8_t resPos;
void main(void)
{
	
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
   initTimer32();
	initADC14();

    P2DIR |=(1<<2); // output P2.2
    //P5.5 tertiary module function (ADC)
    P5->SEL0 |= (1<<5); // p5.5 as adc input
    P5->SEL1 |= (1<<5);
    P5->IES |= 0x0A;
    P5DIR &=~(1<<5);
    P2OUT ^= BIT2; // toogle output

    delay_usTimer32(50); // atraso de 50us


    while(1)
    {


	};
}
void ADC14_IRQHandler(void)
{

	clearIRQFlagADC14();
}
/* Timer32 ISR */
void T32_INT1_IRQHandler(void)
{


	startConversion();
	resultsBuffer[resPos++] = readADC14();
	clearIRQFlagTimer32();
}

