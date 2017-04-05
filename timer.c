#include <msp430.h>
#include "motor.h"
extern tick, count, direction;  // define for global 


//NOTE check this 
void timer_A1_setup(void){
 //setup timer A 
  TA3CTL |= TASSEL__ACLK | ID_0 | TACLR; // use ACLK assuming 32 KHz
  TA3CCTL0=CCIE;
}

void Timer_A1_ISR(void)__interrupt[TIMER3_A0_VECTOR]{
  //switch(TA3IV){
   // case  TA3IV_TA3CCR1:  // change motor pole state 
    P1OUT ^= BIT0;      // TEST INTERRUPT FREQ
        
        if(direction == 'F'){
          switch (tick){
            case one:
               PosOne();
               tick++;           // increment tick <-- global for motor position
               P7OUT ^= 0xFF;    // just cuz i like lights
               //TA3CCR1 = TA3CCR1 + count;           // set capture for next tick 
               P1OUT ^= BIT0;
            break;
            case two:
               PosTwo();
               tick++;           // increment tick <-- global for motor position
               P7OUT ^= 0xFF;    // just cuz i like lights
               //TA3CCR1 = TA3CCR1 + count;           // set capture for next tick 
               P1OUT ^= BIT0;
            break;
            case three:
               PosThree();
               tick++;           // increment tick <-- global for motor position
               P7OUT ^= 0xFF;    // just cuz i like lights
              // TA3CCR1 = TA3CCR1 + count;           // set capture for next tick 
               P1OUT ^= BIT0;
            break;
            case four:
               PosFour();
               tick = 0;           // increment tick <-- global for motor position
               P7OUT ^= 0xFF;    // just cuz i like lights
               //TA3CCR1 = TA3CCR1 + count;           // set capture for next tick 
               P1OUT ^= BIT0;
            break;
            default:
            break;
           }
         }
         else{
           switch (tick){
            case one:
               PosFour();
               tick++;           // increment tick <-- global for motor position
               P7OUT ^= 0xFF;    // just cuz i like lights
               //TA3CCR1 = TA3CCR1 + count;           // set capture for next tick 
               P1OUT ^= BIT0;
            break;
            case two:
               PosThree();
               tick++;           // increment tick <-- global for motor position
               P7OUT ^= 0xFF;    // just cuz i like lights
               //TA3CCR1 = TA3CCR1 + count;           // set capture for next tick 
               P1OUT ^= BIT0;
            break;
            case three:
               PosTwo();
               tick++;           // increment tick <-- global for motor position
               P7OUT ^= 0xFF;    // just cuz i like lights
              // TA3CCR1 = TA3CCR1 + count;           // set capture for next tick 
               P1OUT ^= BIT0;
            break;
            case four:
               PosOne();
               tick = 0;           // increment tick <-- global for motor position
               P7OUT ^= 0xFF;    // just cuz i like lights
               //TA3CCR1 = TA3CCR1 + count;           // set capture for next tick 
               P1OUT ^= BIT0;
            break;
            default:
            break;
           }
         }

 }
