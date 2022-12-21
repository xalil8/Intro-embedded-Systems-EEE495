#include <msp430.h>
#include "func.h"

void motor_clockwise(void);
void motor_counter_clockwise(void);
void cw_8_step(void);
void run_motor(int);


void main(void) {
    //MSP430 SETTINGS
    WDTCTL = WDTPW | WDTHOLD;


    BCSCTL3 |= LFXT1S_2;
    BCSCTL2 |= SELM_3 + DIVM_0  ; //clock is really slow
    ///////////////////////////////////////////////

    P1DIR = IN1 + IN2 +IN3 +IN4 + GREEN + RED;
    P1OUT = 0;

    P1OUT |= BIT3;   // |=  is used for set         set pull up resistor for button P1.3
    P1REN |= BIT3 ;   // &= is used for reset    enable pull up resisstor


    const int stepnumber = 512;

    for(;;){  //for infinity loop

        if((P1IN & 0x08) == 0){

            run_motor(stepnumber);
        }
        else{
            P1OUT &=  ~GREEN;
            P1OUT &=  ~IN1;
            P1OUT &=  ~IN2;
            P1OUT &=  ~IN3;
            P1OUT &=  ~IN4;
        }
    }
}






