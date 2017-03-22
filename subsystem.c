//This file will cover all stack up events
//TODO motor code should be triggered through ARCbus events for flight code
#include <msp430.h>
#include <ctl.h>
#include <ARCbus.h>
#include <Error.h>
#include <SDlib.h>
#include "subsystem.h"

CTL_EVENT_SET_t SYS_evt; // This creates the event struct,change SYS to actual subsystem

//handle subsystem specific commands - this is for I2C commands on the BUS that are not SUB events, so system specific commands.
int SUB_parseCmd(unsigned char src,unsigned char cmd,unsigned char *dat,unsigned short len){
  switch(cmd){

    default:
      return ERR_UNKNOWN_CMD;
  }
}


//parse subsystem events
void sub_events(void *p) __toplevel{
  unsigned int e,len;
  int i;
  unsigned char buf[10],*ptr;
  extern unsigned char async_addr;

  for(;;){
    e=ctl_events_wait(CTL_EVENT_WAIT_ANY_EVENTS_WITH_AUTO_CLEAR,&SUB_events,SUB_EV_ALL|SUB_EV_ASYNC_OPEN|SUB_EV_ASYNC_CLOSE,CTL_TIMEOUT_NONE,0);
    if(e&SUB_EV_PWR_OFF){  //**************************************** Sent when the subsystem receives the power off command **********************************
      //print message
      puts("System Powering Down\r");
    }
    if(e&SUB_EV_PWR_ON){ //***************************************** Sent when the subsystem receives the power on command ************************************
      //print message
      puts("System Powering Up\r");
    }
    if(e&SUB_EV_SEND_STAT){ // ************************************* Sent when the subsystem receives the send status command  ********************************
      //send status
      puts("Sending status\r");
      //setup packet 
      //ptr=BUS_cmd_init(buf,CMD_SYS_STAT); // replace CMD_SYS_STAT with actual subsystem ie CMD_COMM_STAT
      //send command
      //BUS_cmd_tx(BUS_ADDR_CDH,buf,0,0); //sending status contained in "buf" CDH 

      // FOR TESTING SEND_I2C command!!

    }
    if(e&SUB_EV_SPI_DAT){ // ************************************** Sent when SPI data is received correctly **************************************************
      puts("SPI data rx\r");
    }
    if(e&SUB_EV_SPI_ERR_CRC){ // ********************************* Sent when SPI transaction was rejected because of busy buffer *****************************
      puts("SPI bad CRC\r");
    }
    if(e&SUB_EV_SPI_ERR_BUSY){
      puts("SPI Busy\r");
    }
    if(e&SUB_EV_ASYNC_OPEN){ // ********************************** An async connection was opened remotely **************************************************
      //close async connection, not supported
      puts("Async open called");
    }
    if(e&SUB_EV_ASYNC_CLOSE){ // ********************************** An async connection was closed remotely  *************************************************
     //close async connection, not supported
     puts("Async close called");
    }
    if(e&SUB_EV_INT_0){ // ************************************** Event on interrupt bus pin 0  *************************************************************  
    puts("EV 0 has been called.");
    }
  }
}

void sys_events(void *p) __toplevel{
  unsigned int e;
  ctl_events_init(&SYS_evt,0); //Initialize Event
  
  for(;;){
    // wait for events
    e=ctl_events_wait(CTL_EVENT_WAIT_ANY_EVENTS_WITH_AUTO_CLEAR,&SYS_evt,SYS_EVT_ALL,CTL_TIMEOUT_NONE,0);
//*************************************************** Events to be processed for system ****************************************************************
    if(e&SYS_EV_1){
    puts("SYS_EV_1 called");
    }
    if(e&SYS_EV_2){
    puts("SYS_EV_2 called");
    }
    if(e&SYS_EV_3){
    puts("SYS_EV_3 called");
    }
    if(e&SYS_EV_4){
    puts("SYS_EV_4 called");
    }
  }
}
