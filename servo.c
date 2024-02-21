/*
 * servo.c
 *
 *  Created on: Oct 31, 2023
 *      Author: jhsoto
 */

#include "servo.h"
#include "timer.h"

int pulse_width;

void servo_init(void){
    SYSCTL_RCGCGPIO_R |= 0x02;

    //alt. function
    GPIO_PORTB_AFSEL_R |= 0x20;
    GPIO_PORTB_PCTL_R |= 0x700000;

    //set as outputs
    GPIO_PORTB_DIR_R |= 0x20;

    //digital enable
    GPIO_PORTB_DEN_R |= 0x20;

    //CONFIGURE TIMER
    //turn on clk for timer1
    SYSCTL_RCGCTIMER_R |= 0x02;

    //disable timer to config
    TIMER1_CTL_R &= ~0x100;

    //set size of timer to 16
    TIMER1_CFG_R |= 0x04;

    //periodic and PWM enable
    TIMER1_TBMR_R |= (0x02 | 0x08);
    TIMER1_TBMR_R &= ~0x04;

    //set to non-inverted PWM mode
    TIMER1_CTL_R &= ~0x4000;

    // set lower 16 bits of interval
    TIMER1_TBILR_R |= (320000 & 0xFFFF);

    //set upper 8 bits of interval
    TIMER1_TBPR_R |= (320000 >> 16);

//      TEST MOVEMENT
//    pulse_width = 0;
//    servo_move(pulse_width);

    // set lower 16 bits of pulse width
    TIMER1_TBMATCHR_R |= ((320000 - pulse_width) & 0xFFFF);

    //set upper 8 bits of pulse width
    TIMER1_TBPMR_R |= ((320000 - pulse_width) >> 16);

    //enable timer
    TIMER1_CTL_R |= 0x100;

}



void servo_move(uint16_t degrees){
        // Timer count value and servo position
        // Duty cycle = Pulse With / period
        // degrees = count
    //28992 constant multiplier     // Offset
    pulse_width = ((28992 * (degrees / 180.0)) + 874);

    //set lower 16 bits of pulse width
    TIMER1_TBMATCHR_R = ((320000 - pulse_width) & 0xFFFF);

    //set the upper 8 bits of the pulse width
    TIMER1_TBPMR_R |= ((320000 - pulse_width) >> 16);

    //Delay for the servo to move to the position
    timer_waitMillis(1);

}

void servo_move_slow(uint16_t degrees){
        // Timer count value and servo position
        // Duty cycle = Pulse With / period
        // degrees = count
    //28992 constant multiplier     // Offset
    pulse_width = ((28992 * (degrees / 180.0)) + 874);

    //set lower 16 bits of pulse width
    TIMER1_TBMATCHR_R = ((320000 - pulse_width) & 0xFFFF);

    //set the upper 8 bits of the pulse width
    TIMER1_TBPMR_R |= ((320000 - pulse_width) >> 16);

    //Delay for the servo to move to the position
    //timer_waitMillis(100);

}



