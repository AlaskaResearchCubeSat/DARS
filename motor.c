#include <msp430.h>
#include <ctl.h>
#include <ARCbus.h>
#include <Error.h>
#include <terminal.h>
#include <UCA1_uart.h>
#include "pins.h"
#include "subsystem.h"

void motor_setup(void){
P5DIR|= MOTOR_INPUT1 | MOTOR_INPUT2 | MOTOR_INPUT3 | MOTOR_INPUT4;  // define motor I/O as outputs 
}

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
  printf("four\r\n");
}
