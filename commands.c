/**********************************************************************************************************************************************
The commands.c file is for commands that will be displayed through the serial terminal. 
In order to add a command you must create a function as seen below.
Then function must be added to the "const CMD_SPEC cmd_tbl[]={{"help"," [command]",helpCmd}" table at the end of the file.
**********************************************************************************************************************************************/
#include <msp430.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <terminal.h>
#include <commandLib.h>
#include <stdlib.h>
#include <ARCbus.h>
#include <SDlib.h>
#include <i2c.h>
#include <UCA2_uart.h>        // to use UCA2_CheckKey()
#include "motor.h"

unsigned short tick = 0;  // set tick to start at motor position one 
float count;  // so timer can see freq
char direction; // direction of the motor 


int motor_cmd(char *argv[], unsigned short argc){
unsigned int rpm;
  //check to make sure that there are two inputs, and make sure that the input direction is either forward or backwards

  if ((argc != 2) || ((*argv[1] != 'F') && (*argv[1] != 'B'))){ // input checking
  //if ((  && (argv[1] != "B "))){ // WHY WONT THIS WORK !?!?!!?!?!?!?!?!?!?!? 

   printf("To use the motor command input direction then desired RPM.\n\rmotor [F/B] [RPM]\n\r");
  }
  else{
    direction = *argv[1];             // parse motor direction
    rpm = strtol(argv[2],0,0);        // parse motor RPM
    count = 32767/(rpm*2);           // convert RPM into timer counts
    count=count*60;                  //  (had to do the count calculation in 2 steps we ran out of bits)
    TA3CCR0 = count;                // set capture interrupt for motor speed
    TA3CTL |= MC__UP;                 // start timer A0 to trigger motor position 
    WDT_STOP(); // hold watch dog 
  while(UCA2_CheckKey()==EOF){ // stay in command until serial presses a key 
  }
  WDT_KICK();   //re-start watch dog 
  TA3CTL &= ~MC__UP;                  // stop timer A0 to stop motor  
  P7OUT = 0x00;                        // turn off all LEDS
  PosOff();                           // turn motor lines off 

  return 0; // is good 
  }
}

//table of commands with help
const CMD_SPEC cmd_tbl[]={{"help"," [command]",helpCmd},
                   {"motor","[F/B] [RPM] ...\r\n\t""Example command to show how arguments are passed",motor_cmd},

                   ARC_COMMANDS,CTL_COMMANDS,ERROR_COMMANDS,
                   //end of list
                   {NULL,NULL,NULL}};

