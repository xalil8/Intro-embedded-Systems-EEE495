/*
 * func.c
 *
 *  Created on: Dec 19, 2022
 *      Author: halil
 */

#include "func.h"



void run_motor(int step_number){

    int i;
    for(i = 0 ;i <=step_number;i++){  //for infinity loop
        motor_clockwise();
    }
}

void motor_clockwise(void){

    //IN1 IN2 IN3 IN4
    //1    0   0    1
    P1OUT |= IN1;
    P1OUT |= IN4;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN3;
    _delay_cycles(motor_speed);

    //IN1 IN2 IN3 IN4
    //1    0   0    0
    P1OUT |= IN1;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN3;
    P1OUT &=  ~IN4;
    _delay_cycles(motor_speed);

    //IN1 IN2 IN3 IN4
    //1    1   0    0
    P1OUT |= IN1;
    P1OUT |= IN2;
    P1OUT &=  ~IN3;
    P1OUT &=  ~IN4;
    _delay_cycles(motor_speed);

    //IN1 IN2 IN3 IN4
    //0    1   0    0
    P1OUT |= IN2;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN3;
    P1OUT &=  ~IN4;
    _delay_cycles(motor_speed);

    //IN1 IN2 IN3 IN4
    //0    1   1    0
    P1OUT |= IN2;
    P1OUT |= IN3;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN4;
    _delay_cycles(motor_speed);

    //IN1 IN2 IN3 IN4
    //0    0   1    0
    P1OUT |= IN3;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN4;
    _delay_cycles(motor_speed);

    //IN1 IN2 IN3 IN4
    //0    0   1    1
    P1OUT |= IN3;
    P1OUT |= IN4;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN2;
    _delay_cycles(motor_speed);


    //IN1 IN2 IN3 IN4
    //0    0   0    1
    P1OUT |= IN4;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN3;
    _delay_cycles(motor_speed);

}

void motor_counter_clockwise(void){

    //IN1 IN2 IN3 IN4
    //0    0   0    1
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN3;
    P1OUT |= IN4;
    _delay_cycles(motor_speed);

    //IN1 IN2 IN3 IN4
    //0    0   1    1
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN2;
    P1OUT |= IN3;
    P1OUT |= IN4;
    _delay_cycles(motor_speed);

    //IN1 IN2 IN3 IN4
    //0    0   1    0
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN2;
    P1OUT |= IN3;
    P1OUT &=  ~IN4;
    _delay_cycles(motor_speed);

    //IN1 IN2 IN3 IN4
    //0    1   1    0
    P1OUT &=  ~IN1;
    P1OUT |= IN2;
    P1OUT |= IN3;
    P1OUT &=  ~IN4;
    _delay_cycles(motor_speed);

    //IN1 IN2 IN3 IN4
    //0    1   0    0
    P1OUT &=  ~IN1;
    P1OUT |= IN2;
    P1OUT &=  ~IN3;
    P1OUT &=  ~IN4;
    _delay_cycles(motor_speed);

    //IN1 IN2 IN3 IN4
    //1    1   0    0
    P1OUT |= IN1;
    P1OUT |= IN2;
    P1OUT &=  ~IN3;
    P1OUT &=  ~IN4;
    _delay_cycles(motor_speed);

    //IN1 IN2 IN3 IN4
    //1    0   0    0
    P1OUT |= IN1;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN3;
    P1OUT &=  ~IN4;
    _delay_cycles(motor_speed);

    //IN1 IN2 IN3 IN4
    //1    0   0    1
    P1OUT |= IN1;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN3;
    P1OUT |= IN4;
    _delay_cycles(motor_speed);
}


