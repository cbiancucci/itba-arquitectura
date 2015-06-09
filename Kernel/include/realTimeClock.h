#ifndef REAL_TIME_CLOCK_HEADER
#define REAL_TIME_CLOCK_HEADER

#include <stdint.h>
#include <definitions.h>

#define PORT_POS		0x70
#define PORT_VALUE		0x71

#define REGISTER_STATUS		0xb

#define SECOND		0x0
#define MINUTE 		0x2
#define HOUR 		0x4
#define DAY			0x7
#define MONTH 		0x8
#define YEAR 		0x9

void getTime(time_t* t);
void setTime(time_t* t);

#endif