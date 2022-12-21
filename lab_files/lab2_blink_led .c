#include <msp430.h>
// #include<msp430g2553.h>


/*
 halil ibrahim Özcan
 2017514050
 */
//#define SW  BIT6


void main(void) {
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer


    P1DIR = BIT0;

    P1OUT = BIT0;



}
