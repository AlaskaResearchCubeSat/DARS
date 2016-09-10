#include <msp430.h>
#include <ctl.h>
#include <stdio.h>
#include <ARCbus.h>
#include <string.h>
#include <SDlib.h>
#include "ACDS.h"
#include "Error.h"

signed char settings_dat[10];
ACDS_STAT status;
CTL_EVENT_SET_t ACDS_evt;
MAG_DAT magData;
SPI_DATA_ACTION spi_action;

int ACDS_parseCmd(unsigned char src,unsigned char cmd,unsigned char *dat,unsigned short len,unsigned char flags);

CMD_PARSE_DAT ACDS_parse={ACDS_parseCmd,CMD_PARSE_ADDR0|CMD_PARSE_GC_ADDR,BUS_PRI_NORMAL,NULL};

unsigned long SD_read_addr;
    //Address range for ERROR data on the SD card
    enum{LOG_ADDR_START=ERR_ADDR_END+1,LOG_ADDR_END=LOG_ADDR_START+500,SD_FIRST_FREE_ADDR};

    #define LOG_IDX_MAX     (LOG_ADDR_START-LOG_ADDR_END-1)

    enum{ACDS_LOG_ERR_UNINIT=-15};
    
    //flags for log blocks
    enum{LOG_FLAGS_FIRST=1<<0};
    
    //initial state for flags
    #define LOG_INIT_FLAGS          LOG_FLAGS_FIRST


//handle ACDS specific commands
int ACDS_parseCmd(unsigned char src,unsigned char cmd,unsigned char *dat,unsigned short len,unsigned char flags){
  int i;
  unsigned long block_id;
  unsigned long sector;
  signed char *parms;
  switch(cmd)
  {
    case CMD_SPI_DATA_ACTION:
        if(len==0){
            return ERR_PK_LEN;
        }
        switch(dat[0])
        {
            case SPI_DAT_ACTION_SD_WRITE:
                if(len!=5)
                {
                    return ERR_PK_LEN;
                }
                sector=((unsigned long)dat[1]<<24)|((unsigned long)dat[2]<<16)|((unsigned long)dat[3]<<8)|((unsigned long)dat[4]);
                //get lock on action
                if(!ctl_mutex_lock(&spi_action.lock,CTL_TIMEOUT_DELAY,10))
                {
                    return ERR_SPI_BUSY;
                }
                spi_action.action=dat[0];
                spi_action.parm.sector=sector;
                ctl_mutex_unlock(&spi_action.lock);
            break;
            default:
                return ERR_UNKNOWN_CMD;
        }
    return RET_SUCCESS;
    case CMD_ACDS_READ_BLOCK:
      if(len!=3)
      {
        return ERR_PK_LEN;
      }
      block_id =((unsigned long)dat[0])<<16;
      block_id|=((unsigned long)dat[1])<<8;
      block_id|=((unsigned long)dat[2]);
      //check range
      if(block_id>LOG_IDX_MAX)
      {
        //index is out of range
        return ERR_PK_BAD_PARM;
      }
      //set SD address
      SD_read_addr=LOG_ADDR_START+block_id;
      //trigger event
      ctl_events_set_clear(&ACDS_evt,ACDS_EVT_SEND_DAT,0);
      return RET_SUCCESS;
    case CMD_ACDS_CONFIG:
      //check length
      if(len<1)
      {
        return ERR_PK_LEN;
      }
      //parameters start at 1
      parms=(signed char*)&dat[1];
      //see what to configure
      switch(dat[0])
      {
        default:
          return RET_SUCCESS;
      }
      return ERR_PK_BAD_PARM;
  }
  //Return Error
  return ERR_UNKNOWN_CMD;
}

void sub_events(void *p) __toplevel
{
  unsigned int e;
  int i, resp;

  for(;;)
  {
    e=ctl_events_wait(CTL_EVENT_WAIT_ANY_EVENTS_WITH_AUTO_CLEAR,&SUB_events,SUB_EV_ALL,CTL_TIMEOUT_NONE,0);
  }
}

//handle ACDS specific commands don't wait here.
int SUB_parseCmd(unsigned char src, unsigned char cmd, unsigned char *dat, unsigned short len)
{
  return ERR_UNKNOWN_CMD;
}

void ACDS_events(void *p) __toplevel
{
  unsigned int e;
  int i, resp; 
  unsigned char buf[BUS_I2C_HDR_LEN+sizeof(ACDS_STAT)+BUS_I2C_CRC_LEN],*ptr;
  ctl_events_init(&ACDS_evt,0);

  //endless loop
  for(;;)
  {
    //wait for events
    e=ctl_events_wait(CTL_EVENT_WAIT_ANY_EVENTS_WITH_AUTO_CLEAR,&ACDS_evt,ACDS_EVT_ALL,CTL_TIMEOUT_NONE,0);

//******************* SEND IMG STATUS TO CDH ***************************
    if(e&SUB_EV_SEND_STAT)
    {
      //send status
      puts("Sending status\r\n");
      //setup packet 
      ptr=BUS_cmd_init(buf,CMD_ACDS_STAT);
      //fill in telemetry data
      for(i=0;i<sizeof(ACDS_STAT);i++)
      {
        //ptr[i]=((unsigned char*)(&status))[i];
        ptr[i]=i;
      }
      //send command
      resp=BUS_cmd_tx(BUS_ADDR_CDH,buf,sizeof(ACDS_STAT),0);
      //ctl_events_set_clear(&ACDS_evt,ACDS_EVT_STATUS_REQ,0);
      if(resp!=RET_SUCCESS)
      {
        printf("Failed to send status %s\r\n",BUS_error_str(resp));
      }
    }
  }
}



