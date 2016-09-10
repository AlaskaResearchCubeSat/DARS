#ifndef __ACDS_H
#define __ACDS_H

  //events in COMM_evt
  //enum{ACDS_EVT_STATUS_REQ=1<<3};
  enum{ACDS_EV_SEND_STAT=1<<0,ACDS_EVT_DAT_REC=1<<1,ACDS_EVT_SEND_DAT=1<<2};

  #define ACDS_EVT_ALL (ACDS_EV_SEND_STAT|ACDS_EVT_DAT_REC|ACDS_EVT_SEND_DAT)
  //#define ACDS_EVT_ALL (ACDS_EVT_STATUS_REQ)

  //structure for status data from COMM
  //TODO: figure out COMM status
  typedef struct{
    short mag[3];
    unsigned char mode;
    unsigned char tqstat[3];
    unsigned short flips[3];
    short attitude[4];
    short rates[3];
  }ACDS_STAT;
  
  typedef struct{
        CTL_MUTEX_t lock;
        int action;
        union {
            unsigned long sector;
        } parm;
    }SPI_DATA_ACTION;
  //extern ACDS_STAT status;

  //flags for STAT_PACKET

  //parse events from the bus for the subsystem
  void sub_events(void *p);

  extern CMD_PARSE_DAT ACDS_parse;
  //events for COMM task
  extern CTL_EVENT_SET_t ACDS_evt;

  //parse COMM specific events
  void ACDS_events(void *p);

  void PrintBuffer(char *dat, unsigned int len);

    //magnetometer point
    typedef union{
      struct {
        short a,b;
      }c;
      short elm[2];
    } MAG_POINT;

    typedef struct{
        unsigned short flags;
        MAG_POINT meas[6];
    }MAG_DAT; 

    //flags for magFLags
#define MAG_FLAGS_X0      (1<<(2*2+0))      //Y+ board a-axis
#define MAG_FLAGS_X1      (1<<(2*3+0))      //Y- board a-axis
#define MAG_FLAGS_X2      (1<<(2*4+1))      //Z+ board b-axis
#define MAG_FLAGS_X3      (1<<(2*5+1))      //Z- board b-axis
#define MAG_FLAGS_X       (MAG_FLAGS_X0|MAG_FLAGS_X1|MAG_FLAGS_X2|MAG_FLAGS_X3)

#define MAG_FLAGS_Y0      (1<<(2*0+0))      //X+ board a-axis
#define MAG_FLAGS_Y1      (1<<(2*1+0))      //X- board a-axis
#define MAG_FLAGS_Y2      (1<<(2*4+0))      //Z+ board a-axis
#define MAG_FLAGS_Y3      (1<<(2*5+0))      //Z- board a-axis
#define MAG_FLAGS_Y       (MAG_FLAGS_Y0|MAG_FLAGS_Y1|MAG_FLAGS_Y2|MAG_FLAGS_Y3)

#define MAG_FLAGS_Z0      (1<<(2*0+1))      //X+ board b-axis    
#define MAG_FLAGS_Z1      (1<<(2*1+1))      //X- board b-axis
#define MAG_FLAGS_Z2      (1<<(2*2+1))      //Y+ board b-axis
#define MAG_FLAGS_Z3      (1<<(2*3+1))      //Y- board b-axis
#define MAG_FLAGS_Z       (MAG_FLAGS_Z0|MAG_FLAGS_Z1|MAG_FLAGS_Z2|MAG_FLAGS_Z3)
#endif
