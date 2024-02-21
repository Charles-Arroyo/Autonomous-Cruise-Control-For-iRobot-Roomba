/*
 * ManualMovement.c
 *
 *  Created on: Nov 7, 2023
 *      Author: jhsoto
 */


/*
 * movement.c
 *
 *  Created on: Sep 5, 2023
 *      Author: jhsoto
 */

#include "ManualMovement.h"
#include "open_interface.h"

void move_forward(oi_t*sensor, int millimiters){
//         double sum = 0;
//         oi_update(sensor);
//         while (sum < millimiters) {

         oi_setWheels(192, 195);
         oi_update(sensor);
//         sum += sensor->distance;
             if (sensor->bumpLeft){
                 oi_update(sensor);
                 oi_setWheels(0, 0);// stop
                 oi_update(sensor);
                 uart_sendStr("\n\rObject blocking path in front-left!\n\r");
                 uart_sendStr("Stop!\n\r");
                 timer_waitMillis(3000);
             }

             else if (sensor->bumpRight){
                 oi_update(sensor);
                 oi_setWheels(0, 0);// stop
                 oi_update(sensor);
                 uart_sendStr("\n\rObject blocking path in front-right!\n\r");
                 uart_sendStr("Stop!\n\r");
                 timer_waitMillis(3000);
             }
             else if (sensor->cliffRight){
                 oi_update(sensor);
                 oi_setWheels(0, 0);// stop
                 oi_update(sensor);
                 uart_sendStr("\n\rSTOP CLIFF RIGHT SIDE!\n\r");
                 uart_sendStr("STOP!\n\r");
                 timer_waitMillis(4000);
             }
             else if (sensor->cliffLeft){
                 oi_update(sensor);
                 oi_setWheels(0, 0);// stop
                 oi_update(sensor);
                 uart_sendStr("\n\rSTOP CLIFF LEFT SIDE!\n\r");
                 uart_sendStr("STOP!\n\r");
                 timer_waitMillis(4000);
             }
             else if (sensor->cliffFrontRight){
                 oi_update(sensor);
                 oi_setWheels(0, 0);// stop
                 oi_update(sensor);
                 uart_sendStr("\n\rSTOP CLIFF FRONT-RIGHT!\n\r");
                 uart_sendStr("STOP!\n\r");
                 timer_waitMillis(4000);
             }
             else if (sensor->cliffFrontLeft){
                 oi_update(sensor);
                 oi_setWheels(0, 0);// stop
                 oi_update(sensor);
                 uart_sendStr("\n\rSTOP CLIFF FRONT-LEFT!\n\r");
                 uart_sendStr("STOP!\n\r");
                 timer_waitMillis(4000);
             }
             else if (sensor->cliffRightSignal <= 2770 && sensor->cliffRightSignal >= 2720){
                 oi_update(sensor);
                 oi_setWheels(0, 0);// stop
                 oi_update(sensor);
                 uart_sendStr("\n\rBORDER RIGHT!\n\r");
                 uart_sendStr("STOP!\n\r");
                 timer_waitMillis(4000);
             }
             else if (sensor->cliffLeftSignal <= 2770 && sensor->cliffLeftSignal >= 2720){
                 oi_update(sensor);
                 oi_setWheels(0, 0);// stop
                 oi_update(sensor);
                 uart_sendStr("\n\rBORDER LEFT!\n\r");
                 uart_sendStr("STOP!\n\r");
                 timer_waitMillis(4000);
             }
             else if (sensor->cliffFrontRightSignal <= 2770 && sensor->cliffFrontRightSignal >= 2720){
                 oi_update(sensor);
                 oi_setWheels(0, 0);// stop
                 oi_update(sensor);
                 uart_sendStr("\n\rBORDER FRONT RIGHT!\n\r");
                 uart_sendStr("STOP!\n\r");
                 timer_waitMillis(4000);
             }
             else if (sensor->cliffRightSignal <= 2630 && sensor->cliffRightSignal >= 2580){
                 oi_update(sensor);
                 oi_setWheels(0, 0);// stop
                 oi_update(sensor);
                 uart_sendStr("\n\rBORDER FRONT-RIGHT!\n\r");
                 uart_sendStr("STOP!\n\r");
                 timer_waitMillis(4000);
             }
             else if (sensor->cliffLeftSignal <= 2630 && sensor->cliffLeftSignal >= 2580){
                 oi_update(sensor);
                 oi_setWheels(0, 0);// stop
                 oi_update(sensor);
                 uart_sendStr("\n\rBORDER FRONT-LEFT!\n\r");
                 uart_sendStr("STOP!\n\r");
                 timer_waitMillis(4000);
             }
}

void move_backwards(oi_t*sensor, int millimiters){
//         double sum = 0;
         oi_setWheels(-200, -201); // move backwards; full speed
//         while (sum > millimiters) {
//         oi_update(sensor);
//         sum += sensor->distance;
//         oi_setWheels(0, 0);
//         }
}

void turn_bot(oi_t*sensor, int degrees){
            double sum = 0;
            if (degrees < 0){ // Clockwise
                oi_setWheels(-180, 180);
                while (sum > degrees){
//                    degrees = degrees + 1;
                    oi_update(sensor);

                    sum += sensor -> angle;
                }
            }
            else if (degrees > 0){ // Counter-clockwise
                oi_setWheels(180, -180);

                while (sum < degrees){
                     oi_update(sensor);
                     sum += sensor -> angle;
                 }
            }
             oi_setWheels(0, 0); // stop
//             oi_free(sensor);
    }



