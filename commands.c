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
#include "motor.h"

unsigned short tick = 0;  // set tick to start at motor position one 

int motor_cmd(char *argv[], unsigned short argc){
unsigned int freq;
char direction;
  
  if ((argc != 3) && (argv[1] == "F") || (argv[1] == "B")){ // input checking 
   printf("To use the motor command input direction then desired RPM.\n\rmotor [F/B] [RPM]\n\r");
  }
  else{
    direction = *argv[1];             // parse motor direction
    freq = 60*strtol(argv[2],0,0);    // parse motor RPM --> freq
  
    TA0CCR1 = 32000/freq;           // set capture interrupt for motor speed 
    TA0CTL |= MC_2;                 // start timer A0 to trigger motor position 
  
  while(async_CheckKey()==EOF){ // stay in command until serial presses a key
    switch (tick)
    {
      case one:
         PosOne();
      break;
      case two:
         PosTwo();
      break;
      case three:
         PosThree();
      break;
      case four:
         PosThree();
      break;
      default:
      break;
      }
      TA0CTL |= ~MC_2;           // stop timer A0 to stop motor  
      PosOff();                 // turn motor lines off 

   }
  return 0; // is good 
  }
}

//table of commands with help
const CMD_SPEC cmd_tbl[]={{"help"," [command]",helpCmd},
                   {"motor","[F/B] [RPM] ...\r\n\t""Example command to show how arguments are passed",motor_cmd},

                   ARC_COMMANDS,CTL_COMMANDS,ERROR_COMMANDS,
                   //end of list
                   {NULL,NULL,NULL}};

