/************************* MSP430F6779a module cheat sheet *********************************************
total eUSCI modules are       UCA0,1,2,3 and UCB0,1

Dont forget ARClib uses       UCA0 and UCB0 
SD-lib uses                   UCA1
UART (termlib) uses           UCA2
i2Clib uses                   UCB1 <-- not initialized in main so could be used for something else 

free modules are              UCA3
********************************************************************************************************/

#include <msp430.h>
#include <ctl.h>
#include <ARCbus.h>
#include <Error.h>
#include <terminal.h>         
#include <string.h>           // for memeset prototype
#include <UCA2_uart.h>        // UART setup 
#include "pins.h"             // linked in bare_bones solution 
#include "subsystem.h"        // linked in bare_bones solution 
#include "timer.h"            // motor driver trigger 
#include "motor.h"            // pin def and driver code fro the motor 


CTL_TASK_t terminal_task,sub_task,sys_task; // name your task (first thing to do when setting up a new task (1))

//********************************************* allocate mem for tasks (2)
//stack for terminal
unsigned terminal_stack[2000];
//stack for subsystem events
unsigned sys_stack[1000];
//stack for bus events
unsigned sub_stack[1000];

//******************************************** redefine putchar and getchar 
//make printf and friends use async
int __putchar(int c){
  return UCA2_TxChar(c);
}

//make printf and friends use async
int __getchar(void){
  return UCA2_Getc();
}

//******************************************* DARS motor code main loop
void main(void){
  //DO this first
  ARC_setup();

  //turn on LED's this will flash the LED's during startup
  P7DIR=0xFF;
  //init complete turn on LED0 and all others off
  P7OUT=0xff;

  //TESTING: set log level to report everything by default
  set_error_level(0);

  //initialize UART
  UCA2_init_UART(UART_PORT,UART_TX_PIN_NUM,UART_RX_PIN_NUM);

  timer_A1_setup(); // setup motor driver interrupts  
  
  motor_setup();    // configure motor I/O pins 
  //PosOff();
  //setup bus interface
  initARCbus(0x14);   // Default addr for "SYS" subsystem, should be changed for specific subsystems.

  // initialize stacks (3) 
  memset(terminal_stack,0xcd,sizeof(terminal_stack));                                           //write known values into the stack 
  terminal_stack[0]=terminal_stack[sizeof(terminal_stack)/sizeof(terminal_stack[0])-1]=0xfeed;  //put marker values at the words before/after the stack
  memset(sys_stack,0xcd,sizeof(sys_stack));                                                     //write known values into the stack 
  sys_stack[0]=sys_stack[sizeof(sys_stack)/sizeof(sys_stack[0])-1]=0xfeed;                      //put marker values at the words before/after the stack
  memset(sub_stack,0xcd,sizeof(sub_stack));                                                     //write known values into the stack 
  sub_stack[0]=sub_stack[sizeof(sub_stack)/sizeof(sub_stack[0])-1]=0xfeed;                      //put marker values at the words before/after the stack


  // creating the tasks
  ctl_task_run(&terminal_task,BUS_PRI_LOW,terminal,"DARS motor code","terminal",sizeof(terminal_stack)/sizeof(terminal_stack[0])-2,terminal_stack-1,0);
  ctl_task_run(&sys_task,BUS_PRI_NORMAL,sys_events,NULL,"SYS_events",sizeof(sys_stack)/sizeof(sys_stack[0])-2,sys_stack-1,0);
  ctl_task_run(&sub_task,BUS_PRI_HIGH,sub_events,NULL,"SUB_events",sizeof(sub_stack)/sizeof(sub_stack[0])-2,sub_stack-1,0);

  mainLoop(); //<-- this is an ARCbus function

}

//decode errors
char *err_decode(char buf[150], unsigned short source,int err, unsigned short argument){
  sprintf(buf,"source = %i, error = %i, argument = %i",source,err,argument);
  return buf;
}

