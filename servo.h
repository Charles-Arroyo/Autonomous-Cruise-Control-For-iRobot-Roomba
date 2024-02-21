/*
 * servo.h
 *
 *  Created on: Oct 31, 2023
 *      Author: jhsoto
 */

#include <stdbool.h>
#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"

#ifndef SERVO_H_
#define SERVO_H_

void servo_init(void);
void servo_move(uint16_t degrees);

#endif /* SERVO_H_ */
