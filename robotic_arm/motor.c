 #include <msp430.h>
// #include<msp430g2553.h>

#define motor_speed 3000
/*
 halil ibrahim Özcan
 2017514050
 */
//#define SW  BIT6
void motor_clockwise(void);

void main(void) {

    WDTCTL = WDTPW | WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    CCTL0 = CCIE;
    BCSCTL2 |= SELM_1;



    TACTL = TASSEL_2 + MC_1 + ID_3;       //SMCLK/8, UPMODE


    CCR0 = 125000; // to set clockspeed 10kHz

    P1DIR = BIT0 + BIT1 +BIT6 +BIT7;   //0X41

    P1OUT = 0;

    P1OUT |= BIT3;   // |=  is used for set         set pull up resistor for button P1.3
    P1REN |= BIT3 ;   // &= is used for reset    enable pull up resisstor



    for(;;){  //for infinity loop
        if((P1IN & 0x08) == 0){
            motor_clockwise();
        }
        else{
            P1OUT &=  ~BIT0;
            P1OUT &=  ~BIT1;
            P1OUT &=  ~BIT6;
            P1OUT &=  ~BIT7;
        }

    }
}
void motor_clockwise(void)
{


       _delay_cycles(motor_speed);
       P1OUT |= BIT0;
       P1OUT |= BIT1;
       P1OUT &=  ~BIT6;
       P1OUT &=  ~BIT7;

       _delay_cycles(motor_speed);

       P1OUT |= BIT1;
       P1OUT |= BIT6;
       P1OUT &=  ~BIT0;
       P1OUT &=  ~BIT7;

       _delay_cycles(motor_speed);

       P1OUT |= BIT6;
       P1OUT |= BIT7;
       P1OUT &=  ~BIT0;
       P1OUT &=  ~BIT1;


       _delay_cycles(motor_speed);

       P1OUT |= BIT0;
       P1OUT |= BIT7;
       P1OUT &=  ~BIT1;
       P1OUT &=  ~BIT6;

       _delay_cycles(motor_speed);
    }
