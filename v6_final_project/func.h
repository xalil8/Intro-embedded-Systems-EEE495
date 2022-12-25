/************************************************************
*                      HALIL IBRAHIM OZCAN
*                       2017514050
*                       halil.ozcan1999@gmail.com
************************************************************/

#include <msp430.h>

#ifndef FUNC_H_

#define FUNC_H_


/************************************************************
*                      CONSTANTS
************************************************************/
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

#pragma vector=PORT1_VECTOR
#pragma vector=PORT2_VECTOR

void motor1_counter_clockwise(void);
void motor1_clockwise(void);

void motor2_counter_clockwise(void);
void motor2_clockwise(void);

void UARTSendArray(char *TxArray, unsigned char ArrayLength);

char str[4];  // buffer to store received string
unsigned int i=0;
int x_current = 0;
int y_current = 0;
int x_new, y_new;


#endif /* FUNC_H_ */