
//Halil ibrahim Özcan 2017514050
#include "msp430g2553.h"
void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength);
static volatile char data;

#define MAX_STRING_LENGTH 2
char rxString[MAX_STRING_LENGTH];  // buffer to store received string
int rxIndex = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT

    P1DIR |= BIT0 + BIT6; // Set the LEDs on P1.0, P1.6 as outputs
    P1OUT = BIT0; // Set P1.0

    BCSCTL1 = CALBC1_1MHZ; // Set DCO to 1MHz
    DCOCTL = CALDCO_1MHZ; // Set DCO to 1MHz

    /* Configure hardware UART */
    P1SEL = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2; // Use SMCLK
    UCA0CTL1 &= ~UCSWRST; // Initialize USCI state machine
    UCA0BR0 = 104; // Set baud rate to 9600 with 1MHz clock (Data Sheet 15.3.13)
    UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1
    IE2 |= UCA0RXIE; // Enable USCI_A0 RX interrupt
    __bis_SR_register(LPM0_bits + GIE); // Enter LPM0, interrupts enabled
}
// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    while (1) {
        // Check if a character has been received
        if (UCA0RXBUF != EOF) {
            // Store the character in the rxString buffer
            rxString[rxIndex] = UCA0RXBUF;
            rxIndex++;
            // If the end of the string has been reached, terminate it and reset the index
            if (rxIndex == MAX_STRING_LENGTH) {
                rxString[rxIndex] = '\0';
                rxIndex = 0;
            }
        }
    }

    UARTSendArray("Received command: ", 18);
    //UARTSendArray(&data, 1);
    UARTSendArray("\n\r", 2);


    if (rxString[0] == 'R' && rxString[1] == 'G') {
        P1OUT |= BIT0
        P1OUT |= BIT0
        }
    else{
        UARTSendArray("Unknown Command: ", 17);
        //UARTSendArray(&data, 1);
        UARTSendArray("\n\r", 2);
        }


    
    
}
void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength){
    // Send number of bytes Specified in ArrayLength in the array at using the hardware UART 0
    // Example usage: UARTSendArray("Hello", 5);
    // int data[2]={1023, 235};
    // UARTSendArray(data, 4); // Note because the UART transmits bytes it is necessary to send two
    //bytes for each integer hence the data length is twice the array length
    while(ArrayLength--){ // Loop until StringLength == 0 and post decrement
        while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
        UCA0TXBUF = *TxArray; //Write the character at the location specified by the pointer
        TxArray++; //Increment the TxString pointer to point to the next character
    }
}
