#include <msp430.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctl.h>
#include <terminal.h>
#include <ARCbus.h>
#include <UCA1_uart.h>
#include <crc.h>
#include <commandLib.h>
#include "ACDS.h"
#include <Error.h>
#include "ACDS_errors.h"

int ACDSCmd(char **argv, unsigned short argc)
{
  printf("You are in ACDS\r\n\t");
  return 0;
}

//table of commands with help
const CMD_SPEC cmd_tbl[]={
                    {"ACDS", "\r\n\t", ACDSCmd},
                    {"help"," [command]",helpCmd},

                   {NULL,NULL,NULL}};

