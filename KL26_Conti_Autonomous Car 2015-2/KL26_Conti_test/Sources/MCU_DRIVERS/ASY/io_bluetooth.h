

#ifndef BLUETOOTH_H

extern void Io_Bluetooth_State(void);
extern  int state;
extern  int wait;
extern int dutycycle;
extern char sensor;

#define RIGHT 6
#define LEFT 4
#define FW 8
#define BW 2
#define WAIT 5
#define SLEEP_CAR 0
#define PARK 9
#define RECEIVE -1
#define OBSTACLE 10
#define PLUS 11
#define MINUS 12
#endif
