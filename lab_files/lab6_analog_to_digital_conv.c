#include <msp430g2553.h>

volatile long tempRaw;
volatile long celcius;

/**
 * main.c  n = (Vin - Vss/ Vref-Vss ) * 2^10 -1
 */
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    if(CALBC1_1MHZ == 0XFF|| CALDCO_1MHZ == 0xFF){
        while(1);
    }

   BCSCTL1 = CALBC1_1MHZ ;
   DCOCTL = CALDCO_1MHZ;
   IFG1 &= ~OFIFG;
   BCSCTL2 |= SELM_0 + DIVM_3;
   while(1)
   {
       ADC10CTL1 = INCH_10 + ADC10DIV_0;
       ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON; //refon sets
       _delay_cycles(5); // wait for adc ref to settle
       ADC10CTL0 &= ~ENC;
       ADC10CTL0 &= ~(REFON + ADC10ON); // Stop sampling and conversion

       tempRaw = ADC10MEM;
       celcius = ((tempRaw -673)*432) / 1024;

   }
}
