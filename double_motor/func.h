
#include <msp430.h>

#ifndef FUNC_H_
#define FUNC_H_

/*
************************************************************
*                      CONSTANTS
************************************************************
*/
#define motor_speed 1000


/*
************************************************************
*                        MACROS - MOTOR INPUTS
************************************************************
*/
#define IN1 BIT1
#define IN2 BIT2
#define IN3 BIT4
#define IN4 BIT5

#define GREEN BIT6
#define RED BIT0


/*
************************************************************
*                 FUNCTIONS DECLARATIONS
************************************************************
*/
void motor_clockwise(void);
void counter_motor_clockwise(void);
void cw_8_step(void);




#endif /* FUNC_H_ */