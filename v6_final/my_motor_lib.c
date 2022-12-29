/*
 * func.c
 *  Created on: Dec 26, 2022
 *      Author: Halil Ibrahim Özcan
 *      School No: 2017514050
 *      E-mail : halil.ozcan1999@gmail.com
 */

#include <my_motor_lib.h>

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if (P1IFG & BIT0)  // Check if interrupt was triggered by P1.1
    {
//        write_serial("ISR1 WORKED", 11);
//        write_serial("\n\r", 2);

        while (x_current != x_new) {

            if (x_current < x_new){
                x_current++;
                write_serial("Motor X Moving + Position", 25);
                write_serial("\n\r", 2);
                motor1_clockwise();
            }
            else {
                x_current--;
                write_serial("Motor X Moving - Position", 25);
                write_serial("\n\r", 2);
                motor1_counter_clockwise();
            }
        }
        P1IFG &= ~BIT0;  // Clear interrupt flag
    }

    //interrupt for to get reset positions of motors
    if (P1IFG & BIT3) {
        // This is the interrupt handler for pin 1.3
        reset_sound();
        x_new = 0;
        y_new = 0;
        write_serial("### MOTORS MOVING TO RESET POSITION ###", 39);
        write_serial("\n\r", 2);

        while (x_current != x_new) {

            if (x_current < x_new){
                x_current++;
                write_serial("Motor X Moving + Position", 25);
                write_serial("\n\r", 2);
                motor1_clockwise();
            }
            else {
                x_current--;
                write_serial("Motor X Moving - Position", 25);
                write_serial("\n\r", 2);
                motor1_counter_clockwise();
            }
        }
        P1IFG &= ~BIT3;  // Clear the interrupt flag for pin 1.3
        P2IFG |= BIT0;   //set interrupt flag for y motor to reset position
    }
}


#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    if (P2IFG & BIT0)  // Check if interrupt was triggered by P1.1
    {
//        write_serial("ISR2 WORKED", 11);
//        write_serial("\n\r", 2);

        while (y_current != y_new) {
            if (y_current < y_new){
                y_current++;
                write_serial("Motor Y Moving + Position", 25);
                write_serial("\n\r", 2);
                motor2_clockwise();

            }
            else {
                y_current--;
                write_serial("Motor Y Moving + Position", 25);
                write_serial("\n\r", 2);
                motor2_counter_clockwise();
            }
        }
        P2IFG &= ~BIT0;  // Clear interrupt flag

    }
}



void write_serial(char *string, unsigned char string_lenght){
    while(string_lenght--){ // Loop until StringLength == 0 and post decrement
        while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
        UCA0TXBUF = *string; //Write the character at the location specified by the pointer
        string++; //Increment the TxString pointer to point to the next character
    }
}


void motor1_clockwise(void){

    int c;
    for(c = 0 ;c <=step_number/divider ;c++){
        // buzzer effect to warning
        if (c >= 0 && c < 50/divider) {
          P2OUT |= BUZZER;
        } else if (c >= 130/divider && c < 180/divider) {
          P2OUT |= BUZZER;
        } else if (c >= 260/divider && c < 310/divider) {
          P2OUT |= BUZZER;
        } else if (c >= 390/divider && c < 440/divider) {
          P2OUT |= BUZZER;
        } else {
          P2OUT &= ~BUZZER;
        }
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
    P2OUT &= ~BUZZER;
    //turn off all input
    //0    0    0    0
    P1OUT &=  ~MOTOR1_IN1;
    P1OUT &=  ~MOTOR1_IN2;
    P1OUT &=  ~MOTOR1_IN3;
    P1OUT &=  ~MOTOR1_IN4;

}

void motor1_counter_clockwise(void){

    int c;
    for(c = 0 ;c <=step_number/divider;c++){
        // buzzer effect to warning
        // buzzer effect to warning
        if (c >= 0 && c < 50/divider) {
          P2OUT |= BUZZER;
        } else if (c >= 130/divider && c < 180/divider) {
          P2OUT |= BUZZER;
        } else if (c >= 260/divider && c < 310/divider) {
          P2OUT |= BUZZER;
        } else if (c >= 390/divider && c < 440/divider) {
          P2OUT |= BUZZER;
        } else {
          P2OUT &= ~BUZZER;
        }
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
    for(c = 0 ;c <=step_number/divider;c++){
        // buzzer effect to warning
        if (c >= 0 && c < 50/divider) {
          P2OUT |= BUZZER;
        } else if (c >= 130/divider && c < 180/divider) {
          P2OUT |= BUZZER;
        } else if (c >= 260/divider && c < 310/divider) {
          P2OUT |= BUZZER;
        } else if (c >= 390/divider && c < 440/divider) {
          P2OUT |= BUZZER;
        } else {
          P2OUT &= ~BUZZER;
        }
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
    for(c = 0 ;c <=step_number/divider;c++){
        // buzzer effect to warning
        if (c >= 0 && c < 50/divider) {
          P2OUT |= BUZZER;
        } else if (c >= 130/divider && c < 180/divider) {
          P2OUT |= BUZZER;
        } else if (c >= 260/divider && c < 310/divider) {
          P2OUT |= BUZZER;
        } else if (c >= 390/divider && c < 440/divider) {
          P2OUT |= BUZZER;
        } else {
          P2OUT &= ~BUZZER;
        }
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

//this function take char array like '-2,-3' and conver them into int value in range of [-5,5]
void parse_string(char* str) {

    if(((str[1] < '0' || str[1] > '5') || (str[4] < '0' || str[4] > '5'))){
        write_serial("ENTER DIGIT", 11);
        write_serial("\n\r", 2);
    }


    else if(str[2]==','){
        //////////////for x coordinate////////////////
        if(str[0]=='-'){ // check if number negative or positive
            if (str[1] >= '0' && str[1] <= '5'){ // check if number in range 0-5
                x_new = str[1] - '0'; //convert char to int
                x_new =  -x_new;      //convert the value to negative in order to its sign
            }
            else{
                write_serial("X Coordinates must be in range of [-5,5]", 40);
                write_serial("\n\r", 2);

            }
        }

        else if(str[0]=='+'){


            if (str[1] >= '0' && str[1] <= '5'){// check if number in range 0-5
                x_new = str[1] - '0'; //convert char to int
            }
            else{
                write_serial("X Coordinates must be in range of [-5,5]", 40);
                write_serial("\n\r", 2);
            }
        }

        else{
            write_serial("X Coordinates Sign must be '-' or '+' ", 38);
            write_serial("\n\r", 2);
        }

        //////////////for y coordinate////////////////
        if(str[3]=='-'){ // check if number negative or positive
            if (str[4] >= '0' && str[4] <= '5'){ // check if number in range 0-5
                y_new = str[4] - '0'; //convert char to int
                y_new =  -y_new;      //convert the value to negative in order to its sign
            }
            else{
                write_serial("Y Coordinates must be in range of [-5,5]", 40);
                write_serial("\n\r", 2);
            }
        }

        else if(str[3]=='+'){


            if (str[4] >= '0' && str[4] <= '5'){// check if number in range 0-5
                y_new = str[4] - '0'; //convert char to int
            }
            else{
                write_serial("Y Coordinates must be in range of [-5,5]", 40);
                write_serial("\n\r", 2);
            }
        }

        else{
            write_serial("Y Coordinates Sign must be '-' or '+' ", 38);
            write_serial("\n\r", 2);
        }
    }
    else{
        write_serial("Coordinates must be coma',' separate, like '+x,-y' ", 51);
        write_serial("\n\r", 2);
    }
}


void reset_sound(void){
    int q;
    for(q = 0 ;q <=1400; q++){
        // buzzer effect to warning
        if (q >= 0 && q < 200) {
          P2OUT |= BUZZER;
          __delay_cycles(1000);
        } else if (q >= 400 && q < 600) {
          P2OUT |= BUZZER;
          __delay_cycles(1000);
        } else if (q >= 800 && q < 1000) {
          P2OUT |= BUZZER;
          __delay_cycles(1000);
        } else if (q >= 1200 && q < 1400) {
          P2OUT |= BUZZER;
          __delay_cycles(1000);
        } else {
          P2OUT &= ~BUZZER;
          __delay_cycles(1000);
        }
    }
}
