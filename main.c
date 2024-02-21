/*
*      Author: Jesus Soto
*      Author: Charles Arroyo
*/
#include "timer.h"
#include "lcd.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include "ManualMovement.h"
#include "uart_extra_help.h"
#include "adc.h"
#include "ping.h"
#include "servo.h"


// Global variables
int direction;

int manual_mode(char input, oi_t *sensor_data)
{
    switch (input)
    {
    case 'w':
        uart_sendStr("\rMoving forward!");
        move_forward(sensor_data, 300);
        servo_move(90);
        break;
    case 'o':
        uart_sendStr("\rTurning left!      ");
        turn_bot(sensor_data, 20);
        break;
    case 's':
        uart_sendStr("\rReverse!           ");
        move_backwards(sensor_data, 200);
        break;
    case 'p':
        uart_sendStr("\rTurning right!     ");
        turn_bot(sensor_data, -20);
        break;
    case NULL:
        oi_setWheels(0, 0);

        break;
    case 'a':   // 90 degrees left
        if (direction == 1){
            turn_bot(sensor_data, 81);
            uart_sendStr("\n\rNow you are facing west!");
            uart_sendChar('\n');
            direction = 3;
            timer_waitMillis(2000);
            break;
        }
        if (direction == 2){
            turn_bot(sensor_data, 81);
            uart_sendStr("\n\rNow you are facing north!");
            uart_sendChar('\n');
            direction = 1;
            timer_waitMillis(2000);
            break;
        }
        if (direction == 3){
            turn_bot(sensor_data, 81);
            uart_sendStr("\n\rNow you are facing south!");
            uart_sendChar('\n');
            direction = 4;
            timer_waitMillis(2000);
            break;
        }
        if (direction == 4){
            turn_bot(sensor_data, 81);
            uart_sendStr("\n\rNow you are facing east!");
            uart_sendChar('\n');
            direction = 2;
            timer_waitMillis(2000);
            break;
        }
        break;
    case 'd':   // 90 degrees right
       if (direction == 1){
            turn_bot(sensor_data, -81);
            uart_sendStr("\n\rNow you are facing east!");
            uart_sendChar('\n');
            direction = 2;
            timer_waitMillis(2000);
            break;
        }
        if (direction == 2){
            turn_bot(sensor_data, -81);
            uart_sendStr("\n\rNow you are facing south!");
            uart_sendChar('\n');
            direction = 4;
            timer_waitMillis(2000);
            break;
        }
        if (direction == 3){
            turn_bot(sensor_data, -81);
            uart_sendStr("\n\rNow you are facing north!");
            uart_sendChar('\n');
            direction = 1;
            timer_waitMillis(2000);
            break;
        }
        if (direction == 4){
            turn_bot(sensor_data, -81);
            uart_sendStr("\n\rNow you are facing west!");
            uart_sendChar('\n');
            direction = 3;
            timer_waitMillis(2000);
            break;
        }
       break;
    default:
        oi_setWheels(0, 0);
        uart_sendStr("\rBot is stopped!  "); // stop
    }
    return direction;
}

/**
 * Storing 5 objects
 */
typedef struct
{
    int object_num;
    int angle_detected;
    int radial_width;
    int object_distance;
    int ping_distance;
    int ir_distance;
} DetectedObject;

int main(void)
{

    lcd_init();                     // initialize lcd
    timer_init();                   // initialize timer
    oi_t *sensor_data = oi_alloc(); // sensor data struct
    oi_init(sensor_data);           // initialize sensor data struct
    uart_init(115200);              // initialize uart
    uart_interrupt_init(); // initialize uart interrupt
    adc_init();            // initialize adc
    servo_init();          // initializa servo
    ping_init();           // initialize ping

    unsigned char notesToPlay[] = {75, 74, 75, 75, 74, 75, 75, 74, 75, 75, 74, 75, 75, 74, 75, 75, 74, 75, 75, 74, 75, 75, 74, 75, 75, 75, 74, 75, 75, 75, 74, 75, 75, 74, 75, 72, 71, 72, 71, 70, 68, 72, 71, 72, 71, 70, 68};

    unsigned char lengths[] = {8, 8, 17, 8, 8, 17, 8, 8, 17, 8, 8, 17, 8, 8, 17, 8, 8, 17, 8, 8, 17, 8, 8, 17, 17, 17, 8, 8, 17, 17, 8, 8, 17, 8, 8, 17, 8, 8, 8, 8, 17, 17, 8, 8, 8, 8, 34 };

        int north = 1;
        int east = 2;
        int west = 3;
        int south = 4;

        uart_sendStr("Select starting direction '1' = north, '2' = east, '3' = west, '4' = south \n");
        uart_sendChar('\r');
        char selectedDirection = uart_receive();
        if (selectedDirection == '1'){
            direction = north;
            uart_sendStr("\rFacing North!");
            timer_waitMillis(4000);
        }
        else if (selectedDirection == '2'){
            direction = east;
            uart_sendStr("\rFacing East!");
            timer_waitMillis(4000);
        }
        else if (selectedDirection == '3'){
            direction = west;
            uart_sendStr("\rFacing West!");
            timer_waitMillis(4000);
        }
        else if (selectedDirection == '4'){
            direction = south;
            uart_sendStr("\rFacing South!");
            timer_waitMillis(4000);
        }
        else {
            direction = 0;
        }

    while (1)
    {
        int accurate = 0;
        int i = 0;
        int ir = 0;
        int ping = 0;
        int j = 0;
        int distance_ir[90];
        int distance_ping[90];
        int width = 0;
        int distanceIndex = 0;
        DetectedObject detected_objects[5];
        int detectedObjectIndex = 0;
        int k = 0;
        int indexTracker = 0;
        int degrees = 0;
        char dataHeader[] = "";
        char objectHeader[] = "";
        int p = 0;
        int o = 0;

        for (i = 0; i < 5; i++)
        {
            detected_objects[i].object_num = NULL;
            detected_objects[i].angle_detected = NULL;
            detected_objects[i].object_distance = NULL;
            detected_objects[i].radial_width = NULL;
        }

        char input = uart_recieve_nonblocking();
        manual_mode(input, sensor_data); // non-blocking uart

        if (input == 'm')
        {
            uart_sendChar('\n');
            uart_sendChar('\r');
            // Printing Header
            char header[] = "Degrees\t\t\tDistance (cm)\n \r";
            for (i = 0; i < strlen(header); i++)
            {
                uart_sendChar(header[i]);
            }
            // cyBOT_Scan(0, &scan);
            servo_move(0);

            timer_waitMillis(1000);

            for (degrees = 0; degrees <= 180; degrees += 2)
            {
                servo_move(degrees);
                ir = adc_read();
                ping = ping_getDistance();
                accurate = ((4.26 * pow(10, 6)) * (pow(ir, -1.64)));
                distance_ir[k] = accurate - 20; // adding each to distance
                distance_ping[k] = ping;
                k++;
                sprintf(dataHeader, "%d\t\t\t%d\n \r", degrees, accurate);
                for (j = 0; j < strlen(dataHeader); j++)
                {
                    uart_sendChar(dataHeader[j]);
                }
            }

            for (distanceIndex = 0; distanceIndex < 70; distanceIndex++)
            {

                if (distance_ir[distanceIndex] < 60 && detected_objects[distanceIndex-1].object_distance - detected_objects[distanceIndex].object_distance > 30)
                {

                    sprintf(objectHeader, "%d\t\t%d\n\r", degrees ,distance_ir[distanceIndex]);

                    // this is an object
                    detected_objects[detectedObjectIndex].object_num =
                        detectedObjectIndex + 1;
                    detected_objects[detectedObjectIndex].object_distance =
                            distance_ir[distanceIndex];
                    detected_objects[detectedObjectIndex].ir_distance = distance_ir[distanceIndex];
                    detected_objects[detectedObjectIndex].ping_distance = distance_ping[distanceIndex];

                    detected_objects[detectedObjectIndex].angle_detected = distanceIndex * 2;

                    if(detected_objects[detectedObjectIndex].angle_detected < 90){
                            detected_objects[detectedObjectIndex].angle_detected = detected_objects[detectedObjectIndex].angle_detected + 26;
                         }

                    indexTracker = distanceIndex;

                    while (abs(
                            distance_ir[indexTracker] - detected_objects[detectedObjectIndex].object_distance) < 10)
                    {
                        width += 2;
                        indexTracker++;
                    }

                    detected_objects[detectedObjectIndex].radial_width = width;
                    distanceIndex = indexTracker;
                    detectedObjectIndex++;
                }
            }

            uart_sendChar('\n');
            uart_sendChar('\r');
            uart_sendStr("Object#                 Angle                Distance Obj         Distance IR              Distance Ping                Width\n\r");

            for (p = 0; p < 5; p++) // Index
            {



                sprintf(objectHeader, "%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n\r",
                        detected_objects[p].object_num,
                        detected_objects[p].angle_detected,
                        detected_objects[p].object_distance,
                        detected_objects[p].ir_distance,
                        detected_objects[p].ping_distance,
                        detected_objects[p].radial_width); // String

                for (o = 0; o < strlen(objectHeader); o++) // Bytes
                {
                    uart_sendChar(objectHeader[o]);
                }
            }
            timer_waitMillis(1000);
            input = uart_receive();
            servo_move(90);
            input = NULL;
        }

        if (input == 'i'){
            oi_loadSong(0, 47, notesToPlay, lengths);
            oi_play_song(0);
        }
    }

}
