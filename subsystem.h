//This file will cover all stack up events
#ifndef __SUBSYSTEM_H
#define __SUBSYSTEM_H

enum{SYS_EV_1=1,SYS_EV_2,SYS_EV_3,SYS_EV_4};  // These are events in SYS_evt, add more as necessary 
#define SYS_EVT_ALL (SYS_EV_1|SYS_EV_2|SYS_EV_3|SYS_EV_4)

void sub_events(void *p);

void sys_events(void *p);
extern CTL_EVENT_SET_t SYS_evt;// This creates the event struct,change SYS to actual subsystem

#endif
