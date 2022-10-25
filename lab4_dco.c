#include <msp430g2553.h>
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;


    if(CALBC1_1MHZ == 0xFF || CALDCO_1MHZ == 0xFF)
    {
        while(1);
    }

    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;


    P1DIR = 0x40;
    P1OUT = 0;


    IFG1 &= ~OFIFG;                 //interrupt flag generator
    _bis_SR_register(SCG1 + SCG0);   //system register configuration
    BCSCTL2 |= SELM_1 + DIVM_3 ; // VLO CLK  / 8      == 12k/8 == 1500hz  so Tvlo = 1/1500s
                                  // for 100 cycles ->  100 * Tvlo = 0.067 and for 5000 cycle -- 5000*1/1500 = 3.3s

    while(1){
        P1OUT = 0X40;
        _delay_cycles(100);
        P1OUT = 0;
        _delay_cycles(5000);
    }

}
