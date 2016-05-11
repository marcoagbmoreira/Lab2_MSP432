/*
 * Timer32.c
 *
 *  Created on: 01/05/2016
 *      Author: Marco Moreira
 */

#include <timer32.h>
#define SysClock  3000000 // da pra setar no system_msp432p401r.c
#define Prescaler  16
// Inicia o timer no modo periodico
void initTimer32()
{

	//TIMER32_1->CONTROL |= 0x66;
	TIMER32_1->CONTROL |= (1<<7); // enable timer
	TIMER32_1->CONTROL |= (1<<5); // interrupt
	TIMER32_1->CONTROL |= (1<<6); // periodic mode
	TIMER32_1->CONTROL |= (1<<2);   // prescale,clock is divided by 16 = 01b
	TIMER32_1->CONTROL |= (1<<1);  // size 32bit counter = 1b
	TIMER32_1->CONTROL &= ~(1<<0); //0b = wrapping mode
	setIRQTimer32();

}
// seta o valor de atraso em ms
void delay_msTimer32(uint32_t delay)
{
	uint32_t newClock = (SysClock/Prescaler);
	TIMER32_1->LOAD = newClock*0.001*delay;
	startTimer32();

}
void delay_usTimer32(uint32_t delay)
{
	uint32_t newClock = (SysClock/Prescaler);
		TIMER32_1->LOAD = newClock*0.000001*delay;
		startTimer32();
}
void startTimer32()
{
	TIMER32_1->CONTROL |=(1<<7);
}
uint32_t getValueTimer32()
{
	uint32_t value=TIMER32_1->VALUE;;
	return value;
}
void setIRQTimer32(){
	TIMER32_1->CONTROL |= (1<<5);
	NVIC->ICER[0] |= (1<<25); // clear interrupt register posição 25 do vetor de interrupção precisa usar o registrador ICER0
	NVIC->ISER[0] |= (1<<25); // enable interrupt register
	 NVIC->IP[6] &= ~(1<<8)|(1<<9)|(1<<10)|(1<<11);
}
void clearIRQFlagTimer32()
{
	TIMER32_1->INTCLR = 0x01;
}
