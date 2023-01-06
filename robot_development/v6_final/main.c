/*
 *  Created on: Dec 26, 2022
 *      Author: Halil Ibrahim Özcan
 *      School No: 2017514050
 *      E-mail : halil.ozcan1999@gmail.com
 */
#include "msp430g2553.h"
#include <my_motor_lib.h>


int x_current = 0;
int y_current = 0;
unsigned int i = 0;


void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT
    BCSCTL1 = CALBC1_1MHZ; // Set DCO to 1MHz //main oscillator set 1mhz
    DCOCTL = CALDCO_1MHZ; // Set DCO to 1MHz

    P1DIR = MOTOR1_IN1 + MOTOR1_IN2 +MOTOR1_IN3 +MOTOR1_IN4;  //configure MOTOR1 inputs
    P2DIR = MOTOR2_IN1 + MOTOR2_IN2 +MOTOR2_IN3 +MOTOR2_IN4 + BUZZER;  //configure MOTOR2 inputs
    // clear pins
    P1OUT = 0;
    P2OUT = 0;

    // Configure hardware UART
    P1SEL = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2; // Use SMCLK
    UCA0CTL1 &= ~UCSWRST; // Initialize USCI state machine
    UCA0BR0 = 104; // Set baud rate to 9600 with 1MHz clock to communicate via serial port
    UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1

    //I used to have timer interrupt but canceled ,code below can be used
    // TA0CTL = TASSEL_1 +ID_3 +MC_1; // tassel_1 = aclk=32760hz , mc_1= count mode continuous, id3 = divided by 8
    // TA0CCR0 = 4000; // every 48 second  , 8sec for 10k
    // TA0CCTL0 = CCIE; // Enable interrupt for CCR0
    // TA0CCR1 = 4000;
    // TA0CCTL1 = CCIE;

    //set Software interrupt for motor x at pin P1.0
    P1DIR &= ~BIT0;  // Set P1.1 as an input
    // P1REN |= BIT0;   // Enable pull-up resistor on P1.1
    //P1OUT |= BIT0;   // Set pull-up resistor to pull-up
    P1IE  |= BIT0;    // Enable interrupt on P1.1
    P1IES |= BIT0;   // Set interrupt to trigger on rising edge (logic 1)
    P1IFG &= ~BIT0;  // Clear interrupt flag

    //set Software interrupt for y motor at pin P2.0
    P2DIR &= ~BIT0;  // Set P2.0 as an input
    //P2REN |= BIT0;   // Enable pull-up resistor on P2.0
    //P2OUT |= BIT0;   // Set pull-up resistor to pull-up
    P2IE  |= BIT0;    // Enable interrupt on P2.0
    P2IES |= BIT0;   // Set interrupt to trigger on rising edge (logic 1)
    P2IFG &= ~BIT0;  // Clear interrupt flag

    //set Button interrupt for both motor reset position at pin P1.3
    P1DIR &= ~BIT3;  // Set pin 1.3 as an input
    P1REN |= BIT3;   // Enable the internal resistor for pin 1.3
    P1OUT |= BIT3;   // Set the resistor to pull-up mode
    P1IES |= BIT3;   // Set the interrupt to trigger on falling edge (button press)
    P1IE |= BIT3;    // Enable the interrupt for pin 1.3


    __bis_SR_register(GIE);  // Enable global interrupts

    while(1)
    {
        __delay_cycles(20000);

        write_serial("############ ENTER COORDINATES ###############", 46);
        write_serial("\n\r", 2);
        write_serial("Enter comma separate and use '+' or '-' prefix", 46);
        write_serial("\n\r", 2);
        write_serial("Example input '-2,+3' , '+3,+3' ", 32);
        write_serial("\n\r", 2);

        //this loop for getting string input from serial terminal
        while(1){
            while(!(IFG2 & UCA0RXIFG));
            str[i] = UCA0RXBUF;
            i++;
            if(i==sizeof(str)){
            i = 0;
            break;
            }
        }

        write_serial("YOUR INPUT: ", 12);
        write_serial(str, 5);
        write_serial("\n\r", 2);


        parse_string(str); //convert str to int then assign in x and y

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






