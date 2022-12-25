#include "msp430g2553.h"

#define x_current 0
#define y_current 0


#define IN1 BIT4
#define IN2 BIT5
#define IN3 BIT6
#define IN4 BIT7
#define step_number 512
#define motor_speed 1300



void UARTGetArray(void);
void motor_clockwise(void);
void UARTSendArray(char *TxArray, unsigned char ArrayLength);

char str[4];  // buffer to store received string
unsigned int i=0;

int x_new, y_new;



#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)

{           __bic_SR_register(LPM0_bits);
           UARTSendArray("TIMER_A ISR WORK", 16);
           UARTSendArray("\n\r", 2);

           motor_clockwise();
           P1OUT &=  ~IN1;
           P1OUT &=  ~IN2;
           P1OUT &=  ~IN3;
           P1OUT &=  ~IN4;
}



void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT

    P1DIR = IN1 + IN2 +IN3 +IN4;
    //P1DIR |= BIT0 + BIT6; // Set the LEDs on P1.0, P1.6 as outputs
    P1OUT = 0; // Set P1.0

    BCSCTL1 = CALBC1_1MHZ; // Set DCO to 1MHz //main ossilator set 1mhz
    DCOCTL = CALDCO_1MHZ; // Set DCO to 1MHz

    // Configure hardware UART
    P1SEL = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2; // Use SMCLK
    UCA0CTL1 &= ~UCSWRST; // Initialize USCI state machine
    UCA0BR0 = 104; // Set baud rate to 9600 with 1MHz clock to communicate via serial port
    UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1

    //timer_A settings
    TA0CTL = TASSEL_1 + MC_1 + ID_3; // tassel_1 = aclk, mc_1= count mode continious, id3 = divided by 8
    TA0CCR0 = 40000; // every 48 sec
    TA0CCTL0 = CCIE; // Enable interrupt for CCR0

    // Enable Timer A interrupt
    //IE1 |= TA0CCTL0;
    __bis_SR_register(LPM0_bits + GIE);
    //IE1 |= TA0CCTL0;

//    while(1){//main loop
//        ///////////////////////////////////////////
//        __delay_cycles(2000000);
//        UARTSendArray("enter coordinates", 17);
//        UARTSendArray("\n\r", 2);
//        while(1){
//            while(!(IFG2 & UCA0RXIFG));             //this area for getting input from serial terminal
//            str[i] = UCA0RXBUF;
//            i++;
//            if(i==sizeof(str)){
//            i = 0;
//            break;
//            }
//        }
//        UARTSendArray(str, sizeof(str));
//        UARTSendArray("\n\r", 2);
//      /////////////////////////////////////////////////////
//        // main loop code here
//
//        x_new = str[1] - '0'; //conver string '1' to int 1
//        y_new = str[3] - '0';
//
//        if(x_current != x_new){
//            IPC0 |= BIT1;
//            IE2 |= BIT1;
//            // Set custom interrupt 1 priority to 4
//
//        }
//
//        if(y_current != y_new){
//            IE2 |= BIT2;
//            // Set custom interrupt 1 priority to 4
//          //  IPC0 |= BIT2;
//        }
//        __bis_SR_register(GIE);
//    }
}


void UARTSendArray(char *TxArray, unsigned char ArrayLength){
    while(ArrayLength--){ // Loop until StringLength == 0 and post decrement
        while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
        UCA0TXBUF = *TxArray; //Write the character at the location specified by the pointer
        TxArray++; //Increment the TxString pointer to point to the next character
    }
}


void motor_clockwise(void){

    int c;
    for(c = 0 ;c <=step_number;c++){
        //IN1 IN2 IN3 IN4
           //1    0   0    1
           P1OUT |= IN1;
           P1OUT |= IN4;
           P1OUT &=  ~IN2;
           P1OUT &=  ~IN3;
           _delay_cycles(motor_speed);

           //IN1 IN2 IN3 IN4
           //1    0   0    0
           P1OUT |= IN1;
           P1OUT &=  ~IN2;
           P1OUT &=  ~IN3;
           P1OUT &=  ~IN4;
           _delay_cycles(motor_speed);

           //IN1 IN2 IN3 IN4
           //1    1   0    0
           P1OUT |= IN1;
           P1OUT |= IN2;
           P1OUT &=  ~IN3;
           P1OUT &=  ~IN4;
           _delay_cycles(motor_speed);

           //IN1 IN2 IN3 IN4
           //0    1   0    0
           P1OUT |= IN2;
           P1OUT &=  ~IN1;
           P1OUT &=  ~IN3;
           P1OUT &=  ~IN4;
           _delay_cycles(motor_speed);

           //IN1 IN2 IN3 IN4
           //0    1   1    0
           P1OUT |= IN2;
           P1OUT |= IN3;
           P1OUT &=  ~IN1;
           P1OUT &=  ~IN4;
           _delay_cycles(motor_speed);

           //IN1 IN2 IN3 IN4
           //0    0   1    0
           P1OUT |= IN3;
           P1OUT &=  ~IN1;
           P1OUT &=  ~IN2;
           P1OUT &=  ~IN4;
           _delay_cycles(motor_speed);

           //IN1 IN2 IN3 IN4
           //0    0   1    1
           P1OUT |= IN3;
           P1OUT |= IN4;
           P1OUT &=  ~IN1;
           P1OUT &=  ~IN2;
           _delay_cycles(motor_speed);


           //IN1 IN2 IN3 IN4
           //0    0   0    1
           P1OUT |= IN4;
           P1OUT &=  ~IN1;
           P1OUT &=  ~IN2;
           P1OUT &=  ~IN3;
           _delay_cycles(motor_speed);

    }
}
