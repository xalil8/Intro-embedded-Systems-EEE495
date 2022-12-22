//Halil ibrahim Özcan 2017514050
#include "msp430g2553.h"
void UARTGetArray(void);

void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength);

char str[2];  // buffer to store received string
int i=0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT

    P1DIR |= BIT0 + BIT6; // Set the LEDs on P1.0, P1.6 as outputs
    P1OUT = 0; // Set P1.0

    BCSCTL1 = CALBC1_1MHZ; // Set DCO to 1MHz
    DCOCTL = CALDCO_1MHZ; // Set DCO to 1MHz

    /* Configure hardware UART */
    P1SEL = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2; // Use SMCLK
    UCA0CTL1 &= ~UCSWRST; // Initialize USCI state machine
    UCA0BR0 = 104; // Set baud rate to 9600 with 1MHz clock (Data Sheet 15.3.13)
    UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1


    while(1){
        UARTGetArray();

    }
}


void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength){
    while(ArrayLength--){ // Loop until StringLength == 0 and post decrement
        while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
        UCA0TXBUF = *TxArray; //Write the character at the location specified by the pointer
        TxArray++; //Increment the TxString pointer to point to the next character
    }
}


void UARTGetArray(void){
    char input = UCA0RXBUF;

    while(1){
        while(!(IFG2 & UCA0RXIFG));
        str[i] = UCA0RXBUF;
        i++;
        if(i==sizeof(str)){
             i = 0;
             break;
        }
    }

    UARTSendArray(str, sizeof(str));
    UARTSendArray("\n\r", 2);

//    if (str[0] == '3' && str[1] == 'g') {
//        P1OUT |= BIT0;
//        P1OUT &= ~BIT6;
//
//        UARTSendArray("ANAN", 4);
//        UARTSendArray("\n\r", 2);
//        UARTSendArray(&str, 2);
//        UARTSendArray("\n\r", 2);
//        }
//    else{
//        P1OUT |= BIT6;
//        P1OUT &= ~BIT0;
//
//        }
}
