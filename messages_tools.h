#ifndef RECEIVE_MESSAGES_TOOLS_H_
#define RECEIVE_MESSAGES_TOOLS_H_

#include <time.h>

void time_ns_diff(struct timespec starttime, struct timespec endtime, long long *delta_ns);

double TIMER_DURATION;
time_t TIMER_START_TIME;

void start_receive_messages_timer();
void set_receive_messages_timer(int seconds);
int receive_messages_timeout();

#endif
