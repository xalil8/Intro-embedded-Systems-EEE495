#include <msp430.h>

#include "func.h"

void main(void) {

    WDTCTL = WDTPW | WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    CCTL0 = CCIE;
    BCSCTL2 |= SELM_1;

    TACTL = TASSEL_2 + MC_1 + ID_3;       //SMCLK/8, UPMODE

    CCR0 = 125000; // to set clockspeed 10kHz


    P1DIR = IN1 + IN2 +IN3 +IN4 + GREEN + RED;   //0X41

    P1OUT = 0;

    P1OUT |= BIT3;   // |=  is used for set         set pull up resistor for button P1.3
    P1REN |= BIT3 ;   // &= is used for reset    enable pull up resisstor



    for(;;){  //for infinity loop
        if((P1IN & 0x08) == 0){
            cw_8_step();
        }
        else{
            P1OUT &=  ~IN1;
            P1OUT &=  ~IN2;
            P1OUT &=  ~IN3;
            P1OUT &=  ~IN4;
        }

    }
}

