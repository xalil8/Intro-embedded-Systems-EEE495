#include <msp430.h>



 
void main(void)
{
    
    
    WDTCTL = WDTPW | WDTHOLD;  
    BCSCTL1 = CALBC1_1MHZ;   
    DCOCTL = CALDCO_1MHZ;

    CCTL0 = CCIE;        
    BCSCTL2 |= SELM_1;
  
    
    
    TACTL = TASSEL_2 + MC_1 + ID_3;       //SMCLK/8, UPMODE
    
    
    CCR0 = 125000;                          //125KHZ

    P1DIR |= BIT0 + BIT6;               //ALL LED PINS ARE OUTPUT
    
    P1OUT = 0;
    
    P1DIR &= ~BIT3;                     //BUTTON IS INPUT

    P1IE |= BIT3;                       //HARDWARE INTERRUPT ENABLE FOR BIT3
    P1IES |= BIT3;                      //P1.3 HI/LOW EDGE

    P1REN |= BIT3;
    P1OUT |= BIT3;
    P1IFG &= ~BIT3;                     //P1.3 IFG CLEARED


    while (1) //LOW POWER MODE
    {
        _BIS_SR(CPUOFF +GIE); //GIE: GLOBAL INTERRUPT ENABLE
    }
}



#pragma vector= TIMER0_A0_VECTOR

__interrupt void Timer_A (void)


{
 P1OUT ^= BIT0;
}

#pragma vector=PORT1_VECTOR
__interrupt void button (void)
{
    P1OUT ^= BIT6; 
    P1IFG &= ~BIT3;
    _delay_cycles(1000);
}
