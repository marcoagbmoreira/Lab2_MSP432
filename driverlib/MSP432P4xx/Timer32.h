/*
 * Timer32.h
 *
 *  Created on: 01/05/2016
 *      Author: Marco Moreira
 */

#ifndef DRIVERLIB_MSP432P4XX_TIMER32_H_
#define DRIVERLIB_MSP432P4XX_TIMER32_H_

#include <stdint.h>
#include <math.h>
#include <msp.h>
void initTimer32();
void delay_msTimer32(uint32_t delay);
void delay_usTimer32(uint32_t delay);
void startTimer32();
uint32_t getValueTimer32();
void setIRQTimer32();
void clearIRQFlagTimer32();
#endif /* DRIVERLIB_MSP432P4XX_TIMER32_H_ */
