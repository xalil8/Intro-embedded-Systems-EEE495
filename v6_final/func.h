/*
 * func.h
 *
 *  Created on: Dec 26, 2022
 *      Author: halil
 */
#include "msp430.h"

#ifndef FUNC_H_
#define FUNC_H_



#define step_number 512
#define motor_speed 1300


#define MOTOR1_IN1 BIT4
#define MOTOR1_IN2 BIT5
#define MOTOR1_IN3 BIT6
#define MOTOR1_IN4 BIT7

#define MOTOR2_IN1 BIT1
#define MOTOR2_IN2 BIT2
#define MOTOR2_IN3 BIT3
#define MOTOR2_IN4 BIT4



void motor1_counter_clockwise(void);
void motor1_clockwise(void);
void motor2_counter_clockwise(void);
void motor2_clockwise(void);

void write_serial(char *string, unsigned char string_lenght);

char str[5];  // buffer to store received string
extern unsigned int i;
extern int x_current ;
extern int y_current ;
int x_new, y_new;


#endif /* FUNC_H_ */
