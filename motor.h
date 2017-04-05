#ifndef  __MOTOR_H
#define __MOTOR_H

#define ticks;

enum motorPos {one=0 , two , three , four};

void motor_setup(void);
void PosOne(void);
void PosTwo(void);
void PosThree(void);
void PosFour(void);
void PosOff(void);


#endif
