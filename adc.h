/*
 * adc.h
 *
 *  Created on: Oct 17, 2023
 *      Author: jhsoto
 */

#ifndef ADC_H_
#define ADC_H_

// ADC initialization function
void adc_init(void);

// Function to take samples
uint16_t adc_read(void);

#endif /* ADC_H_ */
