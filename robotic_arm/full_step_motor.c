#include <msp430.h>
#define motor_speed 1000



#define IN1 BIT1
#define IN2 BIT2
#define IN3 BIT4
#define IN4 BIT5

#define GREEN BIT6
#define RED BIT0


void motor_clockwise(void);
void counter_motor_clockwise(void);
void cw_8_step(void);

void main(void) {

    WDTCTL = WDTPW | WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    CCTL0 = CCIE;
    BCSCTL2 |= SELM_1;



    TACTL = TASSEL_2 + MC_1 + ID_3;       //SMCLK/8, UPMODE


    CCR0 = 125000; // to set clockspeed 10kHz

    P1DIR = IN1 + IN2 +IN3 +IN4 + GREEN + RED;   //0X41

    P1OUT = 0;

    P1OUT |= BIT3;   // |=  is used for set         set pull up resistor for button P1.3
    P1REN |= BIT3 ;   // &= is used for reset    enable pull up resisstor



    for(;;){  //for infinity loop
        if((P1IN & 0x08) == 0){
            cw_8_step();
        }
        else{
            P1OUT &=  ~IN1;
            P1OUT &=  ~IN2;
            P1OUT &=  ~IN3;
            P1OUT &=  ~IN4;
        }

    }
}
void motor_clockwise(void){

    P1OUT |= GREEN; //WHEN MOTOR TURN  CLOCKWISE GREEN LIGHT ON
    P1OUT &= ~RED;

    _delay_cycles(motor_speed);
    P1OUT |= IN1;
    P1OUT |= IN2;
    P1OUT &=  ~IN3;
    P1OUT &=  ~IN4;

    _delay_cycles(motor_speed);

    P1OUT |= IN2;
    P1OUT |= IN3;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN4;

    _delay_cycles(motor_speed);

    P1OUT |= IN3;
    P1OUT |= IN4;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN2;


    _delay_cycles(motor_speed);

    P1OUT |= IN1;
    P1OUT |= IN4;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN3;


 }


void counter_motor_clockwise(void){
    P1OUT |= RED;       //WHEN MOTOR TURN COUNTER CLOCKWISE RED LIGHT ON
    P1OUT &= ~GREEN;


    _delay_cycles(motor_speed);
    P1OUT |= IN1;
    P1OUT |= IN4;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN3;

    _delay_cycles(motor_speed);
    P1OUT |= IN3;
    P1OUT |= IN4;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN2;


    _delay_cycles(motor_speed);

    P1OUT |= IN2;
    P1OUT |= IN3;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN4;

    _delay_cycles(motor_speed);
    P1OUT |= IN1;
    P1OUT |= IN2;
    P1OUT &=  ~IN3;
    P1OUT &=  ~IN4;
 }

void cw_8_step(void){
    //IN1 IN2 IN3 IN4
    //1    0   0    0
    _delay_cycles(motor_speed);
    P1OUT |= IN1;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN3;
    P1OUT &=  ~IN4;

    //IN1 IN2 IN3 IN4
    //1    1   0    0
    _delay_cycles(motor_speed);
    P1OUT |= IN1;
    P1OUT |= IN2;
    P1OUT &=  ~IN3;
    P1OUT &=  ~IN4;


    //IN1 IN2 IN3 IN4
    //0    1   0    0
    _delay_cycles(motor_speed);
    P1OUT |= IN2;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN3;
    P1OUT &=  ~IN4;

    //IN1 IN2 IN3 IN4
    //0    1   1    0
    _delay_cycles(motor_speed);
    P1OUT |= IN2;
    P1OUT |= IN3;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN4;

    //IN1 IN2 IN3 IN4
    //0    0   1    0
    _delay_cycles(motor_speed);
    P1OUT |= IN3;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN4;

    //IN1 IN2 IN3 IN4
    //0    0   1    1
    _delay_cycles(motor_speed);
    P1OUT |= IN3;
    P1OUT |= IN4;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN2;

    //IN1 IN2 IN3 IN4
    //0    0   0    1
    _delay_cycles(motor_speed);
    P1OUT |= IN4;
    P1OUT &=  ~IN1;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN3;

    //IN1 IN2 IN3 IN4
    //1    0   0    1
    _delay_cycles(motor_speed);
    P1OUT |= IN1;
    P1OUT |= IN4;
    P1OUT &=  ~IN2;
    P1OUT &=  ~IN3;
}
