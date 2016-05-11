/*
 * ADC14.h
 *
 *  Created on: 02/05/2016
 *      Author: Marco Moreira
 */

#ifndef DRIVERLIB_MSP432P4XX_ADC14_H_
#define DRIVERLIB_MSP432P4XX_ADC14_H_
#include <msp.h>
void initADC14();
float readADC14();
void clearIRQFlagADC14();
void startConversion();
#endif /* DRIVERLIB_MSP432P4XX_ADC14_H_ */
