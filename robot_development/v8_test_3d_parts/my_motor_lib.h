/*
 * my_motor_lib.h
 *
 *  Created on: Dec 26, 2022
 *      Author: Halil Ibrahim Özcan
 *      School No: 2017514050
 *      E-mail : halil.ozcan1999@gmail.com
 */
#include "msp430.h"

#ifndef MY_MOTOR_LIB_H_
#define MY_MOTOR_LIB_H_

/*************************************************************
*                      CONSTANTS
*************************************************************/
#define step_number 512  //512 approximately 1 revolution, 2*512= 2 revolution
#define motor_speed 2000   //this calculated based on main clock work, lower is faster
#define divider 1

/*************************************************************
*                      MACROS - MOTOR INPUTS
*************************************************************/
#define MOTOR1_IN1 BIT4
#define MOTOR1_IN2 BIT5
#define MOTOR1_IN3 BIT6
#define MOTOR1_IN4 BIT7

#define MOTOR2_IN1 BIT1
#define MOTOR2_IN2 BIT2
#define MOTOR2_IN3 BIT3
#define MOTOR2_IN4 BIT4

#define BUTTON     BIT3
#define BUZZER     BIT5
/************************************************************
*                 FUNCTIONS DECLARATIONS
************************************************************/
void motor1_counter_clockwise(void);
void motor1_clockwise(void);
void motor2_counter_clockwise(void);
void motor2_clockwise(void);
void write_serial(char *string, unsigned char string_lenght);
void parse_string(char* str);
void reset_sound(void);
/************************************************************
*                 GLOBAL VARIABLES
************************************************************/
char str[5];  // buffer to store received string
extern unsigned int i;
extern int x_current ;
extern int y_current ;
int x_new, y_new;


#endif /* MY_MOTOR_LIB_H_ */
