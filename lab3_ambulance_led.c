#include <msp430.h>
// #include<msp430g2553.h>


/*
 halil ibrahim Özcan
 2017514050
 */
//#define SW  BIT6


void main(void) {
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer


    P1DIR = BIT6 + BIT0;   //0X41

    P1OUT = 0;

    P1OUT |= BIT3;   // |=  is used for set         set pull up resistor for button P1.3
    P1REN |= BIT3 ;   // &= is used for reset    enable pull up resisstor




    for(;;){  //for infinity loop

        if((P1IN & 0x08) == 0){

            P1OUT |= BIT0;   //  p1 or p0(BIT0)
            P1OUT &=  ~BIT6;
        }

        else{
            P1OUT |= BIT6;
            P1OUT &=  ~BIT0;  // p1 and p0(BIT0) COMPLIMENT
        }
    }
}

