#include <string.h>
#include <ctl.h>
#include <msp430.h>
#include <ARCbus.h>
#include <terminal.h>
#include <UCA1_uart.h>
#include <stdio.h>
#include <Error.h>
#include "ACDS.h"
#include "pins.h"
#include "ACDS_errors.h"

//Define three task structures in array tasks (what are these tasks?)
CTL_TASK_t tasks[3];

//Define stacks for each tasks, STACKSize is the middle number
unsigned stack1[1+256+1];
unsigned stack2[1+512+1];
unsigned stack3[1+256+1];

//make printf and friends to send chars out UCA1 uart
int __putchar(int c)
{
  async_TxChar(c);
  UCA1_TxChar(c);
  return 0;
}

//set scanf and friends to read chars from UAC1 uart
int __getchar(void)
{
  return async_Getc();
}

int main(void)
{
  //Do this first
  ARC_setup();
  
  //register error handler
  err_register_handler(ACDS_MIN_ERR,ACDS_MAX_ERR,ACDS_err_decode,ERR_FLAGS_SUBSYSTEM);

  //setup CDH reset pin
  P6OUT &=~BIT0;
  P6DIR |= BIT0;
  P6SEL0&=~BIT0;
  P6SEL1&=~BIT0;
  //setup UCA1 uart
  UCA1_init_UART(UART_PORT,UART_TX_PIN_NUM,UART_RX_PIN_NUM);

  //setup buss interface - COMM
  initARCbus(BUS_ADDR_ACDS);
  
  BUS_register_cmd_callback(&ACDS_parse);

  //initialize stacks
  memset(stack1, 0xcd, sizeof(stack1));  // write known values into the stack
  stack1[0]=stack1[sizeof(stack1)/sizeof(stack1[0])-1]=0xfeed; // put marker values at the words before/after the stack
 
  memset(stack2, 0xcd, sizeof(stack2));  // write known values into the stack
  stack2[0]=stack2[sizeof(stack2)/sizeof(stack2[0])-1]=0xfeed; // put marker values at the words before/after the stack

  memset(stack3, 0xcd, sizeof(stack3));  // write known values into the stack
  stack3[0]=stack3[sizeof(stack3)/sizeof(stack3[0])-1]=0xfeed; // put marker values at the words before/after the stack

//create tasks
  //ctl_task_run(&tasks[0], BUS_PRI_LOW, ACDS_events, NULL, "ACDS_events", sizeof(stack1)/sizeof(stack1[0])-2,stack1+1,0);
  ctl_task_run(&tasks[1], BUS_PRI_NORMAL, terminal, "Test ACDS code", "terminal", sizeof(stack2)/sizeof(stack2[0])-2,stack2+1,0);
  //ctl_task_run(&tasks[2], BUS_PRI_HIGH, sub_events, NULL, "sub_events", sizeof(stack3)/sizeof(stack3[0])-2,stack3+1,0);

  //set LED's for shifting
  if(!P7OUT){
    P7OUT = BIT0;
  }
  P7DIR = 0xFF;
  P7SEL0 = 0;
   
 //Call mainLoop to initialize the ARCbus task and drop the idle task priority to zero allowing other tasks to run.  This is the idle loop.
  mainLoop();

}

