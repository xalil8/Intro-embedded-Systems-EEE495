#include <msp430g2553.h>
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;


    P1DIR = 0x40;
    P1OUT = 0;

    BCSCTL3 |= LFXT1S_2;            //VLO basic clock controller

    IFG1 &= ~OFIFG;                 //interrupt flag generator
    _bis_SR_register(SCG1 + SCG0);   //system register configuration


    BCSCTL2 |= SELM_3 + DIVM_3 ; // VLO CLK  / 8      == 12k/8 == 1500hz  so Tvlo = 1/1500s
                                  // for 100 cycles ->  100 * Tvlo = 0.067 and for 5000 cycle -- 5000*1/1500 = 3.3s



    while(1){
        P1OUT = 0X40;
        _delay_cycles(100);
        P1OUT = 0;
        _delay_cycles(5000);
    }

}
