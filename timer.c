#include <msp430.h>


//NOTE check this 
void timer_A0_setup(void){
 //setup timer A 
  TA0CTL |= TASSEL_1 | ID_0 | TACLR; // use ACLK assuming 32 KHz
  TA0CCTL1=CCIE;
}

void Timer_A0_ISR(void)__interrupt[TIMER0_A1_VECTOR]{
  switch(TA0IV){
    case  TA0IV_TA0CCR1:  // change motor pole state 
        P7OUT ^= BIT7;    // just cuz i like lights
        tick++;           // increment tick <-- global for motor position
    break;
    default:
    break;
    }
 }
