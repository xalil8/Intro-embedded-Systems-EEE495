/*halil ibrahim Ozcan */

#include "msp430g2553.h"

#define IN1 BIT4
#define IN2 BIT5
#define IN3 BIT6
#define IN4 BIT7
#define step_number 512
#define motor_speed 1300


void motor_counter_clockwise(void);
void motor_clockwise(void);


void UARTGetArray(void);
void UARTSendArray(char *TxArray, unsigned char ArrayLength);

char str[2];  // buffer to store received string
unsigned int i=0;

int x_current = 0;
int y_current = 0;
int x_new, y_new;


#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if (P1IFG & BIT0)  // Check if interrupt was triggered by P1.1
    {
        UARTSendArray("ISR1 WORKED ", 12);
        UARTSendArray("\n\r", 2);

        while (x_current != x_new) {
            if (x_current < x_new){
                x_current++;
                UARTSendArray("x_current += 1", 14);
                UARTSendArray("\n\r", 2);

                motor_clockwise();
                P1OUT &=  ~IN1;
                P1OUT &=  ~IN2;
                P1OUT &=  ~IN3;
                P1OUT &=  ~IN4;


            }
            else {
                x_current--;
                UARTSendArray("x_current -= 1", 14);
                UARTSendArray("\n\r", 2);

                motor_counter_clockwise();
                P1OUT &=  ~IN1;
                P1OUT &=  ~IN2;
                P1OUT &=  ~IN3;
                P1OUT &=  ~IN4;
            }
        }
        P1IFG &= ~BIT0;  // Clear interrupt flag
    }
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    if (P2IFG & BIT0)  // Check if interrupt was triggered by P1.1
    {

        UARTSendArray("ISR2 WORKED ", 12);
        UARTSendArray("\n\r", 2);


        while (y_current != y_new) {
            if (y_current < y_new){
                y_current++;
                UARTSendArray("y_current += 1", 14);
                UARTSendArray("\n\r", 2);

//                motor_clockwise();
//                P1OUT &=  ~IN1;
//                P1OUT &=  ~IN2;
//                P1OUT &=  ~IN3;
//                P1OUT &=  ~IN4;

            }
            else {
                y_current--;
                UARTSendArray("y_current -= 1", 14);
                UARTSendArray("\n\r", 2);

//                motor_counter_clockwise();
//                P1OUT &=  ~IN1;
//                P1OUT &=  ~IN2;
//                P1OUT &=  ~IN3;
//                P1OUT &=  ~IN4;
            }
        }
        P2IFG &= ~BIT0;  // Clear interrupt flag
    }
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

    // TA0CTL = TASSEL_1 +ID_3 +MC_1; // tassel_1 = aclk=32760hz , mc_1= count mode continious, id3 = divided by 8

    // TA0CCR0 = 4000; // every 48 sec  , 8sec for 10k
    // TA0CCTL0 = CCIE; // Enable interrupt for CCR0
    // TA0CCR1 = 4000;
    // TA0CCTL1 = CCIE;

    //###############################
    //interrupt P1.0
    P1DIR &= ~BIT0;  // Set P1.1 as an input
    P1REN |= BIT0;   // Enable pull-up resistor on P1.1
    P1OUT |= BIT0;   // Set pull-up resistor to pull-up
    P1IE |= BIT0;    // Enable interrupt on P1.1
    P1IES |= BIT0;   // Set interrupt to trigger on rising edge (logic 1)
    P1IFG &= ~BIT0;  // Clear interrupt flag
    //interrupt P2.0
    P2DIR &= ~BIT0;  // Set P2.0 as an input
    P2REN |= BIT0;   // Enable pull-up resistor on P2.0
    P2OUT |= BIT0;   // Set pull-up resistor to pull-up
    P2IE |= BIT0;    // Enable interrupt on P2.0
    P2IES |= BIT0;   // Set interrupt to trigger on rising edge (logic 1)
    P2IFG &= ~BIT0;  // Clear interrupt flag
    //###############################

    __bis_SR_register(GIE);  // Enable global interrupts

    while(1)
    {
        __delay_cycles(20000);
        UARTSendArray("enter coordinates", 17);
        UARTSendArray("\n\r", 2);
        while(1){
            while(!(IFG2 & UCA0RXIFG));             //this area for getting input from serial terminal
            str[i] = UCA0RXBUF;
            i++;
            if(i==sizeof(str)){
            i = 0;
            break;
            }
        }
        UARTSendArray(str, 2);
        UARTSendArray("\n\r", 2);
        x_new = str[0] - '0'; //conver string '1' to int 1
        y_new = str[1] - '0';

        if (x_new != x_current) //if new x coordinate different than current , interrupt occur
        {
            P1IFG |= BIT0;
        }


        if (y_new != y_current)//if new y coordinate different than current , interrupt occur
        {
            P2IFG |= BIT0;
        }
        __no_operation();  // Wait for interrupt
    }
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

        //IN1 IN2 IN3 IN4
        //1    0   0    1
        P1OUT |= IN1;
        P1OUT |= IN4;
        P1OUT &=  ~IN2;
        P1OUT &=  ~IN3;
        _delay_cycles(motor_speed);

    }
}

void motor_counter_clockwise(void){

    int c;
    for(c = 0 ;c <=step_number;c++){
        //IN1 IN2 IN3 IN4
        //0    0   0    1
        P1OUT &=  ~IN1;
        P1OUT &=  ~IN2;
        P1OUT &=  ~IN3;
        P1OUT |= IN4;
        _delay_cycles(motor_speed);

        //IN1 IN2 IN3 IN4
        //0    0   1    1
        P1OUT &=  ~IN1;
        P1OUT &=  ~IN2;
        P1OUT |= IN3;
        P1OUT |= IN4;
        _delay_cycles(motor_speed);

        //IN1 IN2 IN3 IN4
        //0    0   1    0
        P1OUT &=  ~IN1;
        P1OUT &=  ~IN2;
        P1OUT |= IN3;
        P1OUT &=  ~IN4;
        _delay_cycles(motor_speed);

        //IN1 IN2 IN3 IN4
        //0    1   1    0
        P1OUT &=  ~IN1;
        P1OUT |= IN2;
        P1OUT |= IN3;
        P1OUT &=  ~IN4;
        _delay_cycles(motor_speed);

        //IN1 IN2 IN3 IN4
        //0    1   0    0
        P1OUT &=  ~IN1;
        P1OUT |= IN2;
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
        //1    0   0    0
        P1OUT |= IN1;
        P1OUT &=  ~IN2;
        P1OUT &=  ~IN3;
        P1OUT &=  ~IN4;
        _delay_cycles(motor_speed);

        //IN1 IN2 IN3 IN4
        //1    0   0    1
        P1OUT |= IN1;
        P1OUT &=  ~IN2;
        P1OUT &=  ~IN3;
        P1OUT |= IN4;
        _delay_cycles(motor_speed);

    }
}
