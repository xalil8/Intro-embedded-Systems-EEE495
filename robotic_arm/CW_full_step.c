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
