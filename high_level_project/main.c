#include <msp430.h>
#include <stdio.h>

int x, y;

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

  // Configure UART
  P1SEL = BIT1 + BIT2;   // P1.1 = RXD, P1.2=TXD
  P1SEL2 = BIT1 + BIT2;  // P1.1 = RXD, P1.2=TXD
  UCA0CTL1 |= UCSSEL_2;  // SMCLK
  UCA0BR0 = 104;         // 1MHz 9600
  UCA0BR1 = 0;           // 1MHz 9600
  UCA0MCTL = UCBRS0;     // Modulation UCBRSx = 1
  UCA0CTL1 &= ~UCSWRST;  // **Initialize USCI state machine**

  // Read input from serial terminal
  scanf("%d,%d", &x, &y);


  return 0;
}
