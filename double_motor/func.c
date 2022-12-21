/*
 * func.c
 *
 *  Created on: Dec 19, 2022
 *      Author: halil
 */

#include "func.h"

void motor_clockwise(void){

    P1OUT |= GREEN; //WHEN MOTOR TURN  CLOCKWISE GREEN LIGHT ON
    P1OUT &= ~RED;

    _delay_cycles(motor_speed);
    P1OUT |= IN1;
    P1OUT |= IN2;
    P1OUT &=  ~IN3;
    P1OUT &=  ~IN4;

    _delay_cycles(motor_speed);

    P1OUT |= IN2;
    P1OUT |= IN3;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN4;

    _delay_cycles(motor_speed);

    P1OUT |= IN3;
    P1OUT |= IN4;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN2;


    _delay_cycles(motor_speed);

    P1OUT |= IN1;
    P1OUT |= IN4;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN3;

 }


void counter_motor_clockwise(void){
    P1OUT |= RED;       //WHEN MOTOR TURN COUNTER CLOCKWISE RED LIGHT ON
    P1OUT &= ~GREEN;


    _delay_cycles(motor_speed);
    P1OUT |= IN1;
    P1OUT |= IN4;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN3;

    _delay_cycles(motor_speed);
    P1OUT |= IN3;
    P1OUT |= IN4;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN2;

    _delay_cycles(motor_speed);
    P1OUT |= IN2;
    P1OUT |= IN3;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN4;

    _delay_cycles(motor_speed);
    P1OUT |= IN1;
    P1OUT |= IN2;
    P1OUT &=  ~IN3;
    P1OUT &=  ~IN4;
 }

void cw_8_step(void){


    //IN1 IN2 IN3 IN4
    //1    0   0    0
    _delay_cycles(motor_speed);
    P1OUT |= IN1;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN3;
    P1OUT &=  ~IN4;

    //IN1 IN2 IN3 IN4
    //1    1   0    0
    _delay_cycles(motor_speed);
    P1OUT |= IN1;
    P1OUT |= IN2;
    P1OUT &=  ~IN3;
    P1OUT &=  ~IN4;


    //IN1 IN2 IN3 IN4
    //0    1   0    0
    _delay_cycles(motor_speed);
    P1OUT |= IN2;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN3;
    P1OUT &=  ~IN4;

    //IN1 IN2 IN3 IN4
    //0    1   1    0
    _delay_cycles(motor_speed);
    P1OUT |= IN2;
    P1OUT |= IN3;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN4;

    //IN1 IN2 IN3 IN4
    //0    0   1    0
    _delay_cycles(motor_speed);
    P1OUT |= IN3;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN4;

    //IN1 IN2 IN3 IN4
    //0    0   1    1
    _delay_cycles(motor_speed);
    P1OUT |= IN3;
    P1OUT |= IN4;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN2;

    //IN1 IN2 IN3 IN4
    //0    0   0    1
    _delay_cycles(motor_speed);
    P1OUT |= IN4;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN3;

    //IN1 IN2 IN3 IN4
    //1    0   0    1
    _delay_cycles(motor_speed);
    P1OUT |= IN1;
    P1OUT |= IN4;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN3;
}



