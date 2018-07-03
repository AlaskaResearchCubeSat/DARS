#include <msp430.h>
#include <ctl.h>
#include <ARCbus.h>
#include <Error.h>
#include <terminal.h>
#include <UCA1_uart.h>
#include "pins.h"
#include "subsystem.h"

void motor_setup(void){
P5DIR|= MOTOR_INPUT1 | MOTOR_INPUT2;  // define motor I/O as outputs 
//P5DIR|= MOTOR_INPUT1 | MOTOR_INPUT2 | MOTOR_INPUT3 | MOTOR_INPUT4;  // define motor I/O as outputs 
}
//BLK___   ____     Pos1      Pos2     Pos3    Pos4 
//      3 | \/ |    NW        NE        SE      SW
//GRN___3 | /\ |   GRN->BLK  GRN->BLK BLK->GRN BLK->GRN
//        |____|   BLU->RED  RED-BLU  RED-BLU  BLU->RED     
//       
//        mmmm
//       |   |
//      RED  BLU
//
//MOTOR_INPUTS 1 AND 3 ARE CONTROLLING PMOS 
//MOTOR_INPUTS 2 AND 4 ARE CONTROLLING NMOS 
//
//


//Justin bread board (w/ inverter chip) 
void PosOne(void){
  P5OUT |= MOTOR_INPUT1;  // HIGH
  P5OUT &= ~MOTOR_INPUT2; // LOW
}


void PosTwo(void){
  P5OUT |= MOTOR_INPUT1; // HIGH
  P5OUT |= MOTOR_INPUT2;  // HIGH

}

void PosThree(void){
  P5OUT &= ~MOTOR_INPUT1; // LOW
  P5OUT |= MOTOR_INPUT2;  // HIGH

}

void PosFour(void){
  P5OUT &= ~MOTOR_INPUT1; // LOW
  P5OUT &= ~MOTOR_INPUT2; // LOW

}

void PosOff(void){
  P5OUT &= ~MOTOR_INPUT1; // LOW
  P5OUT &= ~MOTOR_INPUT2; // LOW

  printf("Motor OFF\r\n");
}


/* This configuration is for NMSO PMOS breakout board
void PosOne(void){
  P5OUT |= MOTOR_INPUT1;  // OFF
  P5OUT |= MOTOR_INPUT2;  // ON
  P5OUT |= MOTOR_INPUT3;  // OFF
  P5OUT |= MOTOR_INPUT4;  // ON 
}


void PosTwo(void){
  P5OUT |= MOTOR_INPUT1;  // OFF
  P5OUT |= MOTOR_INPUT2;  // ON
  P5OUT &= ~MOTOR_INPUT3; // OFF
  P5OUT &= ~MOTOR_INPUT4; // ON
}

void PosThree(void){
  P5OUT &= ~MOTOR_INPUT1; // ON
  P5OUT &= ~MOTOR_INPUT2; // OFF
  P5OUT &= ~MOTOR_INPUT3; // ON
  P5OUT &= ~MOTOR_INPUT4; // OFF
}

void PosFour(void){
  P5OUT &= ~MOTOR_INPUT1; // ON
  P5OUT &= ~MOTOR_INPUT2; // OFF
  P5OUT |= MOTOR_INPUT3;  // OFF
  P5OUT |= MOTOR_INPUT4;  // ON
}

void PosOff(void){
  P5OUT |= MOTOR_INPUT1;  // OFF
  P5OUT &= ~MOTOR_INPUT2; // OFF
  P5OUT |= MOTOR_INPUT3;  // OFF
  P5OUT &= ~MOTOR_INPUT4; // OFF
  printf("Motor OFF\r\n");
}
*/

//orignal code for Hbridge commands 
/*
void PosOne(void){
  P5OUT |= MOTOR_INPUT1;  // HIGH
  P5OUT &= ~MOTOR_INPUT2; // LOW
  P5OUT &= ~MOTOR_INPUT3; // LOW
  P5OUT |= MOTOR_INPUT4;  // HIGH
  printf("one\r\n"); 
}


void PosTwo(void){
  P5OUT &= ~MOTOR_INPUT1; // LOW
  P5OUT |= MOTOR_INPUT2;  // HIGH
  P5OUT &= ~MOTOR_INPUT3; // LOW
  P5OUT |= MOTOR_INPUT4;  // HIGH
  printf("two\r\n");
}

void PosThree(void){
  P5OUT &= ~MOTOR_INPUT1; // LOW
  P5OUT |= MOTOR_INPUT2;  // HIGH
  P5OUT |= MOTOR_INPUT3;  // HIGH
  P5OUT &= ~MOTOR_INPUT4; // LOW
  printf("three\r\n");
}

void PosFour(void){
  P5OUT |= MOTOR_INPUT1;  // HIGH
  P5OUT &= ~MOTOR_INPUT2; // LOW
  P5OUT |= MOTOR_INPUT3;  // HIGH
  P5OUT &= ~MOTOR_INPUT4; // LOW
  printf("four\r\n");
}

void PosOff(void){
  P5OUT &= ~MOTOR_INPUT1; // LOW
  P5OUT &= ~MOTOR_INPUT2; // LOW
  P5OUT &= ~MOTOR_INPUT3; // LOW
  P5OUT &= ~MOTOR_INPUT4; // LOW
  printf("Motor OFF\r\n");
}

*/