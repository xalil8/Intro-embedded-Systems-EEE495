/************************************************************
*                      HALIL IBRAHIM OZCAN
*                       2017514050
*                       halil.ozcan1999@gmail.com
************************************************************/


#include "func.h"

__interrupt void Port_1(void)
{
    if (P1IFG & BIT0)  // Check if interrupt was triggered by P1.1
    {
        UARTSendArray("ISR1 WORKED ", 12);
        UARTSendArray("\n\r", 2);

        while (x_current != x_new) {
            if (x_current < x_new){
                x_current++;
                UARTSendArray("x_current += 1", 14);
                UARTSendArray("\n\r", 2);

                motor1_clockwise();
            }
            else {
                x_current--;
                UARTSendArray("x_current -= 1", 14);
                UARTSendArray("\n\r", 2);
                motor1_counter_clockwise();
            }
        }
        P1IFG &= ~BIT0;  // Clear interrupt flag
    }
}


__interrupt void Port_2(void)
{
    if (P2IFG & BIT0)  // Check if interrupt was triggered by P1.1
    {
        UARTSendArray("ISR2 WORKED ", 12);
        UARTSendArray("\n\r", 2);

        while (y_current != y_new) {
            if (y_current < y_new){
                y_current++;
                UARTSendArray("y_current += 1", 14);
                UARTSendArray("\n\r", 2);
                motor2_clockwise();


            }
            else {
                y_current--;
                UARTSendArray("y_current -= 1", 14);
                UARTSendArray("\n\r", 2);
                motor2_counter_clockwise();
            }
        }
        P2IFG &= ~BIT0;  // Clear interrupt flag
    }
}


void UARTSendArray(char *TxArray, unsigned char ArrayLength){
    while(ArrayLength--){ // Loop until StringLength == 0 and post decrement
        while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
        UCA0TXBUF = *TxArray; //Write the character at the location specified by the pointer
        TxArray++; //Increment the TxString pointer to point to the next character
    }
}


void motor1_clockwise(void){

    int c;
    for(c = 0 ;c <=step_number;c++){
        //MOTOR1_IN1 MOTOR1_IN2 MOTOR1_IN3 MOTOR1_IN4
        //1    0   0    0
        P1OUT |= MOTOR1_IN1;
        P1OUT &=  ~MOTOR1_IN2;
        P1OUT &=  ~MOTOR1_IN3;
        P1OUT &=  ~MOTOR1_IN4;
        _delay_cycles(motor_speed);

        //MOTOR1_IN1 MOTOR1_IN2 MOTOR1_IN3 MOTOR1_IN4
        //1    1   0    0
        P1OUT |= MOTOR1_IN1;
        P1OUT |= MOTOR1_IN2;
        P1OUT &=  ~MOTOR1_IN3;
        P1OUT &=  ~MOTOR1_IN4;
        _delay_cycles(motor_speed);

        //MOTOR1_IN1 MOTOR1_IN2 MOTOR1_IN3 MOTOR1_IN4
        //0    1   0    0
        P1OUT |= MOTOR1_IN2;
        P1OUT &=  ~MOTOR1_IN1;
        P1OUT &=  ~MOTOR1_IN3;
        P1OUT &=  ~MOTOR1_IN4;
        _delay_cycles(motor_speed);

        //MOTOR1_IN1 MOTOR1_IN2 MOTOR1_IN3 MOTOR1_IN4
        //0    1   1    0
        P1OUT |= MOTOR1_IN2;
        P1OUT |= MOTOR1_IN3;
        P1OUT &=  ~MOTOR1_IN1;
        P1OUT &=  ~MOTOR1_IN4;
        _delay_cycles(motor_speed);

        //MOTOR1_IN1 MOTOR1_IN2 MOTOR1_IN3 MOTOR1_IN4
        //0    0   1    0
        P1OUT |= MOTOR1_IN3;
        P1OUT &=  ~MOTOR1_IN1;
        P1OUT &=  ~MOTOR1_IN2;
        P1OUT &=  ~MOTOR1_IN4;
        _delay_cycles(motor_speed);

        //MOTOR1_IN1 MOTOR1_IN2 MOTOR1_IN3 MOTOR1_IN4
        //0    0   1    1
        P1OUT |= MOTOR1_IN3;
        P1OUT |= MOTOR1_IN4;
        P1OUT &=  ~MOTOR1_IN1;
        P1OUT &=  ~MOTOR1_IN2;
        _delay_cycles(motor_speed);


        //MOTOR1_IN1 MOTOR1_IN2 MOTOR1_IN3 MOTOR1_IN4
        //0    0   0    1
        P1OUT |= MOTOR1_IN4;
        P1OUT &=  ~MOTOR1_IN1;
        P1OUT &=  ~MOTOR1_IN2;
        P1OUT &=  ~MOTOR1_IN3;
        _delay_cycles(motor_speed);

        //MOTOR1_IN1 MOTOR1_IN2 MOTOR1_IN3 MOTOR1_IN4
        //1    0   0    1
        P1OUT |= MOTOR1_IN1;
        P1OUT |= MOTOR1_IN4;
        P1OUT &=  ~MOTOR1_IN2;
        P1OUT &=  ~MOTOR1_IN3;
        _delay_cycles(motor_speed);

    }

    //turn off all input
    //0    0    0    0
    P1OUT &=  ~MOTOR1_IN1;
    P1OUT &=  ~MOTOR1_IN2;
    P1OUT &=  ~MOTOR1_IN3;
    P1OUT &=  ~MOTOR1_IN4;

}

void motor1_counter_clockwise(void){

    int c;
    for(c = 0 ;c <=step_number;c++){
        //MOTOR1_IN1 MOTOR1_IN2 MOTOR1_IN3 MOTOR1_IN4
        //0    0   0    1
        P1OUT &=  ~MOTOR1_IN1;
        P1OUT &=  ~MOTOR1_IN2;
        P1OUT &=  ~MOTOR1_IN3;
        P1OUT |= MOTOR1_IN4;
        _delay_cycles(motor_speed);

        //MOTOR1_IN1 MOTOR1_IN2 MOTOR1_IN3 MOTOR1_IN4
        //0    0   1    1
        P1OUT &=  ~MOTOR1_IN1;
        P1OUT &=  ~MOTOR1_IN2;
        P1OUT |= MOTOR1_IN3;
        P1OUT |= MOTOR1_IN4;
        _delay_cycles(motor_speed);

        //MOTOR1_IN1 MOTOR1_IN2 MOTOR1_IN3 MOTOR1_IN4
        //0    0   1    0
        P1OUT &=  ~MOTOR1_IN1;
        P1OUT &=  ~MOTOR1_IN2;
        P1OUT |= MOTOR1_IN3;
        P1OUT &=  ~MOTOR1_IN4;
        _delay_cycles(motor_speed);

        //MOTOR1_IN1 MOTOR1_IN2 MOTOR1_IN3 MOTOR1_IN4
        //0    1   1    0
        P1OUT &=  ~MOTOR1_IN1;
        P1OUT |= MOTOR1_IN2;
        P1OUT |= MOTOR1_IN3;
        P1OUT &=  ~MOTOR1_IN4;
        _delay_cycles(motor_speed);

        //MOTOR1_IN1 MOTOR1_IN2 MOTOR1_IN3 MOTOR1_IN4
        //0    1   0    0
        P1OUT &=  ~MOTOR1_IN1;
        P1OUT |= MOTOR1_IN2;
        P1OUT &=  ~MOTOR1_IN3;
        P1OUT &=  ~MOTOR1_IN4;
        _delay_cycles(motor_speed);

        //MOTOR1_IN1 MOTOR1_IN2 MOTOR1_IN3 MOTOR1_IN4
        //1    1   0    0
        P1OUT |= MOTOR1_IN1;
        P1OUT |= MOTOR1_IN2;
        P1OUT &=  ~MOTOR1_IN3;
        P1OUT &=  ~MOTOR1_IN4;
        _delay_cycles(motor_speed);

        //MOTOR1_IN1 MOTOR1_IN2 MOTOR1_IN3 MOTOR1_IN4
        //1    0   0    0
        P1OUT |= MOTOR1_IN1;
        P1OUT &=  ~MOTOR1_IN2;
        P1OUT &=  ~MOTOR1_IN3;
        P1OUT &=  ~MOTOR1_IN4;
        _delay_cycles(motor_speed);

        //MOTOR1_IN1 MOTOR1_IN2 MOTOR1_IN3 MOTOR1_IN4
        //1    0   0    1
        P1OUT |= MOTOR1_IN1;
        P1OUT &=  ~MOTOR1_IN2;
        P1OUT &=  ~MOTOR1_IN3;
        P1OUT |= MOTOR1_IN4;
        _delay_cycles(motor_speed);

    }
    //turn off all input
    //0    0    0    0
    P1OUT &=  ~MOTOR1_IN1;
    P1OUT &=  ~MOTOR1_IN2;
    P1OUT &=  ~MOTOR1_IN3;
    P1OUT &=  ~MOTOR1_IN4;

}

void motor2_clockwise(void){

    int c;
    for(c = 0 ;c <=step_number;c++){

        //MOTOR2_IN1 MOTOR2_IN2 MOTOR2_IN3 MOTOR2_IN4
        //1    0   0    0
        P2OUT |=  MOTOR2_IN1;
        P2OUT &= ~MOTOR2_IN2;
        P2OUT &= ~MOTOR2_IN3;
        P2OUT &= ~MOTOR2_IN4;
        _delay_cycles(motor_speed);

        //MOTOR2_IN1 MOTOR2_IN2 MOTOR2_IN3 MOTOR2_IN4
        //1    1   0    0
        P2OUT |=  MOTOR2_IN1;
        P2OUT |=  MOTOR2_IN2;
        P2OUT &= ~MOTOR2_IN3;
        P2OUT &= ~MOTOR2_IN4;
        _delay_cycles(motor_speed);

        //MOTOR2_IN1 MOTOR2_IN2 MOTOR2_IN3 MOTOR2_IN4
        //0    1   0    0
        P2OUT &= ~MOTOR2_IN1;
        P2OUT |=  MOTOR2_IN2;
        P2OUT &= ~MOTOR2_IN3;
        P2OUT &= ~MOTOR2_IN4;
        _delay_cycles(motor_speed);

        //MOTOR2_IN1 MOTOR2_IN2 MOTOR2_IN3 MOTOR2_IN4
        //0    1   1    0
        P2OUT &= ~MOTOR2_IN1;
        P2OUT |=  MOTOR2_IN2;
        P2OUT |=  MOTOR2_IN3;
        P2OUT &= ~MOTOR2_IN4;
        _delay_cycles(motor_speed);

        //MOTOR2_IN1 MOTOR2_IN2 MOTOR2_IN3 MOTOR2_IN4
        //0    0   1    0
        P2OUT &= ~MOTOR2_IN1;
        P2OUT &= ~MOTOR2_IN2;
        P2OUT |=  MOTOR2_IN3;
        P2OUT &= ~MOTOR2_IN4;
        _delay_cycles(motor_speed);

        //MOTOR2_IN1 MOTOR2_IN2 MOTOR2_IN3 MOTOR2_IN4
        //0    0   1    1
        P2OUT &= ~MOTOR2_IN1;
        P2OUT &= ~MOTOR2_IN2;
        P2OUT |=  MOTOR2_IN3;
        P2OUT |=  MOTOR2_IN4;
        _delay_cycles(motor_speed);

        //MOTOR2_IN1 MOTOR2_IN2 MOTOR2_IN3 MOTOR2_IN4
        //0    0   0    1

        P2OUT &=  ~MOTOR2_IN1;
        P2OUT &=  ~MOTOR2_IN2;
        P2OUT &=  ~MOTOR2_IN3;
        P2OUT |= MOTOR2_IN4;
        _delay_cycles(motor_speed);

        //MOTOR2_IN1 MOTOR2_IN2 MOTOR2_IN3 MOTOR2_IN4
        //1    0   0    1
        P2OUT |= MOTOR2_IN1;
        P2OUT &=  ~MOTOR2_IN2;
        P2OUT &=  ~MOTOR2_IN3;
        P2OUT |= MOTOR2_IN4;
        _delay_cycles(motor_speed);

    }
    //turn off all input
    //0    0    0    0
    P2OUT &= ~MOTOR2_IN1;
    P2OUT &= ~MOTOR2_IN2;
    P2OUT &= ~MOTOR2_IN3;
    P2OUT &= ~MOTOR2_IN4;
}

void motor2_counter_clockwise(void){
    int c;
    for(c = 0 ;c <=step_number;c++){
        //MOTOR2_IN1 MOTOR2_IN2 MOTOR2_IN3 MOTOR2_IN4
        //0    0   0    1
        P2OUT &=  ~MOTOR2_IN1;
        P2OUT &=  ~MOTOR2_IN2;
        P2OUT &=  ~MOTOR2_IN3;
        P2OUT |= MOTOR2_IN4;
        _delay_cycles(motor_speed);

        //MOTOR2_IN1 MOTOR2_IN2 MOTOR2_IN3 MOTOR2_IN4
        //0    0   1    1
        P2OUT &=  ~MOTOR2_IN1;
        P2OUT &=  ~MOTOR2_IN2;
        P2OUT |= MOTOR2_IN3;
        P2OUT |= MOTOR2_IN4;
        _delay_cycles(motor_speed);

        //MOTOR2_IN1 MOTOR2_IN2 MOTOR2_IN3 MOTOR2_IN4
        //0    0   1    0
        P2OUT &=  ~MOTOR2_IN1;
        P2OUT &=  ~MOTOR2_IN2;
        P2OUT |= MOTOR2_IN3;
        P2OUT &=  ~MOTOR2_IN4;
        _delay_cycles(motor_speed);

        //MOTOR2_IN1 MOTOR2_IN2 MOTOR2_IN3 MOTOR2_IN4
        //0    1   1    0
        P2OUT &=  ~MOTOR2_IN1;
        P2OUT |= MOTOR2_IN2;
        P2OUT |= MOTOR2_IN3;
        P2OUT &=  ~MOTOR2_IN4;
        _delay_cycles(motor_speed);

        //MOTOR2_IN1 MOTOR2_IN2 MOTOR2_IN3 MOTOR2_IN4
        //0    1   0    0
        P2OUT &=  ~MOTOR2_IN1;
        P2OUT |= MOTOR2_IN2;
        P2OUT &=  ~MOTOR2_IN3;
        P2OUT &=  ~MOTOR2_IN4;
        _delay_cycles(motor_speed);

        //MOTOR2_IN1 MOTOR2_IN2 MOTOR2_IN3 MOTOR2_IN4
        //1    1   0    0
        P2OUT |= MOTOR2_IN1;
        P2OUT |= MOTOR2_IN2;
        P2OUT &=  ~MOTOR2_IN3;
        P2OUT &=  ~MOTOR2_IN4;
        _delay_cycles(motor_speed);

        //MOTOR2_IN1 MOTOR2_IN2 MOTOR2_IN3 MOTOR2_IN4
        //1    0   0    0
        P2OUT |= MOTOR2_IN1;
        P2OUT &=  ~MOTOR2_IN2;
        P2OUT &=  ~MOTOR2_IN3;
        P2OUT &=  ~MOTOR2_IN4;
        _delay_cycles(motor_speed);

        //MOTOR2_IN1 MOTOR2_IN2 MOTOR2_IN3 MOTOR2_IN4
        //1    0   0    1
        P2OUT |= MOTOR2_IN1;
        P2OUT &=  ~MOTOR2_IN2;
        P2OUT &=  ~MOTOR2_IN3;
        P2OUT |= MOTOR2_IN4;
        _delay_cycles(motor_speed);
    }
    //turn off all input
    //0    0    0    0
    P2OUT &=  ~MOTOR2_IN1;
    P2OUT &=  ~MOTOR2_IN4;
    P2OUT &=  ~MOTOR2_IN2;
    P2OUT &=  ~MOTOR2_IN3;
}