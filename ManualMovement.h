/*
 * ManualMovement.h
 *
 *  Created on: Nov 7, 2023
 *      Author: jhsoto
 */

#ifndef MANUALMOVEMENT_H_
#define MANUALMOVEMENT_H_
#include "open_interface.h"
#include "uart_extra_help.h"

 // Move the robot forward
void move_forward(oi_t*sensor, int centemeters);

 // Turn the robot right
void turn_bot(oi_t*sensor, int degrees);

void move_backwards(oi_t*sensor, int millimiters);

void uart_sendCharNonBlocking(char data);

#endif /* MANUALMOVEMENT_H_ */
